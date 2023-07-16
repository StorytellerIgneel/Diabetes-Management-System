#include <iostream>
#include <string>
#include <map>

using namespace std;

struct user_details {
    string name;
    string age;
    string phone_number;
    string home_address;
};

struct user {
    user_details details;
};

// Function to change the specified detail
void change(user user_list[], int size, const string& detail) {
    // Create a map of member pointers
    map<string, string user_details::*> memberPointers = {
        {"name", &user_details::name},
        {"age", &user_details::age},
        {"phone_number", &user_details::phone_number},
        {"home_address", &user_details::home_address}
    };

    // Check if the specified detail exists in the map
    auto it = memberPointers.find(detail);
    if (it == memberPointers.end()) {
        cout << "Invalid detail specified." << endl;
        return;
    }

    // Iterate through the user_list array and modify the desired detail
    for (int i = 0; i < size; i++) {
        cout << "Enter new " << detail << " for user " << i << ": ";
        cin >> user_list[i].details.*it->second;
    }
}

int main() {
    user_details userDetails;
    userDetails.name = "John";
    userDetails.age = "30";
    userDetails.phone_number = "123456789";
    userDetails.home_address = "123 Main St";

    user user_list[1];
    user_list[0].details = userDetails;

    change(user_list, 1, "name");

    // Print the updated user details
    cout << "Updated user name: " << user_list[0].details.name << endl;

    return 0;
}