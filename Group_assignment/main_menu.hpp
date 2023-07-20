#include "headers.hpp"
#include "template.hpp"

void    user_menu(user user_list, string username)
{
    while(1)
    {
        int choice;
        map < int, function < void(user, string) >> function_list;
        function_list[1] = update_condition();
        function_list[2] = make_appointment();
        function_list[3] = update_account();

        menu("MAIN MENU", username, "Please choose one of the following functions to use: \n1. Update health condition.\n2. Make appointment\n3. Update account details\n4. Exit", "Enter your choice: ");
        cin >> 
    }
}