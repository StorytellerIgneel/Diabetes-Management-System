#pragma once
#ifndef ADMIN_MENU_HPP
#define ADMIN_MENU_HPP

#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"
#include "user_menu.hpp"

void    admin_menu                      (admin admin, user user_list[]);
void    find_patient                    (user **patient, user user_list[], admin target_admin);
void    update_patient_condition        (user *patient, admin target_admin);
void    ogtt_update                     (user *patient, admin target_admin);
void    prescribe_medication_control    (user *patient, admin target_admin);
void    prescribe_medication            (user *patient, admin target_admin);
void    medication_guide                (admin target_admin);
bool    get_medication                  (int *step, string prompt, string *medication, admin target_admin);
void    set_diet_control                (user   *patient, admin target_admin);
void    check_medical_guides            (user* patient, admin target_admin);
//admin main menu
void    admin_menu(admin target_admin, user user_list[])
{
    while(1)
    {
        int     choice_int;
        string  choice_str;
        user    *patient;
        map < int, function < void(user*, admin) >> option_list;
        option_list[1] = update_patient_condition;
        option_list[2] = prescribe_medication_control;
        option_list[5] = check_medical_guides;
        //option_list[3] = target_for_control;

        patient = nullptr;
        find_patient(&patient, user_list, target_admin);
        menu(*patient, target_admin, "MAIN MENU", "Please choose one of the following functions to use: \n1. Update patient health condition.\n2. Check and approve appointment\n3. Provide Medication\n4. Check patient profile\n5. Check medical guides", "Enter your choice: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if (is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
                option_list[choice_int](patient, target_admin);  // Call the selected function
            else
                error_message(2);
        }
        else
            error_message(1);
    }
}

void    find_patient(user **patient, user   user_list[], admin target_admin)
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
                    success_message(10);
                    *patient = &user_list[i];
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
    string  choice_str;
    int     choice_int;

    map <int, function <void(user*, admin)> > update_list;
    update_list[1] = vpg_test;
    update_list[2] = hba1c_test;
    update_list[3] = ogtt_update;

    while(1)
    {
        menu(*patient, target_admin, "UPDATE PATIENT CONDITION", "Here, you can update the medical condition of patients. Please choose one of the following conditions to update:\n1. vpg\n2. hba1c\n3. ogtt", "Enter the choice of medical condition to update: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if (is_number(choice_str, &choice_int))
        {
            if (update_list.find(choice_int) != update_list.end())
                update_list[choice_int](patient, target_admin);
            else
                error_message(2);
        }
        else
            error_message(1);
    }
    return;
}

//8/9
void    ogtt_update(user* patient, admin target_admin)
{
    string  mode_str;
    string  ogtt_str;
    int     mode_int;
    double  ogtt_double;


    while(1)
    {
        menu(*patient, target_admin, "Oral Glucose Tolerance Test (OGTT)", "Welcome to update for patient ogtt value. \nYou are required to choose the time period of the OGTT test done\n1.0 hours (immediate)\n2. 2 hours", "Please enter the patient's ogtt value: ");
        getline(cin, mode_str);
        if (is_number(mode_str, &mode_int))
        {
            if (mode_int == 1)
            {
                while(1)
                {
                    menu(*patient, target_admin, "Oral Glucose Tolerance Test (OGTT)", "You have chosen the immediate (0 hour) time period.", "Please enter the patient's ogtt value (mmol/L): ");
                    getline(cin, ogtt_str);
                    if(exit_check(&cin))
                        break;
                    if (is_double(ogtt_str, &ogtt_double))
                    {
                        if (ogtt_double < 6.1 && ogtt_double > 0)
                        {
                            success_message(7);
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = false;
                            return;
                        }
                        else if (ogtt_double >= 6.1 && ogtt_double <= 6.9 || ogtt_double >= 7.0)
                        {
                            success_message(7);
                            patient->medical.current_state = "IMPAIRED GLUCOSE (IFG)";
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else if (ogtt_double >= 7.0)
                        {
                            success_message(7);
                            patient->medical.current_state = "DIABETES MELLITUS (DM)";
                            patient->medical.ogtt = ogtt_double;
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
            else if (mode_int == 2)
            {
                while(1)
                {
                    menu(*patient, target_admin, "Oral Glucose Tolerance Test (OGTT)", "You have chosen the 2hours time period.", "Please enter the patient's ogtt value (mmol/mol): ");
                    getline(cin, ogtt_str);
                    if(exit_check(&cin))
                        break;
                    if (is_double(ogtt_str, &ogtt_double))
                    {
                        if (ogtt_double < 7.8 && ogtt_double > 0)
                        {
                            success_message(7);
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = false;
                            return;
                        }
                        else if (ogtt_double >= 7.8 && ogtt_double <= 11.0)
                        {
                            success_message(7);
                            patient->medical.current_state = "IMPAIRED GLUCOSE TOLERANCE (IGT)";
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else if (ogtt_double >= 11.1)
                        {
                            success_message(7);
                            patient->medical.current_state = "DIABETES MELLITUS (DM)";
                            patient->medical.ogtt = ogtt_double;
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
}

//////HAVENT COMPLETE
//prescribe_medication section
void    prescribe_medication_control(user   *patient, admin target_admin) //control access to the actual function
{
    string  choice_str;
    int     choice_int;
    map <int, function<void(user* , admin)>> option_list;
    option_list[1] = set_diet_control;
    option_list[2] = prescribe_medication;

    while(1)
    {
        menu(*patient, target_admin, "ISSUE MEDICATION ", "Choose one of the following to issue/prescriibe:\n1. Diet control\n2. Medications (OGLDs) \n3. Insulin", "Press y to continue and n to quit.");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if (is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
                option_list[choice_int](patient, target_admin);
            else
                error_message(2);
        }
        else
            error_message(1);
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
    menu(*patient, target_admin, "MEDICATION PRESCRIPTION", "Enter the details of the medication prescription for the patient here.\nYou can press g or G to show the guide for the medication prescription.\nYou can also press B or b to go back to the previous step.");
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
        menu(*patient, target_admin, "Medication Prescription", "The medication you have prescribed is:\n" + for_menu, "Are you sure that you want to prescribe this medication for the patient? Do double check before confirming,\nPress y for yes and n to quit: ");
        getline(cin, choice);
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
        menu(*patient, target_admin, "Issue Diet Control", "You are about to issue a diet for the patient, continue?", "Press \"y\" to continue or \"n\" to cancel : ");
        getline(cin, choice);
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

//check medical guide
void    check_medical_guides(user* patient, admin target_admin)
{
    string  filename_list[] = {"filler", "t2dm_management.txt", "control_targets.txt", "individualised_hba1c_target.txt", "principle_recommend.txt", "SMBG_recommendation.txt", "medication_guide.txt", "newly_diagnosed_treatment.txt", "clinic_followup_treatment.txt"};
    string  choice_str;
    int     choice_int;

    while(1)
    {
        menu(*patient, target_admin, "Medical Guides Checking", "Please choose one of the following medical guides to check on: \n1. Management of T2DM\n2. T2DM: Targets for control\n3. Individualised HbA1c targets based on patient profile\n4. Principal recommendation: Medical nutrition therapy & lifestyle modification\n5. Recommendations for SMBG\n6. OGLD prescription guide\n7. Treatment algorithm: Newly diagnosed T2DM\n8. Treatment recommendations: Clinic follow-up", "Enter your choice: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if (is_number(choice_str, &choice_int))
        {
            if (choice_int >= 1 && choice_int <= 8)
            {
                while(1)
                {
                    menu(*patient, target_admin, "Medical Guides Checking", "The medical guide is as follows: ", "Would you like to change the content of the guide?\nPress y for yes and n for no: ", false, filename_list[choice_int]);
                    getline(cin, choice_str);
                    if (choice_str == "Y" || choice_str == "y")
                    {
                        cout << "Please open the current directory and enter the new content of the medical guide in the text file with the name: " << filename_list[choice_int];
                        cout << "If you are done, please type 'ok': ";
                        getline(cin, choice_str);
                        return;
                    }
                    else
                        return;
                }   
            }
            else
                error_message(2);
        }
        else
            error_message(1);
    }   
}
#endif