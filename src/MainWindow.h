#pragma once

#include <QMainWindow>

#include "core/CurrencyConverter.h"
#include "core/ExchangeRateService.h"

class QStatusBar;
class QTabWidget;
class ConverterPage;
class TallyBookPage;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onRatesUpdated();
    void onFetchFailed(const QString &reason);

private:
    void setupMockRates();
    void fetchLiveRates();

    CurrencyConverter m_converter;
    ExchangeRateService m_rateService;
    QTabWidget *m_tabs = nullptr;
    QStatusBar *m_statusBar = nullptr;
    ConverterPage *m_converterPage = nullptr;
    TallyBookPage *m_tallyPage = nullptr;
};
