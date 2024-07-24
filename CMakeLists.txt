cmake_minimum_required(VERSION 3.5)

# Setting the project name to be used as the target name and the name of the executable
set(PROJECT_NAME PokerGame)
project(${PROJECT_NAME})

# Define the source path variable 
set(SRC_PATH src)

# Get all source files in the source path
file(GLOB_RECURSE SRC_FILES ${SRC_PATH}/*.cpp)

# Defining the executable target and adding all source files
add_executable(${PROJECT_NAME} ${SRC_FILES})
