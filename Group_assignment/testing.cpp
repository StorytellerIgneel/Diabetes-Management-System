#include "headers.hpp"
#include "access_control.hpp"
#include "validation.hpp"
#include "file_handling.hpp"

int main(void) //initial access control
{
    string  details_list[] = {"", "name", "age", "phone number", "home address", "username", "password"};
    int     choice;

    while(1)
    {
        try
        {
            cin >> choice;
            cout << details_list[choice];
            break;
        }
        catch(const invalid_argument& e)
        {
            cout << "u gay";
        }
        catch(const exception& e)
        {
            cout << "u ultra gaycl";
        }
    }
    
}