/**
 * @date 11/27/25
 * 
 * @author amitayus_
 */

#pragma once

#include <cstdint> //Работает и без инклюда, но все равно добавил для большей ясности
#include <QObject>
#include <../core/constants.cpp>


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
			quint16 workInSec,
			quint16 shortBreakInSec,
			quint16 longBreakInSec,
			QObject *parent = nullptr
		);

		[[nodiscard]] Phase currentPhase() const;
		[[nodiscard]] quint16 currentPhaseDuration() const;
		[[nodiscard]] quint16 phaseDuration(Phase rhs) const;

	public slots:

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, quint16 phaseDuration);
		void setPhaseDuration(quint16 work, quint16 shortBreak, quint16 longBreak);

	signals: //Возможно стоит добавить еще сигналов в будущем

		void phaseChanged();
		void phaseDurationChanged();

		void workDurationChanged();
		void shortBreakDurationChanged();
		void longBreakDurationChanged();

	private:

		Phase m_currentPhase;
		quint16 m_arrPhaseDurations[c_phaseCount]; // 32767 секунд или 546 минут должно быть достаточно
	};

	using Phase = PhaseManager::Phase; /// Чтобы можно было по-нормальному обращаться к `enum class`
}
