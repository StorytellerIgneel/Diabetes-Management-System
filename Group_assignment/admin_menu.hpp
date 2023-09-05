#pragma once
#ifndef ADMIN_MENU_HPP
#define ADMIN_MENU_HPP

#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"

void    admin_menu                      (admin admin, user user_list[]);
void    find_patient                    (user *patient, user user_list[], admin target_admin);
void    update_patient_condition        (user *patient, admin target_admin);
void    ogtt_update                     (user *user_ptr, admin target_admin);
void    prescribe_medication_control    (user *patient, admin target_admin);
void    prescribe_medication            (user *patient, admin target_admin);
void    medication_guide                (admin target_admin);
bool    get_medication                  (int *step, string prompt, string *medication, admin target_admin);
void    set_diet_control                (user   *patient, admin target_admin);
//admin main menu
void    admin_menu(admin target_admin, user user_list[])
{
    while(1)
    {
        int     choice;
        user    *patient;
        map < int, function < void(user*, admin) >> option_list;
        option_list[1] = update_patient_condition;
        option_list[2] = prescribe_medication_control;
        //option_list[3] = target_for_control;

        patient = nullptr;
        find_patient(patient, user_list, target_admin);
        cout << "Problem: " << patient->details.name;
        cin >> choice;
        
        if (patient == nullptr)
        {
            cin >> choice;
            return;
        }
            
        cout << "Entered";
        cin >> choice;
        menu(user(), target_admin, "MAIN MENU", "Please choose one of the following functions to use: \n1. Update patient health condition.\n2. Check and approve appointment\n3. Provide Medication\n4. Check patient profile", "Enter your choice: ");
        cin >> choice;
        if(exit_check(&cin))
            return;
        else if (option_list.find(choice) != option_list.end())
            option_list[choice](patient, target_admin);  // Call the selected function
        else if (cin.fail())
            error_message(1);
        else
            error_message(2);
    }
}

void    find_patient(user *patient, user   user_list[], admin target_admin)
{
    int             i;
    user            dummy;
    string          content;
    string          target_patient;

    content = "Which patient would you like to choose?\n\n";
    for(int i = 0; user_list[i].details.name != ""; i++)
        content = content + to_string(i+1) + ". " + user_list[i].details.name + "\n";
        
    while(1)
    {
        menu(user(), target_admin, "Patient selection", content, "Enter the patient name you wish to view: ");
        getline(cin, target_patient);
        if(exit_check(&cin))
            return;
        else
        {
            for(int i = 0; user_list[i].details.name != ""; i++)
            {
                if(target_patient == user_list[i].details.name)
                {
                    patient = &user_list[i];
                    return;
                }
            }
            error_message(12);
        }
    }
    return;
}

//update_patient_condition section
void    update_patient_condition(user *patient, admin target_admin)
{
    char choice;

    map <int, function <void(user*, admin)> > update_list;
    update_list[1] = vpg_test;
    update_list[2] = hba1c_test;
    update_list[3] = ogtt_update;

    while(1)
    {
        menu(*patient, target_admin, "UPDATE PATIENT CONDITION", "Here, you can update the medical condition of patients. Please choose one of the following conditions to update:\n1. vpg\n2. hba1c\n3. ogtt", "Enter the choice of medical condition to update: ");
        cin >> choice;
        if(exit_check(&cin))
            return;
        else if (isdigit(choice))
        {
            choice = (int)choice;
            if (choice >= 1 && choice <= 3)
                update_list[choice](patient, target_admin);
            else
                error_message(2);
        }
        else if (cin.fail())
            error_message(1);
        else
            error_message(1);
    }
    return;
}

void    ogtt_update(user* user_ptr, admin target_admin)
{
    int     mode;
    double  ogtt;

    while(1)
    {
        menu(user(), target_admin, "Oral Glucose Tolerance Test (OGTT)", "Welcome to update for patient ogtt value. \nYou are required to choose the time period of the OGTT test done\n1.0 hours (immediate)\n2. 2 hours", "Please enter the patient's ogtt value: ");
        cin >> mode;
        if (mode == 1)
        {
            while(1)
            {
                menu(user(), target_admin, "Oral Glucose Tolerance Test (OGTT)", "You have chosen the immediate (0 hour) time period.", "Please enter the patient's ogtt value (mmol/L): ");
                cin >> ogtt;
                if(exit_check(&cin))
                    break;
                if (ogtt < 6.1 && ogtt > 0)
                {
                    success_message(7);
                    user_ptr->medical.diabetic_patient = false;
                    return;
                }
                else if (ogtt >= 6.1 && ogtt <= 6.9 || ogtt >= 7.0)
                {
                    success_message(7);
                    user_ptr->medical.current_state = "IMPAIRED GLUCOSE (IFG)";
                    user_ptr->medical.diabetic_patient = true;
                    return;
                }
                else if (ogtt >= 7.0)
                {
                    success_message(7);
                    user_ptr->medical.current_state = "DIABETES MELLITUS (DM)";
                    user_ptr->medical.diabetic_patient = true;
                    return;
                }
                else if (cin.fail())
                    error_message(1);
                else
                    error_message(1);
            }
        }
        else if (mode == 2)
        {
            while(1)
            {
                menu(user(), target_admin, "Oral Glucose Tolerance Test (OGTT)", "You have chosen the 2hours time period.", "Please enter the patient's ogtt value (mmol/mol): ");
                cin >> ogtt;
                if(exit_check(&cin))
                    break;
                else if (ogtt < 7.8 && ogtt > 0)
                {
                    success_message(7);
                    user_ptr->medical.diabetic_patient = false;
                    return;
                }
                else if (ogtt >= 7.8 && ogtt <= 11.0)
                {
                    success_message(7);
                    user_ptr->medical.current_state = "IMPAIRED GLUCOSE TOLERANCE (IGT)";
                    user_ptr->medical.diabetic_patient = true;
                    return;
                }
                else if (ogtt >= 11.1)
                {
                    success_message(7);
                    user_ptr->medical.current_state = "DIABETES MELLITUS (DM)";
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
}

//////HAVENT COMPLETE
//prescribe_medication section
void    prescribe_medication_control(user   *patient, admin target_admin) //control access to the actual function
{
    int choice;
    map <int, function<void(user* , admin)>> option_list;
    option_list[1] = set_diet_control;
    option_list[2] = prescribe_medication;

    while(1)
    {
        menu(user(), target_admin, "ISSUE MEDICATION ", "Choose one of the following to issue/prescriibe:\n1. Diet control\n2. Medications (OGLDs) \n3. Insulin", "Press y to continue and n to quit.");
        cin >> choice;
        if(exit_check(&cin))
            return;
        else if (choice <= 3  && choice >= 1)
            option_list[choice](patient, target_admin);
        else if (cin.fail())
            error_message(1);
        else
            error_message(2);
    }
    return;
}

void    prescribe_medication(user   *patient, admin target_admin)
{
    string  choice;
    string  medication;
    string  for_menu;
    string  *name;
    string  *formulation;
    string  *unit;
    string  *frequency;
    string  *note;
    int     *step;

    *step = 1;
    menu(user(), target_admin, "MEDICATION PRESCRIPTION", "Enter the details of the medication prescription for the patient here.\nYou can press g or G to show the guide for the medication prescription.\nYou can also press B or b to go back to the previous step.");
    while(1)
    {
        if (*step == 1)
            if (get_medication(step, "Enter the name of the drug: ", name, target_admin))
                return;
        if (*step == 2)
            if (get_medication(step, "Enter the formulation of the drug: ", formulation, target_admin))
                return;
        if (*step == 3)
            if (get_medication(step, "Enter the unit of the drug formulation: ", unit, target_admin))
                return;
        if (*step == 4)
            if (get_medication(step, "Enter the number of times for the drug to be ingested per day: ", frequency, target_admin))
                return;
        if (*step == 5)
            if (get_medication(step, "Are there any extra notes you would like to add to the prescription of the medication?\nPress n if you don't have any: ", note, target_admin))
                return;
        if (*step == 6)
            break;
    }
    medication = "Your medication is:\n" + *formulation + " " + *unit + " of " + *name + ".\nPlease take the drug " + *frequency + " times a day.\nFor more information, please contact your doctor.";
    if (*note != "No extra note")
        for_menu = medication + "\nExtra note from doctor: " + *note;
    else
        for_menu = medication;
    while(1)
    {
        menu(user(), target_admin, "Medication Prescription", "The medication you have prescribed is:\n" + for_menu, "Are you sure that you want to prescribe this medication for the patient? Do double check before confirming,\nPress y for yes and n to quit: ");
        cin >> choice;
        if(!cin || choice == "n" || choice == "N")
            return;
        else if (choice == "y" || choice == "Y")
        {
            success_message(9);
            patient->medical.medication = medication;
            patient->medical.medication_note = *note;
            return;
        }
        else
            error_message(2);
    }
    return;
}

void    medication_guide(admin target_admin)
{
    ifstream    print_guide("medication_guide.txt", ios::in);
    string      line;
    string      for_menu;
    string      dummy;

    for_menu = "This is the guide for the medication prescription: \n";
    while(getline(print_guide, line))
        for_menu += line;
    menu(user(), target_admin, "Medication Prescription Guide", for_menu, "Press enter to continue.");
    cin >> dummy;
    print_guide.close();
    return;
}

bool    get_medication(int *step, string prompt, string *medication, admin target_admin)
{
    while(1)
    {
        cout << prompt;
        getline(cin, *medication);
        if(exit_check(&cin))
            return 1;
        else if(*medication == "G" || *medication == "g")
            medication_guide(target_admin);
        else if (*step != 1 && (*medication == "B" || *medication == "b"))
        {
            *step -= 1;
            return 0;
        }
        else if (*step == 5 && (*medication == "Y" || *medication == "y"))
        {
            *medication = "Extra note: " + *medication;
            return 0;
        }
        else if (*step == 5 && (*medication == "N" || *medication == "n"))
        {
            *medication = "No extra note";
            return 0;
        }
        else
        {
            *step += 1;
            return 0;
        }
    }
    return 0;
}

void set_diet_control(user   *patient, admin target_admin)
{
    string  choice;
    while(1)
    {
        menu(user(), target_admin, "Issue Diet Control", "You are about to issue a diet for the patient, continue?", "Press \"y\" to continue or \"n\" to cancel : ");
        cin >> choice;
        if(!cin || choice == "n" || choice == "N")
        {
            cin.clear();
            return;
        }
        else if (choice == "y" || choice == "Y")
        {
            patient->medical.diet = true;
            success_message(8);
            return;
        }
        else if (cin.fail())
            error_message(1);
        else
            error_message(2);
    }
}

#endif