#pragma once

#include "../core/Currency.h"
#include "../core/TallyEntry.h"

#include <QList>

// Persists tally-book entries and the selected target currency to a JSON file
// in the user's standard writable application-data location.
//
// All functions are safe to call on a missing or corrupt file: load() simply
// returns false and leaves the outputs unchanged rather than throwing.
//
// File format (JSON, pretty-printed):
// {
//   "targetCurrency": "USD",
//   "entries": [
//     {
//       "amount": 12.50,
//       "currency": "CNY",
//       "convertedAmount": 1.72,
//       "note": "Lunch",
//       "createdAt": "2026-06-15T10:30:00"
//     }
//   ]
// }
namespace TallyStorage {

// Returns the absolute path of the JSON storage file.
// Ensures the parent directory exists (creates it if needed).
QString storageFilePath();

// Writes the given entries and target currency to disk. Returns true on success.
bool save(const QList<TallyEntry> &entries, Currency targetCurrency);

// Reads entries and the target currency from disk into the out-parameters.
// Returns true on success; on any error (file missing, unreadable, or corrupt)
// returns false and leaves the out-parameters untouched.
bool load(QList<TallyEntry> &outEntries, Currency &outTargetCurrency);

} // namespace TallyStorage
