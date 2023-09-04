#pragma once
#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

#include "headers.hpp"
#include "validation.hpp"

bool  stob(string target);
void    read_admin_data(admin admin_list[], int admin_count);
int     get_user_num(string access_type);
void    read_user_data(user user_list[], int size);
void    export_user_data(user user_list[], admin admin_list[]);


bool  stob(string target)
{
    string  converted;

    transform(target.begin(), target.end(), back_inserter(converted), ::tolower);
    if (converted == "true")
        return true;
    return false; 
}

void    read_admin_data(admin admin_list[], int admin_count)
{
    ifstream    in_file_admin("admin.txt", ios::in);
    int         counter;

    counter = 0;
    while(counter < admin_count)
    {
        getline(in_file_admin, admin_list[counter].admin_name);
        getline(in_file_admin, admin_list[counter].password);
        counter++;
    }
    in_file_admin.close();
    return;
}

int     get_user_num(string access_type)
{
    int         line_number;
    int         details_count;
    ifstream    in_file_user("user_access.txt", ios::in);
    ifstream    in_file_admin("admin.txt", ios::in);
    string      line;

    line_number  = 0;
    details_count = 2; 
    if(access_type == "user")
    {
        while(getline(in_file_user, line))
            line_number++;
    }
    else if (access_type == "admin")
    {
        while(getline(in_file_admin, line))
            line_number++;
    }
    in_file_user.close();
    in_file_admin.close();
    return (line_number / details_count);
}

void    read_user_data(user user_list[], int size)
{
    ifstream    in_file_details("user_details.txt", ios::in);
    ifstream    in_file_access("user_access.txt", ios::in);
    ifstream    in_file_medical("user_medical.txt", ios::in);
    string      bool_getter;
    string      double_getter;
    string      int_getter;
    int         counter;
    char         test;

    counter = 0;
    while(counter < size)
    {
        getline(in_file_details, user_list[counter].details.name);
        getline(in_file_details, user_list[counter].details.age);
        getline(in_file_details, user_list[counter].details.phone_number);
        getline(in_file_details, user_list[counter].details.home_address);
        getline(in_file_access, user_list[counter].access.username);
        getline(in_file_access, user_list[counter].access.password);
        getline(in_file_medical, bool_getter);
        user_list[counter].medical.diabetic_patient = stob(bool_getter);
        getline(in_file_medical, double_getter);
        user_list[counter].medical.vpg = stod(double_getter);
        getline(in_file_medical, double_getter);
        user_list[counter].medical.hba1c = stod(double_getter);
        getline(in_file_medical, user_list[counter].medical.medication);
        if (user_list[counter].medical.medication != "No prescription")
            user_list[counter].medical.medication_received = true;
        counter++;
    }
    
    in_file_details.close();
    in_file_access.close();
    return;
}

void    export_user_data(user user_list[], admin admin_list[])
{
    ofstream    out_file_details("user_details.txt", ios::out);
    ofstream    out_file_access("user_access.txt", ios::out);
    ofstream    out_file_medical("user_medical.txt", ios::out);
    ofstream    out_file_admin("admin.txt", ios::out);
    int         counter;

    counter = 0;
    while(user_list[counter].access.username != "")
    {
        //user outfile
        if (counter != 0)
        {
            out_file_details << endl;
            out_file_access << endl;
            out_file_medical << endl;
            out_file_admin << endl;
        }
        out_file_details << user_list[counter].details.name << endl;
        out_file_details << user_list[counter].details.age << endl;
        out_file_details << user_list[counter].details.phone_number << endl;
        out_file_details << user_list[counter].details.home_address;
        out_file_access << user_list[counter].access.username << endl;
        out_file_access << user_list[counter].access.password;
        if (user_list[counter].medical.diabetic_patient == true)
            out_file_medical << "true" << endl;
        else
            out_file_medical << "false" << endl;
        out_file_medical << user_list[counter].medical.vpg << endl;
        out_file_medical << user_list[counter].medical.hba1c << endl;
        if (user_list[counter].medical.medication == "No prescription")
            out_file_medical << "No prescription";
        else 
            out_file_medical << user_list[counter].medical.medication;
        //admin outfile
        out_file_admin << admin_list[counter].admin_name << endl;
        out_file_admin << admin_list[counter].password;
        counter++;
    }
    out_file_details.close();
    out_file_access.close();
    out_file_medical.close();
    return;
}

#endif