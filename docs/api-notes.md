# API Notes — Exchange Rates

The application fetches live foreign-exchange rates from the **Frankfurter** API.

## Provider

Frankfurter is a **free, open exchange-rate API that requires no API key and no registration**. This is a deliberate change from the original course project, which used a keyed provider (`currencylayer`) with an API secret embedded in source. Because Frankfurter is keyless:

- There is **no API key to configure**, hardcode, or leak.
- The Phase 5 requirement in [`development-plan.md`](development-plan.md) to read `CURRENCY_API_KEY` from the environment is therefore **moot for the current provider**. The abstraction point for swapping providers remains (see [Swapping providers](#swapping-providers)).

## Endpoint

Defined in [`src/core/ExchangeRateService.cpp`](../src/core/ExchangeRateService.cpp):

```cpp
static const char *kApiBaseUrl = "https://api.frankfurter.dev/v1/latest";
```

The request is a GET with two query parameters, built in `fetchRates()`:

| Parameter | Value | Example |
|-----------|-------|---------|
| `from` | Base currency ISO code | `USD` |
| `to` | Comma-separated target ISO codes (all supported currencies except the base) | `CNY,GBP,EUR,AUD,CAD,JPY,SGD` |

Example request:

```
https://api.frankfurter.dev/v1/latest?from=USD&to=CNY,GBP,EUR,AUD,CAD,JPY,SGD
```

The base currency is currently fixed to `USD` — see [`MainWindow::fetchLiveRates()`](../src/MainWindow.cpp) (`m_rateService.fetchRates(Currency::USD)`). All live rates are therefore USD-referenced.

Redirects are allowed but constrained with `QNetworkRequest::NoLessSafeRedirectPolicy`.

## Response Format

A JSON object with a `rates` map and a `date` string:

```json
{
  "amount": 1.0,
  "base": "USD",
  "date": "2026-06-15",
  "rates": {
    "CNY": 7.2451,
    "GBP": 0.7864,
    "EUR": 0.9213,
    "AUD": 1.5402,
    "CAD": 1.3671,
    "JPY": 156.83,
    "SGD": 1.3455
  }
}
```

Only `rates` and `date` are consumed by the app. `amount` and `base` are ignored.

## Rate Processing

Raw API rates are direct `base → target` values. In `ExchangeRateService::onReplyFinished()` the converter is populated with three layers so any currency pair resolves in a single lookup:

1. **Direct rates** — from the API (`USD → CNY`, etc.).
2. **Inverse rates** — `target → base = 1 / rate`, added when `rate > 0`.
3. **Cross rates** — for every pair not already covered, computed as `from → base × base → to` (triangular conversion through the base).

Unrecognized currency codes in the response are skipped, so the app is robust to the API returning codes outside the supported set.

## Error Handling

`fetchRates()` is async; outcomes are delivered via two signals on `ExchangeRateService`:

- `ratesUpdated()` — fetch and parse succeeded; the converter now holds fresh rates.
- `fetchFailed(const QString &reason)` — one of:
  - Network error (the reply's `errorString()`).
  - Invalid JSON (`QJsonParseError`).
  - No `rates` object in the response.

On failure, `MainWindow::onFetchFailed()` shows the reason in the status bar and the app **continues using the mock fallback rates** loaded in `setupMockRates()`. The app never crashes on a bad response.

## Caching

- **In memory:** rates are held in the `CurrencyConverter` owned by `MainWindow` until the next successful fetch. They are not re-requested per conversion or per target currency (a problem in the original project).
- **On disk:** the app does **not** cache rates to disk. Only tally-book entries are persisted (see [`architecture.md`](architecture.md#tally-persistence)). A restart always re-fetches live rates and falls back to compiled-in mock rates until the fetch completes.

## Swapping Providers

To use a different provider, the integration points are:

1. `kApiBaseUrl` in [`ExchangeRateService.cpp`](../src/core/ExchangeRateService.cpp).
2. The response parsing in `onReplyFinished()` — adapt it to the new provider's JSON schema (specifically the `rates` and `date` field names and the per-pair rate value).
3. If the new provider requires a key, read it from an environment variable (e.g. `CURRENCY_API_KEY`) or `QSettings`, never from source — fulfilling the original Phase 5 requirement. Build the key into the request header or query as the provider specifies.

The rest of the app (converter, pages, tally book) is provider-agnostic and needs no changes.
