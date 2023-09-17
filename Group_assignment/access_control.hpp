#pragma once
#ifndef ACCESS_CONTROL_HPP
#define ACCESS_CONTROL_HPP

#include "headers.hpp"
#include "validation.hpp"
#include "user_menu.hpp"
#include "admin_menu.hpp"

void    registration(user user_list[], int user_count);
void    registration_control(user user_list[], int user_count, admin admin_list[]);
void    user_login(user  user_list[], int user_count, admin admin_list[]);
void    admin_login(user  user_list[], int user_count, admin admin_list[]);

//Function: act as a control function to ensure that user know that what kind of information will be required to register a new account.
void    registration_control(user user_list[], int user_count, admin admin_list[])
{
    string    choice;

    while(1)
    {
        menu(user(), admin(), "REGISTRATION", "Welcome to registration.\nYou will be required to register to the diabetes management system with your name, age, contact number, and home address.", "Press y if you wish to continue or n to exit: ");
        getline(cin, choice);
        if(exit_check(&cin))
            return;
        if (choice == "y" || choice == "Y")
            registration(user_list, user_count);
        else if (choice == "n" || choice == "N")
            return;
        else
            error_message(1);
    }
    return;
}

void    registration(user user_list[], int user_count)
{
    bool        continue_step;
    user        new_user;
    string      choice;
    string      confirm_pw;
    string      details_list[] = {"name", "age", "phone number", "home address"};
    string      for_menu;    
    
    continue_step = false;
    for(int details_list_count = 0; details_list_count < 4; details_list_count++)
    {
        if (change_detail(&new_user, details_list[details_list_count], user_list, true) == EXIT)
        {
            details_list_count -= 2;
            if (details_list_count == -2)
                return;
        }    
    }
    while(1)
    {
        for_menu =  "Thank you for registering your details.\nPlease check if your details are as follows: \nName\t\t: " + new_user.details.name + "\nAge\t\t: " + new_user.details.age + "\nPhone number\t: " + new_user.details.phone_number + "\nHome Address\t: " + new_user.details.home_address;
        menu(new_user, admin(), "REGISTRATION", for_menu, "Do you wish to proceed with these details? Press y for yes and n for no: ");
        getline(cin, choice);
        if(exit_check(&cin))
            return;
        if (choice == "y" || choice == "Y")
        {
            while(1)
            {
                if (change_detail(&new_user, "username", user_list, true) != EXIT)
                {
                    if (change_detail(&new_user, "password", user_list,true) != EXIT)
                    {
                        continue_step = true;
                        break;
                    }     
                }
                else
                    break;
            }
            if (continue_step == true)
                break;
        }
        else if (choice == "n" || choice == "N")
            return;
        else
            error_message(2);
    }
    while(1)
    {
        cout << "Please re-enter your password to confirm password set (Enter Ctrl + Z to quit)\t: ";
        getline(cin, confirm_pw);
        if(exit_check(&cin))
            return;
        if (confirm_pw == new_user.access.password)
        {
            success_message(1, new_user.access.username);
            break;
        }
        else
            error_message(4);
    }
    user_list[user_count] = new_user;
    return;
    //hidden input for pw (asterisk)
}

void    user_login(user  user_list[], int user_count, admin admin_list[])
{
    string  username;
    string  password;
    bool     found_username;
    int     counter;
    int     login_validated;

    while(1)
    {
        counter = 0;
        found_username = FALSE;
        login_validated = FALSE;
        menu(user(), admin(), "USER LOGIN", "Welcome to user login.\nPlease enter your username and password to login into your account.", "Username\t\t\t: ");
        getline(cin, username);
        if(exit_check(&cin))
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
        if(found_username == true)//username is found
        {
            while(1)
            {
                cout << "Enter your password\t\t: ";
                getline(cin, password);
                if(exit_check(&cin))
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
        {
            user_menu(&user_list[counter]);
            break;
        }
    }
    return;
}

void    admin_login(user user_list[], int admin_count ,admin  admin_list[])
{
    string  admin_name;
    string  password;
    bool    found_admin;
    bool    login_validated;
    int     counter;

    while(1)
    {
        counter = 0;
        found_admin = false;
        login_validated = false;
        menu(user(), admin(), "ADMIN LOGIN", "Welcome to admin login.\nPlease enter your username and password to login into your account.", "Admin name\t\t\t: ");
        getline(cin, admin_name);
        if(exit_check(&cin))
            return;
        while(counter < admin_count)
        {
            if (admin_name == admin_list[counter].admin_name)
            {
                found_admin = true;
                break;
            }
            counter++;
        }
        if(found_admin == true)//username is found
        {
            while(1)
            {
                cout << "Enter your password\t\t: ";
                getline(cin, password);
                if(exit_check(&cin))
                    return;
                if(password == admin_list[counter].password)
                {
                    success_message(2, admin_list[counter].admin_name);
                    login_validated = true;
                    break;
                }
                else
                    error_message(15);
            }
        }
        else//admin name not found
            error_message(14);
        if(login_validated == true)
        {
            admin_menu(admin_list[counter], user_list, admin_list);
            break;
        }
    }
    return;
}
#endif