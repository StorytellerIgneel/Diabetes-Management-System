#pragma once
#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP
#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"
#include "access_control.hpp"

void    user_menu(user   target_user);
void    update_condition(user   target_user);
void    make_appointment(user   target_user);
void    update_account(user   target_user);
void    vpg_test(user *user_ptr);
void    hba1c_test(user *user_ptr);
void    ogtt_test(user *user_ptr);

void    user_menu(user  target_user)
{
    while(1)
    {
        int choice;
        map < int, function < void(user) >> option_list;
        option_list[1] = update_condition;
        option_list[2] = make_appointment;
        option_list[3] = update_account;

        menu(target_user, "MAIN MENU", "Please choose one of the following functions to use: \n1. Update health condition.\n2. Make appointment\n3. Update account details\n4. Exit", "Enter your choice: ");
        cin >> choice;
        if (cin.fail())
            error_message(1);
        else if (choice == 4)
            break;
        else if (option_list.find(choice) != option_list.end())
            option_list[choice](target_user);  // Call the selected function
        else
            error_message(2);
    }
}

void    update_condition(user   target_user)
{
    menu(target_user, "UPDATE MEDICAL CONDITION", "You can update your medical conditions here.\nPlease select which medical condition to update: \n1. Diabetic patient confirmation", "Please enter your choice: ", false);
    map < int, function < void(user) >> option_list;
    option_list[1] = update_diabetic_condition;
    
    return;
}

void    vpg_test(user *user_ptr)
{
    int     state;
    double  vpg;

    while(1)
    {
        menu(*user_ptr, "VENOUS PLASMA GLUCOSE TEST", "Welcome to Venous Plasma Glucose test for T2DM. \nPlease choose confirm your current state, whether you are doing the test under fasting or random conditions.Press 1 for fasting and 2 for random.", "Please enter your choice: ");
        cin >> state;
        if (state == 1)
        {
            menu(*user_ptr, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the fasting state", "Please enter your venous plasma glucose value (mmol/L) (Press 0 to quit): ");
            cin >> vpg;
            if (vpg == 0)
                break;
            else if (vpg < 7.00 && vpg > 0)
            {
                cout << "Congradulations! You are not diagnosed as a T2DM patient.";
                user_ptr->medical.diabetic_patient = false;
                break;
            }
            else if (vpg >= 7.00)
            {
                cout << "You are diagnosed as a T2DM patient.\nPlease remain calm and seek medical advices from our medical personnels.";
                user_ptr->medical.diabetic_patient = true;
                break;
            }
            else if (cin.fail())
                error_message(1);
            else
                error_message(1);
        }
        else if (state == 2)
        {
            menu(*user_ptr, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the random state", "Please enter your venous plasma glucose value (mmol/L) (Press 0 to quit): ");
            cin >> vpg;
            if (vpg == 0)
                break;
            else if (vpg < 11.1)
            {
                cout << "Congradulations! You are not diagnosed as a T2DM patient.";
                user_ptr->medical.diabetic_patient = false;
                break;
            }
            else if (vpg >= 7.00 && vpg <= 11.1)
            {
                cout << "You are diagnosed as a T2DM patient.\nPlease remain calm and seek medical advices from our medical personnels.";
                user_ptr->medical.diabetic_patient = true;
                break;
            }
            else if (cin.fail())
                error_message(1);
            else
                error_message(10);
        }

}
}

void    hba1c_test(user *user_ptr)
{

}

void    ogtt_test(user *user_ptr)
{

}

void    update_diabetic_condition(user   target_user)
{
    menu(target_user, "UPDATE DIABETIC CONDITION", "Please choose which diagnostic value would you like to use to determine your diabetic condition: \n1. Venous plasma glucose\n2. HbA1c\n3. OGTT", "Please enter your choice: ");
    map < int, function < void(&user) >> option_list;
    option_list[1] = vpg_test;
    option_list[2] = make_appointment;
    option_list[3] = update_account;
}

void    make_appointment(user   target_user)
{
    return;
}

void    update_account(user   target_user)
{
    string  details_list[] = {"name", "age", "phone number", "home address", "username", "password"};
    int     choice;

    while(1)
    {
        try
        {
            menu(target_user, "UPDATE ACCOUNT DETAILS", "Please choose which detail you wish to change: \n1. Name\n2. Age\n3. Phone number\n4. Home address\n5. Username\n6. Password", "Enter your choice: ", 1);
            cin >> choice;
            change_detail(&target_user, details_list[choice]);
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

#endif