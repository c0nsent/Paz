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


namespace paz::backend::pomodoro
{
	class TimerEngine final : public QObject
	{
		Q_OBJECT

	public:

		explicit TimerEngine(QObject* parent = nullptr);

		[[nodiscard]] quint16 getDuration() const;
		[[nodiscard]] quint16 getCurrentTime() const;

		TimerEngine &setDuration(quint16 duration);
		TimerEngine &setCurrentTime(quint16 currentTime);

		bool isPaused() const;

	public slots:

		void start();
		void pause();
		void reset();

	private slots:

		void handleTick();

	signals:

		void timerTicked();
		void timerFinished();

	private:

		QTimer m_timer;

		quint16 m_duration{ 0 };
		quint16 m_currentTime{ 0 };
	};
}