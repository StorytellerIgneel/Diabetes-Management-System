#pragma once
#ifndef USER_MENU_DIET_HPP
#define USER_MENU_DIET_HPP

#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"

void    update_meal_record(user *patient);
void    add_record(user *patient);
void    add_meal(user *patient, string meal);
void    display_meal(user *patient);

void    update_meal_record(user *patient)
{
    int choice;
    diet_record breakfast, lunch, dinner;

    string  choice_str;
    int     choice_int;
    map < int, function < void(user *) >> option_list;
    option_list[1] = add_record;
    option_list[2] = display_meal;


    while(1)
    {
        menu(*patient, admin(), "UPDATE MEAL RECORD", "Please choose one of the following functions to use:\n1. Add new record\n2. Review record", "Please enter your choice: ");
        getline(cin, choice_str);            
        if(exit_check(&cin))
            return;
        else if(is_number(choice_str, &choice_int))
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

void    add_record(user *patient)
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
        else if(is_number(choice_str, &choice_int))
        {
            if (choice_int >= 1 && choice_int <= 3)
                add_meal(patient, meal_list[choice_int]);  // Call the selected function
            else
                error_message(2);
        }
        else
            error_message(1);
    }
    return;
}

void    add_meal(user *patient, string meal) //breakfast
{
    string  choice_str;
    string  prompt;

    prompt = "\nDid you eat your " + meal + " ?\nPress \"y\" for yes and \"n\" for no. ";
    while(1)
    {
        menu(*patient, admin(), "ADD MEAL RECORD", "Please enter the details of the meal here: ", prompt);
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        else if((choice_str == "y" || choice_str == "Y") )
        {   
            if (meal == "Breakfast")
            {
                patient->breakfast.option = true;
                cout << "Meal time taking " << meal << " (24-hours format): ";
                getline(cin, patient->breakfast.time);
                if(exit_check(&cin))
                    return;
                cout << "Fill in the level of food ingested for each food type (None / Low / Medium / High):\n";
                cout << "Carbohydrate: ";
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
            else if (meal == "Lunch")
            {
                patient->lunch.option = true;
                cout << "Meal time taking " << meal << " (24-hours format): ";
                getline(cin, patient->lunch.time);
                if(exit_check(&cin))
                    return;
                cout << "Fill in the level of food ingested for each food type ( ___ quantity of ___ food):\n";
                cout << "Carbohydrate: ";
                getline(cin, patient->lunch.carbohydrate);
                if(exit_check(&cin))
                    return;
                cout << "Protein     : ";
                getline(cin, patient->lunch.protein);
                if(exit_check(&cin))
                    return;
                cout << "Vegetable   : ";
                getline(cin, patient->lunch.vegetable);
                if(exit_check(&cin))
                    return;
                cout << "Fruit       : ";
                getline(cin, patient->lunch.fruit);
                if(exit_check(&cin))
                    return;
                cout << "Fats        : ";
                getline(cin, patient->lunch.fats);
                if(exit_check(&cin))
                    return;
                success_message(12);
            }
            else if (meal == "Dinner")
            {
                patient->dinner.option = true;
                cout << "Meal time taking " << meal << " (24-hours format): ";
                getline(cin, patient->dinner.time);
                if(exit_check(&cin))
                    return;
                cout << "Fill in the level of food ingested for each food type ( ___ quantity of ___ food):\n";
                cout << "Carbohydrate: ";
                getline(cin, patient->dinner.carbohydrate);
                if(exit_check(&cin))
                    return;
                cout << "Protein     : ";
                getline(cin, patient->dinner.protein);
                if(exit_check(&cin))
                    return;
                cout << "Vegetable   : ";
                getline(cin, patient->dinner.vegetable);
                if(exit_check(&cin))
                    return;
                cout << "Fruit       : ";
                getline(cin, patient->dinner.fruit);
                if(exit_check(&cin))
                    return;
                cout << "Fats        : ";
                getline(cin, patient->dinner.fats);
                if(exit_check(&cin))
                    return;
                success_message(12);
            }
        }
        else if (choice_str == "n" || choice_str == "N")
            notification("You should have eaten your food no matter what.\nSkipping meals will only cause your insulin to surge.\nThis will cause your health to deterioate and not help with weight reducing.");
        else
            error_message(1);
    }
    return;
}
//cacat
void    display_meal(user *patient)
{   
    string meal_choice;
    string to_menu;
    string meal_title;

    while(1)
    {
        menu(*patient, admin(), "MEAL RECORD", "1. Breakfast\n2. Lunch\n3. Dinner", "Please choose your meal : ");
        getline(cin, meal_choice);
        if(exit_check(&cin))
            return;
        else if (meal_choice == "1")
        {   
            if (patient->breakfast.option == true)
            {            
                to_menu = "Carbohydrates : " + patient->breakfast.carbohydrate +
                        "\nProtein       : " + patient->breakfast.protein +
                        "\nVegetables    : " + patient->breakfast.vegetable +
                        "\nFruits        : " + patient->breakfast.fruit +
                        "\nFats          : " + patient->breakfast.fats;
                menu(*patient, admin(), "BREAKFAST RECORD", "Time of meal taken : " + patient->breakfast.time +"\n"+ to_menu, "Press enter to continue");
                cin.get();
            }
            else
                error_message(19); //No meal record
        }
        else if (meal_choice == "2")
        {
            if (patient->lunch.option == true)
            {
                to_menu = "Carbohydrates : " + patient->lunch.carbohydrate +
                        "\nProtein       : " + patient->lunch.protein +
                        "\nVegetables    : " + patient->lunch.vegetable +
                        "\nFruits        : " + patient->lunch.fruit +
                        "\nFats          : " + patient->lunch.fats;
                menu(*patient, admin(), "LUNCH RECORD", "Time of meal taken : " + patient->lunch.time +"\n"+ to_menu, "Press enter to continue");
                cin.get();
            }
            else
                error_message(19); //No meal record
        }
        else if (meal_choice == "3")
        {
            if (patient->dinner.option == true)
            {
                to_menu = "Carbohydrates : " + patient->dinner.carbohydrate +
                    "\nProtein       : " + patient->dinner.protein +
                    "\nVegetables    : " + patient->dinner.vegetable +
                    "\nFruits        : " + patient->dinner.fruit +
                    "\nFats          : " + patient->dinner.fats;
                menu(*patient, admin(), "DINNER RECORD", "Time of meal taken : " + patient->dinner.time +"\n"+ to_menu, "Press enter to continue");
                cin.get();
            }
            else
                error_message(19); //No meal record
        }
        else
            error_message(2);
    }
    return;
}
#endif