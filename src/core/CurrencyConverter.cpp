#include "CurrencyConverter.h"

#include <QLocale>
#include <QStringBuilder>

void CurrencyConverter::setRate(Currency from, Currency to, double rate)
{
    m_rates[makeKey(from, to)] = rate;
}

double CurrencyConverter::rate(Currency from, Currency to) const
{
    if (from == to)
        return 1.0;
    auto it = m_rates.constFind(makeKey(from, to));
    if (it != m_rates.constEnd())
        return it.value();
    return 0.0;
}

double CurrencyConverter::convert(double amount, Currency from, Currency to) const
{
    if (from == to)
        return amount;
    const double r = rate(from, to);
    if (r <= 0.0)
        return -1.0; // rate not available
    return amount * r;
}

QString CurrencyConverter::formatResult(double value)
{
    if (value < 0.0)
        return QStringLiteral("--");
    return QLocale().toString(value, 'f', 2);
}

bool CurrencyConverter::hasRate(Currency from, Currency to) const
{
    if (from == to)
        return true;
    return m_rates.contains(makeKey(from, to));
}

QString CurrencyConverter::makeKey(Currency from, Currency to) const
{
    return currencyToString(from) % u'_' % currencyToString(to);
}
