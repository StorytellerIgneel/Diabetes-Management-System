#pragma once
#ifndef GROUP_ASSIGNMENT_HPP
#define GROUP_ASSIGNMENT_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <functional>
#include <map>

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

#endif