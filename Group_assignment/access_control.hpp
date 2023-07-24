#pragma once
#ifndef ACCESS_CONTROL_HPP
#define ACCESS_CONTROL_HPP

#include "headers.hpp"
#include "validation.hpp"

void    change_detail(user user_list[], string detail,int new_user = FALSE, int new_user_count = 0, string username = "")
{
    int     user_count;
    string  new_detail;

    map < string, string user_details::* > user_details_list =
    {
        {"name", &user_details::name},
        {"age", &user_details::age},
        {"phone  number", &user_details::phone_number},
        {"home address", &user_details::home_address}
    };

    map < string, string access_control::* > access_control_list = 
    {
        {"username", &access_control::username},
        {"password", &access_control::password}
    };

    auto details_iterator = user_details_list.find(detail);
    auto access_iterator = access_control_list.find(detail);
    user_count = 0;

    if (new_user == FALSE)
    {
        while(user_list[user_count].access.username != username)
            user_count++;
    }
    else
        user_count = new_user_count;

    if (details_iterator != user_details_list.end())//the detail to be changed is in the user_detail struct
    {
        if (new_user == FALSE)
            cout << "Old detail\t\t: " << (user_list[user_count].details.*details_iterator->second) << endl;
        cout << "Please enter your new" << detail << ": ";
        cin >> new_detail;
        if (new_detail == (user_list[user_count].details.*details_iterator->second))
            error_message(7);
        else
            (user_list[user_count].details.*details_iterator->second) = new_detail;
    }
    else
    {
        if (new_user == FALSE)
            cout << "Old detail\t\t: " << (user_list[user_count].access.*access_iterator->second) << endl;
        cout << "Please enter your new" << detail << ": ";
        cin >> new_detail;
        if (new_detail == (user_list[user_count].access.*access_iterator->second))
            error_message(7);
        else
            (user_list[user_count].access.*access_iterator->second) = new_detail;
    }
    return;
}

void    registration(user user_list[], int user_count)
{
    user            new_user;
    string          choice;
    string          confirm_pw;
    string          details_list[] = {"name", "age", "phone number", "home address"};
    int             details_list_count;

    while(details_list[details_list_count] != "")
    {
        change_detail(user_list, details_list[details_list_count], 1, user_count);
        details_list_count++;
    }
    //validation for exit 

    while(1)
    {
        system("cls"); //remember to cchange for windows
        cout << "Thank you for registering your details.\nPlease check if your details are as follows: \nName\t\t: " << new_user.details.name << "\nAge\t\t: " << new_user.details.age << "\nPhone number\t: " << new_user.details.phone_number << "\nHome Address\t: " << new_user.details.home_address << "\n\nDo you wish to proceed with these details? Press y for yes and n for no: ";
        cin >> choice;
        if (exit_validation(choice, "n", "y") == CONTINUE)
            break;
        else if (exit_validation(choice, "n", "y") == EXIT)
            return;
        else
            error_message(2);
    }

    change_detail(user_list, "username", 1, user_count);
    change_detail(user_list, "password", 1, user_count);
    while(1)
    {
        cout << "Please re-enter your password to confirm password set(Enter 0 to quit)\t: ";
        cin >> confirm_pw;
        if (confirm_pw == new_user.access.password)
        {
            success_message(1, new_user.access.username);
            break;
        }
        else if (confirm_pw == "0")
            return;
        else
            error_message(4);
    }
    user_list[user_count] = new_user;
    return;
    //hidden input for pw (asterisk)
}

void    registration_control(user user_list[], int user_count)
{
    char    choice;

    while(1)
    {
        system("clear");
        cout << "Welcome to registration.\nYou will be required to register to the diabetes management system with your name, age, contact number, and home address.\nPress y if you wish to continue or n to exit: ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            registration(user_list, user_count);
            break;
        }
        else if (choice == 'n' || choice == 'N')
            break;
        else
            error_message(1);
    }
}

void    login(user  user_list[], int user_count)
{
    string  username;
    string  password;
    int     counter;
    int     found_username;
    int     login_validated;

    cout << "Welcome to user login.\nPlease enter your username and password to login into your account." << endl << endl;
    while(1)
    {
        counter = 0;
        found_username = FALSE;
        login_validated = FALSE;
        menu(user_list, "USER LOGIN", "Guest", "Welcome to user login.\nPlease enter your username and password to login into your account.", "Username (Press 0 to quit)\t\t: ");
        cin >> username;
        if (exit_validation(username, "0") == EXIT)
            return;
        while(counter < user_count)
        {
            if (username == user_list[counter].access.username)
            {
                found_username = TRUE;
                break;
            }
            counter++;
        }
        if(found_username == TRUE)//username is found
        {
            while(1)
            {
                cout << "Enter your password (Press 0 to quit)\t: ";
                cin >> password;
                if (exit_validation(username, "0") == EXIT)
                    return;
                if(password == user_list[counter].access.password)
                {
                    success_message(2, user_list[counter].access.username);
                    login_validated = TRUE;
                    break;
                }
                else
                    error_message(6);
            }
        }
        else//username not found
            error_message(5);
        if(login_validated == TRUE)
            //user_menu(user_list, user_list[counter].access.username);
            break;
    }
    //call user function
    return;
}
#endif