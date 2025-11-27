/**
 * @date 11/19/25
 * 
 * @author amitayus_
 */

#include <QtTypes>
#include <limits>

namespace paz
{
	static constexpr bool c_isDebug{false};

	namespace impl::pt
	{
		static constexpr std::size_t c_phaseCount{3};

		static constexpr quint16 c_MaxPhaseDuration{99 * 60}; // 99 минут
		static constexpr quint16 c_MinPhaseDuration{60};      // 1 минута
		static constexpr quint16 c_invalidPhaseDuration{0};		// 0 секунд

		static constexpr quint16 c_maxPomodoroCount{std::numeric_limits<quint16>::max() - 1};
		static constexpr quint16 c_invalidPomodoroCount{std::numeric_limits<quint16>::max()};

		namespace defaults
		{
			static constexpr quint16 c_workDuration{25 * 60};       // 25 минут
			static constexpr quint16 c_shortBreakDuration{5 * 60};  // 5 минут
			static constexpr quint16 c_longBreakDuration{45 * 60};  // 45 минут

			static constexpr quint16 c_pomodorosInRound{6};
		}
	}
}