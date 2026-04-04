#include "impl/pomodoro-calculator.hpp"

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QString>

void processCliInput(const int argc, char **argv)
{
    if (argc != 2)  return;

    impl::PomodoroCalculator calculator;
    qInfo() << calculator.calculate(QString{argv[1]}.toUShort());
}

int main(int argc, char *argv[])
{
    processCliInput(argc, argv);

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