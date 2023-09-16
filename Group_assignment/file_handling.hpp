#pragma once
#ifndef FILE_HANDLING_HPP
#define FILE_HANDLING_HPP

#include "headers.hpp"
#include "validation.hpp"

bool    stob(string target);
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
    return ((line_number / details_count) % 100);
}

void    read_user_data(user user_list[], int size)
{
    ifstream    in_file_details("user_details.txt", ios::in);
    ifstream    in_file_access("user_access.txt", ios::in);
    ifstream    in_file_medical("user_medical.txt", ios::in);
    ifstream    in_file_meal("user_meal_record.txt", ios::in);
    string      bool_getter;
    string      double_getter;
    string      int_getter;
    int         counter;
    char         test;

    counter = 0;
    while(counter < size)
    {
        //details
        getline(in_file_details, user_list[counter].details.name);
        getline(in_file_details, user_list[counter].details.age);
        getline(in_file_details, user_list[counter].details.phone_number);
        getline(in_file_details, user_list[counter].details.home_address);
        //access
        getline(in_file_access, user_list[counter].access.username);
        getline(in_file_access, user_list[counter].access.password);
        //medical
        //diabetic patient
        getline(in_file_medical, bool_getter);
        user_list[counter].medical.diabetic_patient = stob(bool_getter);
        //current state
        getline(in_file_medical, user_list[counter].medical.current_state);
        //fasting
        getline(in_file_medical, bool_getter);
        user_list[counter].medical.vpg_fasting = stob(bool_getter);
        //hypoglycaemia
        getline(in_file_medical, bool_getter);
        user_list[counter].medical.hypoglycaemia = stob(bool_getter);
        //hyperglycaemia
        getline(in_file_medical, bool_getter);
        user_list[counter].medical.hyperglycaemia = stob(bool_getter);
        //diet
        getline(in_file_medical, bool_getter);
        user_list[counter].medical.diet = stob(bool_getter);
        //insulin
        getline(in_file_medical, bool_getter);
        user_list[counter].medical.insulin = stob(bool_getter);
        //vpg
        getline(in_file_medical, double_getter);
        user_list[counter].medical.vpg = stod(double_getter);
        //vpg_time
        getline(in_file_medical, user_list[counter].medical.vpg_time);
        //hba1c
        getline(in_file_medical, double_getter);
        user_list[counter].medical.hba1c = stod(double_getter);
        //hba1c_time
        getline(in_file_medical, user_list[counter].medical.hba1c_time);
        //ogtt
        getline(in_file_medical, double_getter);
        user_list[counter].medical.ogtt = stod(double_getter);
        //ogtt_time
        getline(in_file_medical, user_list[counter].medical.ogtt_time);
        //medication
        getline(in_file_medical, user_list[counter].medical.medication);
        //medication note
        getline(in_file_medical, user_list[counter].medical.medication_note);
        if (user_list[counter].medical.medication != "No prescription")
            user_list[counter].medical.medication_received = true;
        //meals
        //breakfast
        getline(in_file_meal, bool_getter);
        user_list[counter].breakfast.option = stob(bool_getter);
        getline(in_file_meal, user_list[counter].breakfast.time);
        getline(in_file_meal, user_list[counter].breakfast.carbohydrate);
        getline(in_file_meal, user_list[counter].breakfast.protein);
        getline(in_file_meal, user_list[counter].breakfast.vegetable);
        getline(in_file_meal, user_list[counter].breakfast.fruit);
        getline(in_file_meal, user_list[counter].breakfast.fats);
        //lunch
        getline(in_file_meal, bool_getter);
        user_list[counter].lunch.option = stob(bool_getter);
        getline(in_file_meal, user_list[counter].lunch.time);
        getline(in_file_meal, user_list[counter].lunch.carbohydrate);
        getline(in_file_meal, user_list[counter].lunch.protein);
        getline(in_file_meal, user_list[counter].lunch.vegetable);
        getline(in_file_meal, user_list[counter].lunch.fruit);
        getline(in_file_meal, user_list[counter].lunch.fats);
        //dinner
        getline(in_file_meal, bool_getter);
        user_list[counter].dinner.option = stob(bool_getter);
        getline(in_file_meal, user_list[counter].dinner.time);
        getline(in_file_meal, user_list[counter].dinner.carbohydrate);
        getline(in_file_meal, user_list[counter].dinner.protein);
        getline(in_file_meal, user_list[counter].dinner.vegetable);
        getline(in_file_meal, user_list[counter].dinner.fruit);
        getline(in_file_meal, user_list[counter].dinner.fats);
        counter++;
    }   
    in_file_details.close();
    in_file_access.close();
    in_file_medical.close();
    return;
}

void    export_user_data(user user_list[], admin admin_list[])
{
    ofstream    out_file_details("user_details.txt", ios::out);
    ofstream    out_file_access("user_access.txt", ios::out);
    ofstream    out_file_medical("user_medical.txt", ios::out);
    ofstream    out_file_meal("user_meal_record.txt", ios::out);
    ofstream    out_file_admin("admin.txt", ios::out);

    int         counter;

    counter = 0;
    while(user_list[counter].access.username != "") // user section
    {
        if (counter != 0)
        {
            out_file_details << endl;
            out_file_access << endl;
            out_file_medical << endl;
            out_file_meal << endl;
        }
        // details section
        out_file_details << user_list[counter].details.name << endl;
        out_file_details << user_list[counter].details.age << endl;
        out_file_details << user_list[counter].details.phone_number << endl;
        out_file_details << user_list[counter].details.home_address;
        //access section
        out_file_access << user_list[counter].access.username << endl;
        out_file_access << user_list[counter].access.password;
        //medication section
        out_file_medical << ((user_list[counter].medical.diabetic_patient == true)? "true\n" : "false\n");
        out_file_medical << user_list[counter].medical.current_state << endl;
        out_file_medical << ((user_list[counter].medical.vpg_fasting == true)? "true\n" : "false\n");
        out_file_medical << ((user_list[counter].medical.hypoglycaemia == true)? "true\n" : "false\n");
        out_file_medical << ((user_list[counter].medical.hyperglycaemia == true)? "true\n" : "false\n");
        out_file_medical << ((user_list[counter].medical.diet == true)? "true\n" : "false\n");
        out_file_medical << ((user_list[counter].medical.insulin == true)? "true\n" : "false\n");
        out_file_medical << user_list[counter].medical.vpg << endl;
        out_file_medical << user_list[counter].medical.vpg_time << endl;
        out_file_medical << user_list[counter].medical.hba1c << endl;
        out_file_medical << user_list[counter].medical.hba1c_time << endl;
        out_file_medical << user_list[counter].medical.ogtt << endl;
        out_file_medical << user_list[counter].medical.ogtt_time << endl;
        out_file_medical << user_list[counter].medical.medication << endl;
        out_file_medical << user_list[counter].medical.medication_note;
        //meal section
        //breakfast
        out_file_meal << ((user_list[counter].breakfast.option == true)? "true\n" : "false\n");
        out_file_meal << user_list[counter].breakfast.time << endl;
        out_file_meal << user_list[counter].breakfast.carbohydrate << endl;
        out_file_meal << user_list[counter].breakfast.protein << endl;
        out_file_meal << user_list[counter].breakfast.vegetable << endl;
        out_file_meal << user_list[counter].breakfast.fruit << endl;
        out_file_meal << user_list[counter].breakfast.fats << endl;
        //lunch
        out_file_meal << ((user_list[counter].lunch.option == true)? "true\n" : "false\n");
        out_file_meal << user_list[counter].lunch.time << endl;
        out_file_meal << user_list[counter].lunch.carbohydrate << endl;
        out_file_meal << user_list[counter].lunch.protein << endl;
        out_file_meal << user_list[counter].lunch.vegetable << endl;
        out_file_meal << user_list[counter].lunch.fruit << endl;
        out_file_meal << user_list[counter].lunch.fats << endl;
        //dinner
        out_file_meal << ((user_list[counter].dinner.option == true)? "true\n" : "false\n");
        out_file_meal << user_list[counter].dinner.time << endl;
        out_file_meal << user_list[counter].dinner.carbohydrate << endl;
        out_file_meal << user_list[counter].dinner.protein << endl;
        out_file_meal << user_list[counter].dinner.vegetable << endl;
        out_file_meal << user_list[counter].dinner.fruit << endl;
        out_file_meal << user_list[counter].dinner.fats;
        counter++;
    }
    counter = 0;
    while(admin_list[counter].admin_name != "")
    {
        if (counter != 0)
            out_file_admin << endl;
        out_file_admin << admin_list[counter].admin_name << endl;
        out_file_admin << admin_list[counter].password;
        counter++;
    }
    out_file_details.close();
    out_file_access.close();
    out_file_medical.close();
    out_file_admin.close();
    return;
}

#endif