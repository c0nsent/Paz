/**
 * @date 11/16/25
 * 
 * @author amitayus_
 *
 * @brief  Обвертка над enum для поддержки Q_ENUM
 */

#pragma once

#include <QObject>

namespace paz::backend::pt
{
	class State final : public QObject
	{
		Q_OBJECT
		//Q_PROPERTY(Phs curPhase READ getCurPhase WRITE setCurPhase NOTIFY phaseChanged)
	public:

		enum class Phase : quint8 {Work, ShortBreak, LongBreak};
		Q_ENUM(Phase)

		static constexpr quint8 c_phaseCount{ 3 };
		//static constexpr qint16 c_invalidDuration{ -1 };

		State(
			bool isPaused ,
			Phase phase,
			qint16 workInSecs,
			qint16 shortBreakInSecs,
			qint16 longBreakInSecs,
			QObject *parent = nullptr
		);

		[[nodiscard]] bool isPaused () const;
		[[nodiscard]] Phase currentPhase() const;
		[[nodiscard]] quint16 currentPhaseDuration() const;
		[[nodiscard]] quint16 phaseDuration(Phase obj) const;

	public slots:

		void setIsPaused(bool paused);
		void setCurrentPhase(Phase phase);
		void setPhaseDuration(Phase phase, qint16 seconds);
		void setPhaseDuration(qint16 work, qint16 shortBreak, qint16 longBreak);

	signals:

		void isPausedChanged();
		void phaseChanged();
		void phaseDurationChanged();
		void workDurationChanged();
		void shortBreakDurationChanged();
		void longBreakDurationChanged();

	private:

		bool m_isPaused;
		Phase m_currentPhase;
		qint16 m_phasesDuration[c_phaseCount];
	};
	using Phase = State::Phase;
}
