#pragma once

#include "Currency.h"

#include <QMap>
#include <QString>

// Converts amounts between currencies using provided exchange rates.
//
// Rates are keyed by "SOURCE_TARGET", e.g. "USD_CNY" -> 7.25.
// The rate value means: 1 unit of source currency = rate units of target currency.
class CurrencyConverter
{
public:
    // Sets the exchange rate for a source->target pair.
    void setRate(Currency from, Currency to, double rate);

    // Returns the exchange rate, or 0.0 if not available.
    double rate(Currency from, Currency to) const;

    // Converts amount from one currency to another.
    // Returns the converted amount, or -1.0 if the rate is not available.
    // Same-currency conversion returns the original amount.
    double convert(double amount, Currency from, Currency to) const;

    // Formats a numeric result to a fixed 2-decimal string.
    static QString formatResult(double value);

    // Returns true if a rate exists for the given pair (or same currency).
    bool hasRate(Currency from, Currency to) const;

private:
    QString makeKey(Currency from, Currency to) const;
    QMap<QString, double> m_rates;
};
