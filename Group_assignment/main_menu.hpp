#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"
#include "access_control.hpp"

void    user_menu(user user_list[], string username)
{
    while(1)
    {
        int choice;
        map < int, function < void(user[], string) >> option_list;
        option_list[1] = update_condition;
        option_list[2] = make_appointment;
        option_list[3] = update_account;

        menu(user_list, "MAIN MENU", username, "Please choose one of the following functions to use: \n1. Update health condition.\n2. Make appointment\n3. Update account details\n4. Exit", "Enter your choice: ");
        cin >> choice;
        if (cin.fail())
            error_message(1);
        else if (choice == 4)
            break;
        else if (option_list.find(choice) != option_list.end())
            option_list[choice](user_list, username);  // Call the selected function
        else
            error_message(2);
    }
}

void    update_condition(user   user_list[], string username)
{
    
    return;
}

void    make_appointment(user   user_list[], string username)
{
    return;
}

void    update_account(user   user_list[], string username)
{
    string  details_list[] = {"name", "age", "phone number", "home address", "username", "password"};
    int     choice;
    int     user_count;

    user_count = 0;
    while(user_list[user_count].access.username != username)
        user_count++;

    while(1)
    {
        try
        {
            menu(user_list, "UPDATE ACCOUNT DETAILS", username, "Please choose which detail you wish to change: \n1. Name\n2. Age\n3. Phone number\n4. Home address\n5. Username\n6. Password", "Enter your choice: ", 1);
            cin >> choice;
            change_detail(&user_list[user_count], details_list[choice]);
            break;
        }
        catch(const invalid_argument& e)
        {
            error_message(1);
        }
        catch(const exception& e)
        {
            error_message(8);
        }
    }
}