cmake_minimum_required(VERSION 3.5)

# Setting the project name to be used as the target name and the name of the executable
set(PROJECT_NAME PokerGame)
project(${PROJECT_NAME})

# Define the source path variable 
set(SRC_PATH src)

# Defining the file used to run the program 
set(MAIN_FILE main.cpp)

# Get all source and header files in the source path
file(GLOB_RECURSE SRC_FILES ${SRC_PATH}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${SRC_PATH}/*.hpp)

# Defining the executable target and adding all source files
add_executable(${PROJECT_NAME} ${MAIN_FILE} ${SRC_FILES} ${HEADER_FILES})