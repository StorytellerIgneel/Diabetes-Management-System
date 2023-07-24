#include "headers.hpp"
#include "access_control.hpp"
#include "validation.hpp"
#include "file_handling.hpp"

int main(void) //initial access control
{
    string  details_list[] = {"", "name", "age", "phone number", "home address", "username", "password"};
    int     choice;

    while(1)
    {
        cout << "Enter the fucking choice: ";
        cin >> choice;
        if (cin.fail())
            error_message(1);
        else
        {
            cout << details_list[choice];
            break;
        }
    }
}