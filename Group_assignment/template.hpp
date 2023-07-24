#pragma once
#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "headers.hpp"
#define TERMINAL_WIDTH 80
#define LINE string(TERMINAL_WIDTH, '-') + '\n'

string    banner(string to_print)
{
    string  whitespace((TERMINAL_WIDTH-to_print.length())/2, ' ');
    return  (whitespace + to_print + whitespace + "\n");
}

void    notification(string notification)
{   
    system("clear");
    cout << LINE << endl
         << banner("Notification")
         << LINE << endl << endl
         << notification << endl << endl << LINE;
    return;
}

void    display_user_details(user   user_list[], string   username)
{
    int user_count;

    user_count = 0;
    while(user_list[user_count].access.username != username)
        user_count++;
    cout << "Name: " << user_list[user_count].details.name << endl
        << "Age\t:" << user_list[user_count].details.age << endl
        << "Phone number: " << user_list[user_count].details.phone_number << endl
        << "Home address: " << user_list[user_count].details.home_address << endl
        << "Username\t: " << user_list[user_count].access.username << endl
        << "Password\t: " << user_list[user_count].access.password << endl << endl;
    return;
}

void    menu(user   user_list[], string stage, string username, string content, string prompt = "", int display_details = 0) //for selections
{
    time_t  current_time = time(nullptr);
    string  string_time;

    current_time = time(nullptr);
    string_time  = ctime(&current_time);
    system("cls");
    cout << LINE    
         << banner(stage)
         << LINE;

    if (username != "Guest")
        cout << "User: ";
        
    cout << left << username << right << setw(TERMINAL_WIDTH - username.length()) << string_time
         << LINE << endl;
    if(display_details == 1)
        display_user_details(user_list, username);
    cout << content << endl << endl
         << LINE
         << prompt;
    return;
}

#endif