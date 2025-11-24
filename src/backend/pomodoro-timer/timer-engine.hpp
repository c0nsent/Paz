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


namespace paz::backend::pt
{
	class TimerEngine final : public QObject
	{
		Q_OBJECT

	public:

		explicit TimerEngine(qint16 totalDuration, qint16 currentTime = 0, QObject *parent = nullptr);

		[[nodiscard]] qint16 getTotalDuration() const;
		[[nodiscard]] qint16 getCurrentTime() const;

		[[nodiscard]] bool isActive() const;

		TimerEngine &setDuration(qint16 seconds);
		TimerEngine &setCurrentTime(qint16 seconds);

	public slots:

		void start();
		void start(qint16 seconds);
		void stop();
		void resetAndStop();

	private slots:

		void handleTick();

	signals:

		void timerTicked();
		void timerFinished();

	private:

		QTimer m_timer;

		qint16 m_currentTime;
		qint16 m_totalDuration;
	};
}