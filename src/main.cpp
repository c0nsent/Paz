#include "impl/initializer.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTime>
#include <QDebug>


int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    QTime test;

    qInfo() << test.toString();
    //impl::PomodoroStats stats;

    /*stats.addPomodoro(std::chrono::seconds{10}, QDate{2021, 1, 1});
    stats.addPomodoro(std::chrono::seconds{10}, QDate{2021, 1, 2});
    stats.addPomodoro(std::chrono::seconds{10}, QDate{2021, 1, 3});
    stats.addPomodoro(std::chrono::seconds{60}, QDate{2021, 1, 1});
    stats.sync();*/

    QGuiApplication::setOrganizationName("amitayus_");
    QGuiApplication::setApplicationName("Paz");
    QGuiApplication::setApplicationVersion(APP_VERSION);

    auto settingsManager{ new(std::nothrow) impl::SettingsManager{&app}};

    auto initializer{ new(std::nothrow) impl::Initializer{&app} };

    auto pt{ initializer->createPomodoroTimer()};
    auto pomodoroStats{initializer->createPomodoroStats()};
    auto systemTray{initializer->createSystemTrayIcon()};

    QQmlApplicationEngine engine;
    QObject::connect( &engine, &QQmlApplicationEngine::objectCreationFailed,
        [] { QCoreApplication::exit(-1); }
    );

    engine.setInitialProperties({
        {"pomodoroTimer", QVariant::fromValue(pt)},
        {"settingsManager", QVariant::fromValue(settingsManager)},
        {"pomodoroStats", QVariant::fromValue(&pomodoroStats)},
        { "appVersion", QGuiApplication::applicationVersion()}
    });

    engine.loadFromModule("Paz", "Main");

    return QGuiApplication::exec();
}