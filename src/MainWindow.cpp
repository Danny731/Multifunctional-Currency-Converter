#include "MainWindow.h"

#include <QComboBox>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTabWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QWidget>

namespace {
const QStringList currencies = {"CNY", "USD", "GBP", "EUR", "AUD", "CAD"};
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Multifunctional Currency Converter");
    resize(720, 520);

    auto *tabs = new QTabWidget(this);
    tabs->addTab(createConverterPage(), tr("Currency Converter"));
    tabs->addTab(createTallyBookPage(), tr("Tally Book"));

    setCentralWidget(tabs);
}

QWidget *MainWindow::createConverterPage()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);

    sourceCurrencyCombo = new QComboBox(page);
    sourceCurrencyCombo->addItems(currencies);

    amountEdit = new QLineEdit(page);
    amountEdit->setPlaceholderText(tr("Amount"));

    auto *convertButton = new QPushButton(tr("Convert"), page);

    converterResultTable = new QTableWidget(currencies.size(), 2, page);
    converterResultTable->setHorizontalHeaderLabels({tr("Currency"), tr("Amount")});
    converterResultTable->horizontalHeader()->setStretchLastSection(true);
    converterResultTable->verticalHeader()->setVisible(false);
    converterResultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for (int row = 0; row < currencies.size(); ++row) {
        converterResultTable->setItem(row, 0, new QTableWidgetItem(currencies.at(row)));
        converterResultTable->setItem(row, 1, new QTableWidgetItem("-"));
    }

    converterStatusLabel = new QLabel(tr("Qt 6 UI scaffold is ready. Exchange-rate logic will be migrated next."), page);
    converterStatusLabel->setWordWrap(true);

    layout->addWidget(new QLabel(tr("Source currency"), page));
    layout->addWidget(sourceCurrencyCombo);
    layout->addWidget(new QLabel(tr("Amount"), page));
    layout->addWidget(amountEdit);
    layout->addWidget(convertButton);
    layout->addWidget(converterResultTable);
    layout->addWidget(converterStatusLabel);

    return page;
}

QWidget *MainWindow::createTallyBookPage()
{
    auto *page = new QWidget(this);
    auto *layout = new QVBoxLayout(page);

    targetCurrencyCombo = new QComboBox(page);
    targetCurrencyCombo->addItems(currencies);

    entryEdit = new QLineEdit(page);
    entryEdit->setPlaceholderText(tr("Example: 123 USD"));

    auto *addEntryButton = new QPushButton(tr("Add Entry"), page);

    tallyTable = new QTableWidget(0, 3, page);
    tallyTable->setHorizontalHeaderLabels({tr("Amount"), tr("Currency"), tr("Converted")});
    tallyTable->horizontalHeader()->setStretchLastSection(true);
    tallyTable->verticalHeader()->setVisible(false);
    tallyTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tallyStatusLabel = new QLabel(tr("Tally-book storage and conversion will be migrated from the SFML version."), page);
    tallyStatusLabel->setWordWrap(true);

    layout->addWidget(new QLabel(tr("Target currency"), page));
    layout->addWidget(targetCurrencyCombo);
    layout->addWidget(new QLabel(tr("Expense entry"), page));
    layout->addWidget(entryEdit);
    layout->addWidget(addEntryButton);
    layout->addWidget(tallyTable);
    layout->addWidget(tallyStatusLabel);

    return page;
}
