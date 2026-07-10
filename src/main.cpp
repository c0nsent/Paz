#include "impl/pomodoro-stats.hpp"
#include "impl/pomodoro-timer.hpp"
#include "impl/settings-manager.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>
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

    QSystemTrayIcon trayIcon;
    trayIcon.show();

    QQmlApplicationEngine engine;
    QObject::connect( &engine, &QQmlApplicationEngine::objectCreationFailed,
        [] { QCoreApplication::exit(-1); }
    );

    auto *pt { new impl::PomodoroTimer{&app} };

    auto *settingsManager { new impl::SettingsManager{pt, &app}};
    settingsManager->readSettings(pt);

    QObject::connect(&app, &QGuiApplication::aboutToQuit, settingsManager, &impl::SettingsManager::saveAllSettings);

    QObject::connect(
        pt,
        &impl::PomodoroTimer::timerFinished,
        &trayIcon,
        [&trayIcon](const impl::PomodoroTimer::Phase currentPhase)
        {
            const QString message{ currentPhase == impl::PomodoroTimer::Phase::Work ?
                "It is time to be productive" : "You can chill a bit"};
            trayIcon.showMessage("Time is out", message, QSystemTrayIcon::NoIcon);
        }
    );

    /*QObject::connect(pt, &impl::PomodoroTimer::pomodoroFinished, [&]
    {
        stats.addPomodoro(std::chrono::seconds{pt->workDuration()});
    });*/
    //QObject::connect(&app, &QGuiApplication::aboutToQuit, &stats, &impl::PomodoroStats::sync);

    engine.setInitialProperties({
        {"pomodoroTimer", QVariant::fromValue(pt)},
        {"settingsManager", QVariant::fromValue(settingsManager)},
        //{"pomodoroStats", QVariant::fromValue(&stats)},
        { "appVersion", QGuiApplication::applicationVersion()}
    });

    engine.loadFromModule("Paz", "Main");

    return QGuiApplication::exec();
}