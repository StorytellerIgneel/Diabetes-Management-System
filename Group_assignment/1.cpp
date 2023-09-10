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
    int     choice_int;
    string  choice_str;
    user    user_list[MAX_CAPACITY];
    admin   admin_list[MAX_CAPACITY];
    map < int, function < void(user[], int, admin[]) >> option_list;
    option_list[1] = user_login;
    option_list[2] = registration_control;

    while(1)
    {
        user_count = get_user_num("user");
        admin_count = get_user_num("admin");
        read_admin_data(admin_list, admin_count);
        read_user_data(user_list, user_count);
        menu(user(), admin(), "LOGIN", "Welcome to Diabetes Management System!\nPlease choose to login or to register:\n1. User login\n2. Register\n3. Admin login", "Enter choice: ");
        getline(cin, choice_str);
        if (!cin)
        {
            export_user_data(user_list, admin_list);
            exit(0);
        }
        if(is_number(choice_str, &choice_int))
        {
            if (choice_int == 1 || choice_int == 2)
                option_list[choice_int](user_list, user_count, admin_list);  // Call the selected function
            else if (choice_int == 3)
                admin_login(user_list, admin_count, admin_list);
            else
                error_message(2);
            export_user_data(user_list, admin_list);
        }
        else
            error_message(1);
    }
    return 0;
}