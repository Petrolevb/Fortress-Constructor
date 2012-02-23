cmake_minimum_required(VERSION 2.8)

project(Fortress_Constructor)


include_directories("/usr/include/irrlicht")
link_directories("/usr/lib")


file(
	GLOB_RECURSE
	SRC
	src/*.cpp
)
file(
	GLOB_RECURSE
	HEAD
	src/*.hpp
)

add_EXECutable(
	bin/Fortress_Constructor
	${SRC}
	${HEAD}
)


set(CMAKE_CXX_FLAGS "-g -ansi -pedantic -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "")

target_link_libraries(
	bin/Fortress_Constructor
	Irrlicht
	GL
)
