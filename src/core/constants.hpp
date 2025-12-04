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
	//TODO Стоит поискать альтернативы
	/// Дебаг флаг
	static constexpr bool c_debug{true};

	namespace impl
	{
		///Неймспейс с константами, задающими ограничения для значений
		namespace limits
		{
			using namespace std::chrono_literals;

			/// Максимальная длительность фазы - 99 минут
			static constexpr std::chrono::seconds c_MaxPhaseDuration{99min};
			/// Минимальная длительность фазы - 1 минута
			static constexpr std::chrono::seconds c_MinPhaseDuration{1min};
			//TODO Переделать
			//static constexpr quint16 c_invalidPhaseDuration{};		// 0 секунд

			/// Максимальное количество помодоро за сессию
			static constexpr quint16 c_maxPomodoro{std::numeric_limits<quint16>::max() - 1};
			/// Значение, обозначающее невалидное количество помодоро
			static constexpr quint16 c_invalidPomodoro{std::numeric_limits<quint16>::max()};

			static constexpr quint16 c_maxRoundLength{99};
			static constexpr quint16 c_minRoundLength{1};
		}

		/// Неймспейс с константами, задающими значение по-умолчанию
		namespace defaults
		{
			using namespace std::chrono_literals;

			///Количество фаз в помодоро таймере
			static constexpr std::size_t c_phaseCount{3};

			/// Интервал тика QTimer в миллисекундах
			static constexpr auto c_TimerInterval{1000ms};

			/// Длительности фазы `PhaseManager::Phase::Work` по-умолчанию
			static constexpr std::chrono::seconds c_workDuration{25min};
			/// Длительности фазы `PhaseManager::Phase::ShortBreak` по-умолчанию
			static constexpr std::chrono::seconds c_shortBreakDuration{5min};
			/// Длительности фазы `PhaseManager::Phase::LongBreak` по-умолчанию
			static constexpr std::chrono::seconds c_longBreakDuration{45min};

			static constexpr quint16 c_pomodorosInRound{6};
		}

	}
}