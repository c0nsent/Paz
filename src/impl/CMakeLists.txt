qt_add_library(PazImplementation STATIC
		pomodoro-timer.cpp pomodoro-timer.hpp
)

target_link_libraries(PazImplementation PRIVATE
		PazCore
		Qt6::Core
)

target_compile_features(PazImplementation PUBLIC cxx_std_23)

#target_include_directories(PazImplementation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

