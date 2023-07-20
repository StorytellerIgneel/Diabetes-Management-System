#include <iostream>
#include <stdexcept>

int main() {
    try {
        throw std::runtime_error("A runtime error occurred!");
    }
    catch (const std::runtime_error& ex) {
        std::cout << "Caught runtime error: " << ex.what() << std::endl;
    }
    return 0;
}