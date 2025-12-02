/**
 * @date 11/19/25
 * 
 * @author amitayus_
 */

#pragma once

#include <chrono>
#include <limits>
#include <QtTypes>

namespace paz
{
	static constexpr bool c_isDebug{false};

	namespace impl
	{
		namespace pt
		{
			namespace limits
			{
				using namespace std::chrono_literals;

				static constexpr std::chrono::seconds c_MaxPhaseDuration{99min};
				static constexpr std::chrono::seconds c_MinPhaseDuration{1min};
				//TODO Переделать
				//static constexpr quint16 c_invalidPhaseDuration{};		// 0 секунд

				static constexpr quint16 c_maxPomodoro{std::numeric_limits<quint16>::max() - 1};
				static constexpr quint16 c_invalidPomodoro{std::numeric_limits<quint16>::max()};

				static constexpr quint16 c_maxRoundLength{99};
				static constexpr quint16 c_minRoundLength{1};
			}

			/** @brief Константы, задающие значение по-умолчанию */
			namespace defaults
			{
				using namespace std::chrono_literals;

				static constexpr std::size_t c_phaseCount{3};

				static constexpr auto c_TimerInterval{1000ms};

				static constexpr std::chrono::seconds c_workDuration{25min};
				static constexpr std::chrono::seconds c_shortBreakDuration{5min};
				static constexpr std::chrono::seconds c_longBreakDuration{45min};

				static constexpr quint16 c_pomodorosInRound{6};
			}
		}
	}
}