#pragma once

#include <QMainWindow>

#include "core/CurrencyConverter.h"

class QTabWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void setupMockRates();

    CurrencyConverter m_converter;
    QTabWidget *m_tabs = nullptr;
};
