#pragma once
#ifndef USER_MENU_HPP
#define USER_MENU_HPP
#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"
#include "user_menu_diet.hpp"

void    user_menu                   (user *patient);
void    update_condition            (user *patient);
void    update_diabetic_condition   (user *patient);
void    vpg_test                    (user *patient, admin);
void    hba1c_test                  (user *patient, admin);
void    make_appointment            (user *patient);
void    update_account              (user *patient);
void    target_for_control          (user *patient);
void    receive_medication          (user *patient);
bool    change_detail               (user *patient, string detail, bool new_user = false);

//user main menu
void    user_menu(user  *patient)
{
    while(1)
    {
        string  choice_str;
        int     choice_int;
        map < int, function < void(user*) >> option_list;
        option_list[1] = update_condition;
        option_list[2] = make_appointment;
        option_list[3] = update_account;
        option_list[4] = target_for_control;
        option_list[5] = receive_medication;

        if ((*patient).medical.medication_received == true)
            notification("You have received a medication prescription from your doctor. Please proceed to the section 'receive medication' to view the details.");
        menu(*patient, admin(), "MAIN MENU", "Please choose one of the following functions to use: \n1. Update health condition.\n2. Make appointment\n3. Update account details\n4. Recommendations and suggestions on target for control (T2DM patient only)\n5. Receive medication (T2DM patient only)", "Enter your choice: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if(is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
                option_list[choice_int](patient);  // Call the selected function
            else
                error_message(2);
        }
        else
            error_message(1);
    }
}

//update condition section
void    update_condition(user   *patient)
{
    string  choice_str;
    int     choice_int;
    map < int, function < void(user *) >> option_list;
    option_list[1] = update_diabetic_condition;
    option_list[2] = update_meal_record;
    
    while(1)
    {
        menu(*patient, admin(), "UPDATE MEDICAL CONDITION", "You can update your medical conditions here.\nPlease select which medical condition to update: \n1. Diabetic patient confirmation\n2. Update meal record", "Please enter your choice: ", false);
        getline(cin, choice_str);            
        if(exit_check(&cin))
            return;
        if(is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
                option_list[choice_int](patient);  // Call the selected function
            else
                error_message(2);
        }
        else
            error_message(1);        
    }
    
    return;
}

void    update_diabetic_condition(user   *patient)
{
    string  choice_str;
    int     choice_int;
    map < int, function < void(user *, admin) >> option_list;
    option_list[1] = vpg_test;
    option_list[2] = hba1c_test;
    //ogtt not here as it is limited to the admin (doctor)
    while(1)
    {
        menu(*patient, admin(), "UPDATE DIABETIC CONDITION", "Please choose which diagnostic value would you like to use to determine your diabetic condition: \n1. Venous plasma glucose\n2. HbA1c\n3. OGTT", "Please enter your choice (Press Ctrl + Z to quit): ");
        getline(cin, choice_str);            
        if(exit_check(&cin))
            return;
        if(is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
                option_list[choice_int](patient, admin());  // Call the selected function
            else
                error_message(2);
        }
        else
            error_message(1);        
    }
}

void    vpg_test(user *patient, admin target_admin)
{
    string  choice_str;;
    string  vpg_str;
    int     choice_int;
    double  vpg_double;
    bool    is_user;

    is_user = false;
    if (patient->access.username != "")
        is_user = true;
    while(1)
    {
        if (is_user)
            menu(*patient, admin(), "VENOUS PLASMA GLUCOSE TEST", "Welcome to Venous Plasma Glucose test for T2DM. \nPlease choose your current state, whether you are doing the test under fasting or random conditions.\n1. Fasting\n2. Random.", "Please enter your choice: ");
        else
            menu(user(), target_admin, "VENOUS PLASMA GLUCOSE TEST", "Welcome to Venous Plasma Glucose condition update for T2DM patients.\nPlease choose the patient's current state, whether under fasting or random conditions.\n1. Fasting\n2. Random.", "Please enter your choice: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if(is_number(choice_str, &choice_int))
        {
            if (choice_int == 1)
            {
                while(1)
                {
                    if(is_user)
                        menu(*patient, admin(), "VENOUS PLASMA GLUCOSE TEST", "You have chosen the fasting state", "Please enter your venous plasma glucose value (mmol/L): ");
                    else
                        menu(*patient, target_admin, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the fasting state", "Please enter the patient's venous plasma glucose value (mmol/L): ");
                    getline(cin, vpg_str);
                    if(exit_check(&cin))
                        break;
                    if(is_double(vpg_str, &vpg_double))
                    {
                        if (vpg_double < 7.00 && vpg_double > 0)
                        {
                            if(is_user)
                                success_message(11);
                            else
                                success_message(5);
                            patient->medical.vpg = vpg_double;
                            return;
                        }
                        else if (vpg_double >= 7.00)
                        {
                            if (is_user)
                                cout << "You are diagnosed as a T2DM patient.\nPlease remain calm and seek medical advices from our medical personnels.";
                            else
                                success_message(5);
                            patient->medical.vpg = vpg_double;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else
                            error_message(1);
                    }
                    else
                        error_message(1);
                }  
            }
            else if (choice_int == 2)
            {
                while(1)
                {
                    if (is_user)
                        menu(*patient, admin(), "VENOUS PLASMA GLUCOSE TEST", "You have chosen the random state", "Please enter your venous plasma glucose value (mmol/L): ");
                    else
                        menu(*patient, target_admin, "VENOUS PLASMA GLUCOSE TEST", "You have chosen the random state", "Please enter the patient's venous plasma glucose value (mmol/L): ");
                    getline(cin, vpg_str);
                    if(exit_check(&cin))
                        break;
                    if(is_double(vpg_str, &vpg_double))
                    {
                        if (vpg_double < 11.1)
                        {
                            if (vpg_double < 3.9) // hypoglycaemia
                            {
                                if(is_user)
                                    success_message(16);
                                else
                                    success_message(13);
                                patient->medical.vpg = vpg_double;
                                patient->medical.hypoglycaemia = true;
                            }
                            else if (vpg_double >= 10 && vpg_double <= 11.1) // hyperglycaemia
                            {
                                if(is_user)
                                    success_message(17);
                                else
                                    success_message(14);
                                patient->medical.vpg = vpg_double;
                                patient->medical.hyperglycaemia = true;
                            }
                            else // normal
                            {
                                if(is_user)
                                    success_message(11);
                                else
                                    success_message(5);
                                patient->medical.vpg = vpg_double;
                                return;
                            }
                        }
                        else if (vpg_double >= 11.1)
                        {
                            if(is_user)
                                success_message(15);
                            else
                                success_message(5);
                            patient->medical.vpg = vpg_double;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else
                            error_message(10);
                    }
                    else
                        error_message(1);
                }
            }
        }
        else
            error_message(1);
    }
    return;
}

void    hba1c_test(user *patient, admin target_admin)
{
    string  mode_str;
    string  hba1c_str;
    int     mode_int;
    double  hba1c_double;
    bool    is_user;

    is_user = false;
    if (patient->access.username != "")
        is_user = true;
    while(1)
    {
        if(is_user)
            menu(*patient, admin(), "HbA1c TEST", "Welcome to HbA1c test for pre-diabetes and T2DM patients.\nYou are required to enter your HbA1c value in unit percentage.\n", "Please enter your HbA1c value (%): ");
        else
            menu(*patient, target_admin, "HbA1c TEST", "Welcome to update for pre-diabetes and T2DM patient HbA1c value. \nYou are required to enter the patient's HbA1c value in unit percentage.\n", "Please enter the patient's HbA1c value: ");
        getline(cin, hba1c_str);
        if(exit_check(&cin))
            return; 
        if(is_double(hba1c_str, &hba1c_double))
        {
            if (hba1c_double < 5.7 && hba1c_double > 0)
            {
                if (hba1c_double < 4.1) //hypoglycaemia
                {
                    success_message(16);
                    patient->medical.hba1c = hba1c_double;
                    patient->medical.hypoglycaemia = true;
                }
                else // normal
                {
                    success_message(11);
                    patient->medical.hba1c = hba1c_double;
                    return;
                }
            }
            else if (hba1c_double >= 5.7 && hba1c_double < 6.3)
            {
                success_message(18);
                patient->medical.hba1c = hba1c_double;
                patient->medical.diabetic_patient = true;
                return;
            }
            else if (hba1c_double >= 6.3)
            {
                success_message(18);
                patient->medical.hba1c = hba1c_double;
                patient->medical.diabetic_patient = true;
                return;
            }
            else
                error_message(2);
        }
        else
            error_message(1);
    }
}

//update account section
bool    change_detail(user *patient, string detail, bool new_user)
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
            cout << "Old detail\t: " << ((*patient).details.*details_iterator->second) << endl << endl;
        cout << "Please enter your ";
        if (new_user != TRUE)
            cout << "new ";
        cout << detail << " (Press Ctrl + Z to quit): ";
        getline(cin, new_detail);
        if(exit_check(&cin))
            return EXIT;
        else if (new_detail == ((*patient).details.*details_iterator->second) && new_user == FALSE)
            error_message(7);
        else
            ((*patient).details.*details_iterator->second) = new_detail;
    }
    else
    {
        if (new_user == FALSE)
            cout << "Old detail\t\t: " << ((*patient).access.*access_iterator->second) << endl;
        cout << "Please enter your new " << detail << " (Press Ctrl + Z to quit): ";
        getline(cin, new_detail);
        if(exit_check(&cin))
            return EXIT;
        else if (new_detail == ((*patient).access.*access_iterator->second) && new_user == FALSE)
            error_message(7);
        else
            ((*patient).access.*access_iterator->second) = new_detail;
    }
    if(new_user == false)
        success_message(3);
    return CONTINUE;
}

///7/9

void    update_account(user   *patient)
{
    string  details_list[] = {"filler(ignore this)", "name", "age", "phone number", "home address", "username", "password"};
    string  choice_str;
    int     choice_int;

    while(1)
    {
        menu(*patient, admin(), "UPDATE ACCOUNT DETAILS", "Please choose which detail you wish to change: \n1. Name\n2. Age\n3. Phone number\n4. Home address\n5. Username\n6. Password", "Enter your choice: ", 1);
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if (is_number(choice_str, &choice_int))
        {
            if (choice_int >= 1 &&  choice_int <= 6)
                change_detail(patient, details_list[choice_int]);
            else
                error_message(2);
        }   
        else
            error_message(1);
    }
    return;
}

//target for control section
void    target_for_control(user *patient)
{
    string  content;
    string  choice_str;
    int     choice_int;

    if(patient->medical.diabetic_patient == false)
    {
        error_message(11);
        return;
    }
    while(1)
    {
        menu(*patient, admin(), "TARGET FOR CONTROL", "You can see a variety of suggestions and recommendations for your diabetes control here.\nPlease choose one of the following to see:\n\n1. Target levels for various medical parameters\n2. Individualised HbA1c targets based on patient profile\n3. Principal recommendation", "Press enter your choice: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if (is_number(choice_str, &choice_int))
        {
            if (choice_int == 1)
            {
                //
            }
            else if (choice_int == 2)
            {
                if(stoi(patient->details.age) < 40)
                    menu(*patient, admin(), "Individualised HbA1c targets", "Your HbA1c target is <= 6.5% (Tight)\nThis is because your fulfil the following conditions: ", "Press Enter to continue", false, "hba1c_tight.txt");
                
            }
            else
                error_message(2);
        }
        else
            error_message(1);
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
    string      choice;
    string      filename = patient->details.name + "_medication.txt";
    string      for_menu;
    ofstream    out_file_medication(filename, ios::in);

    for_menu = "You can view your medications here.\nThe following is the medication prescribed to you by your doctor:\n\n" + patient->medical.medication;
    while(1)
    {
        menu(*patient, admin(), "RECEIVE MEDICATION", for_menu, "Would you like to print this out?\nPress y for yes and n for no: ");
        getline(cin, choice);
        if(exit_check(&cin))
            return;
        else if (choice == "Y" || choice == "y")
        {
            out_file_medication << patient->medical.medication;
            patient->medical.medication = "\n";
            patient->medical.medication_received = false;
            success_message(4);
            return;
        }
        else if (choice == "N" || choice == "n")
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
        //else if (patient.medical.insulin == true)
    }
    else {
        std::cout << "Good night!" << std::endl;
    }
}
#endif