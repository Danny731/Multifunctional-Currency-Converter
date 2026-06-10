#include "MainWindow.h"

#include "core/Currency.h"
#include "ui/ConverterPage.h"
#include "ui/TallyBookPage.h"

#include <QStatusBar>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Multifunctional Currency Converter"));
    resize(720, 520);

    // Use mock rates as initial fallback
    setupMockRates();

    m_tabs = new QTabWidget(this);

    m_converterPage = new ConverterPage(this);
    m_converterPage->setConverter(&m_converter);
    m_tabs->addTab(m_converterPage, tr("Currency Converter"));

    m_tallyPage = new TallyBookPage(this);
    m_tallyPage->setConverter(&m_converter);
    m_tabs->addTab(m_tallyPage, tr("Tally Book"));

    setCentralWidget(m_tabs);

    // Status bar for rate info
    m_statusBar = statusBar();
    m_statusBar->showMessage(tr("Using mock exchange rates. Fetching live rates..."));

    // Connect rate service
    connect(&m_rateService, &ExchangeRateService::ratesUpdated,
            this, &MainWindow::onRatesUpdated);
    connect(&m_rateService, &ExchangeRateService::fetchFailed,
            this, &MainWindow::onFetchFailed);

    // Fetch live rates from Frankfurter API
    fetchLiveRates();
}

void MainWindow::setupMockRates()
{
    // Mock exchange rates (approximate, relative to USD)
    // Used as fallback when network is unavailable
    const double usdRates[] = {
        7.25,     // CNY
        1.0,      // USD
        0.79,     // GBP
        0.92,     // EUR
        1.54,     // AUD
        1.37,     // CAD
        144.50,   // JPY
        1.34      // SGD
    };
    const auto currencies = supportedCurrencies();
    for (int i = 0; i < currencies.size(); ++i) {
        const double usdToTarget = usdRates[i];
        m_converter.setRate(Currency::USD, currencies[i], usdToTarget);
        if (usdToTarget > 0.0)
            m_converter.setRate(currencies[i], Currency::USD, 1.0 / usdToTarget);
    }

    // Cross rates
    for (auto from : currencies) {
        for (auto to : currencies) {
            if (from == to) continue;
            if (!m_converter.hasRate(from, to)) {
                const double fromUsd = m_converter.convert(1.0, from, Currency::USD);
                const double usdTo = m_converter.convert(1.0, Currency::USD, to);
                if (fromUsd > 0.0 && usdTo > 0.0)
                    m_converter.setRate(from, to, fromUsd * usdTo);
            }
        }
    }
}

void MainWindow::fetchLiveRates()
{
    m_rateService.fetchRates(Currency::USD);
}

void MainWindow::onRatesUpdated()
{
    m_converter = m_rateService.converter();
    m_converterPage->setConverter(&m_converter);
    m_tallyPage->setConverter(&m_converter);

    m_statusBar->showMessage(
        tr("Live rates loaded (source: Frankfurter API, date: %1)")
            .arg(m_rateService.lastUpdateDate()));
}

void MainWindow::onFetchFailed(const QString &reason)
{
    m_statusBar->showMessage(
        tr("Could not load live rates: %1 — using mock rates.").arg(reason));
}
