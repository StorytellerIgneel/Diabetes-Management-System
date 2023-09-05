#pragma once
#ifndef USER_MENU_HPP
#define USER_MENU_HPP
#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"

void    user_menu                   (user *target_user);
void    update_condition            (user *target_user);
void    update_diabetic_condition   (user *target_user);
void    vpg_test                    (user *user_ptr, admin);
void    hba1c_test                  (user *user_ptr, admin);
void    make_appointment            (user *target_user);
void    update_account              (user *target_user);
void    change_detail               (user *target_user_ptr, string detail, bool new_user = false);
void    target_for_control          (user *target_user);
void    receive_medication          (user *target_user);

//user main menu
void    user_menu(user  *target_user)
{
    while(1)
    {
        int choice;
        map < int, function < void(user*) >> option_list;
        option_list[1] = update_condition;
        option_list[2] = make_appointment;
        option_list[3] = update_account;
        option_list[4] = target_for_control;
        option_list[5] = receive_medication;

        if ((*target_user).medical.medication_received == true)
            notification("You have received a medication prescription from your doctor. Please proceed to the section 'receive medication' to view the details.");
        menu(*target_user, admin(), "MAIN MENU", "Please choose one of the following functions to use: \n1. Update health condition.\n2. Make appointment\n3. Update account details\n4. Recommendations and suggestions on target for control (T2DM patient only)\n5. Receive medication (T2DM patient only)", "Enter your choice: ");
        cin >> choice;
        if (!cin)
        {
            cin.clear();
            return;
        }
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

//update condition section
void    update_condition(user   *target_user)
{
    menu(*target_user, admin(), "UPDATE MEDICAL CONDITION", "You can update your medical conditions here.\nPlease select which medical condition to update: \n1. Diabetic patient confirmation", "Please enter your choice: ", false);
    map < int, function < void(user *) >> option_list;
    //option_list[1] = update_diabetic_condition;
    
    return;
}

void    update_diabetic_condition(user   *target_user)
{
    int choice;
    map < int, function < void(user *, admin) >> option_list;
    option_list[1] = vpg_test;
    option_list[2] = hba1c_test;
    //option_list[3] = ogtt_test;
    while(1)
    {
        menu(*target_user, admin(), "UPDATE DIABETIC CONDITION", "Please choose which diagnostic value would you like to use to determine your diabetic condition: \n1. Venous plasma glucose\n2. HbA1c\n3. OGTT", "Please enter your choice (Press Ctrl + Z to quit): ");
        cin >> choice;
        if (!cin)
        {
            cin.clear();
            return;
        }
        else if (option_list.find(choice) != option_list.end())
            option_list[choice](target_user, admin());  // Call the selected function
        else if (cin.fail())
            error_message(1);
        else
            error_message(2);
    }
}

void    vpg_test(user *user_ptr, admin target_admin)
{
    int     state;
    double  vpg;
    bool    is_user;

    is_user = false;
    if (user_ptr->access.username != "")
        is_user = true;
    while(1)
    {
        if (is_user)
            menu(*user_ptr, admin(), "VENOUS PLASMA GLUCOSE TEST", "Welcome to Venous Plasma Glucose test for T2DM. \nPlease choose your current state, whether you are doing the test under fasting or random conditions.Press 1 for fasting and 2 for random.", "Please enter your choice: ");
        else
            menu(user(), target_admin, "VENOUS PLASMA GLUCOSE TEST", "Welcome to Venous Plasma Glucose condition update for T2DM patients.\nPlease choose the patient's current state, whether under fasting or random conditions.Press 1 for fasting and 2 for random.", "Please enter your choice: ");
        cin >> state;
        if(exit_check(&cin))
            return;
        if (state == 1)
        {
            while(1)
            {
                if(is_user)
                    menu(*user_ptr, admin(), "VENOUS PLASMA GLUCOSE TEST", "You have chosen the fasting state", "Please enter your venous plasma glucose value (mmol/L): ");
                else
                    menu(user(), target_admin, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the fasting state", "Please enter the patient's venous plasma glucose value (mmol/L): ");
                cin >> vpg;
                if(exit_check(&cin))
                    break;
                else if (vpg < 7.00 && vpg > 0)
                {
                    if(is_user)
                        cout << "Congradulations! You are not diagnosed as a T2DM patient.";
                    else
                        success_message(5);
                    user_ptr->medical.diabetic_patient = false;
                    return;
                }
                else if (vpg >= 7.00)
                {
                    if (is_user)
                        cout << "You are diagnosed as a T2DM patient.\nPlease remain calm and seek medical advices from our medical personnels.";
                    else
                        success_message(5);
                    user_ptr->medical.diabetic_patient = true;
                    return;
                }
                else if (cin.fail())
                    error_message(1);
                else
                    error_message(1);
            }
            
        }
        else if (state == 2)
        {
            while(1)
            {
                if (is_user)
                    menu(*user_ptr, admin(), "VENOUS PLASMA GLUCOSE TEST", "You have chosen the random state", "Please enter your venous plasma glucose value (mmol/L): ");
                else
                    menu(user(), target_admin, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the random state", "Please enter the patient's venous plasma glucose value (mmol/L): ");
                cin >> vpg;
                if(exit_check(&cin))
                    break;
                else if (vpg < 11.1)
                {
                    if(is_user)
                        cout << "Congradulations! You are not diagnosed as a T2DM patient.";
                    else
                        success_message(5);
                    user_ptr->medical.diabetic_patient = false;
                    return;
                }
                else if (vpg >= 11.1)
                {
                    if(is_user)
                        cout << "You are diagnosed as a T2DM patient.\nPlease remain calm and seek medical advices from our medical personnels.";
                    else
                        success_message(5);
                    user_ptr->medical.diabetic_patient = true;
                    return;
                }
                else if (cin.fail())
                    error_message(1);
                else
                    error_message(10);
            }
        }
    }
    return;
}

void    hba1c_test(user *user_ptr, admin target_admin)
{
    int     mode;
    double  hba1c;
    bool    is_user;

    is_user = false;
    if (user_ptr->access.username != "")
        is_user = true;
    while(1)
    {
        if(is_user)
            menu(*user_ptr, admin(), "HbA1c TEST", "Welcome to HbA1c test for pre-diabetes and T2DM patients.\nYou are required to enter your HbA1c value in unit percentage.\n", "Please enter your HbA1c value: ");
        else
            menu(user(), target_admin, "HbA1c TEST", "Welcome to update for pre-diabetes and T2DM patient HbA1c value. \nYou are required to enter the patient's HbA1c value in unit percentage.\n", "Please enter the patient's HbA1c value: ");
        cin >> mode;
        if (mode == 1)
        {
            menu(*user_ptr, admin(), "HbA1c TEST", "You have chosen to enter your HbA1c value in unit percentage.", "Please enter your HbA1c value (%) (Press Ctrl + Z to quit): ");
            cin >> hba1c;
            if (!cin)
            {
                cin.clear();
                return;
            }
            else if (hba1c < 5.7 && hba1c > 0)
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
            menu(*user_ptr, admin(), "HbA1c TEST", "You have chosen to enter your HbA1c value in unit mmol/mol.", "Please enter your HbA1c value (mmol/mol) (Press CTRL + Z to quit): ");
            cin >> hba1c;
            if (!cin)
            {
                cin.clear();
                return;
            }
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

//make appointment section
void    make_appointment(user   *target_user)
{
    cout << (target_user->access.username);
    return;
}

//update account section
void    change_detail(user *target_user_ptr, string detail, bool new_user)
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
        {
            cin.clear();
            return;
        }
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
        {
            cin.clear();
            return;
        }
        else if (new_detail == ((*target_user_ptr).access.*access_iterator->second))
            error_message(7);
        else
            ((*target_user_ptr).access.*access_iterator->second) = new_detail;
    }
    if(new_user == false)
        success_message(3);
    return;
}

void    update_account(user   *target_user)
{
    string  details_list[] = {"filler(ignore this)", "name", "age", "phone number", "home address", "username", "password"};
    int     choice;

    while(1)
    {
        try
        {
            menu(*target_user, admin(), "UPDATE ACCOUNT DETAILS", "Please choose which detail you wish to change: \n1. Name\n2. Age\n3. Phone number\n4. Home address\n5. Username\n6. Password", "Enter your choice: ", 1);
            cin >> choice;
            if (!cin)
            {
                cin.clear();
                return;
            }
            change_detail(target_user, details_list[choice]);
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

//target for control section
void    target_for_control(user *target_user)
{
    string content;
    int     choice;

    if(target_user->medical.diabetic_patient == false)
    {
        error_message(11);
        return;
    }
    while(1)
    {
        menu(*target_user, admin(), "TARGET FOR CONTROL", "You can see a variety of suggestions and recommendations for your diabetes control here.\nPlease choose one of the following to see:\n\n1. Target levels for various medical parameters\n2. Individualised HbA1c targets based on patient profile\n3. Principal recommendation\n0. Exit", "Press enter your choice: ");
        cin >> choice;
        if (!cin)
        {
            cin.clear();
            return;
        }
        else if (choice == 1)
        {
            //
        }
        else if (choice == 2)
        {
            if(stoi(target_user->details.age) < 40)
            {
                cout << "Your HbA1c target is <= 6.5% (Tight)";
            }
        }
        else if (cin.fail())
            error_message(1);
        else
            error_message(2);
    }
    return;
}

//receive medication section
void    receive_medication (user *patient)
{
    if (patient->medical.medication_received == false)
    {
        error_message(13);
        return;
    }
    char        choice;
    string      filename = patient->details.name + "_medication.txt";
    string      for_menu;
    ofstream    out_file_medication(filename, ios::in);

    for_menu = "You can view your medications here.\nThe following is the medication prescribed to you by your doctor:\n\n" + patient->medical.medication;
    while(1)
    {
        menu(*patient, admin(), "RECEIVE MEDICATION", for_menu, "Would you like to print this out?\nPress y for yes and n for no: ");
        cin >> choice;
        if (!cin)
        {
            cin.clear();
            return;
        }
        else if (choice == 'Y' || choice == 'y')
        {
            out_file_medication << patient->medical.medication;
            patient->medical.medication = "\n";
            patient->medical.medication_received = false;
            success_message(4);
            return;
        }
        else if (choice == 'N' || choice == 'n')
        {
            patient->medical.medication = "\n";
            patient->medical.medication_received = false;
            return;
        }
        else
            error_message(1);
    }
    return;
}

//incomplete
void    reminder(user patient)
{
    auto    now = chrono::system_clock::now();
    int     current_hour;
    time_t  current_time;
    tm*     time_info;
    string  reason;

    current_time = chrono::system_clock::to_time_t(now);
    time_info    = localtime(&current_time);
    current_hour = time_info->tm_hour;
    reason = "This is because u are under: ";

    if (current_hour >= 5 && current_hour < 12) //morning (breakfast)
    {
        if (patient.medical.diet == true || patient.medical.medication != "No precription" || patient.medical.insulin == true)
        {
            if (patient.medical.diet == true)
                reason += "\nDiet treatment";
            if (patient.medical.medication != "No precription")
                reason += "\nOral Glucose Lowering Drugs (OGLDs) treatment";
            if (patient.medical.insulin == true)
                reason += "\nInsulin treatment";
            notification("Good Morning. You are required to do a Self Monitoring Blood Glucose (SMBG) test both BEFORE and AFTER your breakfast and record your results in the section 1 'Update health condition'.\nPlease be informed that you are not permitted to leave the system before you do so.");
        }
    }
    else if (current_hour >= 12 && current_hour < 18) //afternnoon (lunch)
    {
        if (patient.medical.diet == true || patient.medical.medication != "No precription")
        {
            if (patient.medical.diet == true)
                reason += "\nDiet treatment";
            if (patient.medical.medication != "No precription")
                reason += "\nOral Glucose Lowering Drugs (OGLDs) treatment";
            if (patient.medical.insulin == true)
                reason += "\nInsulin treatment";
            notification("Good Morning. You are required to do the Self Monitoring Blood Glucose (SMBG) and record your results in the section 1 'Update health condition'.\nPlease be informed that you are not permitted to leave the system before you do so.");
        }
        else if (patient.medical.insulin == true)
    }
    else {
        std::cout << "Good night!" << std::endl;
    }
}
#endif