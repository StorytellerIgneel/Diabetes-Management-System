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

void    menu(string stage, string username, string content, string prompt = "") //for selections
{
    time_t  current_time = time(nullptr);
    string  string_time;

    current_time = time(nullptr);
    string_time  = ctime(&current_time);
    system("clear");
    cout << LINE    
         << banner(stage)
         << LINE
         << left << "User: " << username << right << string_time
         << LINE << endl
         << content << endl
         << LINE
         << prompt;
    return;
}

void    test()
{
    cout << LINE;
    return;
}

#endif