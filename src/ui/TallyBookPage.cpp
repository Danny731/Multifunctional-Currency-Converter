#include "TallyBookPage.h"

#include "../core/Currency.h"

#include <QComboBox>
#include <QDoubleValidator>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

TallyBookPage::TallyBookPage(QWidget *parent)
    : QWidget(parent)
{
    setupUi();
}

void TallyBookPage::setConverter(CurrencyConverter *converter)
{
    m_converter = converter;
}

void TallyBookPage::setupUi()
{
    auto *layout = new QVBoxLayout(this);

    // Target currency for total
    layout->addWidget(new QLabel(tr("Target currency (for total)"), this));
    m_targetCurrencyCombo = new QComboBox(this);
    populateCurrencyCombo(m_targetCurrencyCombo);
    layout->addWidget(m_targetCurrencyCombo);

    // Amount input
    layout->addWidget(new QLabel(tr("Amount"), this));
    m_amountEdit = new QLineEdit(this);
    m_amountEdit->setPlaceholderText(tr("e.g. 123.45"));
    m_amountEdit->setValidator(new QDoubleValidator(0.0, 1e12, 2, this));
    layout->addWidget(m_amountEdit);

    // Source currency
    layout->addWidget(new QLabel(tr("Currency"), this));
    m_sourceCurrencyCombo = new QComboBox(this);
    populateCurrencyCombo(m_sourceCurrencyCombo);
    layout->addWidget(m_sourceCurrencyCombo);

    // Optional note
    layout->addWidget(new QLabel(tr("Note (optional)"), this));
    m_noteEdit = new QLineEdit(this);
    m_noteEdit->setPlaceholderText(tr("e.g. Lunch"));
    layout->addWidget(m_noteEdit);

    // Buttons
    auto *btnLayout = new QVBoxLayout();
    m_addButton = new QPushButton(tr("Add Entry"), this);
    connect(m_addButton, &QPushButton::clicked, this, &TallyBookPage::onAddEntry);
    btnLayout->addWidget(m_addButton);

    m_deleteButton = new QPushButton(tr("Delete Selected"), this);
    connect(m_deleteButton, &QPushButton::clicked, this, &TallyBookPage::onDeleteSelected);
    btnLayout->addWidget(m_deleteButton);

    m_clearButton = new QPushButton(tr("Clear All"), this);
    connect(m_clearButton, &QPushButton::clicked, this, &TallyBookPage::onClearAll);
    btnLayout->addWidget(m_clearButton);
    layout->addLayout(btnLayout);

    // Entries table
    m_table = new QTableWidget(0, 4, this);
    m_table->setHorizontalHeaderLabels({tr("Amount"), tr("Currency"), tr("Converted"), tr("Note")});
    m_table->horizontalHeader()->setStretchLastSection(true);
    m_table->verticalHeader()->setVisible(false);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    layout->addWidget(m_table);

    // Total label
    m_totalLabel = new QLabel(tr("Total: --"), this);
    QFont boldFont = m_totalLabel->font();
    boldFont.setBold(true);
    m_totalLabel->setFont(boldFont);
    layout->addWidget(m_totalLabel);

    // Status label
    m_statusLabel = new QLabel(this);
    m_statusLabel->setWordWrap(true);
    layout->addWidget(m_statusLabel);
}

void TallyBookPage::populateCurrencyCombo(QComboBox *combo)
{
    for (auto c : supportedCurrencies())
        combo->addItem(currencyToString(c), static_cast<int>(c));
}

void TallyBookPage::onAddEntry()
{
    if (!m_converter) {
        m_statusLabel->setText(tr("No converter available."));
        return;
    }

    // Validate amount
    const QString text = m_amountEdit->text().trimmed();
    if (text.isEmpty()) {
        m_statusLabel->setText(tr("Please enter an amount."));
        return;
    }

    bool ok = false;
    const double amount = text.toDouble(&ok);
    if (!ok || amount < 0.0) {
        m_statusLabel->setText(tr("Invalid amount. Please enter a non-negative number."));
        return;
    }

    const auto sourceCurrency = static_cast<Currency>(
        m_sourceCurrencyCombo->currentData().toInt());
    const auto targetCurrency = static_cast<Currency>(
        m_targetCurrencyCombo->currentData().toInt());

    TallyEntry entry;
    entry.amount = amount;
    entry.currency = sourceCurrency;
    entry.note = m_noteEdit->text().trimmed();
    entry.createdAt = QDateTime::currentDateTime();

    if (!m_tallyBook.addEntry(entry, targetCurrency, *m_converter)) {
        m_statusLabel->setText(tr("Failed to convert. Exchange rate may be missing."));
        return;
    }

    // Clear inputs
    m_amountEdit->clear();
    m_noteEdit->clear();

    refreshTable();
    updateTotalLabel();
    m_statusLabel->setText(tr("Entry added."));
}

void TallyBookPage::onDeleteSelected()
{
    const auto selected = m_table->selectionModel()->selectedRows();
    if (selected.isEmpty()) {
        m_statusLabel->setText(tr("Please select a row to delete."));
        return;
    }

    // Delete from highest index first to avoid index shifting
    QList<int> rows;
    for (const auto &index : selected)
        rows << index.row();
    std::sort(rows.begin(), rows.end(), std::greater<int>());

    for (int row : rows)
        m_tallyBook.removeEntry(row);

    refreshTable();
    updateTotalLabel();
    m_statusLabel->setText(tr("Entry deleted."));
}

void TallyBookPage::onClearAll()
{
    if (m_tallyBook.count() == 0)
        return;

    auto answer = QMessageBox::question(this, tr("Clear All"),
        tr("Delete all %n entry/entries?", nullptr, m_tallyBook.count()),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (answer == QMessageBox::Yes) {
        m_tallyBook.clear();
        refreshTable();
        updateTotalLabel();
        m_statusLabel->setText(tr("All entries cleared."));
    }
}

void TallyBookPage::refreshTable()
{
    m_table->setRowCount(m_tallyBook.count());
    const auto &entries = m_tallyBook.entries();

    for (int i = 0; i < entries.size(); ++i) {
        const auto &e = entries.at(i);
        m_table->setItem(i, 0, new QTableWidgetItem(CurrencyConverter::formatResult(e.amount)));
        m_table->setItem(i, 1, new QTableWidgetItem(currencyToString(e.currency)));
        m_table->setItem(i, 2, new QTableWidgetItem(CurrencyConverter::formatResult(e.convertedAmount)));
        m_table->setItem(i, 3, new QTableWidgetItem(e.note));
    }
}

void TallyBookPage::updateTotalLabel()
{
    const auto targetCurrency = static_cast<Currency>(
        m_targetCurrencyCombo->currentData().toInt());

    if (m_tallyBook.count() == 0) {
        m_totalLabel->setText(tr("Total: --"));
    } else {
        m_totalLabel->setText(tr("Total: %1 %2")
            .arg(CurrencyConverter::formatResult(m_tallyBook.total()))
            .arg(currencyToString(targetCurrency)));
    }
}
