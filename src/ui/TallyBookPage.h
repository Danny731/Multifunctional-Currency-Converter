#pragma once

#include <QWidget>

#include "../core/Currency.h"
#include "../core/CurrencyConverter.h"
#include "../core/TallyBook.h"

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class TallyBookPage : public QWidget
{
    Q_OBJECT

public:
    explicit TallyBookPage(QWidget *parent = nullptr);

    void setConverter(CurrencyConverter *converter);

private slots:
    void onAddEntry();
    void onDeleteSelected();
    void onClearAll();

private:
    void setupUi();
    void populateCurrencyCombo(QComboBox *combo);
    void refreshTable();
    void updateTotalLabel();

    CurrencyConverter *m_converter = nullptr;
    TallyBook m_tallyBook;

    QComboBox *m_targetCurrencyCombo = nullptr;
    QLineEdit *m_amountEdit = nullptr;
    QComboBox *m_sourceCurrencyCombo = nullptr;
    QLineEdit *m_noteEdit = nullptr;
    QPushButton *m_addButton = nullptr;
    QPushButton *m_deleteButton = nullptr;
    QPushButton *m_clearButton = nullptr;
    QTableWidget *m_table = nullptr;
    QLabel *m_totalLabel = nullptr;
    QLabel *m_statusLabel = nullptr;
};
