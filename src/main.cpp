#include "impl/pomodoro-timer.hpp"
#include "ui/pomodoro-timer/pomodoro-timer-widget.hpp"

#include <QApplication>
#include <QDebug>
#include <QSettings>
#include <QTranslator>

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	/*QTranslator qtTranslator;
	Q_UNUSED(qtTranslator.load("Paz_en"));
	app.installTranslator(&qtTranslator);*/


	ui::PomodoroTimerWidget pomodoroTimerWidget;
	pomodoroTimerWidget.show();
	return QApplication::exec();
}