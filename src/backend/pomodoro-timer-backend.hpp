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

		PomodoroTimerBackend & setWorkTime(quint16 workTime);
		PomodoroTimerBackend &setShortBreakTime(quint16 shortBreakTime);
		PomodoroTimerBackend &setLongBreakTime(quint16 longBreakTime);
		PomodoroTimerBackend &setPomodorosInCycle(quint16 pomodorosInCycle);
		PomodoroTimerBackend &setCurrentTime(quint16 currentTime);
		PomodoroTimerBackend &setCurrentCyclePomodoroCount(quint16 currentCyclePomodoroCount);
		PomodoroTimerBackend &setState(State state);

	public slots:

		PomodoroTimerBackend &start();
		PomodoroTimerBackend &stop();
		PomodoroTimerBackend &reset();
		PomodoroTimerBackend &skip();

	signals:

		PomodoroTimerBackend &timerTicked();
		PomodoroTimerBackend &timerFinished();

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