#pragma once
#ifndef ACCESS_CONTROL_HPP
#define ACCESS_CONTROL_HPP

#include "headers.hpp"

void    registration_control()
{
    char    choice;

    system("cls");
    cout << "Welcome to registration.\nYou will be required to register to the diabetes management system with your name, age, contact number, and home address.\nPress y if you wish to continue or n to exit: ";
    cin >> choice;
    while(1)
    {
        if (choice == 'y' || choice == 'Y')
        {
            //registration();
            break;
        }
        else if (choice == 'n' || choice == 'N')
            break;
        else
            error_message(1);
    }
}

void    registration()
{
    user        new_user;
    string      choice;
    
    while(1)
    {
        cout << "\nPlease enter your name (Enter 0 to quit)\t: " << endl;
        cin >> new_user.details.name;
        if (validation(new_user.details.name, "0") == EXIT)
            return;
        else
            break;
    }
    while(1)
    {
        cout << "\nPlease enter your age (Enter 0 to quit)\t: " << endl;
        cin >> new_user.details.age;
        if (validation(new_user.details.age, "0") == EXIT)
            return;
        else
            break;
    }
    while(1)
    {
        cout << "\nPlease enter your phone number (Enter 0 to quit)\t: " << endl;
        cin >> new_user.details.phone_number;
        if (validation(new_user.details.phone_number, "0") == EXIT)
            return;
        else
            break;
    }
    while(1)
    {
        cout << "\nPlease enter your home address (Enter 0 to quit)\t: " << endl;
        cin >> new_user.details.home_address;
        if (validation(new_user.details.home_address, "0") == EXIT)
            return;
        else
            break;
    }
    while(1)
    {
        system("cls");
        cout << "Thank you for registering your details.\nPlease check if your details are as follows: \nName\t\t: " << new_user.details.name << "\nAge\t\t: " << new_user.details.age << "\nPhone number\t: " << new_user.details.phone_number << "\nHome Address\t: " << new_user.details.home_address << "\n\nDo you wish to proceed with these details? Press y for yes and n for no: ";
        cin >> choice;
        if (validation(choice, "n", "y") == CONTINUE)
    }

    cout << "Please enter your username (Enter 0 to quit)\t: " << endl;
    cin >> new_user.access.username;
    cout << "Please enter your password (Enter 0 to quit)\t: " << endl;
    cin >> new_user.access.password;
    //return?
}

#endif