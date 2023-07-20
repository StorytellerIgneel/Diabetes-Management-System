#pragma once
#ifndef ACCESS_CONTROL_HPP
#define ACCESS_CONTROL_HPP

#include "headers.hpp"

void    registration(user user_list[], int user_count)
{
    user            new_user;
    string          choice;
    string          confirm_pw;

    cout << "\nPlease enter your name (Enter 0 to quit)\t\t: ";
    cin >> new_user.details.name;
    if (exit_validation(new_user.details.name, "0") == EXIT)
        return;
    cout << "\nPlease enter your age (Enter 0 to quit)\t\t\t: ";
    cin >> new_user.details.age;
    if (exit_validation(new_user.details.age, "0") == EXIT)
        return;
    cout << "\nPlease enter your phone number (Enter 0 to quit)\t: ";
    cin >> new_user.details.phone_number;
    if (exit_validation(new_user.details.phone_number, "0") == EXIT)
        return;
    cout << "\nPlease enter your home address (Enter 0 to quit)\t: ";
    cin >> new_user.details.home_address;
    if (exit_validation(new_user.details.home_address, "0") == EXIT)
        return;

    while(1)
    {
        system("clear"); //remember to cchange for windows
        cout << "Thank you for registering your details.\nPlease check if your details are as follows: \nName\t\t: " << new_user.details.name << "\nAge\t\t: " << new_user.details.age << "\nPhone number\t: " << new_user.details.phone_number << "\nHome Address\t: " << new_user.details.home_address << "\n\nDo you wish to proceed with these details? Press y for yes and n for no: ";
        cin >> choice;
        if (exit_validation(choice, "n", "y") == CONTINUE)
            break;
        else if (exit_validation(choice, "n", "y") == EXIT)
            return;
        else
            error_message(2);
    }
    cout << "\nPlease enter your username (Enter 0 to quit)\t: " << endl;
    cin >> new_user.access.username;
    if (exit_validation(new_user.access.username, "0") == EXIT)
        return;
    cout << "\nPlease enter your password (Enter 0 to quit)\t: " << endl;
    cin >> new_user.access.password;
    if (exit_validation(new_user.access.password, "0") == EXIT)
        return;
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
        cout << "Username (Press 0 to quit)\t\t: ";
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