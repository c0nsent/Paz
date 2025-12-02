/**
 * @date 11/24/25
 * 
 * @author amitayus_
 */

#pragma once

#include "phase-manager.hpp"
#include "timer-engine.hpp"

#include <chrono>

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
			Phase phase,
			std::chrono::seconds work,
			std::chrono::seconds shortBreak,
			std::chrono::seconds longBreak,
			QObject* parent = nullptr
		);

		[[nodiscard]] bool isPaused() const;

		[[nodiscard]] quint16 roundCount() const;
		[[nodiscard]] quint16 roundLength() const;
		[[nodiscard]] quint16 inTotal() const;

		[[nodiscard]] Phase currentPhase() const;
		[[nodiscard]] auto currentPhaseDuration() const -> std::chrono::seconds;
		[[nodiscard]] auto phaseDuration(Phase phase) const -> std::chrono::seconds;

		[[nodiscard]] auto timeLeft() const -> std::chrono::seconds;



	public slots:

		void setIsPaused(bool isPaused);

		void setRoundCount(quint16 roundCount);
		void setRoundLength(quint16 roundLength);
		void setInTotal(quint16 inTotal);

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, std::chrono::seconds phaseDuration);

		/**
		 * @brief Устанавливает длительности всех фаз сразу
		 * @note Возможно стоит удалить этот метод, т.к. он не особо нужен
		 * @param work Длительность рабочей фазы
		 * @param shortBreak Длительность короткого перерыва
		 * @param longBreak Длительность длинного перерыва
		 */
		[[deprecated]] void setPhaseDuration(std::chrono::seconds work, std::chrono::seconds shortBreak, std::chrono::seconds longBreak);


		void start();
		//void start(quint16 startTime);
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