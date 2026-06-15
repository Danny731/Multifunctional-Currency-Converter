#include "TallyStorage.h"

#include "../core/Currency.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

namespace TallyStorage {

namespace {
const char *kFileName = "tallybook.json";
}

QString storageFilePath()
{
    // AppLocalDataLocation is per-user and platform-appropriate:
    //   Windows: %LOCALAPPDATA%/<org>/<app>/
    //   macOS:   ~/Library/Application Support/<org>/<app>/
    //   Linux:   ~/.local/share/<org>/<app>/
    const QString dir =
        QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir().mkpath(dir); // no-op if it already exists
    return dir + QDir::separator() + QString::fromLatin1(kFileName);
}

bool save(const QList<TallyEntry> &entries, Currency targetCurrency)
{
    QJsonArray entriesArray;
    for (const auto &e : entries) {
        QJsonObject obj;
        obj["amount"] = e.amount;
        obj["currency"] = currencyToString(e.currency);
        obj["convertedAmount"] = e.convertedAmount;
        obj["note"] = e.note;
        obj["createdAt"] = e.createdAt.toString(Qt::ISODate);
        entriesArray.append(obj);
    }

    QJsonObject root;
    root["targetCurrency"] = currencyToString(targetCurrency);
    root["entries"] = entriesArray;

    const QJsonDocument doc(root);

    QFile file(storageFilePath());
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return false;

    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return file.error() == QFile::NoError;
}

bool load(QList<TallyEntry> &outEntries, Currency &outTargetCurrency)
{
    QFile file(storageFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
        return false;

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    const auto doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError || !doc.isObject())
        return false; // corrupt or unexpected content

    const auto root = doc.object();

    // Target currency (optional field; ignore if absent or unrecognized).
    bool ok = false;
    const Currency loadedTarget =
        currencyFromString(root.value(u"targetCurrency").toString(), &ok);
    if (ok)
        outTargetCurrency = loadedTarget;

    const auto entriesArray = root.value(u"entries").toArray();

    QList<TallyEntry> loaded;
    loaded.reserve(entriesArray.size());
    for (const auto &value : entriesArray) {
        const auto obj = value.toObject();

        bool currencyOk = false;
        const Currency currency =
            currencyFromString(obj.value(u"currency").toString(), &currencyOk);
        if (!currencyOk)
            continue; // skip entries with an unrecognized currency code

        TallyEntry entry;
        entry.amount = obj.value(u"amount").toDouble();
        entry.currency = currency;
        entry.convertedAmount = obj.value(u"convertedAmount").toDouble();
        entry.note = obj.value(u"note").toString();
        entry.createdAt =
            QDateTime::fromString(obj.value(u"createdAt").toString(), Qt::ISODate);
        loaded.append(entry);
    }

    outEntries = std::move(loaded);
    return true;
}

} // namespace TallyStorage
