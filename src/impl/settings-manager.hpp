#pragma once

#include "../core/core"

#include <QObject>
#include <QSettings>


namespace paz::impl
{
    class SettingsManager : public QObject
    {
        Q_OBJECT

        SettingsManager();



    private:

        QSettings m_settings;
    };
}