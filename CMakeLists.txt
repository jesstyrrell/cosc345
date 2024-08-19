cmake_minimum_required(VERSION 3.5)

enable_testing()


# Supresses "warning: range-based for loop is a C++11 extension [-Wc++11-extensions]"
add_definitions(-w)

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

# Add the test executable
add_executable(TestCard tests/test_Card.cpp ${SRC_FILES} ${HEADER_FILES})
add_executable(TestDeck tests/test_Deck.cpp ${SRC_FILES} ${HEADER_FILES})
add_executable(TestPlayer tests/test_Player.cpp ${SRC_FILES} ${HEADER_FILES})
# add_executable(TestGame tests/test_Game.cpp ${SRC_FILES} ${HEADER_FILES})

# Register the test
add_test(NAME TestCard COMMAND TestCard)
add_test(NAME TestDeck COMMAND TestDeck)
add_test(NAME TestPlayer COMMAND TestPlayer) 
# add_test(NAME TestGame COMMAND TestGame)
