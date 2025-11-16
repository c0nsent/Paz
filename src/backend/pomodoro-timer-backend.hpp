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

		enum class Phase : quint8 { work, shortBreak, longBreak, paused };

		PomodoroTimerBackend(quint16 workTime, quint16 shortBreakTime, quint16 longBreakTime, quint16 pomodorosInCycle, QObject* parent = nullptr);

		[[nodiscard]] quint16 getWorkTime() const;
		[[nodiscard]] quint16 getShortBreakTime() const;
		[[nodiscard]] quint16 getLongBreakTime() const;
		[[nodiscard]] quint16 getPomodorosInCycle() const;
		[[nodiscard]] quint16 getCurrentTime() const;
		[[nodiscard]] quint16 getCurrentCyclePomodoroCount() const;
		[[nodiscard]] Phase getState() const;

		PomodoroTimerBackend & setWorkTime(quint16 workTime);
		PomodoroTimerBackend &setShortBreakTime(quint16 shortBreakTime);
		PomodoroTimerBackend &setLongBreakTime(quint16 longBreakTime);
		PomodoroTimerBackend &setPomodorosInCycle(quint16 pomodorosInCycle);
		PomodoroTimerBackend &setCurrentTime(quint16 currentTime);
		PomodoroTimerBackend &setCurrentCyclePomodoroCount(quint16 currentCyclePomodoroCount);
		PomodoroTimerBackend &setState(Phase state);

	public slots:

		void start();
		void stop();
		void reset();
		void skipCurrentPhase();

	private slots:

		void handleTimerTick();
		void handlePhaseChange();

	signals:

		void timerTicked();
		void phaseChanged();

	private:

		QTimer m_timer{};

		quint16 m_workTime;
		quint16 m_shortBreakTime;
		quint16 m_longBreakTime;
		quint16 m_pomodorosInCycle;

		quint16 m_currentTime{0};
		quint16 m_currentCyclePomodoroCount{0};
		Phase m_phase{Phase::paused};
	};
}