cmake_minimum_required(VERSION 3.7)


# Set compiler version (currently C++20).
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Setup project.
project(clipp)

set (CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${PROJECT_SOURCE_DIR}/cmake/modules
)


# Main executable.
set(cloud_tracer_sources_main
	src/main.cpp
)
set(cloud_tracer_headers_main
)
set(cloud_tracer_headers_math
	src/math/vector.h
)
set(cloud_tracer_sources_math
	src/math/vector.cpp
)
set(cloud_tracer_sources_all
	${cloud_tracer_sources_main}
	${cloud_tracer_sources_math}
)
set(cloud_tracer_headers_all
	${cloud_tracer_headers_main}
	${cloud_tracer_headers_math}
)
source_group("" FILES ${cloud_tracer_sources_main} ${cloud_tracer_headers_main})
source_group("math" FILES ${cloud_tracer_sources_math} ${cloud_tracer_headers_math})
add_executable (clipp ${cloud_tracer_sources_all} ${cloud_tracer_headers_all})
target_include_directories(clipp PRIVATE src)
