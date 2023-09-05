#pragma once
#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "headers.hpp"
#define TERMINAL_WIDTH 100
#define LINE string(TERMINAL_WIDTH, '-') + '\n'

string      banner                  (string to_print);
void        notification            (string notification);
void        display_user_details    (user   target_user, bool    registration);
void        menu                    (user   patient, admin target_admin, string stage, string content, string prompt, bool display_details, string file);

string    banner(string to_print)
{
    string  whitespace((TERMINAL_WIDTH-to_print.length())/2, ' ');
    return  (whitespace + to_print + whitespace + "\n");
}

void    notification(string notification)
{   
    system("cls");
    cout << LINE << endl
         << banner("Notification")
         << LINE << endl << endl
         << notification << endl << endl << LINE;
    return;
}

void    display_user_details(user   target_user, bool    registration = false)
{
    cout << "Name\t\t: " << target_user.details.name << endl
        << "Age\t\t:" << target_user.details.age << endl
        << "Phone number\t: " << target_user.details.phone_number << endl
        << "Home address\t: " << target_user.details.home_address << endl;
    if (registration == true)
    {
        cout << "Username\t: " << target_user.access.username << endl
            << "Password\t: " << target_user.access.password << endl << endl;
    }
    return;
}

void    menu(user   patient, admin target_admin, string stage, string content, string prompt = "", bool display_details = false, string file = "") //for selections
{
    time_t  current_time = time(nullptr);
    string  string_time;
    string  username;
    string  patient_name;

    current_time = time(nullptr);
    string_time  = ctime(&current_time);
    system("cls");
    cout << LINE    
         << banner(stage)
         << LINE;

    if (target_admin.admin_name != "") // admin using
    {
        username = "Admin: " + target_admin.admin_name;
        if (patient.details.name != "") // admin using and for a patient.
            patient_name = "Viewing Patient: " + patient.details.name;
        else // admin using but not for patient yet
            patient_name = "";
    }
    else if (target_admin.admin_name == "" && patient.access.username != "") // user is using
        username = "User: " + patient.access.username;
    else //guest mode
        username = "Guest";

    cout << left << username << right << setw(TERMINAL_WIDTH - username.length()) << string_time;

    if (patient_name != "")
        cout << patient_name << endl;
    cout << LINE << endl;
    if(display_details == 1)
        display_user_details(patient, true);
    cout << content << endl << endl << "(Press Ctrl + Z together and enter to quit)" << endl
         << LINE
         << prompt;
    return;
}



#endif