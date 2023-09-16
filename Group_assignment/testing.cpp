void doctor_feedback(USER c[], int* i_ptr)
{
	system("CLS");
	char feedback[600];
	cout << "Username:\t\t" << c[*i_ptr].username << endl;
	cout << "User ic:\t\t" << c[*i_ptr].ic << endl;
	cout << "User status:\t\t" << c[*i_ptr].status << endl;
	cout << "Enter your feedback:\t";
	cin.get(feedback, 50);
	cout << &feedback[0];
}