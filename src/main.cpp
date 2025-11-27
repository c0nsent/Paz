#include <QtWidgets>

#include "backend/pomodoro-timer/phase-manager.hpp"
#include "backend/pomodoro-timer/timer-engine.hpp"

#include <QDebug>

constexpr bool timerTest{ false };

using namespace paz::backend::pt;

int timerTestFunction( int argc, char *argv[] )
{

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
  PhaseManager aboba{PhaseManager::Phase::Work, 25, 5, 15};
	QObject::connect(&aboba, &PhaseManager::phaseChanged, []() { qInfo() << "phase changed";});

	aboba.setCurrentPhase(PhaseManager::Phase::LongBreak);

	return QApplication::exec();
}

int main(int argc, char *argv[])
{
	timerTestFunction( argc, argv );

	//pomodoroPhaseTestFunction( argc, argv );
}