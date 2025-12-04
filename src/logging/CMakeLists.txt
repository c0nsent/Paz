qt_add_library(PazLogging STATIC
		logging.cpp logging.hpp
)

target_link_libraries(PazLogging PRIVATE
		PazImplementation
		PazCore
		Qt6::Core
		Qt6::Widgets
)

target_compile_features(PazLogging PUBLIC cxx_std_23)

# target_include_directories(PazUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
