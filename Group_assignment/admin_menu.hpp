#pragma once
#ifndef ADMIN_MENU_HPP
#define ADMIN_MENU_HPP

#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"

void    admin_menu                      (admin admin, user user_list[]);
user    find_patient                    (user user_list[]);
void    update_patient_condition        (user *patient, admin target_admin);
void    prescribe_medication_control    (user *patient, admin target_admin);
void    prescribe_medication            (user *patient, admin target_admin);
//admin main menu
void    admin_menu(admin target_admin, user user_list[])
{
    while(1)
    {
        int     choice;
        user    patient;
        map < int, function < void(user*, admin) >> option_list;
        option_list[1] = update_patient_condition;
        option_list[2] = prescribe_medication_control;
        //option_list[4] = target_for_control;

        patient = find_patient(user_list);
        menu(user(), target_admin, "MAIN MENU", "Please choose one of the following functions to use: \n1. Update patient health condition.\n2. Check and approve appointment\n3. Provide Medication\n4. Check patient profile", "Enter your choice: ");
        cin >> choice;
        if (!cin)
        {
            cin.clear();
            return;
        }
        else if (option_list.find(choice) != option_list.end())
            option_list[choice](&patient, target_admin);  // Call the selected function
        else if (cin.fail())
            error_message(1);
        else
            error_message(2);
    }
}

user    find_patient(user   user_list[])
{
    int             i;
    user            dummy;
    string          content;
    string          target_patient;
    vector<string>  patient_list;

    content = "Which patient would you like to choose?\n\n";
    for(int i = 0; user_list[i].details.name != ""; i++)
    {
        content = content + to_string(i) + ". " + user_list[i].details.name + "\n";
        patient_list.push_back(user_list[i].details.name);
    }
        
    while(1)
    {
        menu(user(), admin(), "Patient selection", content, "Enter the patient name you wish to view: ");
        cin >> target_patient;
        if (!cin)
        {
            cin.clear();
            return dummy;
        }
        else if (find(patient_list.begin(), patient_list.end(), target_patient) != patient_list.end())//patient found
        {
            for(i = 0; user_list[i].details.name != target_patient; i++);
            return user_list[i];
        }
        else
            error_message(12);
    }
    return dummy;
}

//update_patient_condition section
void    update_patient_condition(user *patient, admin target_admin)
{
    
    while(1)
    {
        menu(*patient, target_admin, "UPDATE PATIENT CONDITION", "Here, you can update the medical condition of patients. Please choose one of the following conditions to update:\n1. vpg\n2. hba1c\n3. ogtt", "Enter the choice of medical condition to update: ");
        if (!cin)
        {
            cin.clear();
            return;
        }
        
    }
}

void    ogtt_update(user* ){};
//prescribe_medication section
void    prescribe_medication_control(user   *patient, admin target_admin) //control access to the actual function
{
    string    choice;
    while(1)
    {
        menu(user(), target_admin, "ISSUE MEDICATION ", "You are about to prescribe a medication for the patient, continue?", "Press y to continue and n to quit.");
        getline(cin, choice);
        if(!cin || choice == "n" || choice == "N")
        {
            cin.clear();
            return;
        }
        else if (choice == "y" || choice == "Y")
            prescribe_medication(patient, target_admin);
        else
            error_message(1);
    }
    return;
}

void    prescribe_medication(user   *patient, admin target_admin)
{
    string  medication;
    string  name;
    string  formulation;
    string  unit;
    string  frequency;
    string  note;

    menu(user(), target_admin, "MEDICATION PRESCRIPTION", "Enter the details of the medication prescription for the patient here.");
    cout << "Enter the name of the drug: ";
    getline(cin, name);
    cout << "Enter the formulation of the drug: ";
    getline(cin, formulation);
    cout << "Enter the unit of the drug formulation: ";
    getline(cin, unit);
    cout << "Enter the number of times for the drug to be ingested per day: ";
    getline(cin, frequency);
    cout << "Are there any extra notes you would like to add to the prescription of the medication?\nPress n if you don't have any: ";
    getline(cin, note);
    if(note == "n")
        note = "";
    medication = "Your medication is:\n" + formulation + " " + unit + " of " + name + ".\nPlease take the drug " + frequency + " times a day.\nFor more information, please contact your doctor.";
    patient->medical.medication = medication;
    return;
}

#endif