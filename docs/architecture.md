# Architecture

The application is a layered Qt 6 Widgets desktop app. Business logic is kept out of the UI layer so the core can be reasoned about and tested without any widgets.

## Layers

```
┌─────────────────────────────────────────────┐
│  Entry / Composition                        │
│  main.cpp, MainWindow                       │
├─────────────────────────────────────────────┤
│  UI Layer (Qt Widgets)                      │
│  ConverterPage, TallyBookPage               │
├─────────────────────────────────────────────┤
│  Core / Domain                              │
│  Currency, CurrencyConverter, TallyBook,    │
│  TallyEntry, ExchangeRateService            │
├─────────────────────────────────────────────┤
│  Storage                                    │
│  TallyStorage                               │
└─────────────────────────────────────────────┘
```

**Dependency rule:** upper layers depend on lower layers, never the reverse. The core layer has no dependency on Qt Widgets — only on `QtCore` types (`QString`, `QMap`, `QList`, `QDateTime`) and, for `ExchangeRateService`, `QtNetwork`. This keeps conversion math and rate logic testable without a GUI.

## Module Responsibilities

| Module | Layer | Responsibility |
|--------|-------|----------------|
| `main.cpp` | Entry | Creates `QApplication`, sets app identity, shows `MainWindow`. |
| `MainWindow` | Composition | Owns the shared `CurrencyConverter` and `ExchangeRateService`, builds the two-tab UI, wires rate updates into the pages, seeds fallback rates. |
| `ConverterPage` | UI | Converter tab: amount input, source currency, results table. Calls `CurrencyConverter` to produce output. |
| `TallyBookPage` | UI | Tally tab: owns a `TallyBook`, manages entry add/delete/clear, computes totals, loads/persists via `TallyStorage`. |
| `Currency` | Core | The supported-currency enum plus string parse/format helpers. Header-only. |
| `CurrencyConverter` | Core | Holds exchange rates keyed `FROM_TO`; converts amounts; formats results. Plain value class. |
| `TallyBook` / `TallyEntry` | Core | In-memory collection of expense entries with converted totals. Plain class. |
| `ExchangeRateService` | Core | Fetches live rates via `QNetworkAccessManager`, parses JSON, derives rates, emits signals. `QObject`. |
| `TallyStorage` | Storage | Loads/saves tally entries and the target currency as JSON in the user data directory. Namespace of free functions. |

## Data Flow

### Startup and live rates

```
main.cpp
  └─ MainWindow()
       ├─ setupMockRates() ─► CurrencyConverter (fallback rates)
       ├─ create ConverterPage / TallyBookPage, give them &converter
       └─ fetchLiveRates()
              └─ ExchangeRateService::fetchRates()
                    └─ HTTP GET (async)
                          ├─ success → ratesUpdated()
                          │     └─ MainWindow::onRatesUpdated()
                          │           ├─ converter = service.converter()
                          │           └─ page->setConverter(&converter)  (both pages)
                          └─ failure → fetchFailed(reason)
                                └─ status bar shows message, mock rates remain
```

Rates flow one way into the converter, and the converter is pushed down into the pages whenever it changes. Pages hold a **non-owning pointer** to the shared converter; they never fetch rates themselves.

### Tally persistence

```
TallyBookPage::onAddEntry() / onDeleteSelected() / onClearAll()
  └─ mutate m_tallyBook
  └─ refreshTable() + updateTotalLabel()
  └─ saveState()
        └─ TallyStorage::save(entries, targetCurrency)  →  tallybook.json
```

On startup, `TallyBookPage::setConverter()` (called by `MainWindow` once rates are available) triggers `loadState()` once:

```
setConverter()  (first call)
  └─ loadState()
        └─ TallyStorage::load() → entries + targetCurrency
        └─ m_tallyBook.setEntries(...)
        └─ recalculate(targetCurrency, converter)   ← refresh against current rates
        └─ refreshTable() + updateTotalLabel()
```

A `m_loaded` flag ensures the file is read exactly once; subsequent `setConverter()` calls (e.g. when live rates arrive) only re-run `recalculate` so totals reflect the freshest rates.

## Design Notes

- **Async networking.** `QNetworkAccessManager` is non-blocking. The UI stays responsive; results land through signals/slots. The app never blocks waiting on the network — mock rates are shown immediately and replaced when the fetch completes.
- **Value semantics for the converter.** `CurrencyConverter` is copied (not shared) when live rates arrive (`m_converter = m_rateService.converter()`). This is cheap relative to the UI refresh and avoids shared-state complexity.
- **Cross rates.** The converter stores direct rates (`A→B`). `ExchangeRateService` and `MainWindow::setupMockRates()` additionally derive inverse rates (`B→A`) and triangular/cross rates (`A→B` via the base) so any currency pair is convertible in one lookup.
- **Single-threaded.** All logic runs on the GUI thread. No locks are required.
- **Storage format.** JSON, one file per user, in `QStandardPaths::AppLocalDataLocation`. Corrupt or missing files are handled gracefully — `load()` returns false and the app starts with an empty tally book.

## Layering Rules (for future work)

1. UI code calls core; core never calls UI.
2. Keep conversion math in `CurrencyConverter`, not in page slots.
3. Validate user input before calling numeric functions (pages use `QDoubleValidator` and re-check before parsing).
4. Do not parse JSON by string slicing or regex — use `QJsonDocument` / `QJsonObject`.
5. Do not hardcode secrets. The current provider (Frankfurter) is keyless; see [`api-notes.md`](api-notes.md).
