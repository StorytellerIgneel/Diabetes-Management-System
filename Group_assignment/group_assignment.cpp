#include "headers.hpp"
#include "validation.hpp"
#include "access_control.hpp"
#include "file_handling.hpp"

int main(void) //initial access control
{
    unsigned int choice;
    map < int, function < void() >> option_list;
    /*
    option_list[1] = login();
    option_list[2] = registration();
    */

    while(1)
    {
        system("cls");
        cout << "Welcome to Diabetes Management System!\nPlease choose to login or to register:\n1. Login\n2. Register\n3. Exit System\n\nEnter choice: ";
        cin >> choice;
        if (option_list.find(choice) != option_list.end())
        {
            option_list[choice]();  // Call the selected function
            break;
        }
        else if (choice == 3)
            exit(1);
        else
            error_message(2);
    }
    return 0;
}

