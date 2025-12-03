/**
 * @date 11/27/25
 * 
 * @author amitayus_
 */

#pragma once


#include "../../core/constants.hpp"

#include <QObject>

#include <chrono>


namespace paz::impl::pt
{
	/**
	 * @brief Менеджер фаз помодоро-таймера.
	 *
	 * @details Хранит текущую фазу и длительности всех фаз в массиве.
	 *
	 * @note Класс довольно простой, стоит задуматься об объединении его с PomodoroTimer.
	 */

	class PhaseManager final : public QObject
	{
		Q_OBJECT

	public:

		enum class Phase : quint8 {Work, ShortBreak, LongBreak};
		Q_ENUM(Phase) // Для поддержки инфраструктуры Qt (например, в QML)

		PhaseManager(
			Phase phase,
			std::chrono::seconds work,
			std::chrono::seconds shortBreak,
			std::chrono::seconds longBreak,
			QObject *parent = nullptr
		);

		/**
		 * @brief Геттер для получения текущей фазы.
		 *
		 * @return Текущая фаза в виде `PhaseManager::Phase`.
		 */

		[[nodiscard]] Phase currentPhase() const;

		/**
		 * @brief Геттер для получения длительности текущей фазы.
		 *
		 * @return Длительность текущей фазы в `std::chrono::seconds`.
		 */

		[[nodiscard]] auto currentPhaseDuration() const -> std::chrono::seconds;

		/**
		 * @brief Геттер для получения длительности указанной фазы.
		 *
		 * @param phase Фаза, длительность которой нужно получить.
		 *
		 * @return Длительность указанной фазы в `std::chrono::seconds`.
		 */

		[[nodiscard]] auto phaseDuration(Phase phase) const -> std::chrono::seconds;

	public slots:

		/**
		 * @brief Сеттер для установки текущей фазы.
		 *
		 * @details При изменении фазы испускается сигнал `phaseChanged()`.
		 *
		 * @param phase Фаза, которую нужно установить.
		 */

		void setCurrentPhase(Phase phase);

		/**
		 * @brief Сеттер для установки длительности указанной фазы.
		 *
		 * @details При изменении длительности фазы испускается сигнал phaseDurationChanged().
		 *
		 * @param phase Фаза, длительность которой нужно установить.
		 * @param phaseDuration передаваемая длительность в std::chrono::seconds.
		 */

		void setPhaseDuration(Phase phase, std::chrono::seconds phaseDuration);

	signals:

		/**
		 * @brief Сигнал, испускаемый при изменении текущей фазы.
		 *
		 * @param currentPhase Новая текущая фаза в виде `PhaseManager::Phase`.
		 *
		 * @details Сигнал испускается при изменении текущей фазы в `setCurrentPhase()`.
		 */

		void phaseChanged(Phase currentPhase);

		/**
		 * @brief Сигнал, испускаемый при изменении длительности указанной фазы.
		 *
		 * @details Сигнал испускается при изменении длительности фазы в `setPhaseDuration()`.
		 */

		void phaseDurationChanged(Phase, std::chrono::seconds);

	private:

		Phase m_currentPhase; /// Текущая фаза помодоро-таймера.
		std::chrono::seconds m_arrPhaseDurations[defaults::c_phaseCount]; /// Массив длительностей фаз.
	};

	using Phase = PhaseManager::Phase; /// Удобный алиас для `PhaseManager::Phase`.
}
