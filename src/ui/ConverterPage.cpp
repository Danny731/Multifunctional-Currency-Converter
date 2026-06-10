#include "ConverterPage.h"

#include "../core/Currency.h"

#include <QComboBox>
#include <QDoubleValidator>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

ConverterPage::ConverterPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void ConverterPage::setConverter(CurrencyConverter *converter)
{
    m_converter = converter;
}

void ConverterPage::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    // Source currency
    layout->addWidget(new QLabel(tr("Source currency"), this));
    m_sourceCurrencyCombo = new QComboBox(this);
    populateCurrencyCombo(m_sourceCurrencyCombo);
    layout->addWidget(m_sourceCurrencyCombo);

    // Amount input with validator
    layout->addWidget(new QLabel(tr("Amount"), this));
    m_amountEdit = new QLineEdit(this);
    m_amountEdit->setPlaceholderText(tr("Enter amount, e.g. 100.00"));
    m_amountEdit->setValidator(new QDoubleValidator(0.0, 1e12, 2, this));
    layout->addWidget(m_amountEdit);

    // Convert button
    m_convertButton = new QPushButton(tr("Convert"), this);
    connect(m_convertButton, &QPushButton::clicked,
            this, &ConverterPage::onConvert);
    layout->addWidget(m_convertButton);

    // Results table
    const auto currencies = supportedCurrencies();
    m_resultTable = new QTableWidget(currencies.size(), 2, this);
    m_resultTable->setHorizontalHeaderLabels({tr("Currency"), tr("Amount")});
    m_resultTable->horizontalHeader()->setStretchLastSection(true);
    m_resultTable->verticalHeader()->setVisible(false);
    m_resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int row = 0; row < currencies.size(); ++row) {
        m_resultTable->setItem(row, 0, new QTableWidgetItem(currencyToString(currencies.at(row))));
        m_resultTable->setItem(row, 1, new QTableWidgetItem(QStringLiteral("--")));
    }
    layout->addWidget(m_resultTable);

    // Status label
    m_statusLabel = new QLabel(this);
    m_statusLabel->setWordWrap(true);
    layout->addWidget(m_statusLabel);
}

void ConverterPage::populateCurrencyCombo(QComboBox *combo)
{
    for (auto c : supportedCurrencies())
        combo->addItem(currencyToString(c), static_cast<int>(c));
}

void ConverterPage::onConvert()
{
    // Validate converter
    if (!m_converter) {
        m_statusLabel->setText(tr("No converter available."));
        return;
    }

    // Validate amount
    const QString text = m_amountEdit->text().trimmed();
    if (text.isEmpty()) {
        m_statusLabel->setText(tr("Please enter an amount."));
        clearResults();
        return;
    }

    bool ok = false;
    const double amount = text.toDouble(&ok);
    if (!ok || amount < 0.0) {
        m_statusLabel->setText(tr("Invalid amount. Please enter a non-negative number."));
        clearResults();
        return;
    }

    // Get source currency
    const auto sourceCurrency = static_cast<Currency>(
        m_sourceCurrencyCombo->currentData().toInt());

    // Convert to all currencies
    const auto currencies = supportedCurrencies();
    int missingRates = 0;

    for (int row = 0; row < currencies.size(); ++row) {
        const auto target = currencies.at(row);
        const double result = m_converter->convert(amount, sourceCurrency, target);

        if (result < 0.0) {
            m_resultTable->item(row, 1)->setText(QStringLiteral("--"));
            if (target != sourceCurrency)
                ++missingRates;
        } else {
            m_resultTable->item(row, 1)->setText(CurrencyConverter::formatResult(result));
        }
    }

    if (missingRates > 0) {
        m_statusLabel->setText(
            tr("Conversion complete. %n rate(s) missing.", nullptr, missingRates));
    } else {
        m_statusLabel->setText(tr("Converted successfully."));
    }
}

void ConverterPage::clearResults()
{
    const auto currencies = supportedCurrencies();
    for (int row = 0; row < currencies.size(); ++row)
        m_resultTable->item(row, 1)->setText(QStringLiteral("--"));
}
