#pragma once
#ifndef GROUP_ASSIGNMENT_HPP
#define GROUP_ASSIGNMENT_HPP

#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#define MAX_CAPACITY 100
#define TRUE 1
#define FALSE 0

using namespace std; //not a good practice but judging that this assignment doesnt involve the use of other libraries that will cause clashes, namespace std is used.

typedef struct
{
    string          age;
    string          name;
    string          phone_number;
    string          home_address;
}user_details;

typedef struct
{
    string          username;
    string          password;
}access_control;
typedef struct
{
    bool    diabetic_patient = false;
    double  vpg = 0;
    double  hba1c = 0;
    double  ogtt = 0;
}medical_condition;
typedef struct
{
    user_details        details;
    access_control      access;
    medical_condition   medical;   
}user;
#endif