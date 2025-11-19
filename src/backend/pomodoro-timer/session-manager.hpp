/**
 * @date 11/19/25
 * 
 * @author amitayus_
 */

#pragma once

#include "timer-engine.hpp"
#include "timer-phase.hpp"

#include <QObject>


namespace paz::backend::pomodoro
{
	class SessionManager final : public QObject
	{
		Q_OBJECT

		struct SessionTime
		{
			quint16 work;
			quint16 shortBreak;
			quint16 longBreak;
		};

	public:

		explicit SessionManager( QObject* parent = nullptr );

		bool isActive() const;
		quint16 getWorkTime() const;
		quint16 getShortBreakTime() const;
		quint16 getLongBreakTime() const;
		quint16 getPomodoroCount() const;
		quint16 getPomodorosTillLongBreak() const;
		quint16 getSessionDurationInPomodoros() const;
		quint64 getTotalTimeInSeconds() const;
		TimerPhase::Phase getTimerPhase() const;

		SessionManager &setWorkTime( quint16 workTime );
		SessionManager &setShortBreakTime( quint16 shortBreakTime );
		SessionManager &setLongBreakTime( quint16 longBreakTime );
		SessionManager &setPomodoroCount( quint16 pomodoroCount );
		SessionManager &setPomodorosTillLongBreak( quint16 pomodorosTillLongBreak );
		SessionManager &setSessionDurationInPomodoros( quint16 sessionDurationInPomodoros );

	public slots:

	private slots:

	signals:

		void sessionStarted();

		void phaseChanged();


	private:

		bool m_isActive{ false };

		quint16 m_workTime{ 25 };
		quint16 m_shortBreakTime{ 5 };
		quint16 m_longBreakTime{ 45 };

		quint16 m_pomodoroCount{ 0 };
		quint16 m_pomodorosTillLongBreak{ 6 };
		quint16 m_sessionDurationInPomodoros{ 6 };

		quint64 m_totalTimeInSeconds{ 0 };

		TimerEngine m_timerEngine;
		TimerPhase m_timerPhase{ TimerPhase::Phase::paused };
	};
}