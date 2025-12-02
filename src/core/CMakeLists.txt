qt_add_library(PazCore STATIC
		enums.hpp
		constants.hpp
)

target_link_libraries(PazCore PRIVATE
		Qt6::Core
)

target_compile_features(PazCore PUBLIC cxx_std_23)

#target_include_directories(PazCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

