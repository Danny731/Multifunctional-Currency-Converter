#include "MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // Identifies the app for QStandardPaths / storage so data lands in a
    // predictable per-user directory rather than under the executable name.
    app.setOrganizationName(QStringLiteral("FloatingO"));
    app.setApplicationName(QStringLiteral("CurrencyConverter"));

    MainWindow window;
    window.show();

    return app.exec();
}
