#pragma once
#ifndef GROUP_ASSIGNMENT_HPP
#define GROUP_ASSIGNMENT_HPP

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <string>
#define MAX_CAPACITY 100
#define TRUE 1
#define FALSE 0

using namespace std; //not a good practice but judging that this assignment doesnt involve the use of other libraries that will cause clashes, namespace std is used.
struct user_details
{
    string          name;
    string          age;
    string          phone_number;
    string          home_address;
};

struct access_control
{
    string          username;
    string          password;
};
struct medical_condition
{
    bool    diabetic_patient = false;
    string  current_state = "Normal";
    bool    diet = false;
    bool    insulin = false;
    
    double  vpg = 0;
    double  hba1c = 0;
    double  ogtt = 0;
    string  medication;
    string  medication_note;
    bool    medication_received = false; //equivalent to ogld
};
struct user
{
    user_details        details;
    access_control      access;
    medical_condition   medical;

    user(){}
};

struct admin
{
    string  admin_name;
    string  password;

    admin(){}
};

#endif