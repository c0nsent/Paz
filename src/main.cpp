#include "impl/pomodoro-calculator.hpp"
#include "impl/pomodoro-timer.hpp"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
//#include <QQmlContext>
#include <QString>
#include <QObject>

#include <cstdlib>


class Dummy : public QObject
{
    Q_OBJECT
};

auto processCliInput(char **argv)
{
    impl::PomodoroCalculator calculator;
    qInfo() << calculator.calculate(QString{argv[1]}.toUShort());
}

int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        processCliInput(argv);
        return EXIT_SUCCESS;
    }
    if (argc > 2)
    {
        qWarning() << "Too many arguments. Usage: Paz [repeatCount]";
        return EXIT_FAILURE;
    }

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("amitayus_");
    QGuiApplication::setApplicationName("Paz");

    //qmlRegisterType<impl::PomodoroTimer>("PazQml", 1, 0, "PomodoroTimer");

    QQmlApplicationEngine engine;
    engine.loadFromModule("PazQml", "Main");
    if (engine.rootObjects().isEmpty())
    {
        qWarning() << "Paz couldn't load module";
        return EXIT_FAILURE;
    }

    return QGuiApplication::exec();
}