cmake_minimum_required(VERSION 2.8)

project(Fortress_Constructor)


include_directories("/usr/include/irrlicht")
link_directories("/usr/lib")

#EXEC=Fortress_Constructor


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

add_executable(
	bin/Fortress_Constructor
	${SRC}
	${HEAD}
)

target_link_libraries(
	bin/Fortress_Constructor
	Irrlicht
	GL
)
