qt_add_library(PazImplementation STATIC
		#utility.cpp
		pomodoro-timer/pomodoro-timer.cpp pomodoro-timer/pomodoro-timer.hpp
		pomodoro-timer/timer-engine.cpp pomodoro-timer/timer-engine.hpp
		pomodoro-timer/phase-manager.cpp pomodoro-timer/phase-manager.hpp
)

target_link_libraries(PazImplementation PRIVATE
		PazCore
		Qt6::Core
)

target_compile_features(PazImplementation PUBLIC cxx_std_23)

#target_include_directories(PazImplementation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

