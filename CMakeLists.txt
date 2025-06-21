cmake_minimum_required(VERSION 3.25)
set(CMAKE_CXX_STANDARD 98) # <----- ATTENTION ALL BUILDERS! change c++ standard here
project(jastd-${CMAKE_CXX_STANDARD} CXX)

# set dirs and variables for build ouputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/UnitTesters/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/libjastd/bin)
if(${CMAKE_BUILD_TYPE} MATCHES "Debug")
	set(BUILD_POSTFIX -deb)
	add_compile_definitions(_DEBUG)
endif()

# adds includes directory to library and executable
include_directories(libjastd/includes)

# this generates the .dll etc
set(LIB_NAME ${PROJECT_NAME}${BUILD_POSTFIX})
add_library(${LIB_NAME} STATIC
	libjastd/src/macros.cpp
	libjastd/src/string.cpp	libjastd/src/string.tpp
)

# this is for the unit tests executable
set(EXE_NAME ${PROJECT_NAME}-unit-tests${BUILD_POSTFIX})
add_executable(${EXE_NAME}
	main.cpp
	UnitTesters/UnitTesters.cpp
)
# add libjastd as dependency
add_dependencies(${EXE_NAME} ${LIB_NAME})
# link the libjastd
target_link_libraries(${EXE_NAME} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}/lib${LIB_NAME}.a)