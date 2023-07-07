#pragma once
#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include "headers.hpp"
#define ALL_PRESENT 0
#define CONTINUE    0
#define MISSING     1
#define EXIT        1
#define ERROR       2 //technically can be any number other than 0 and 1
//defined global variables to 

void error_message(unsigned int error_code, string missing_file = "")
{
    string          error_message;
    unsigned int    current_line = 1;
    ifstream        in_file("error_message.txt");

    cout << "\n";
    if (missing_file != "")
        cout << missing_file;
    while(current_line < error_code)
    {
        in_file >> error_message;
        current_line++;
    }
    cout << error_message << "\nPress enter to contine";
    cin.get();
    in_file.close();
}

int     check_file_present()
{
    string          file_list[]         = {"error_message.txt", "file_handling.txt", "user_access.txt", "user_details.txt"};
    unsigned int    file_list_counter   = 0;

    while(!file_list[file_list_counter].empty())
    {
        ifstream    in_file(file_list[file_list_counter]);
        if(!in_file)
        {
            error_message(3, file_list[file_list_counter]);
            return MISSING;
        }
        else
            in_file.close();
        file_list_counter++;
    }
    return ALL_PRESENT;
}

int    validation(string user_input, string exit_choice, string continue_choice = "")
{
    if (continue_choice != "") //there is an actual continue choice for user to select
    {
        if (user_input == continue_choice)
            return CONTINUE; //0
        else if (user_input == exit_choice)
            return EXIT; //1
        else
        {
            error_message(2);
            return ERROR;
        }   
    }
    else if (continue_choice == "") // there is no correct choice 
    {
        if (user_input == exit_choice)
            return EXIT; // 1
        else
            return CONTINUE; // 0
    }
}
#endif