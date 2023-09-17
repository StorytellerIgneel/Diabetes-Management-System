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
#define EXIT true
#define CONTINUE false
#define TERMINAL_WIDTH 100
#define LINE string(TERMINAL_WIDTH, '-') + '\n'
//VPG
#define VPG_FASTING_DIAGNOSIS 7.0
#define VPG_RANDOM_DIAGNOSIS 11.1
//HBA1C
#define HBA1C_NORMAL_PERCENT_MAX 5.7
#define HBA1C_PRE_DM_PERCENT_MIN 5.7
#define HBA1C_PRE_DM_PERCENT_MAX 6.3
#define HBA1C_DM_PERCENT_MIN 6.3
//OGTT
#define OGTT_NORMAL_0HR_MAX 6.1
#define OGTT_NORMAL_2HR_MAX 7.8
#define OGTT_IFG_0HR_MIN 6.1
#define OGTT_IFG_0HR_MAX 6.9
#define OGTT_IGT_2HR_MIN 7.8
#define OGTT_IGT_2HR_MAX 11.0
#define OGTT_DM_0HR_MIN 7.0
#define OGTT_DM_2HR_MIN 11.1
//GENERAL
#define YOUNG_AGE 40
#define ELDERLY_AGE 60
#define HYPOGLYCAEMIA_LEVEL_MMOL 3.9
#define HYPERGLYCAEMIA_LEVEL_MMOL_MIN 10
#define HYPERGLYCAEMIA_LEVEL_MMOL_MAX 11.1
//HYPER/HYPO
#define HYPO_VPG 3.9
#define HYPER_VPG 10.0
#define HYPO_HBA1C_PERCENT 4.1
#define HYPER_HBA1C_PERCENT 7.9
//ERROR INPUTS
#define ERROR_INPUT_LESS_VPG 2.2
#define ERROR_INPUT_MORE_VPG 16.7
#define ERROR_INPUT_LESS_HBA1C_PERCENT 3.0
#define ERROR_INPUT_MORE_HBA1C_PERCENT 12.1 

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
    bool    vpg_fasting = false;
    bool    hypoglycaemia = false;
    bool    hyperglycaemia = false;
    bool    diet = false;
    bool    insulin = false;
    double  vpg = 0;
    string  vpg_time = "No record";
    double  hba1c = 0;
    string  hba1c_time = "No record";
    double  ogtt = 0;
    string  ogtt_time = "No record";
    string  medication = "No prescription";
    string  medication_note = "No extra note";
    bool    medication_received = false; //equivalent to ogld
};

struct diet_record
{
    bool     option = false;
    string   time = "No record";
    string   carbohydrate = "No record";   // Carbohydrate ingested level
    string   protein = "No record";        // Protein ingested level 
    string   vegetable = "No record";      // Vegetable ingested level
    string   fruit = "No record";          // Fruit ingested level
    string   fats = "No record";           // Fats ingested level  
};
struct user
{
    user_details        details;
    access_control      access;
    medical_condition   medical;
    diet_record         breakfast;
    diet_record         lunch;
    diet_record         dinner;

    user(){}
};

struct admin
{
    string  admin_name;
    string  password;

    admin(){}
};

#endif