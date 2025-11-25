#include <QtWidgets>

#include "backend/pomodoro-timer/pomodoro-phase.hpp"
#include "backend/pomodoro-timer/timer-engine.hpp"

#include <QDebug>

constexpr bool timerTest{ true };



int timerTestFunction( int argc, char *argv[] )
{
	using namespace paz::backend::pt;
	QApplication app{argc, argv};

	paz::backend::pt::TimerEngine engine(25);

	auto startNewTimer = [&engine]()
	{
		qInfo() << "Timer finished";
		engine.start(3);

		qInfo() << "Timer started";
	};

	engine.start(3);
	QObject::connect( &engine, &TimerEngine::timerTicked, []() { qInfo() <<  "tick";});
	QObject::connect( &engine, &TimerEngine::timerFinished, startNewTimer);

	return QApplication::exec();
}

int pomodoroPhaseTestFunction( int argc, char *argv[] )
{
	QApplication app{argc, argv};
  PomodoroPhase aboba{PomodoroPhase::Phs::Work, 25, 5, 15};
	QObject::connect(aboba, &PomodoroPhase::phaseChanged, []() { qInfo() << "phase changed";});

	aboba.setCurrentPhase(PomodoroPhase::Phs::LongBreak);

	return QApplication::exec();
}

int main(int argc, char *argv[])
{
	//timerTestFunction( argc, argv );

	pomodoroPhaseTestFunction( argc, argv );
}