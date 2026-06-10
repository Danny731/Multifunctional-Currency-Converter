#pragma once

#include "Currency.h"
#include "CurrencyConverter.h"

#include <QMap>
#include <QNetworkAccessManager>
#include <QObject>

// Fetches live exchange rates from the Frankfurter API (free, no key required)
// and populates a CurrencyConverter with the results.
//
// Usage:
//   ExchangeRateService service;
//   service.fetchRates(Currency::USD);
//   // connect to ratesUpdated / fetchFailed signals
class ExchangeRateService : public QObject
{
    Q_OBJECT

public:
    explicit ExchangeRateService(QObject *parent = nullptr);

    // Returns the converter populated with the latest rates.
    // Before the first successful fetch, contains no rates.
    const CurrencyConverter &converter() const;

    // Returns true if at least one successful fetch has completed.
    bool hasRates() const;

    // Returns the date string from the last successful API response.
    QString lastUpdateDate() const;

    // Initiates a network request for rates based on the given source currency.
    // Emits ratesUpdated() on success or fetchFailed() on error.
    void fetchRates(Currency baseCurrency);

signals:
    void ratesUpdated();
    void fetchFailed(const QString &reason);

private:
    void onReplyFinished();

    QNetworkAccessManager *m_networkManager = nullptr;
    CurrencyConverter m_converter;
    Currency m_pendingBase = Currency::USD;
    QString m_lastUpdateDate;
    bool m_hasRates = false;
};
