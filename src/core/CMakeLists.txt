qt_add_library(PazCore STATIC
		enums.cpp
		constants.cpp
)

#target_compile_features(Core PUBLIC cxx_std_23)

target_include_directories(PazCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

