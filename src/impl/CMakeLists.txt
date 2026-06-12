qt_add_library(PazImplementation SHARED
		pomodoro-timer.cpp pomodoro-timer.hpp
		pomodoro-calculator.cpp pomodoro-calculator.hpp
        #settings-manager.cpp settings-manager.hpp
)

target_link_libraries(PazImplementation PRIVATE
		PazCore
		Qt6::Core
)

target_compile_features(PazImplementation PUBLIC cxx_std_23)