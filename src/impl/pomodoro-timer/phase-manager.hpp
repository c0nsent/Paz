/**
 * @date 11/27/25
 * 
 * @author amitayus_
 */

#pragma once

#include <../core/constants.cpp>

#include <QObject>

#include <chrono>
#include <cstdint> //Работает и без инклюда, но все равно добавил для большей ясности



namespace paz::impl::pt
{
	class PhaseManager final : public QObject
	{
		Q_OBJECT

	public:

		enum class Phase : quint8 {Work, ShortBreak, LongBreak};
		Q_ENUM(Phase)

		PhaseManager(
			Phase phase,
			std::chrono::seconds work,
			std::chrono::seconds shortBreak,
			std::chrono::seconds longBreak,
			QObject *parent = nullptr
		);

		[[nodiscard]] Phase currentPhase() const;
		[[nodiscard]] std::chrono::seconds currentPhaseDuration() const;
		[[nodiscard]] std::chrono::seconds phaseDuration(Phase phase) const;

	public slots:

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, std::chrono::seconds phaseDuration);
		void setPhaseDuration(std::chrono::seconds work, std::chrono::seconds shortBreak, std::chrono::seconds longBreak);

	signals: //Возможно стоит добавить еще сигналов в будущем

		void phaseChanged();
		void phaseDurationChanged();

		void workDurationChanged();
		void shortBreakDurationChanged();
		void longBreakDurationChanged();

	private:

		Phase m_currentPhase;
		std::chrono::seconds m_arrPhaseDurations[c_phaseCount]; // 32767 секунд или 546 минут должно быть достаточно
	};

	using Phase = PhaseManager::Phase; /// Чтобы можно было по-нормальному обращаться к `enum class`
}
