#include "core/basic-types-aliases.hpp"
#include "impl/pomodoro-timer.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>
#include <QVariant>

#include "settings-manager.hpp"
#include "pomodoro-stats.hpp"


int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    impl::PomodoroStats stats;

    stats.addPomodoro(std::chrono::seconds{10}, QDate{2021, 1, 1});
    stats.addPomodoro(std::chrono::seconds{10}, QDate{2021, 1, 2});
    stats.addPomodoro(std::chrono::seconds{10}, QDate{2021, 1, 3});
    stats.addPomodoro(std::chrono::seconds{60}, QDate{2021, 1, 1});
    stats.sync();


    QGuiApplication::setOrganizationName("amitayus_");
    QGuiApplication::setApplicationName("Paz");
    QGuiApplication::setApplicationVersion(APP_VERSION);

    QSystemTrayIcon trayIcon;
    trayIcon.show();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
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
            using enum impl::PomodoroTimer::Phase;

            QString message{ currentPhase == Work ? "It is time to be productive" : "You can chill a bit"};
            trayIcon.showMessage("Time is out", message, QSystemTrayIcon::NoIcon);
        }
    );

    engine.setInitialProperties({
        {"pomodoroTimer", QVariant::fromValue(pt)},
        {"settingsManager", QVariant::fromValue(settingsManager)},
        { "appVersion", QGuiApplication::applicationVersion()}
    });

    engine.loadFromModule("Paz", "Main");

    return QGuiApplication::exec();
}