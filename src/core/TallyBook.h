#pragma once

#include "TallyEntry.h"

#include <QList>

class CurrencyConverter;

// Manages a collection of tally entries and computes totals.
class TallyBook
{
public:
    // Adds an entry. The convertedAmount is computed using the converter
    // for the given target currency. Returns false if conversion fails.
    bool addEntry(const TallyEntry &entry, Currency targetCurrency,
                  const CurrencyConverter &converter);

    // Removes the entry at the given index.
    void removeEntry(int index);

    // Clears all entries.
    void clear();

    // Returns all entries.
    const QList<TallyEntry> &entries() const;

    // Recalculates convertedAmount for all entries using the given
    // target currency and converter.
    void recalculate(Currency targetCurrency, const CurrencyConverter &converter);

    // Returns the total of all converted amounts.
    double total() const;

    // Returns the number of entries.
    int count() const;

private:
    QList<TallyEntry> m_entries;
};
