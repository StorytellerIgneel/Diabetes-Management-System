#include <iostream>
using namespace std;

int main (void)
{
    int a;

    
    while(1)
    {
        cin >> a;
        if(!cin)
        {
            cout << "not int";
            cin.clear();
            cin.ignore();
        }
        else
            cout << "int";
    }
    
}