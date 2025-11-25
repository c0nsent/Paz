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
	class PomodoroPhase final : public QObject
	{
		Q_OBJECT
		//Q_PROPERTY(Phs currentPhase READ getCurrentPhase WRITE setCurrentPhase NOTIFY phaseChanged)
	public:

		enum class Phs : quint8 { Work, ShortBreak, LongBreak};
		Q_ENUM(Phs)

		static constexpr quint8 c_phaseCount{ 3 };
		//static constexpr qint16 c_invalidDuration{ -1 };

		PomodoroPhase(Phs phase,
			qint16 workInSecs, qint16 shortBreakInSecs, qint16 longBreakInSecs, QObject *parent = nullptr);

		[[nodiscard]] Phs getCurrentPhase() const;
		[[nodiscard]] quint16 getCurrentPhaseDuration() const;
		[[nodiscard]] quint16 getPhaseDuration(Phs obj) const;

	public slots:

		void setCurrentPhase(Phs phase);
		void setPhaseDuration(Phs phase, qint16 seconds);
		void setPhaseDuration(qint16 work, qint16 shortBreak, qint16 longBreak);

	signals:

		void phaseChanged();
		void phaseDurationChanged();
		void workDurationChanged();
		void shortBreakDurationChanged();
		void longBreakDurationChanged();

	private:

		Phs m_currentPhase;
		qint16 m_phasesDuration[c_phaseCount];
	};
}
