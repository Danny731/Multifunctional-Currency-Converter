#pragma once

#include <QMainWindow>

class QComboBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTableWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QWidget *createConverterPage();
    QWidget *createTallyBookPage();

    QComboBox *sourceCurrencyCombo = nullptr;
    QLineEdit *amountEdit = nullptr;
    QLabel *converterStatusLabel = nullptr;
    QTableWidget *converterResultTable = nullptr;

    QComboBox *targetCurrencyCombo = nullptr;
    QLineEdit *entryEdit = nullptr;
    QLabel *tallyStatusLabel = nullptr;
    QTableWidget *tallyTable = nullptr;
};
