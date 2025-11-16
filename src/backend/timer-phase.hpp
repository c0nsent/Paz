/**
 * @date 11/16/25
 * 
 * @author amitayus_
 */

#pragma once

#include <QObject>

namespace paz::backend
{
	class TimerPhase : public QObject
	{
		Q_OBJECT

	public:

		enum class Phase : quint8 { work, shortBreak, longBreak, paused };

		explicit TimerPhase(QObject *parent = nullptr);

		explicit TimerPhase(Phase phase, QObject *parent = nullptr);

		[[nodiscard]] Phase getPhase() const;

	public slots:

		void setPhase(Phase phase);

		signals:

			void phaseChanged();

	private:

		Phase m_phase;
	};
}
