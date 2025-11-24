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

		explicit TimerEngine(QObject* parent = nullptr);

		[[nodiscard]] quint16 getTotalDuration() const;
		//[[nodiscard]] quint16 getCurrentTime() const;

		//duration в секундах
		TimerEngine &setDuration(quint16 seconds);
		//TimerEngine &setCurrentTime(quint16 currentTime);

		bool isActive() const;

	public slots:

		void start();
		void start(quint16 seconds);
		void stop();
		void resetAndStop();

	private slots:

		void handleTick();

	signals:

		void timerTicked();
		void timerFinished();

	private:

		QTimer m_timer;

		quint16 m_totalDuration{ 0 };
		quint16 m_currentTime{ 0 };
	};
}