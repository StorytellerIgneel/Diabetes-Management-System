#include "headers.hpp"
#include "validation.hpp"
#include "access_control.hpp"
#include "file_handling.hpp"

//Act as the initial starter of the entire programme (main) and as the initial access control.
int main(void) //initial access control
{
    
    int     user_count;
    int     admin_count;
    int     choice_int;
    int     file_present;
    string  choice_str;
    user    user_list[MAX_CAPACITY];
    admin   admin_list[MAX_CAPACITY];
    map < int, function < void(user[], int, admin[]) >> option_list;
    option_list[1] = user_login;
    option_list[2] = registration_control;
    
    file_present = check_file_present();
    if (file_present == MISSING)
    {
        cout << "As the system does not have all files required to run the system, the system will be shutting down now to prevent failures.\nPlease ensure all required files are present before attempting to run the system.";
        cin.get();
        return 0;
    }
    while(1)
    {
        user_count = get_user_num("user") % MAX_CAPACITY; //to allow cycling configuration of new users (if theres the 101st patient, the 1st will be removed and the 101st will take the place)
        admin_count = get_user_num("admin") % MAX_CAPACITY;
        read_admin_data(admin_list, admin_count);
        read_user_data(user_list, user_count);
        menu(user(), admin(), "LOGIN", "Welcome to Diabetes Management System!\nPlease choose to login or to register:\n1. User login\n2. Register\n3. Admin login", "Enter choice: ");
        getline(cin, choice_str);
        choice_str = remove_trail(choice_str);
        if (!cin)
        {
            export_user_data(user_list, admin_list);
            exit(0);
        }
        else if (choice_str != "")
        {
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
        else
            error_message(17);
    }
    return 0;
}