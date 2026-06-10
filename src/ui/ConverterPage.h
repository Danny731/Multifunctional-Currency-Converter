#pragma once

#include <QWidget>

#include "../core/CurrencyConverter.h"

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class ConverterPage : public QWidget
{
    Q_OBJECT

public:
    explicit ConverterPage(QWidget *parent = nullptr);

    // Sets the converter instance (takes a pointer; does not take ownership).
    void setConverter(CurrencyConverter *converter);

private slots:
    void onConvert();

private:
    void setupUi();
    void populateCurrencyCombo(QComboBox *combo);
    void updateResultRow(int row, Currency target, double amount);
    void clearResults();

    CurrencyConverter *m_converter = nullptr;

    QComboBox *m_sourceCurrencyCombo = nullptr;
    QLineEdit *m_amountEdit = nullptr;
    QPushButton *m_convertButton = nullptr;
    QTableWidget *m_resultTable = nullptr;
    QLabel *m_statusLabel = nullptr;
};
