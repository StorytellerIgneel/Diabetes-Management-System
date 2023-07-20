#include <iostream>
#include <limits>
#include <headers.hpp>
#include <access_control.hpp>

int main(void) //initial access control
{
    int user_count = 0; // Initialize user_count to 0 initially

    user user_list[MAX_CAPACITY];
    map<int, function<void(user[], int)>> option_list;
    option_list[1] = login;
    option_list[2] = registration_control;

    read_user_data(user_list, 50);

    while (1)
    {
        system("clear");
        cout << "Welcome to Diabetes Management System!\nPlease choose to login or to register:\n1. Login\n2. Register\n3. Exit System\n\nEnter choice: ";
        int choice;
        cin >> choice;
        if (option_list.find(choice) != option_list.end())
            option_list[choice](user_list, user_count); // Call the selected function
        else if (choice == 3)
        {
            export_user_data(user_list);
            exit(1);
        }
        else
            error_message(2);
    }

    return 0;
}