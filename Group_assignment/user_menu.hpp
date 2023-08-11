#pragma once
#ifndef USER_MENU_HPP
#define USER_MENU_HPP
#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"

void    change_detail(user *target_user_ptr, string detail, bool new_user);
void    user_menu(user   target_user);
void    update_condition(user   target_user);
void    make_appointment(user   target_user);
void    update_account(user   target_user);
void    vpg_test(user *user_ptr);
void    hba1c_test(user *user_ptr);
void    ogtt_test(user *user_ptr);
void    update_diabetic_condition(user   target_user);

void    change_detail(user *target_user_ptr, string detail, bool new_user = false)
{
    string  new_detail;

    map < string, string user_details::* > user_details_list =
    {
        {"name", &user_details::name},
        {"age", &user_details::age},
        {"phone number", &user_details::phone_number},
        {"home address", &user_details::home_address}
    };

    map < string, string access_control::* > access_control_list = 
    {
        {"username", &access_control::username},
        {"password", &access_control::password}
    };

    auto details_iterator = user_details_list.find(detail);
    auto access_iterator = access_control_list.find(detail);

    if (details_iterator != user_details_list.end())//the detail to be changed is in the user_detail struct
    {
        if (new_user == FALSE)
            cout << "Old detail\t: " << ((*target_user_ptr).details.*details_iterator->second) << endl << endl;
        cout << "Please enter your ";
        if (new_user == TRUE)
            cout << "new ";
        cout << detail << " (Press Ctrl + Z to quit): ";
        cin >> new_detail;
        if (!cin)
            return;
        else if (new_detail == ((*target_user_ptr).details.*details_iterator->second))
            error_message(7);
        else
            ((*target_user_ptr).details.*details_iterator->second) = new_detail;
    }
    else
    {
        if (new_user == FALSE)
            cout << "Old detail\t\t: " << ((*target_user_ptr).access.*access_iterator->second) << endl;
        cout << "Please enter your new " << detail << " (Press Ctrl + Z to quit): ";
        cin >> new_detail;
        if (!cin)
            return;
        else if (new_detail == ((*target_user_ptr).access.*access_iterator->second))
            error_message(7);
        else
            ((*target_user_ptr).access.*access_iterator->second) = new_detail;
    }
    return;
}

void    user_menu(user  target_user)
{
    while(1)
    {
        int choice;
        map < int, function < void(user) >> option_list;
        option_list[1] = update_condition;
        option_list[2] = make_appointment;
        option_list[3] = update_account;
        //option_list[4] = target_for_control;

        menu(target_user, "MAIN MENU", "Please choose one of the following functions to use: \n1. Update health condition.\n2. Make appointment\n3. Update account details\n4. Check targets for control (T2DM patients).", "Enter your choice: ");
        cin >> choice;
        if (!cin)
            return;
        else if (choice == 4)
            break;
        else if (option_list.find(choice) != option_list.end())
            option_list[choice](target_user);  // Call the selected function
        else if (cin.fail())
            error_message(1);
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
            menu(*user_ptr, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the random state", "Please enter your venous plasma glucose value (mmol/L) (Press CTRL + Z to quit): ");
            cin >> vpg;
            if (!cin)
                break;
            else if (vpg < 11.1)
            {
                cout << "Congradulations! You are not diagnosed as a T2DM patient.";
                user_ptr->medical.diabetic_patient = false;
                break;
            }
            else if (vpg >= 11.1)
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
    int     mode;
    double  hba1c;

    while(1)
    {
        menu(*user_ptr, "HbA1c TEST", "Welcome to HbA1c test for pre-diabetes and T2DM patients.\nYou are required to choose to enter your HbA1c value in either unit percentage or mmol/mol.\nEnter 1 for percentage and 2 for mmol/mol.\n(Press Ctrl + Z to quit)", "Please enter your choice of unit input: ");
        cin >> mode;
        if (mode == 1)
        {
            menu(*user_ptr,  "HbA1c TEST", "You have chosen the fasting state", "Please enter your HbA1c value (%) (Press Ctrl + Z to quit): ");
            cin >> hba1c;
            if (!cin)
                break;
            else if (hba1c < 5.97 && hba1c > 0)
            {
                cout << "Congradulations! You are not diagnosed as a T2DM patient.";
                user_ptr->medical.diabetic_patient = false;
                break;
            }
            else if (hba1c >= 5.7 && hba1c < 6.3)
            {
                cout << "You are diagnosed as a pre-T2DM patient.\nPlease remain calm and seek medical advices from our medical personnels.";
                user_ptr->medical.diabetic_patient = true;
                break;
            }
            else if (hba1c >= 6.3)
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
        else if (mode == 2)
        {
            menu(*user_ptr, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the random state", "Please enter your venous plasma glucose value (mmol/L) (Press CTRL + Z to quit): ");
            cin >> hba1c;
            if (!cin)
                break;
            else if (hba1c < 39 && hba1c > 0)
            {
                cout << "Congradulations! You are not diagnosed as a T2DM patient.";
                user_ptr->medical.diabetic_patient = false;
                break;
            }
            else if (hba1c >= 39 && hba1c < 45)
            {
                cout << "You are diagnosed as a pre-T2DM patient.\nPlease remain calm and seek medical advices from our medical personnels.";
                user_ptr->medical.diabetic_patient = true;
                break;
            }
            else if (hba1c >= 45)
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

void    update_diabetic_condition(user   target_user)
{
    int choice;
    map < int, function < void(user *) >> option_list;
    option_list[1] = vpg_test;
    option_list[2] = hba1c_test;
    option_list[3] = ogtt_test;
    while(1)
    {
        menu(target_user, "UPDATE DIABETIC CONDITION", "Please choose which diagnostic value would you like to use to determine your diabetic condition: \n1. Venous plasma glucose\n2. HbA1c\n3. OGTT", "Please enter your choice (Press Ctrl + Z to quit): ");
        cin >> choice;
        if (!cin)
            break;
        else if (option_list.find(choice) != option_list.end())
            option_list[choice](&target_user);  // Call the selected function
        else if (cin.fail())
            error_message(1);
        else
            error_message(2);
    }
}

void    make_appointment(user   target_user)
{
    cout << (target_user.access.username);
    return;
}

void    update_account(user   target_user)
{
    string  details_list[] = {"filler(ignore this)", "name", "age", "phone number", "home address", "username", "password"};
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

void    target_for_control(user target_user)
{
    string content;

    if(target_user.medical.diabetic_patient == false)
    {
        error_message(11);
        return;
    }
    content = "GLYCAEMIC CONTROL\n1. Fasting or pre-pandial: 4.4 mmol/L-7.0 mmol/L\n2. ";//change ltr
    menu(target_user, "TARGET FOR CONTROL", content, "Press enter to continue: ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return;
}

#endif