#include "MainWindow.h"

#include "core/Currency.h"
#include "ui/ConverterPage.h"

#include <QLabel>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Multifunctional Currency Converter"));
    resize(720, 520);

    setupMockRates();

    m_tabs = new QTabWidget(this);

    auto *converterPage = new ConverterPage(this);
    converterPage->setConverter(&m_converter);
    m_tabs->addTab(converterPage, tr("Currency Converter"));

    // Tally Book tab placeholder — will be replaced in Step 4
    auto *tallyPlaceholder = new QWidget(this);
    auto *label = new QLabel(tr("Tally Book — coming soon."), tallyPlaceholder);
    label->setAlignment(Qt::AlignCenter);
    m_tabs->addTab(tallyPlaceholder, tr("Tally Book"));

    setCentralWidget(m_tabs);
}

void MainWindow::setupMockRates()
{
    // Mock exchange rates (approximate, relative to USD)
    // Rate means: 1 USD = X units of target currency
    const double usdRates[] = {
        7.25,   // CNY
        1.0,    // USD
        0.79,   // GBP
        0.92,   // EUR
        1.54,   // AUD
        1.37    // CAD
    };
    const auto currencies = supportedCurrencies();
    for (int i = 0; i < currencies.size(); ++i) {
        const double usdToTarget = usdRates[i];
        // USD -> target
        m_converter.setRate(Currency::USD, currencies[i], usdToTarget);
        // target -> USD (inverse)
        if (usdToTarget > 0.0)
            m_converter.setRate(currencies[i], Currency::USD, 1.0 / usdToTarget);
    }

    // Cross rates: from -> USD -> to
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
