# Multifunctional Currency Converter

A Qt 6 desktop application that combines a **currency converter** with a **multi-currency tally book** (expense tracker). It ships with built-in fallback rates and fetches live exchange rates on startup.

- **Converter**: enter an amount in one currency and see it converted into all supported currencies at once.
- **Tally Book**: record expenses in any supported currency, and they are totaled in a target currency of your choice. Entries persist across restarts.

> This is a modernized rewrite of an older single-file SFML/libcurl course project. The original source is kept at [`Multifunctional-Currency-Converter.cpp`](Multifunctional-Currency-Converter.cpp) as a historical reference; the Qt 6 version under [`src/`](src/) is the active codebase.

## Features

- Currency converter with one-to-all output table
- Multi-currency tally book with totals in a chosen target currency
- Live exchange rates on startup, with mock fallback rates when offline
- Persistent tally storage (entries and target currency survive restart)
- Cross-rate computation (direct, inverse, and triangular rates)
- Input validation on all numeric fields (no crashes on bad input)

Supported currencies: **CNY, USD, GBP, EUR, AUD, CAD, JPY, SGD**.

## UI Overview

The main window has two tabs:

1. **Currency Converter** — source currency dropdown, amount field, a results table (one row per supported currency), and a status line.
2. **Tally Book** — amount + source currency + optional note inputs, an entries table, add/delete/clear controls, and a running total in the selected target currency.

The status bar shows the rate source and last update date (or an error message if live rates fail to load).

## Requirements

- A **C++17** compiler (MSVC, GCC, or Clang)
- **CMake** ≥ 3.21
- **Qt 6** with the **Widgets** and **Network** modules

Qt 6 is the only external dependency; networking and JSON parsing are done entirely through Qt (`QNetworkAccessManager`, `QJsonDocument`).

## Build

The project uses CMake. You need Qt 6 discoverable by CMake first.

### Windows (Visual Studio + vcpkg)

Install Qt 6 via vcpkg:

```powershell
C:\vcpkg\vcpkg.exe install qtbase --triplet x64-windows
```

Then, from a Visual Studio developer environment:

```powershell
cmake -S . -B build -G Ninja ^
  -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build build
```

Run with:

```powershell
.\build\currency_converter.exe
```

### macOS (Homebrew)

```bash
brew install qt6 ninja cmake
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$(brew --prefix qt6)"
cmake --build build
./build/currency_converter
```

### Linux

Install Qt 6 Widgets + Network through your distribution's package manager (e.g. `qt6-base-dev` on Debian/Ubuntu), then:

```bash
cmake -S . -B build -G Ninja
cmake --build build
./build/currency_converter
```

## Configuration

The app uses the **Frankfurter** exchange-rate API, which is **free and requires no API key**. No configuration or secrets are needed to run it — live rates are fetched automatically on startup, and mock rates are used as a fallback when the network is unavailable.

For details on the endpoint, response format, and how rates are derived, see [`docs/api-notes.md`](docs/api-notes.md).

Tally data is stored per-user in the standard application-data location (e.g. `%LOCALAPPDATA%\FloatingO\CurrencyConverter\tallybook.json` on Windows).

## Project Structure

```
.
├── CMakeLists.txt
├── README.md
├── docs/
│   ├── development-plan.md     # phased migration plan and status
│   ├── architecture.md         # module responsibilities and data flow
│   └── api-notes.md            # exchange-rate API documentation
├── src/
│   ├── main.cpp                # entry point
│   ├── MainWindow.{h,cpp}      # composition root: tabs + rate service wiring
│   ├── core/                   # domain logic (no Qt Widgets dependency)
│   ├── ui/                     # Qt widget pages
│   └── storage/                # persistence
└── Multifunctional-Currency-Converter.cpp   # legacy SFML version (reference only)
```

See [`docs/architecture.md`](docs/architecture.md) for the layer breakdown.

## Roadmap

Development follows the phased plan in [`docs/development-plan.md`](docs/development-plan.md). Current status:

- [x] Phase 1 — Qt 6 build foundation
- [x] Phase 2 — core domain model
- [x] Phase 3 — offline converter page
- [x] Phase 4 — tally book (offline)
- [x] Phase 5 — live exchange-rate service
- [x] Phase 6 — persistent tally storage
- [ ] Phase 7 — resource system and UI polish
- [x] Phase 8 — documentation
- [ ] Phase 9 — tests for core logic

## License

Personal/course project. See the repository for details.
