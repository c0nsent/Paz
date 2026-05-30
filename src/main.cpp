#include "impl/pomodoro-calculator.hpp"
#include "impl/test.hpp"

#include <QGuiApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QString>
#include <QQuickView>

void processCliInput(const int argc, char **argv)
{
    if (argc != 2)  return;

    impl::PomodoroCalculator calculator;
    qInfo() << calculator.calculate(QString{argv[1]}.toUShort());
}

int main(int argc, char *argv[])
{
    processCliInput(argc, argv);

    QGuiApplication app(argc, argv);
    QGuiApplication::setOrganizationName("amitayus_");
    QGuiApplication::setApplicationName("Paz");

    QQuickView view;
    paz::impl::Test test;
    view.setInitialProperties({{"test", &test}});

    /*
    QQmlApplicationEngine engine;
    engine.loadFromModule("PazQml", "Main");
    if (engine.rootObjects().isEmpty())
    {
        qWarning() << "Paz couldn't load module";
        return -1;
    }*/

    return QGuiApplication::exec();
}