/**
 * @date 12.12.2025
 * 
 * @author amitayus_
 */

#pragma once

#include <QObject>
#include <QTimer>

namespace impl
{
	class AfkTimer final : public QObject
	{
		Q_OBJECT

		static constexpr quint16 c_timeIsOut{0};

	public:

		explicit AfkTimer(QObject *parent = nullptr);

	public slots:

		void start(quint16 seconds);
		void reset();

	private slots:

		void handleQTimerTimeout();

	signals:

		void started(quint16 seconds);
		void ticked(quint16 seconds);
		void wasReset();
		void finished();

	private:

		quint16 m_duration{0};
		quint16 m_remainingTime{0};
		QTimer m_timer;
	};
}
