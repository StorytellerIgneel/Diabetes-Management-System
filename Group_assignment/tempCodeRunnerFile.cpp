#include <iostream>
#include <string>
#include <algorithm>

int main() {
    std::string line = "No meal record found.\nPlease do add a meal record before choosing to display them.";
    
    // Count the number of newline characters ('\n') in the string
    size_t newline_count = std::count(line.begin(), line.end(), '\n');

    std::cout << "Number of '\\n' characters: " << newline_count << std::endl;

    return 0;
}