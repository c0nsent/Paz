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

#include <chrono>


namespace paz::impl::pt
{
	class TimerEngine final : public QObject
	{
		Q_OBJECT

	public:

		explicit TimerEngine(QObject* parent = nullptr);
		explicit TimerEngine(std::chrono::seconds		startTime, QObject* parent = nullptr);
		TimerEngine(std::chrono::seconds startTime, std::chrono::seconds timeLeft, QObject *parent = nullptr);

		[[nodiscard]] auto startTime() const -> std::chrono::seconds;
		[[nodiscard]] auto timeLeft() const -> std::chrono::seconds;

		[[nodiscard]] bool isActive() const;

	public slots:

		void setStartTime(std::chrono::seconds duration);
		void setTimeLeft(std::chrono::seconds duration);

		void start();
		//void start(std::chrono::seconds seconds);
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

		std::chrono::seconds m_startTime;
		std::chrono::seconds m_timeLeft;
	};
}