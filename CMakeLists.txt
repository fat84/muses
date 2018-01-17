CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(muses )
set(CMAKE_USE_RELATIVE_PATHS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/binary)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/binary/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/binary/lib)

#set(CMAKE_TMPBINARY_PATH ${PROJECT_SOURCE_DIR}/..)
set_property(GLOBAL PROPERTY USE_FOLDERS ON) 
include_directories(${PROJECT_SOURCE_DIR}/include)
ADD_EXECUTABLE(build
	src/build.cpp
	src/fingerprint.cpp
	src/hash.cpp
	src/wav.cpp
)
ADD_EXECUTABLE(recog
	src/recog.cpp
	src/fingerprint.cpp
	src/hash.cpp
	src/wav.cpp
)

