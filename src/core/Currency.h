#pragma once

#include <QList>
#include <QString>
#include <QStringList>

enum class Currency {
    CNY,
    USD,
    GBP,
    EUR,
    AUD,
    CAD
};

// Returns the ISO 4217 code string, e.g. "CNY".
inline QString currencyToString(Currency c)
{
    switch (c) {
    case Currency::CNY: return QStringLiteral("CNY");
    case Currency::USD: return QStringLiteral("USD");
    case Currency::GBP: return QStringLiteral("GBP");
    case Currency::EUR: return QStringLiteral("EUR");
    case Currency::AUD: return QStringLiteral("AUD");
    case Currency::CAD: return QStringLiteral("CAD");
    }
    return {};
}

// Parses an ISO code string into a Currency.
// Returns std::nullopt-equivalent via bool ok pattern.
// Accepts case-insensitive input.
inline Currency currencyFromString(const QString &s, bool *ok = nullptr)
{
    const auto upper = s.trimmed().toUpper();
    if (ok) *ok = true;
    if (upper == u"CNY") return Currency::CNY;
    if (upper == u"USD") return Currency::USD;
    if (upper == u"GBP") return Currency::GBP;
    if (upper == u"EUR") return Currency::EUR;
    if (upper == u"AUD") return Currency::AUD;
    if (upper == u"CAD") return Currency::CAD;
    if (ok) *ok = false;
    return Currency::CNY; // default
}

// Returns all supported currencies in a stable order.
inline QList<Currency> supportedCurrencies()
{
    return {Currency::CNY, Currency::USD, Currency::GBP,
            Currency::EUR, Currency::AUD, Currency::CAD};
}

// Returns all supported currency codes as a QStringList.
inline QStringList supportedCurrencyCodes()
{
    QStringList codes;
    for (auto c : supportedCurrencies())
        codes << currencyToString(c);
    return codes;
}

// Returns true if the string is a recognized currency code.
inline bool isValidCurrencyCode(const QString &s)
{
    bool ok = false;
    currencyFromString(s, &ok);
    return ok;
}
