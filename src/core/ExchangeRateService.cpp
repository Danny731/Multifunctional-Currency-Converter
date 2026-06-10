#include "ExchangeRateService.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QUrlQuery>

static const char *kApiBaseUrl = "https://api.frankfurter.dev/v1/latest";

ExchangeRateService::ExchangeRateService(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
{
}

const CurrencyConverter &ExchangeRateService::converter() const
{
    return m_converter;
}

bool ExchangeRateService::hasRates() const
{
    return m_hasRates;
}

QString ExchangeRateService::lastUpdateDate() const
{
    return m_lastUpdateDate;
}

void ExchangeRateService::fetchRates(Currency baseCurrency)
{
    m_pendingBase = baseCurrency;

    // Build target currency list (all except base)
    QStringList targets;
    for (auto c : supportedCurrencies()) {
        if (c != baseCurrency)
            targets << currencyToString(c);
    }

    QUrl url(QString::fromLatin1(kApiBaseUrl));
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("from"), currencyToString(baseCurrency));
    query.addQueryItem(QStringLiteral("to"), targets.join(u','));
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setAttribute(QNetworkRequest::RedirectPolicyAttribute,
                         QNetworkRequest::NoLessSafeRedirectPolicy);

    auto *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        reply->deleteLater();
        onReplyFinished();
    });
}

void ExchangeRateService::onReplyFinished()
{
    auto *reply = qobject_cast<QNetworkReply *>(sender());
    if (!reply)
        return;

    if (reply->error() != QNetworkReply::NoError) {
        emit fetchFailed(tr("Network error: %1").arg(reply->errorString()));
        return;
    }

    const QByteArray data = reply->readAll();
    QJsonParseError parseError;
    const auto doc = QJsonDocument::fromJson(data, &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        emit fetchFailed(tr("Invalid JSON: %1").arg(parseError.errorString()));
        return;
    }

    const auto obj = doc.object();
    const auto ratesObj = obj.value(u"rates").toObject();

    if (ratesObj.isEmpty()) {
        emit fetchFailed(tr("No rates found in API response."));
        return;
    }

    // Build a new converter with fresh rates
    CurrencyConverter newConverter;

    // Direct rates from API (base -> target)
    for (auto it = ratesObj.begin(); it != ratesObj.end(); ++it) {
        bool ok = false;
        const auto target = currencyFromString(it.key(), &ok);
        if (!ok) continue;
        const double rate = it.value().toDouble();
        newConverter.setRate(m_pendingBase, target, rate);
        // Inverse rate
        if (rate > 0.0)
            newConverter.setRate(target, m_pendingBase, 1.0 / rate);
    }

    // Cross rates
    const auto currencies = supportedCurrencies();
    for (auto from : currencies) {
        for (auto to : currencies) {
            if (from == to) continue;
            if (!newConverter.hasRate(from, to)) {
                const double fromBase = newConverter.convert(1.0, from, m_pendingBase);
                const double baseTo = newConverter.convert(1.0, m_pendingBase, to);
                if (fromBase > 0.0 && baseTo > 0.0)
                    newConverter.setRate(from, to, fromBase * baseTo);
            }
        }
    }

    m_converter = newConverter;
    m_hasRates = true;
    m_lastUpdateDate = obj.value(u"date").toString();

    emit ratesUpdated();
}
