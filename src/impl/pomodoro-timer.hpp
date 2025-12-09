/**
 * @date 12/4/25
 * 
 * @author amitayus_
 */

#pragma once


#include "../core/constants.hpp"

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

		[[nodiscard]] bool isActive() const;

		[[nodiscard]] State state() const;
		[[nodiscard]] Phase phase() const;
		[[nodiscard]] quint16 phaseDuration() const;
		[[nodiscard]] quint16 phaseDuration(Phase phase) const;
		[[nodiscard]] quint16 sessionLength() const;
		[[nodiscard]] quint16 remainingTime() const;
		[[nodiscard]] quint16 currentSessionCount() const;

	public slots:

		void start();
		void start(quint16 seconds, Phase phase);
		void pause();
		void reset();
		void toNextPhase();

		void setPhaseDuration(Phase phase, quint16 seconds);
		void setAllPhaseDurations(
			quint16 workSec,
			quint16 shortBreakSec,
			quint16 longBreakSec
		);
		void setSessionLength(quint16 pomodoros);

	private slots:

		void handleQTimerTimeout();
		
	signals:

		void timerStateChanged(State);
		void phaseChanged(Phase);
		void phaseDurationChanged(Phase, quint16);
		void sessionLengthChanged(quint16);
		void remainingTimeChanged(quint16);
		void pomodoroFinished(quint16 currentSessionCount);
	
	private:

		State m_state;
		Phase m_phase;
		quint16 m_phaseDurations[defaults::c_phaseCount];
		quint16 m_sessionLength;

		quint16 m_remainingTime;
		quint16 m_currentSessionCount;

		QTimer m_timer;
};
}
