#include "core/basic-types-aliases.hpp"
#include "impl/pomodoro-timer.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>
#include <QQuickView>


i32 main(i32 argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    QGuiApplication::setOrganizationName("amitayus_");
    QGuiApplication::setApplicationName("Paz");

    /*QSystemTrayIcon trayIcon;

    trayIcon.show();
    trayIcon.showMessage("Test title", "Test", QSystemTrayIcon::NoIcon);*/

    QQuickView view;
    impl::PomodoroTimer pt;
    view.setInitialProperties({{"pomodoroTimer", QVariant::fromValue(&pt)}});
    view.setSource(QUrl::fromLocalFile("ui/qml/Main.qml"));
    view.show();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [] { QCoreApplication::exit(-1); }
    );

    engine.loadFromModule("Paz.PomodoroTimer", "Main");
    //engine.loadFromModule("Paz.PomodoroTimer", "PomodoroTimerWidget");

    return QGuiApplication::exec();
}