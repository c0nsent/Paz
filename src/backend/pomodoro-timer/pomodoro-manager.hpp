/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#pragma once

#include "timer-engine.hpp"
#include "pomodoro-phase.hpp"

namespace paz::backend::pt
{
	class PomodoroManager final : public QObject
	{
		Q_OBJECT

	public:

		explicit PomodoroManager(PomodoroPhase::Phs phase,
			qint16 workInSecs, qint16 shortBreakInSecs, qint16 longBreakInSecs,  QObject *parent = nullptr);


	public slots:

		/*
		void start();
		void start(qint16 seconds);
		void stop();
		void resetAndStop();

		void skipToNextPhase();
		*/

	private slots:



	signals:

		void timerTicked();
		void timerFinished();
		void timerStarted();
		void timerStopped();
		void timerWasReset();



		void phaseChanged();
		void roundFinished();


	private:

		TimerEngine m_timerEngine;
		PomodoroPhase m_phase;

		qint16 m_pomodorosInRound;
		qint16 m_pomodoroCount;
	};
}