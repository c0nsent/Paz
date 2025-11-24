#include <QtWidgets>

#include "backend/pomodoro-timer/pomodoro-phase.hpp"
#include "backend/pomodoro-timer/timer-engine.hpp"
#include <QDebug>

void test(paz::backend::pt::TimerEngine &engine)
{
	qInfo() << "timer finished";

	//engine.;
}

int main(int argc, char *argv[])
{
	QApplication app{argc, argv};
	using namespace paz::backend::pt;
	TimerEngine engine(25);

	auto startNewTimer = [&engine]()
	{
		qInfo() << "Timer finished";
		engine.start(3);

		qInfo() << "Timer started";
	};
	engine.start(3);
	QObject::connect( &engine, &TimerEngine::timerTicked, []() { qInfo() <<  "tick";});
	QObject::connect( &engine, &TimerEngine::timerFinished, startNewTimer);

	return app.exec();
}