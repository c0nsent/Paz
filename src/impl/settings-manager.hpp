#pragma once

#include "../core/core"

#include <QObject>
#include <QSettings>


namespace paz::impl
{
    class SettingsManager : public QObject
    {
        Q_OBJECT

        auto generateConfigFile() -> void;

    public:

        explicit SettingsManager(QObject *parent = nullptr);

        auto setScope(QStringView scope) -> bool;
        auto value(QStringView name) -> QString;

        auto setValue(QStringView name) -> bool;

    private:

        QSettings m_settings;
    };
}