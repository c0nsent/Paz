#pragma once

#include <QGuiApplication>
#include <QObject>
#include <QSystemTrayIcon>


namespace impl
{
    //Короче ебать надо подумать над архитектурой приложения
    class MainWindow : public QObject
    {
        Q_OBJECT

    public:

        MainWindow();

    public slots:

        void showMessage(QStringView title, QStringView message);

    private:

        QSystemTrayIcon *m_trayIcon;
    };
}