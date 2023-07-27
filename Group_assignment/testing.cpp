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
    user_details    details;
    access_control  access;
}user;

void    change_detail(user *target_user_ptr, string detail,int new_user = FALSE)
{
    string  new_detail;

    map < string, string user_details::* > user_details_list =
    {
        {"name", &user_details::name},
        {"age", &user_details::age},
        {"phone number", &user_details::phone_number},
        {"home address", &user_details::home_address}
    };

    map < string, string access_control::* > access_control_list = 
    {
        {"username", &access_control::username},
        {"password", &access_control::password}
    };
    auto details_iterator = user_details_list.find(detail);
    auto access_iterator = access_control_list.find(detail);

    if (details_iterator != user_details_list.end())//the detail to be changed is in the user_detail struct
    {
        if (new_user == FALSE)
            cout << "Old detail\t\t: " << ((*target_user_ptr).details.*details_iterator->second) << endl;

        cout << "Please enter your ";
        if (new_user == TRUE)
            cout << "new ";
        cout << detail << ": ";
        getline(cin, new_detail);
        cin.ignore();
        if (new_detail == ((*target_user_ptr).details.*details_iterator->second))
            cout << "gay";
        else
            ((*target_user_ptr).details.*details_iterator->second) = new_detail;
    }
    else
    {
        if (new_user == FALSE)
            cout << "Old detail\t\t: " << ((*target_user_ptr).access.*access_iterator->second) << endl;
        cout << "Please enter your new " << detail << ": ";
        getline(cin, new_detail);
        cin.ignore();
        if (new_detail == ((*target_user_ptr).access.*access_iterator->second))
            cout << "gay";
        else
            ((*target_user_ptr).access.*access_iterator->second) = new_detail;
    }
    return;
}
  
int main()
{
  user user_list[MAX_CAPACITY];
  user new_user;
  change_detail(&new_user, "name", 1);
  change_detail(&new_user, "age", 1);
  change_detail(&new_user, "phone number", 1);
  change_detail(&new_user, "home address", 1);
  cout << new_user.details.name;
}