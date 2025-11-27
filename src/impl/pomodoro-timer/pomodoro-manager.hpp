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

		PomodoroManager(
			quint16 m_pomodorosInRound,
			const TimerEngine &timerEngine,
			const PhaseManager &phase,
			QObject* parent = nullptr
		);

		[[nodiscard]] bool isPaused() const;

		[[nodiscard]] quint16 pomodorosTillRoundEnd() const;
		[[nodiscard]] quint16 pomodorosInRound() const;
		[[nodiscard]] quint16 pomodorosInTotal() const;

		[[nodiscard]] quint16 currentPhase() const;
		[[nodiscard]] quint16 currentPhaseDuration() const;
		[[nodiscard]] quint16 phaseDuration(Phase phase) const;

		[[nodiscard]] quint16 timeLeft() const;



	public slots:

		void start();
		void start(quint16 startTime);
		void stop();
		void resetAndStop();

		void skipToNextPhase();

	private slots:

	signals:

		void timerTicked();
		void timerFinished();
		void timerStarted();
		void timerStopped();

		void phaseChanged();
		void phaseDurationChanged();

		void roundFinished();
		void pomodorosInRoundChanged();
		void pomodorosTillRoundEndChanged();
		void pomodorosInTotalChanged();

	private:

		bool m_isPaused;

		quint16 m_pomodorosTillRoundEnd;
		quint16 m_pomodorosInRound;
		quint16 m_pomodorosInTotal;//Максимально количество помидорок за один день

		TimerEngine m_timerEngine;
		PhaseManager m_phase;
	};
}