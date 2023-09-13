void display meal(user *patient)
{   
    string choice;
    int meal_choice;
    while(1)
    {
        menu(*patient, admin(), "MEAL RECORD", "You are about to view your meal record\nPress \"y\" to continue or \"n\" to cancel : ");
        getline(cin, choice);
        if(exit_check(&cin))
            return;
        if((choice_str == "y" || choice_str == "Y"))
        {
            cout << "Please choose your meal : \n1. Breakfast\n2. Lunch\n3. Dinner";
            getline(cin, meal_choice);
            if (meal_choice == 1)
            {
                cout << "====================\n     Breakfast\n====================";
                cout << "Carbohydrates : " << patient->breakfast.carbohydrate;
                cout << "\nProtein : " << patient->breakfast.protein;
                cout << "\nVegetables : " << patient->breakfast.vegetable;
                cout << "\nFruits : " << patient->breakfast.fruit;
                cout << "\nFats : " << patient->breakfast.fats;
                return;
            }
            else if (meal_choice == 2)
            {
                cout << "====================\n     Lunch\n====================";
                cout << "Carbohydrates : " << patient->lunch.carbohydrate;
                cout << "\nProtein : " << patient->lunch.protein;
                cout << "\nVegetables : " << patient->lunch.vegetable;
                cout << "\nFruits : " << patient->lunch.fruit;
                cout << "\nFats : " << patient->lunch.fats;
                return;
            }
            else if (meal_choice == 3)
            {
                cout << "====================\n     Dinner\n====================";
                cout << "Carbohydrates : " << patient->dinner.carbohydrate;
                cout << "\nProtein : " << patient->dinner.protein;
                cout << "\nVegetables : " << patient->dinner.vegetable;
                cout << "\nFruits : " << patient->dinner.fruit;
                cout << "\nFats : " << patient->dinner.fats;
                return;
            }
            else
                error_message(2)
        }
        else if (choice_str == "n" || choice_str == "N")
            return;
        else
            error_message(1); 
    }
}