#pragma once

#include "../core/core"

#include <QObject>
#include <QSettings>


namespace paz::impl
{
    class SettingsManager : public QObject
    {
        Q_OBJECT

        auto generateDefaultConfig() -> void;

    public:

        explicit SettingsManager(QObject *parent = nullptr);

        auto fromScope(QStringView scope) -> QSettings;
        auto value(QStringView name) -> QVariant;

        auto setValue(QStringView name) -> bool;

    private:

        QSettings m_settings;
    };
}