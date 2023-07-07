#pragma once
#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

#include "headers.hpp"
#include "validation.hpp"

int     get_user_num(void)
{
    ifstream        in_file_details("user_details.txt", ios::in);
    unsigned int    user_number         = 0;
    unsigned int    user_detail_count   = 5;
    string          line;

    while(getline(in_file_details, line))
        user_number++;
    return (user_number / user_detail_count);
}

user    read_user_data(void)
{
    user        new_user;
    ifstream    in_file_details("user_details.txt", ios::in);
    ifstream    in_file_access("user_access.txt", ios::in);
    string      line_counter;
    //for more users
    getline(in_file_details, new_user.details.name);
    getline(in_file_details, new_user.details.age);
    getline(in_file_details, new_user.details.phone_number);
    getline(in_file_details, new_user.details.home_address);
    getline(in_file_access, new_user.access.username);
    getline(in_file_access, new_user.access.password);
    
    in_file_details.close();
    in_file_access.close();
    return new_user;
}

void    export_user_data(user user_to_save, unsigned int counter)
{
    ofstream    out_file_details("user_details.txt", ios::out);
    ofstream    out_file_access("user_access.txt", ios::out);

    out_file_details << "Index\t\t: " << counter << endl;
    out_file_details << "Name\t\t: " << user_to_save.details.name << endl;
    out_file_details << "Age\t\t: " << user_to_save.details.age << endl;
    out_file_details << "Age\t\t: " << user_to_save.details.age << endl;
    

}

#endif