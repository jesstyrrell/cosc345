
<!-- PROJECT LOGO -->
<br />
<p align="center">
    <h1 align="center">Running & Writing Tests</h1>

  <p align="center">
   Brief tutorial on how to run and write tests for the project
  </p>
</p>

___


## Example

1. Keep your main project files (Card.cpp, Card.hpp, main.cpp) as they are, without any test methods.

2. Create a `/tests` folder in your project root if it doesn't already exist.

3. Create a new file named `test_Card.cpp` in the `/tests` folder:

```cpp
#include "../Card.hpp"
#include <cassert>
#include <iostream>

void test_card() {
    Card card("Hearts", "Ace");

    assert(card.get_suit() == "Hearts" && "Incorrect suit");
    assert(card.get_rank() == "Ace" && "Incorrect rank");

    std::cout << "Card test passed!" << std::endl;
}

int main() {
    test_card();
    return 0;
}
```

4. Update your `CMakeLists.txt` to build both your main project and the tests:

```cmake
cmake_minimum_required(VERSION 3.10)
project(YourProjectName)

# Enable CTest
enable_testing()

# Add your main project source files
add_executable(YourExecutableName 
    Card.cpp 
    main.cpp
)

# Add the test executable
add_executable(test_Card
    Card.cpp
    tests/test_Card.cpp
)

# Add the test
add_test(NAME CardTest COMMAND test_Card)
```

5. To run the tests, follow these steps:
   - Create a build directory: `mkdir build && cd build`
   - Configure the project: `cmake ..`
   - Build the project: `cmake --build .`
   - Run the tests: `ctest`

This setup creates a separate executable for your tests, which CTest will run. Your main project remains untouched by the testing code.

For each additional class you want to test:

1. Create a new test file in the `/tests` folder (e.g., `test_Deck.cpp` for a `Deck` class).
2. Write the test function and a main function in this new file.
3. Update `CMakeLists.txt` to build the new test executable and add it as a test.

For example, if you had a `Deck` class, you might create `tests/test_Deck.cpp`:

```cpp
#include "../Deck.hpp"
#include <cassert>
#include <iostream>

void test_deck() {
    Deck deck;
    // Your test logic here
    assert(deck.size() == 52 && "Deck should have 52 cards");
    std::cout << "Deck test passed!" << std::endl;
}

int main() {
    test_deck();
    return 0;
}
```

Then update `CMakeLists.txt`:

```cmake
# ... previous content ...

# Add the Deck test executable
add_executable(test_Deck
    Deck.cpp
    tests/test_Deck.cpp
)

# Add the Deck test
add_test(NAME DeckTest COMMAND test_Deck)
```

This approach keeps your tests completely separate from your main code, allows you to run tests individually or all together using CTest, and provides a scalable structure for adding more tests as your project grows.