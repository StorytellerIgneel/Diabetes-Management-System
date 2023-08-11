#pragma once
#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "headers.hpp"
#define TERMINAL_WIDTH 100
#define LINE string(TERMINAL_WIDTH, '-') + '\n'

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

void    menu(user   target_user, string stage, string content, string prompt = "", bool display_details = false) //for selections
{
    time_t  current_time = time(nullptr);
    string  string_time;
    string  username;

    username = target_user.access.username;
    current_time = time(nullptr);
    string_time  = ctime(&current_time);
    system("cls");
    cout << LINE    
         << banner(stage)
         << LINE;

    if (username != "")
        cout << "User: ";
    else
        username = "Guest";
        
    cout << left << username << right << setw(TERMINAL_WIDTH - username.length()) << string_time
         << LINE << endl;
    if(display_details == 1)
        display_user_details(target_user, true);
    cout << content << endl << endl
         << LINE
         << prompt;
    return;
}

#endif