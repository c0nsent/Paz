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
	///TODO Возможно стоит PomodoroPhase интегрировать в PomodoroTimer
	class PomodoroTimer final : public QObject
	{
		Q_OBJECT

		void setupConnections();

	public:

		PomodoroTimer(
			bool isPaused,
			quint16 roundCount,
			quint16 roundLength,
			quint16 inTotal,
			quint16 startTime,
			quint16 timeLeft,
			Phase phase,
			quint16 workInSec,
			quint16 shortBreakInSec,
			quint16 longBreakInSec,
			QObject* parent = nullptr
		);

		[[nodiscard]] bool isPaused() const;

		[[nodiscard]] quint16 roundCount() const;
		[[nodiscard]] quint16 roundLength() const;
		[[nodiscard]] quint16 inTotal() const;

		[[nodiscard]] Phase currentPhase() const;
		[[nodiscard]] quint16 currentPhaseDuration() const;
		[[nodiscard]] quint16 phaseDuration(Phase phase) const;

		[[nodiscard]] quint16 timeLeft() const;



	public slots:

		void setRoundCount(quint16 roundCount);
		void setRoundLength(quint16 roundLength);
		void setInTotal(quint16 inTotal);

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, quint16 phaseDuration);
		void setPhaseDuration(quint16 work, quint16 shortBreak, quint16 longBreak);


		void start();
		//void start(quint16 startTime);
		void stop();
		void resetAndStop();

		void skipPhase();

	private slots:

		void handleTimerEngineTicked();
		void handleTimerEngineFinished();

	signals:

		void timerTicked();
		void timerFinished();
		void timerStarted();
		void timerStopped();

		void phaseChanged();
		void phaseDurationChanged();

		void roundFinished();
		void roundCountChanged();
		void roundLengthChanged();
		void inTotalChanged();

	private:

		bool m_isPaused;

		quint16 m_roundCount;
		quint16 m_roundLength;
		quint16 m_inTotal;//Максимально количество помидорок за один день

		TimerEngine m_timerEngine;
		PhaseManager m_phaseManager;
	};
}