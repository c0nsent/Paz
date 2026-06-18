#include "core/basic-types-aliases.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>


i32 main(i32 argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QGuiApplication::setOrganizationName("amitayus_");
    QGuiApplication::setApplicationName("Paz");

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