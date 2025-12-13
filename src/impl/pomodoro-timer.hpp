/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#pragma once


#include "../core/constants.hpp"

#include "afk-timer.hpp"

#include <QObject>
#include <QTimer>


namespace impl
{
	class PomodoroTimer final : public QObject
	{
		Q_OBJECT

		static constexpr quint16 c_timeIsOut{0};

	public:

		enum class Phase : quint8 { Work, ShortBreak, LongBreak };
		Q_ENUM(Phase)

		enum class State : quint8 { Idle, Running, Paused };
		Q_ENUM(State)

		explicit PomodoroTimer(QObject *parent = nullptr);

		[[nodiscard]] State state() const;
		[[nodiscard]] Phase phase() const;
		[[nodiscard]] quint16 phaseDuration() const;
		[[nodiscard]] quint16 phaseDuration(Phase phase) const;
		[[nodiscard]] quint16 sessionLength() const;
		[[nodiscard]] quint16 remainingTime() const;
		[[nodiscard]] quint16 currentSessionCount() const;

	public slots:

		void start();
		void start(Phase phase);
		void start(Phase phase, quint16 seconds);
		void pause();
		void reset();
		void toNextPhase();

		void setPhaseDuration(quint16 seconds);
		void setPhaseDuration(quint16 seconds, Phase phase);
		void setPhaseDuration(
			quint16 workSec,
			quint16 shortBreakSec,
			quint16 longBreakSec
		);
		void setSessionLength(quint16 pomodoros);

	private slots:

		void updateRemainingTime();

		bool trySetPhase(Phase phase);
		bool trySetRemainingTime(quint16 remainingTime);
		bool trySetState(State state);
		
	signals:

		void stateChanged(State);
		void phaseChanged(Phase);
		void phaseDurationChanged(quint16 seconds, Phase);
		void sessionLengthChanged(quint16 pomodoros);
		void remainingTimeChanged(quint16 seconds);
		void pomodoroFinished(quint16 currentSessionCount);
	
	private:

		State m_state{State::Idle};
		Phase m_phase{Phase::Work};
		quint16 m_phaseDurations[defaults::c_phaseCount]
		{
			defaults::c_workDuration, defaults::c_shortBreakDuration, defaults::c_longBreakDuration
		};
		quint16 m_sessionLength{defaults::c_sessionLength};

		quint16 m_remainingTime{defaults::c_workDuration};
		quint16 m_currentSessionCount{0};

		AfkTimer m_afkTimer;
		QTimer m_timer;
};
}
