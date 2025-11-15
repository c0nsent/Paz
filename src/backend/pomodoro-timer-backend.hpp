/**
 * @date 11/14/25
 * 
 * @author amitayus_
 *
 * С интервалом в одну секунду m_timer инкрементирует currentTime
 */

#pragma once

#include <QObject>
#include <QTimer>
#include <QDebug>


namespace paz::backend
{
	class PomodoroTimerBackend : public QObject
	{
		Q_OBJECT

	public:

		enum class State : quint8 { work, shortBreak, longBreak, paused };

		PomodoroTimerBackend(quint16 workTime, quint16 shortBreakTime, quint16 longBreakTime, quint16 pomodorosInCycle, QObject* parent = nullptr);

		[[nodiscard]] quint16 getWorkTime() const;
		[[nodiscard]] quint16 getShortBreakTime() const;
		[[nodiscard]] quint16 getLongBreakTime() const;
		[[nodiscard]] quint16 getPomodorosInCycle() const;
		[[nodiscard]] quint16 getCurrentTime() const;
		[[nodiscard]] quint16 getCurrentCyclePomodoroCount() const;
		[[nodiscard]] State getState() const;

		void setWorkTime(quint16 workTime);
		void setShortBreakTime(quint16 shortBreakTime);
		void setLongBreakTime(quint16 longBreakTime);
		void setPomodorosInCycle(quint16 pomodorosInCycle);
		void setCurrentTime(quint16 currentTime);
		void setCurrentCyclePomodoroCount(quint16 currentCyclePomodoroCount);
		void setState(State state);

	public slots:

		void start();
		void stop();
		void resume();
		void pause();
		void reset();

	signals:

		void timerTicked();
		void timerFinished();

	private:

		QTimer m_timer{};

		quint16 m_workTime;
		quint16 m_shortBreakTime;
		quint16 m_longBreakTime;
		quint16 m_pomodorosInCycle;

		quint16 m_currentTime{0};
		quint16 m_currentCyclePomodoroCount{0};
		State m_state{State::paused};
	};
}