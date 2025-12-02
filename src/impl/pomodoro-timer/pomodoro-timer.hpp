/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#pragma once

#include "phase-manager.hpp"
#include "timer-engine.hpp"

#include <QObject>

#include <chrono>

///TODO Задумайся об удаление namespace pt. Возможно стоит перенести все в paz::impl
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
			Phase phase,
			std::chrono::seconds work,
			std::chrono::seconds shortBreak,
			std::chrono::seconds longBreak,
			QObject* parent = nullptr
		);

		[[nodiscard]] bool isPaused() const;

		[[nodiscard]] quint16 roundCount() const;
		[[nodiscard]] quint16 roundLength() const;

		[[nodiscard]] Phase currentPhase() const;
		[[nodiscard]] auto currentPhaseDuration() const -> std::chrono::seconds;
		[[nodiscard]] auto phaseDuration(Phase phase) const -> std::chrono::seconds;

		[[nodiscard]] auto timeLeft() const -> std::chrono::seconds;

	public slots:

		void setIsPaused(bool isPaused);

		void setRoundCount(quint16 roundCount);
		void setRoundLength(quint16 roundLength);

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, std::chrono::seconds phaseDuration);

		void start();
		void stop();
		void resetAndStop();

		void skipPhase();

	private slots:

		void handleIsPausedChanged();

		void handleTimerEngineTicked();
		void handleTimerEngineFinished();

	signals:

		void isPausedChanged();

		void timerTicked();
		void timerFinished();
		void timerStarted();
		void timerStopped();

		void phaseChanged();
		void phaseDurationChanged();

		void roundFinished();
		void roundCountChanged();
		void roundLengthChanged();

	private:

		bool m_isPaused;

		quint16 m_roundCount;
		quint16 m_roundLength;

		TimerEngine m_timerEngine;
		PhaseManager m_phaseManager;
	};
}