#pragma once

#include <QObject>
#include <QString>
#include <QtQmlIntegration/qqmlintegration.h>


namespace paz::impl
{
    class Test : public QObject
    {
        Q_OBJECT

        QML_ELEMENT
        Q_PROPERTY(QString string READ string WRITE set NOTIFY changed)

    public:

        QString string() const
        {
            return m_string;
        }

        void set(const QString& value)
        {
            if (m_string == value) return;

            m_string = value;
            emit changed();
        }


    signals:

        void changed();



    public:

        QString m_string;
    };
}
