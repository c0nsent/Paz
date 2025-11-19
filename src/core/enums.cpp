/**
 * @date 11/18/25
 * 
 * @author amitayus_
 */

#include <QMetaEnum>

namespace paz
{
	namespace backend
	{
		namespace pomodoro
		{
			enum Phase : quint8 { work, shortBreak, longBreak, paused };
			Q_ENUM(Phase);
		}
	}
}