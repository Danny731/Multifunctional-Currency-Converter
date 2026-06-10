# Qt 6 Modernization Development Plan

## Project Context

This repository is a five-year-old course project named **Multifunctional Currency Converter**. The original implementation is a single C++ source file using **SFML** for the GUI and **libcurl** for exchange-rate HTTP requests.

The project goal has changed: the new version should be rebuilt as a modern **Qt 6 Widgets** desktop application.

The original SFML implementation should be kept as a reference during migration until the Qt version reaches feature parity.

## Current Branch

Development is happening on:

```text
codex-course-project-updates
```

## Current Repository State

Important existing files:

```text
Multifunctional-Currency-Converter.cpp
README.md
usa.jpeg
uk.jpeg
eur.jpeg
china.jpeg
cad.jpeg
aus.jpeg
```

New modernization files already started:

```text
.gitignore
CMakeLists.txt
src/main.cpp
src/MainWindow.h
src/MainWindow.cpp
docs/development-plan.md
```

Generated build directories such as `build/` and `build-nmake/` are ignored by `.gitignore`.

## Environment Findings

The local machine currently has:

- Visual Studio C++ toolchain installed.
- Visual Studio CMake available at:

```text
C:\Program Files\Microsoft Visual Studio\18\Community\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe
```

- `C:\vcpkg\vcpkg.exe` exists.
- `qmake` exists on PATH, but it is from Anaconda and uses Qt 5.15.2, not Qt 6.
- Qt 6 development packages are not installed yet.

The current Qt 6 CMake scaffold fails at `find_package(Qt6 ...)` until Qt 6 is installed.

Recommended dependency installation:

```powershell
C:\vcpkg\vcpkg.exe install qtbase --triplet x64-windows
```

If networking/API support is later kept entirely in Qt, `qtbase` is enough for `Qt6::Widgets`, `Qt6::Network`, and `QJsonDocument`.

## Build Direction

Use **CMake + Qt 6 Widgets**.

Do not continue using SFML for the new UI.

Do not continue using libcurl unless there is a strong reason. Prefer Qt APIs:

- `Qt Widgets` for UI
- `Qt Network` for HTTP requests
- `QJsonDocument` / `QJsonObject` for JSON parsing
- `QSettings` or JSON files for local configuration

## Recommended Final Directory Structure

The project should evolve toward this structure:

```text
.
├── CMakeLists.txt
├── README.md
├── docs/
│   ├── development-plan.md
│   ├── architecture.md
│   └── api-notes.md
├── resources/
│   ├── resources.qrc
│   ├── flags/
│   │   ├── aud.jpeg
│   │   ├── cad.jpeg
│   │   ├── china.jpeg
│   │   ├── eur.jpeg
│   │   ├── uk.jpeg
│   │   └── usa.jpeg
│   └── styles/
│       └── app.qss
├── src/
│   ├── main.cpp
│   ├── MainWindow.h
│   ├── MainWindow.cpp
│   ├── ui/
│   │   ├── ConverterPage.h
│   │   ├── ConverterPage.cpp
│   │   ├── TallyBookPage.h
│   │   └── TallyBookPage.cpp
│   ├── core/
│   │   ├── Currency.h
│   │   ├── CurrencyConverter.h
│   │   ├── CurrencyConverter.cpp
│   │   ├── ExchangeRateService.h
│   │   ├── ExchangeRateService.cpp
│   │   ├── TallyEntry.h
│   │   ├── TallyBook.h
│   │   └── TallyBook.cpp
│   └── storage/
│       ├── TallyStorage.h
│       └── TallyStorage.cpp
└── tests/
```

This structure does not need to be created all at once. Create files as the corresponding feature is implemented.

## Major Problems in the Original Project

These should guide the modernization work:

1. The original program is a single 1500+ line `.cpp` file.
2. UI, networking, conversion logic, parsing, and data handling are tightly coupled.
3. The code loads `canada.jpeg`, but the repository contains `cad.jpeg`.
4. Font path is hardcoded to Linux:

```cpp
/usr/share/fonts/truetype/ubuntu/Ubuntu-BI.ttf
```

5. Exchange-rate JSON is parsed with fixed `substr` positions.
6. The API key is hardcoded in source.
7. HTTP is used instead of HTTPS.
8. The same exchange-rate URL is requested repeatedly for each target currency.
9. User input is not validated before `stof`.
10. Tally-book input assumes a strict format such as `123 USD`.
11. There is no persistent storage for tally entries.
12. There is no proper build system for Windows.

## Phase 1: Qt 6 Build Foundation

Goal: make the project configure and open a minimal Qt 6 window.

Tasks:

- Install Qt 6 development packages.
- Keep `CMakeLists.txt` as the main build entry.
- Verify CMake can find:
  - `Qt6::Widgets`
  - `Qt6::Network`
- Build the target:

```text
currency_converter
```

- Keep original SFML source untouched until the Qt rewrite is usable.

Suggested configure command from a Visual Studio developer environment:

```powershell
cmake -S . -B build -G "NMake Makefiles" -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake
```

Suggested build command:

```powershell
cmake --build build
```

Acceptance criteria:

- CMake configure succeeds.
- Build succeeds.
- A Qt window opens with two main sections:
  - Currency Converter
  - Tally Book

## Phase 2: Core Domain Model

Goal: separate business logic from UI.

Create a small domain layer before implementing real networking.

Recommended types:

```cpp
enum class Currency {
    CNY,
    USD,
    GBP,
    EUR,
    AUD,
    CAD
};
```

Recommended helpers:

- Convert `Currency` to display string.
- Parse display string into `Currency`.
- Return the supported currency list.
- Validate whether a string is a supported currency code.

Create:

```text
src/core/Currency.h
src/core/CurrencyConverter.h
src/core/CurrencyConverter.cpp
```

`CurrencyConverter` should:

- Accept source amount.
- Accept source currency.
- Accept target currency.
- Accept exchange-rate data.
- Return converted amount.
- Format output consistently, preferably two decimal places for UI.

Acceptance criteria:

- Conversion logic can be called without any Qt widget.
- Same-currency conversion returns the original amount.
- Invalid or missing exchange rates return a controlled error, not a crash.

## Phase 3: Offline Converter Page

Goal: build a working converter page using fixed mock exchange rates.

This phase should not depend on network access.

UI requirements:

- Source currency selector.
- Amount input.
- Convert button.
- Results table showing all supported currencies.
- Inline error/status label.

Validation rules:

- Amount cannot be empty.
- Amount must be a valid non-negative number.
- Source currency must be selected.
- Results should use consistent decimal formatting.

Implementation notes:

- Use Qt validators where useful, for example `QDoubleValidator`.
- UI code should call the core conversion layer instead of doing math directly.
- Do not use `std::stof` on raw user input without validation.

Acceptance criteria:

- User can enter an amount and convert to all supported currencies.
- Invalid input shows a friendly error and does not crash.
- No network is required.

## Phase 4: Tally Book Offline Version

Goal: rebuild the tally-book feature with Qt table widgets and mock rates.

Create:

```text
src/core/TallyEntry.h
src/core/TallyBook.h
src/core/TallyBook.cpp
src/ui/TallyBookPage.h
src/ui/TallyBookPage.cpp
```

Suggested `TallyEntry` fields:

```text
amount
currency
convertedAmount
note
createdAt
```

Minimum UI requirements:

- Target currency selector.
- Amount input.
- Source currency selector.
- Add entry button.
- Entries table.
- Delete selected entry button.
- Total amount display.

Optional but useful:

- Note field.
- Clear all button.
- Recalculate button.

Acceptance criteria:

- User can add entries in different currencies.
- Entries are displayed in a table.
- Total is calculated in the selected target currency.
- Invalid input is rejected without crashing.

## Phase 5: Exchange Rate Service

Goal: replace the old libcurl/string-slicing logic with Qt Network and JSON parsing.

Create:

```text
src/core/ExchangeRateService.h
src/core/ExchangeRateService.cpp
```

Use:

- `QNetworkAccessManager`
- `QNetworkRequest`
- `QNetworkReply`
- `QJsonDocument`
- `QJsonObject`

Requirements:

- Use HTTPS.
- Do not hardcode the API key in source code.
- Load API key from one of:
  - environment variable
  - local config file
  - Qt settings
- Provide a clear missing-key message.
- Cache rates to avoid repeated requests.
- Handle network failure.
- Handle invalid JSON.
- Handle API error responses.

Recommended environment variable:

```text
CURRENCY_API_KEY
```

Acceptance criteria:

- Real exchange rates can be fetched.
- API key is not committed.
- Failed requests show a controlled UI error.
- Converter and tally book can both use the same rate service.

## Phase 6: Persistence

Goal: make tally-book data survive app restarts.

Create:

```text
src/storage/TallyStorage.h
src/storage/TallyStorage.cpp
```

Preferred storage format:

```text
JSON
```

Suggested file location:

- Use Qt standard writable app data location via `QStandardPaths`.

Data to save:

- entries
- target currency
- optional notes
- timestamps

Acceptance criteria:

- Existing entries reload when the app starts.
- User can save changes automatically or explicitly.
- Corrupt storage files do not crash the app.

## Phase 7: Resource System and UI Polish

Goal: make the app look and behave like a modern desktop utility.

Tasks:

- Move flag images into `resources/flags/`.
- Add a Qt resource file:

```text
resources/resources.qrc
```

- Load images through Qt resource paths instead of raw relative file paths.
- Add a simple QSS stylesheet if desired.
- Use layouts instead of fixed pixel coordinates.
- Make the window resizable.
- Add status bar text for:
  - exchange-rate source
  - last update time
  - offline/mock mode

Acceptance criteria:

- App does not depend on current working directory for images.
- UI scales cleanly when resized.
- Missing resources are handled gracefully.

## Phase 8: Documentation

Goal: make the project easy for another developer or agent to continue.

Update `README.md` with:

- Project description.
- Screenshot or UI overview.
- Requirements:
  - C++17
  - CMake
  - Qt 6
  - Visual Studio Build Tools or equivalent compiler
- Setup instructions.
- Build instructions.
- API key configuration.
- Current feature list.
- Roadmap.

Add docs:

```text
docs/architecture.md
docs/api-notes.md
```

Acceptance criteria:

- A new developer can build the app by following README.
- API key handling is documented.
- Architecture responsibilities are documented.

## Phase 9: Testing

Goal: protect core behavior during refactoring.

Prioritize tests for non-UI logic:

- Currency parsing.
- Amount validation.
- Conversion math.
- Same-currency conversion.
- Tally total calculation.
- Storage serialization/deserialization.
- Exchange-rate JSON parsing.

Possible test options:

- Qt Test
- Catch2
- GoogleTest

Keep tests focused on core logic first. UI tests are optional.

Acceptance criteria:

- Core conversion and tally logic can be tested without opening the GUI.
- Tests run from CMake.

## Implementation Rules for Future Agents

Future agents should follow these rules:

1. Do not delete the original SFML source until Qt feature parity is reached.
2. Prefer small, verifiable steps.
3. Keep UI code separate from business logic.
4. Do not hardcode API keys.
5. Do not parse JSON with string positions or regular expressions.
6. Do not introduce network dependency before the offline version works.
7. Add input validation before calling numeric conversion functions.
8. Keep generated build files out of git.
9. Update this document when the plan changes.
10. Update README when build or setup steps change.

## Immediate Next Steps

Recommended next tasks:

1. Decide whether to keep the current Qt scaffold files or recreate them after Qt 6 is installed.
2. Install Qt 6 development package.
3. Verify CMake configure and build.
4. Split `MainWindow` into pages:
   - `ConverterPage`
   - `TallyBookPage`
5. Implement offline `Currency` and `CurrencyConverter` core classes.
6. Wire the converter page to mock rates.

## Known Open Decisions

These decisions should be made before deeper implementation:

1. Qt installation method:
   - vcpkg `qtbase`
   - official Qt installer
   - other package manager
2. API provider:
   - keep apilayer/currencylayer
   - switch to another provider
   - support configurable provider later
3. API key location:
   - environment variable
   - config file
   - Qt settings
4. Tally storage location:
   - project-local file for demo
   - user app data directory for real app
5. UI style:
   - plain native Qt Widgets
   - custom QSS theme

## Current Migration Principle

The best path is:

```text
Build foundation -> offline functionality -> real exchange API -> persistence -> polish -> tests/docs
```

This avoids breaking the project early and ensures that each phase produces a runnable application.
