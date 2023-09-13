#pragma once
#ifndef USER_MENU_DIET_HPP
#define USER_MENU_DIET_HPP

#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"

void    update_meal_record(user *patient);
void add_record(user *patient);
void add_meal(user *patient, string meal);

void    update_meal_record(user *patient)
{
    int choice;
    diet_record breakfast, lunch, dinner;

    string  choice_str;
    int     choice_int;
    map < int, function < void(user *) >> option_list;
    option_list[1] = add_record;
    option_list[2] = update_record;
    //ogtt not here as it is limited to the admin (doctor)
    while(1)
    {
        menu(*patient, admin(), "UPDATE MEAL RECORD", "Please choose one of the following functions to use:\n1. Add new record\n2. Review record", "Please enter your choice: ");
        getline(cin, choice_str);            
        if(exit_check(&cin))
            return;
        if(is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
                option_list[choice_int](patient);  // Call the selected function
            else
                error_message(2);
        }
        else
            error_message(1);
    }
}

void add_record(user *patient)
{
    string  choice_str;
    int     choice_int;
    string  meal_list[] = {"filler", "Breakfast", "Lunch", "Dinner"};

    while(1)
    {
        menu(*patient, admin(), "ADD MEAL RECORD", "Please choose one of the following meals to add record:\n1. Breakfast\n2. Lunch\n3. Dinner", "Please enter your choice: ");
        getline(cin, choice_str);            
        if(exit_check(&cin))
            return;
        if(is_number(choice_str, &choice_int))
        {
            if (choice_int >= 1 && choice_int <= 3)
                add_meal(*patient, meal_list[choice_int]);  // Call the selected function
            else
                error_message(2);
        }
        else
            error_message(1);
    }
    return;
}

void add_meal(user *patient, string meal)
{
    string  choice_str;
    string  prompt;

    prompt = "\nDid you eat your " + meal + " ?\nPress y for yes and n for no. ";
    while(1)
    {
        menu(*patient, admin(), "ADD MEAL RECORD", "Please enter the details of the meal here: ", prompt);
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        if((choice_str == "y" || choice_str == "Y") && meal == "Breakfast")
        {
            patient->breakfast.option = true;
            cout << "Meal time taking " << meal << " (24-hours format): ";
            getline(cin, patient->breakfast.time);
            if(exit_check(&cin))
                return;
            cout << "Fill in the level of food ingested for each food type (None / Low / Medium / High):\n";
            cout << "Carbohydrate: ";
            getline(cin, patient->breakfast.carbohydrate);
            if(exit_check(&cin))
                return;
            cout << "Protein     : ";
            getline(cin, patient->breakfast.protein);
            if(exit_check(&cin))
                return;
            cout << "Vegetable   : ";
            getline(cin, patient->breakfast.vegetable);
            if(exit_check(&cin))
                return;
            cout << "Fruit       : ";
            getline(cin, patient->breakfast.fruit);
            if(exit_check(&cin))
                return;
            cout << "Fats        : ";
            getline(cin, patient->breakfast.fats);
            if(exit_check(&cin))
                return;
            success_message(12);
        }
        else if (choice_str == "n" || choice_str == "N")
            notification("You should have eaten your food no matter what.\nSkipping meals will only cause your insulin to surge.\nThis will cause your health to deterioate and not help with weight reducing.");
        else
            error_message(1);
    }
    return;
}

void display_record(user *patient)
{
    if(meal.option)
        {
            cout << "Meal time: " << meal.time << endl;
            cout << "Food Type   \t  Level\n";
            cout << "Carbohydrate\t" << setw(7) << meal.carbohydrate << endl;
            cout << "Protein\t" << setw(15) << meal.protein << endl;
            cout << "Vegetable\t" << setw(7) << meal.vegetable << endl;
            cout << "Fruit\t" << setw(15) << meal.fruit << endl;
            cout << "Fats\t" << setw(15) << meal.fats << endl;
        }

    else
        cout << "No record \n";
    
    return;
}

#endif