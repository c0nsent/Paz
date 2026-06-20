#include "core/basic-types-aliases.hpp"
#include "impl/pomodoro-timer.hpp"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSystemTrayIcon>
#include <QVariant>


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
    pt->writeSettings();

    QObject::connect(pt, &impl::PomodoroTimer::timeIsOut, &trayIcon, [&]
    {
        QString message{ pt->phase() == impl::PomodoroTimer::Phase::Work ? "It is time to be productive" : "You can chill a bit"};
        trayIcon.showMessage("Time is out", message, QSystemTrayIcon::NoIcon);
    });

    engine.setInitialProperties({{"pomodoroTimer", QVariant::fromValue(pt)}});

    engine.loadFromModule("Paz.PomodoroTimer", "Main");

    return QGuiApplication::exec();
}