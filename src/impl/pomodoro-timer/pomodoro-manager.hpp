/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#pragma once

#include "phase-manager.hpp"
#include "timer-engine.hpp"

namespace paz::impl::pt
{
	class PomodoroManager final : public QObject
	{
		Q_OBJECT

	public:

		static constexpr qint16 INVALID_POMODORO_COUNT{-1};

		//PomodoroManager(QObject* parent = nullptr);

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

		bool m_isPaused;

		qint16 m_pomodorosInRound;
		qint16 m_pomodorosTillRoundEnd;
		qint16 m_pomodoroInCurrentSession;

		TimerEngine m_timerEngine;
		PhaseManager m_phase;
	};
}