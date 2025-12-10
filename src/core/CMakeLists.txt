qt_add_library(PazCore SHARED
		enums.hpp
		constants.hpp
)

target_link_libraries(PazCore PRIVATE
		Qt6::Core
)

target_compile_features(PazCore PUBLIC cxx_std_23)

