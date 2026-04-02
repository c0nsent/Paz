#include "impl/pomodoro-calculator.hpp"
#include "ui/pomodoro-timer-widget.hpp"

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QString>


int main(int argc, char *argv[])
{
    if (argc == 2)
    {
        impl::PomodoroCalculator calculator;
        qInfo() << calculator.calculate(QString{argv[1]}.toUShort());

        return 0;
    }

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    engine.loadFromModule("PazQml", "Main");
    if (engine.rootObjects().isEmpty())
    {
        qWarning() << "Paz couldn't load module";
        return -1;
    }

    return QApplication::exec();
}