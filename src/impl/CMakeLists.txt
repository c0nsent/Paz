qt_add_library(PazBackend STATIC
		#utility.cpp
		pomodoro-timer/pomodoro-timer.cpp pomodoro-timer/pomodoro-timer.hpp
		pomodoro-timer/timer-engine.cpp pomodoro-timer/timer-engine.hpp
		pomodoro-timer/phase-manager.cpp pomodoro-timer/phase-manager.hpp
)

target_link_libraries(PazBackend PRIVATE
		PazCore
		Qt6::Core
)

target_include_directories(PazBackend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})