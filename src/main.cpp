#include "core/basic-types-aliases.hpp"
#include "impl/pomodoro-timer.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>
#include <QVariant>

#include "settings-manager.hpp"


int main(int argc, char *argv[])
{
    QGuiApplication app{argc, argv};

    QGuiApplication::setOrganizationName("amitayus_");
    QGuiApplication::setApplicationName("Paz");

    QSystemTrayIcon trayIcon;
    trayIcon.show();

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        [] { QCoreApplication::exit(-1); }
    );

    impl::PomodoroTimer::CreateInfo createInfo{
        .parent = &app,
        .workPhaseDuration = 5,
        .shortBreakDuration = 5,
        .longBreakDuration = 5,
        .sessionLength = 2,
    };

    auto *pt { new impl::PomodoroTimer{createInfo} };

    auto *settingsManager { new impl::SettingsManager{pt, &app}};


    /*settingsManager->readSettings(*pt);
    settingsManager->writeSettings(*pt);*/

    /*
     * Сначала отладь всю хуету с настройками
     */

    QObject::connect(&app, &QGuiApplication::applicationStateChanged, [&] (Qt::ApplicationState state)
    {
        auto metaState{ QMetaEnum::fromType<Qt::ApplicationState>() };

        qDebug() << metaState.valueToKey(state);
        if (state != Qt::ApplicationState::ApplicationSuspended) return;

        qDebug() << "Отработало";
        settingsManager->saveAllSettings();
    });

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
    });

    engine.loadFromModule("Paz.PomodoroTimer", "Main");

    return QGuiApplication::exec();
}