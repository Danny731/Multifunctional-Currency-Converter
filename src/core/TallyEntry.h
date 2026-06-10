#pragma once

#include "Currency.h"

#include <QDateTime>
#include <QString>

// A single expense entry in the tally book.
struct TallyEntry {
    double amount = 0.0;           // Original amount
    Currency currency = Currency::CNY; // Original currency
    double convertedAmount = 0.0;  // Amount converted to target currency
    QString note;                  // Optional user note
    QDateTime createdAt = QDateTime::currentDateTime();
};
