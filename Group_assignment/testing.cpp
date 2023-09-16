#include "headers.hpp"

int main()
{
	system("CLS");
	string feedback;

	cout << "Enter your feedback:\t";
	getline(cin, feedback);
	cout << "Feedback: " << feedback;
}