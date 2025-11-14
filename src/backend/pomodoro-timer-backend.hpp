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
	class PomodoroTImerBackend : public QObject
	{
		Q_OBJECT

	public:

		enum class State : quint8 { work, shortBreak, longBreak, paused };

		PomodoroTImerBackend(quint16 workTime, quint16 shortBreakTime, quint16 longBreakTime , QObject* parent = nullptr);

		quint16 getWorkTime() const;
		quint16 getShortBreakTime() const;
		quint16 getLongBreakTime() const;
		State getState() const;
		quint16 getCurrentTime() const;

		void setWorkTime(quint16 workTime);
		void setShortBreakTime(quint16 shortBreakTime);
		void setLongBreakTime(quint16 longBreakTime);
		void setState(State state);
		void setCurrentTime(quint16 currentTime);

	public slots:

		void start();
		void stop();
		void resume();
		void pause();
		void reset();

	signals:

		void timerTicked();
		void timerFinished() const;

	private:

		QTimer m_timer;

		quint16 m_workTime;
		quint16 m_shortBreakTime;
		quint16 m_longBreakTime;
		quint16 m_currentTime;

		State m_state;
	};
}