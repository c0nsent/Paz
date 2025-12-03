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

//TODO Задумайся об удаление namespace pt. Возможно стоит перенести все в paz::impl
namespace paz::impl::pt
{
	//TODO Возможно стоит PomodoroPhase интегрировать в PomodoroTimer

	/**
	 * @brief Класс, реализующий логику помодоро-таймера.
	 *
	 * @details Автоматически переключает фазы, считает раунды и управляет состоянием паузы.
	 *					Все свои изменения передает через сигналы.
	 */

	class PomodoroTimer final : public QObject
	{
		Q_OBJECT

		/**
		 * @brief Настраивает все необходимые соединения сигналов и слотов между
		 *					внутренними компонентами класса.
		 */

		void setupSignalsReemitting();
		void setupIntelConnections();
		void debugOutput() const;

	public:

		/**
		 * @brief Конструктор класса PomodoroTimer.
		 *
		 * @details Инициализирует внутренние компоненты класса и настраивает соединения сигналов и слотов,
		 *					вызовом функции `setupConnections()`.
		 *
		 * @param roundCount Количество завершенных помидорок в текущем раунде.
		 * @param roundLength Количество помидорок в одном раунде.
		 * @param phase Фаза, с которой начинается таймер.
		 * @param work Продолжительность рабочей фазы.
		 * @param shortBreak Продолжительность короткого перерыва.
		 * @param longBreak Продолжительность длинного перерыва.
		 * @param parent Указатель на родительский QObject.
		 */
		PomodoroTimer(
			quint16 roundCount,
			quint16 roundLength,
			Phase phase,
			std::chrono::seconds work,
			std::chrono::seconds shortBreak,
			std::chrono::seconds longBreak,
			QObject* parent = nullptr
		);

		/**
		 * @brief Геттер для получения состояния паузы таймера.
		 *
		 * @return Возвращает `paused`.
		 */
		[[nodiscard]] bool isActive() const;

		/**
		 * @brief Геттер для получения количества помидорок в текущем раунде.
		 *
		 * @return Возвращает m_roundCount.
		 */

		[[nodiscard]] quint16 roundCount() const;

		/**
		 * @brief Геттер для получения количества помидорок в одном раунде.
		 *
		 * @return Возвращает m_roundLength.
		 */

		[[nodiscard]] quint16 roundLength() const;

		/**
		 * @brief Геттер для получения текущей фазы таймера.
		 *
		 * @return Возвращает `m_phaseManager.currentPhase()`.
		 */
		[[nodiscard]] Phase currentPhase() const;

		/**
		 * @brief Геттер для получения длительности текущей фазы.
		 *
		 * @return Возвращает `m_phaseManager.currentPhaseDuration()`.
		 */

		[[nodiscard]] auto currentPhaseDuration() const -> std::chrono::seconds;

		/**
		 * @brief Геттер для получения длительности указанной фазы.
		 *
		 * @param phase Фаза, длительность которой нужно получить.
		 *
		 * @return Возвращает `m_phaseManager.phaseDuration(phase)`.
		 */
		[[nodiscard]] auto phaseDuration(Phase phase) const -> std::chrono::seconds;

		/**
		 * @brief Геттер для получения оставшегося времени таймера.
		 *
		 * @return Возвращает `m_timerEngine.timeLeft()`.
		 */

		[[nodiscard]] auto timeLeft() const -> std::chrono::seconds;

	public slots:

		void setRoundCount(quint16 roundCount);
		void setRoundLength(quint16 roundLength);

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, std::chrono::seconds phaseDuration);

		void start();
		void stop();
		void resetAndStop();

		void skipPhase();

	private slots:

		void handleTimerFinished();

	signals:

		void ticked(std::chrono::seconds);
		void timeout();
		void started();
		void stopped();

		void phaseChanged(Phase);
		void phaseDurationChanged(Phase phase, std::chrono::seconds phaseDuration);

		void roundFinished(quint16 roundCount, std::chrono::seconds phaseDuration);
		void roundCountChanged(quint16);
		void roundLengthChanged(quint16);

	private:

		bool m_active;

		quint16 m_roundCount;
		quint16 m_roundLength;

		TimerEngine m_timerEngine;
		PhaseManager m_phaseManager;
	};
}