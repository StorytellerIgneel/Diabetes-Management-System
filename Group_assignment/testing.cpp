#include <iostream>
#include <string>
using namespace std;

bool    is_number(const string  *target)
{
    for (char c : *target)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

string  remove_trail(string input)
{
    if(isspace(input[input.length() - 1]))
        return (input.substr(0, input.length() - 1));
    else
        return input;
}


int main (void)
{
    string test;
    cout << "Enter: ";
    getline(cin, test);
    cout << "New: " << remove_trail(test);
}