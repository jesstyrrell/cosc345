cmake_minimum_required(VERSION 3.5)

# Supresses "warning: range-based for loop is a C++11 extension [-Wc++11-extensions]"
add_definitions(-w)

# Setting the project name to be used as the target name and the name of the executable
set(PROJECT_NAME PokerGame)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Define the source path variable and main file
set(SRC_PATH src)
set(MAIN_FILE main.cpp)

# Get all source and header files in the source path
file(GLOB_RECURSE SRC_FILES ${SRC_PATH}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${SRC_PATH}/*.hpp)

# Defining the executable target and adding all source files
add_executable(${PROJECT_NAME} ${MAIN_FILE} ${SRC_FILES} ${HEADER_FILES})


enable_testing()

add_executable( TestCard ./tests/test_Card.cc ${SRC_FILES} ${HEADER_FILES})
target_link_libraries( TestCard GTest::gtest_main )

add_executable( TestDeck ./tests/test_Deck.cc ${SRC_FILES} ${HEADER_FILES})
target_link_libraries( TestDeck GTest::gtest_main )

add_executable( TestRandomPlayer ./tests/test_RandomPlayer.cc ${SRC_FILES} ${HEADER_FILES})
target_link_libraries( TestRandomPlayer GTest::gtest_main GTest::gmock_main )

add_executable( TestGUI ./tests/test_GUI.cc ${SRC_FILES} ${HEADER_FILES})
target_link_libraries( TestGUI GTest::gtest_main GTest::gmock_main )

add_executable( TestHandEvaluator ./tests/test_HandEvaluator.cc ${SRC_FILES} ${HEADER_FILES})
target_link_libraries( TestHandEvaluator GTest::gtest_main GTest::gmock_main )

add_executable( TestEquityCalculator ./tests/test_EquityCalculator.cc ${SRC_FILES} ${HEADER_FILES})
target_link_libraries( TestEquityCalculator GTest::gtest_main GTest::gmock_main )

# add_executable( TestGame ./tests/test_Game.cc ${SRC_FILES} ${HEADER_FILES})
# target_link_libraries( TestGame GTest::gtest_main GTest::gmock_main )


# Including the GoogleTest module
include(GoogleTest)

# Adding each test executable to the test suite
gtest_discover_tests(TestCard)
gtest_discover_tests(TestDeck)

gtest_discover_tests(TestRandomPlayer)

# gtest_discover_tests(TestGUI)
# gtest_discover_tests(TestGame)

gtest_discover_tests(TestHandEvaluator)
gtest_discover_tests(TestEquityCalculator)
