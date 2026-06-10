#include "TallyBook.h"

#include "CurrencyConverter.h"

bool TallyBook::addEntry(const TallyEntry &entry, Currency targetCurrency,
                          const CurrencyConverter &converter)
{
    double converted = converter.convert(entry.amount, entry.currency, targetCurrency);
    if (converted < 0.0 && entry.currency != targetCurrency)
        return false; // conversion failed

    TallyEntry stored = entry;
    stored.convertedAmount = (entry.currency == targetCurrency) ? entry.amount : converted;
    m_entries.append(stored);
    return true;
}

void TallyBook::removeEntry(int index)
{
    if (index >= 0 && index < m_entries.size())
        m_entries.removeAt(index);
}

void TallyBook::clear()
{
    m_entries.clear();
}

const QList<TallyEntry> &TallyBook::entries() const
{
    return m_entries;
}

void TallyBook::recalculate(Currency targetCurrency,
                             const CurrencyConverter &converter)
{
    for (auto &entry : m_entries) {
        double converted = converter.convert(entry.amount, entry.currency, targetCurrency);
        entry.convertedAmount = (entry.currency == targetCurrency) ? entry.amount
            : (converted < 0.0 ? 0.0 : converted);
    }
}

double TallyBook::total() const
{
    double sum = 0.0;
    for (const auto &entry : m_entries)
        sum += entry.convertedAmount;
    return sum;
}

int TallyBook::count() const
{
    return m_entries.size();
}
