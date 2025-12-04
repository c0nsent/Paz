#include "ui/main-window.hpp"
#include "impl/pomodoro-timer.hpp"

#include <QObject>
#include <QDebug>
#include <QApplication>


int main(int argc, char *argv[])
{
	QApplication app(argc, argv);

	/*paz::ui::MainWindow mainWindow;
	mainWindow.show();*/

	using namespace std::chrono_literals;
	using paz::impl::PomodoroTimer;

	PomodoroTimer timer{
		PomodoroTimer::Phase::Work,
		2s,
		1s,
		3s,
		2
	};

	auto *newTimer = new PomodoroTimer{};

	timer.start();

	//newTimer->start(2s);
	QObject::connect(&timer, &PomodoroTimer::finished, &timer, QOverload<>::of(&PomodoroTimer::start));

	QObject::connect(&timer, &PomodoroTimer::finished, [&timer]
	{
		qDebug() << "Ислам";
	});

	QObject::connect(&timer, &PomodoroTimer::phaseChanged, [](PomodoroTimer::Phase phase)
	{
		qDebug() << "Новая Фаза " << phase;
	});

	return QApplication::exec();
}