#pragma once
#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

#include "headers.hpp"
#include "validation.hpp"

unsigned int     get_user_num(void)
{
    ifstream        in_file_details("user_details.txt", ios::in);
    unsigned int    user_number         = 0;
    unsigned int    user_detail_count   = 5;
    string          line;

    while(getline(in_file_details, line))
        user_number++;
    return (user_number / user_detail_count);
}

void    read_user_data(user user_list[], int size)
{
    ifstream    in_file_details("user_details.txt", ios::in);
    ifstream    in_file_access("user_access.txt", ios::in);
    int      counter;

    counter = 0;
    while(counter < size)
    {
        getline(in_file_details, user_list[counter].details.name);
        getline(in_file_details, user_list[counter].details.age);
        getline(in_file_details, user_list[counter].details.phone_number);
        getline(in_file_details, user_list[counter].details.home_address);
        getline(in_file_access, user_list[counter].access.username);
        getline(in_file_access, user_list[counter].access.password);
        counter++;
    }
    
    in_file_details.close();
    in_file_access.close();
    return;
}

void    export_user_data(user user_list[], int size)
{
    ofstream    out_file_details("user_details.txt", ios::out);
    ofstream    out_file_access("user_access.txt", ios::out);
    int         counter;

    counter = 0;
    while(counter < size)
    {
        out_file_details << user_list[counter].details.name << endl;
        out_file_details << user_list[counter].details.age << endl;
        out_file_details << user_list[counter].details.phone_number << endl;
        out_file_details << user_list[counter].details.home_address << endl;
        out_file_access << user_list[counter].access.username << endl;
        out_file_access << user_list[counter].access.password << endl;
        counter++;
    }
    return;
}

#endif