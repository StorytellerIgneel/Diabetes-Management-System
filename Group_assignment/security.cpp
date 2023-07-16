#include <iostream>
#include <termios.h>
#include <unistd.h>

int main(void){
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= 'a'; // remove ~ECHO
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Hides

    std::string s{}, current{};
    char c{};
    std::cout << "Enter your password: ";
    do {
      std::cout << current;
      s += c;
      current = "*";
    }while((c = getchar()) != '\n' && c != EOF);

    std::cout << "\rYour password is: " << s <<
    "                                 " << '\n';
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // return to display
    return EXIT_SUCCESS;
}