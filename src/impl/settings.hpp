#pragma once

#include <QObject>
#include <QSettings>

namespace impl
{
    class Settings : public QObject
    {
        Q_OBJECT

    public:

        explicit Settings(QObject *parent = nullptr);

        

    private:

        QSettings m_settings;
    };
}
