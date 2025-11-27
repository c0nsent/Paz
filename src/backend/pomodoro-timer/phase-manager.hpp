/**
 * @date 11/27/25
 * 
 * @author amitayus_
 */

#pragma once

#include <cstdint>
#include <QObject>

namespace paz::backend::pt
{
	class PhaseManager final : public QObject
	{
		Q_OBJECT

	public:

		static constexpr std::size_t c_phase{3}; /// TODO: Удалить если будет не нужен

		enum class Phase : uint8_t {Work, ShortBreak, LongBreak};
		Q_ENUM(Phase)

		PhaseManager(
			Phase phase,
			qint16 workInSec,
			qint16 shortBreakInSec,
			qint16 longBreakInSec,
			QObject *parent = nullptr
		);

		[[nodiscard]] Phase currentPhase() const;
		[[nodiscard]] qint16 phaseDuration(Phase rhs) const;

	public slots:

		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, qint16 phaseDuration);
		void setPhaseDuration(qint16 work, qint16 shortBreak, qint16 longBreak);

	signals: ///Возможно стоит добавить еще сигналов в будущем

		void phaseChanged();
		void phaseDurationChanged();

		void workDurationChanged();
		void shortBreakDurationChanged();
		void longBreakDurationChanged();

	private:

		Phase m_currentPhase;
		qint16 m_arrPhaseDurations[c_phase];
	};

	using Phase = PhaseManager::Phase; /// Чтобы можно было по-нормальному обращаться к `enum class`
}
