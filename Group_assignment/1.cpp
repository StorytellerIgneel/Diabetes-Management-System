#include "headers.hpp"
#include "validation.hpp"
#include "access_control.hpp"
#include "file_handling.hpp"

/*
Act as the initial starter of the entire programme (main) and as the initial access control.
Pre:
i.  libary "headers.hpp" is included
ii. libary "validation.hpp" is included
iii. libary "access_control.hpp" is included
iv. libary "file_handling.hpp" is included
*/

int main(void) //initial access control
{
    int     user_count;
    int     admin_count;
    int     choice;
    user    user_list[MAX_CAPACITY];
    admin   admin_list[MAX_CAPACITY];
    map < int, function < void(user[], int, admin[]) >> option_list;
    option_list[1] = user_login;
    option_list[2] = registration_control;

    user_count = get_user_num("user");
    admin_count = get_user_num("admin");
    read_admin_data(admin_list, admin_count);
    read_user_data(user_list, user_count);
    while(1)
    {
        menu(user(), admin(), "LOGIN", "Welcome to Diabetes Management System!\nPlease choose to login or to register:\n1. User login\n2. Register\n3. Admin login", "Enter choice: ");
        cin >> choice;
        if (!cin)
        {
            export_user_data(user_list, admin_list);
            exit(0);
        }
        else if (choice == 1 || choice == 2)
            option_list[choice](user_list, user_count, admin_list);  // Call the selected function
        else if (choice == 3)
            admin_login(user_list, 1, admin_list);
        else if (cin.fail())
            error_message(1);
        else
        {
            error_message(2);
            cin.clear();
            cin.ignore();
        }
    }
    return 0;
}