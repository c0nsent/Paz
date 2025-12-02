/**
 * @date 11/27/25
 * 
 * @author amitayus_
 */

#pragma once

#include <../core/constants.hpp>

#include <QObject>

#include <chrono>


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
		[[nodiscard]] auto currentPhaseDuration() const -> std::chrono::seconds;
		[[nodiscard]] auto phaseDuration(Phase phase) const -> std::chrono::seconds;

	public slots:

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, std::chrono::seconds phaseDuration);

	signals:

		void phaseChanged();
		void phaseDurationChanged();

		///TODO Удали если не понадобится
		void workDurationChanged();
		void shortBreakDurationChanged();
		void longBreakDurationChanged();

	private:

		Phase m_currentPhase;
		std::chrono::seconds m_arrPhaseDurations[defaults::c_phaseCount];
	};

	using Phase = PhaseManager::Phase; /// Чтобы можно было по-нормальному обращаться к `enum class`
}
