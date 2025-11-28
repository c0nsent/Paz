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


namespace paz::impl::pt
{
	class TimerEngine final : public QObject
	{
		Q_OBJECT

	public:

		explicit TimerEngine(quint16 startTime, QObject* parent = nullptr);
		TimerEngine(quint16 startTime, quint16 timeLeft, QObject *parent = nullptr);

		[[nodiscard]] quint16 startTime() const;
		[[nodiscard]] quint16 timeLeft() const;

		[[nodiscard]] bool isActive() const;

		TimerEngine &setStartTime(quint16 seconds);
		TimerEngine &setTimeLeft(quint16 seconds);

	public slots:

		void start();
		//void start(quint16 seconds);
		void stop();
		void resetAndStop();

	private slots:

		void handleTick();

	signals:

		void timerTicked();
		void timerFinished();
		//void timerReset();

		void startTimeChanged();
		void timeLeftChanged();

		void timeExceeded(); //TODO Удали когда реализуешь проверку в родителе

	private:

		QTimer m_timer;

		quint16 m_startTime;
		quint16 m_timeLeft;
	};
}