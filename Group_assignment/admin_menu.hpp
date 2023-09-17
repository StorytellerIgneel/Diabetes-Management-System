#pragma once
#ifndef ADMIN_MENU_HPP
#define ADMIN_MENU_HPP

#include "headers.hpp"
#include "template.hpp"
#include "validation.hpp"
#include "user_menu.hpp"

void    admin_menu                      (admin target_admin, user patient_list[], admin admin_list[]);
void    find_patient                    (user **patient, user patient_list[], admin target_admin);
void    update_patient_condition        (user *patient, admin target_admin);
void    ogtt_update                     (user *patient, admin target_admin);
bool    find_hyper_hypo                 (user patient_list[], string *for_noti, bool skip_notification);
void    check_hyper_hypo                (string hyper_hypo_list, admin target_admin);
void    prescribe_medication_control    (user *patient, admin target_admin);
void    prescribe_medication            (user *patient, admin target_admin);
bool    get_medication                  (int *step, string prompt, string *medication, admin target_admin);
void    set_diet_control                (user *patient, admin target_admin);
void    insulin_issue                   (user *patient, admin target_admin);
void    check_medical_guides            (user *patient, admin target_admin);
void    export_data_control             (user* patient, user patient_list[], admin target_admin);
void    export_all_data                 (user* patient, user patient_list[], admin target_admin);
void    export_selected_user            (user* patient, user patient_list[], admin target_admin);
void    add_new_admin                   (admin target_admin, admin admin_list[]);
//admin main menu
void    admin_menu(admin target_admin, user patient_list[],  admin admin_list[])
{
    bool    hyper_hypo;
    int     choice_int;
    string  choice_str;
    string  checked_hyper_hypo;
    string  hyper_hypo_list;
    string  confirm_quit;
    user    *patient;
    map < int, function < void(user*, admin) >> option_list;
    option_list[1] = update_patient_condition;
    option_list[3] = prescribe_medication_control;
    option_list[4] = display_overview_details;
    option_list[5] = check_medical_guides;
    
    hyper_hypo = find_hyper_hypo(patient_list, &hyper_hypo_list, false);
    while(1)
    {
        patient = nullptr;
        find_patient(&patient, patient_list, target_admin);
        if (patient == nullptr) // chosen to quit in find_patient
            return;
        while(1)
        {
            menu(*patient, target_admin, "MAIN MENU", "Please choose one of the following functions to use: \n1. Update patient health condition.\n2. Check hyperglycaemia and hypoglycaemia patients\n3. Provide Medication\n4. Check patient profile\n5. Check medical guides\n6. Export patient data\n7. Add a new admin", "Enter your choice: ");
            getline(cin, choice_str);
            if(exit_check(&cin))
            {
                hyper_hypo = find_hyper_hypo(patient_list, &hyper_hypo_list, true);
                if (hyper_hypo == true)
                {
                    error_message(16);
                    system("cls");
                    cout << "Although we strongly recommend you to check on the conditions of the hypoglycaemia and hyperglycaemia patients before quitting and also key in their latest blood glucose levels,\nyou can still choose to quit if you are on an urgent situation.\nIn that case, type 'quit' to quit the system.\nJust press enter and press CTrl + Z on the patient choosing page if you are not on an urgent situation: ";
                    getline(cin, confirm_quit);
                    if (confirm_quit == "quit")
                        return;
                    else
                        break;
                }
                else
                    return;
            }
            else if (is_number(choice_str, &choice_int))
            {
                if (choice_int == 2)
                {
                    if (hyper_hypo == true)
                    {
                        check_hyper_hypo(hyper_hypo_list, target_admin);
                        hyper_hypo = false;
                    }
                    else
                        error_message(18);
                }
                else if (choice_int == 6)
                    export_data_control(patient, patient_list, target_admin);
                else if (choice_int == 7)
                    add_new_admin(target_admin, admin_list);
                else if (option_list.find(choice_int) != option_list.end())
                    option_list[choice_int](patient, target_admin);  // Call the selected function
                else
                    error_message(2);
            }
            else
                error_message(1);
        }
    }
}

void    find_patient(user **patient, user   patient_list[], admin target_admin)
{
    int             i;
    user            dummy;
    string          content;
    string          target_patient;

    content = "Which patient would you like to choose?\n\n";
    for(int i = 0; patient_list[i].details.name != ""; i++)
        content = content + to_string(i+1) + ". " + patient_list[i].details.name + "\n";
    while(1)
    {
        menu(user(), target_admin, "Patient selection", content, "Enter the patient name you wish to view: ");
        getline(cin, target_patient);
        if(exit_check(&cin))
            return;
        else
        {
            for(int i = 0; patient_list[i].details.name != ""; i++)
            {
                if(target_patient == patient_list[i].details.name)
                {
                    success_message(10);
                    *patient = &patient_list[i];
                    return;
                }
            }
            error_message(12);
        }
    }
    return;
}
//update_patient_condition section
void    update_patient_condition(user *patient, admin target_admin)
{
    string  choice_str;
    int     choice_int;

    map <int, function <void(user*, admin)> > update_list;
    update_list[1] = vpg_test;
    update_list[2] = hba1c_test;
    update_list[3] = ogtt_update;

    while(1)
    {
        menu(*patient, target_admin, "UPDATE PATIENT CONDITION", "Here, you can update the medical condition of patients. Please choose one of the following conditions to update:\n1. vpg\n2. hba1c\n3. ogtt", "Enter the choice of medical condition to update: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        else if (is_number(choice_str, &choice_int))
        {
            if (update_list.find(choice_int) != update_list.end())
                update_list[choice_int](patient, target_admin);
            else
                error_message(2);
        }
        else
            error_message(1);
    }
    return;
}

void    ogtt_update(user* patient, admin target_admin)
{
    string  mode_str;
    string  ogtt_str;
    int     mode_int;
    double  ogtt_double;

    while(1)
    {
        menu(*patient, target_admin, "Oral Glucose Tolerance Test (OGTT)", "Welcome to update for patient ogtt value. \nYou are required to choose the time period of the OGTT test done\n1. 0 hours (immediate)\n2. 2 hours", "Please enter the patient's ogtt value: ");
        getline(cin, mode_str);
        if (is_number(mode_str, &mode_int))
        {
            if (mode_int == 1)
            {
                while(1)
                {
                    menu(*patient, target_admin, "Oral Glucose Tolerance Test (OGTT)", "You have chosen the immediate (0 hour) time period.", "Please enter the patient's ogtt value (mmol/L): ");
                    getline(cin, ogtt_str);
                    if(exit_check(&cin))
                        break;
                    else if (is_double(ogtt_str, &ogtt_double))
                    {
                        if (ogtt_double < OGTT_IFG_MIN && ogtt_double > 0) //Normal 
                        {
                            if (ogtt_double < HYPOGLYCAEMIA_LEVEL_MMOL) //hypoglycaemia
                            {
                                success_message(27);
                                patient->medical.hypoglycaemia = true;
                            }      
                            else
                            {
                                success_message(7);
                                patient->medical.hypoglycaemia = false;
                            }  
                            patient->medical.ogtt_time = get_time();
                            patient->medical.hyperglycaemia = false;
                            patient->medical.ogtt = ogtt_double;
                            return;
                        }
                        else if (ogtt_double >= OGTT_IFG_MIN && ogtt_double <= OGTT_IFG_MAX) // IFG
                        {
                            success_message(7);
                            patient->medical.current_state = "IMPAIRED GLUCOSE (IFG)";
                            patient->medical.ogtt_time = get_time();
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.hypoglycaemia = false;
                            patient->medical.hyperglycaemia = false;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else if (ogtt_double > OGTT_IFG_MAX  && ogtt_double <= HYPERGLYCAEMIA_LEVEL_MMOL_MAX)
                        {
                            if (ogtt_double < HYPERGLYCAEMIA_LEVEL_MMOL_MIN) // no hyper
                            {
                                success_message(7);
                                patient->medical.hyperglycaemia = false;
                            }
                            else
                            {
                                success_message(28);
                                patient->medical.hyperglycaemia = true;
                            }
                            patient->medical.current_state = "DIABETES MELLITUS (DM)";
                            patient->medical.hypoglycaemia = false;
                            patient->medical.ogtt_time = get_time();
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else
                            error_message(1);
                    }
                    else
                        error_message(1);
                }
            }
            else if (mode_int == 2)
            {
                while(1)
                {
                    menu(*patient, target_admin, "Oral Glucose Tolerance Test (OGTT)", "You have chosen the 2hours time period.", "Please enter the patient's ogtt value (mmol/mol): ");
                    getline(cin, ogtt_str);
                    if(exit_check(&cin))
                        break;
                    else if (is_double(ogtt_str, &ogtt_double))
                    {
                        if (ogtt_double < 7.8 && ogtt_double > 0)
                        {
                            success_message(7);
                            patient->medical.ogtt_time = get_time();
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = false;
                            return;
                        }
                        else if (ogtt_double >= 7.8 && ogtt_double <= 11.0)
                        {
                            success_message(7);
                            patient->medical.current_state = "IMPAIRED GLUCOSE TOLERANCE (IGT)";
                            patient->medical.ogtt_time = get_time();
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else if (ogtt_double >= 11.1)
                        {
                            success_message(7);
                            patient->medical.current_state = "DIABETES MELLITUS (DM)";
                            patient->medical.ogtt_time = get_time();
                            patient->medical.ogtt = ogtt_double;
                            patient->medical.diabetic_patient = true;
                            return;
                        }
                        else
                            error_message(10);
                    }
                    else
                        error_message(1);
                }
            }
        }
        else
            error_message(1);
    }
}
//hyper/hypo section
bool    find_hyper_hypo(user patient_list[], string *for_noti, bool skip_notification = false)
{
    int     count;
    bool    hyper;
    bool    hypo;

    count = 1;
    hyper = false;
    hypo = false;
    *for_noti = "Attention!!";
    for(int i = 0; patient_list[i].details.name != ""; i++)
    {
        if(patient_list[i].medical.hypoglycaemia == true)
        {
            if(hypo == false)
                *for_noti += "\nThe following patients are in risk of hypoglycaemia:\n";
            *for_noti = *for_noti + "\n" + to_string(count) + ". " + patient_list[i].details.name;
            hypo = true;
            count++;
        }
    }
    count = 1;
    for(int i = 0; patient_list[i].details.name != ""; i++)
    {
        if(patient_list[i].medical.hyperglycaemia == true)
        {
            if(hyper == false)
                *for_noti += "\n\nThe following patients are in risk of hyperglycaemia:\n";
            *for_noti = *for_noti + "\n" + to_string(count) + ". " + patient_list[i].details.name;
            hyper = true;
            count++;
        }
    }
    *for_noti += "\nPlease check on their conditions as soon as possible.\nYou will also have to key in their blood glucose levels after you have checked on their conditions.";
    if (hyper == true || hypo == true)
    {
        if (skip_notification == false)
        {
            notification(*for_noti);
            cout << "Press Enter to continue.";
            cin.get();
        }
        return true;
    }
    else
        return false;
}

void    check_hyper_hypo(string hyper_hypo_list, admin target_admin)
{
    size_t firstNewlinePos;
    size_t lastNewlinePos;

    firstNewlinePos = hyper_hypo_list.find('\n');
    lastNewlinePos = hyper_hypo_list.rfind('\n');
    if (firstNewlinePos != std::string::npos && lastNewlinePos != std::string::npos)// Extract the content between the first and last newlines
        hyper_hypo_list = hyper_hypo_list.substr(firstNewlinePos + 1, lastNewlinePos - firstNewlinePos - 1);
    hyper_hypo_list += "\nYou will also have to key in their blood glucose levels after you have checked on their conditions.";
    menu(user(), target_admin, "HYPOGLYCAEMIA/HYPERGLYCAEMIA PATIENTS LIST ", hyper_hypo_list, "Press Enter to continue.");
    cin.get();
    return;
}
//////HAVENT COMPLETE
//prescribe_medication section
void    prescribe_medication_control(user   *patient, admin target_admin) //control access to the actual function
{
    string  choice_str;
    int     choice_int;
    map <int, function<void(user* , admin)>> option_list;
    option_list[1] = set_diet_control;
    option_list[2] = prescribe_medication;
    option_list[3] = insulin_issue;

    while(1)
    {
        menu(*patient, target_admin, "ISSUE MEDICATION ", "Choose one of the following to issue/prescriibe:\n1. Diet control\n2. Medications (OGLDs) \n3. Insulin", "Choose one of the following: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        else if (is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
                option_list[choice_int](patient, target_admin);
            else
                error_message(2);
        }
        else
            error_message(1);
    }
    return;
}

void    prescribe_medication(user   *patient, admin target_admin)
{
    if (patient->medical.diabetic_patient == false && patient->medical.hyperglycaemia == false && patient->medical.hypoglycaemia == false)
    {
        error_message(21);
        return ;
    }
    string  choice;
    string  medication;
    string  for_menu;
    string  name;
    string  formulation;
    string  unit;
    string  frequency;
    string  note;
    string  modified_menu;
    size_t  newline_count;
    size_t  index;
    int     newline_pos;
    int     step;

    step = 1;
    menu(*patient, target_admin, "MEDICATION PRESCRIPTION", "Enter the details of the medication prescription for the patient here.\nYou can press g or G to show the guide for the medication prescription.\nYou can also press B or b to go back to the previous step.");
    while(1)
    {
        if (step == 1)
        {
            if (get_medication(&step, "Enter the name of the drug: ", &name, target_admin))
                return;
        }   
        if (step == 2)
        {
            if (get_medication(&step, "Enter the formulation of the drug: ", &formulation, target_admin))
                return;
        } 
        if (step == 3)
        {
            if (get_medication(&step, "Enter the unit of the drug formulation: ", &unit, target_admin))
                return;
        }
        if (step == 4)
        {
            if (get_medication(&step, "Enter the number of times for the drug to be ingested per day: ", &frequency, target_admin))
                return;
        }
        if (step == 5)
        {
            if (get_medication(&step, "Are there any extra notes you would like to add to the prescription of the medication?\nPress n if you don't have any: ", &note, target_admin))
                return;
        }
        if (step == 6)
            break;
    }
    medication = formulation + " " + unit + " of " + name + ".\\Please take the drug " + frequency + " times a day.\\For more information, please contact your doctor.";
    if (note != "No extra note")
        for_menu = medication + "\nExtra note from doctor: " + note;
    else
        for_menu = medication;
    index = 0;
    newline_count = count(for_menu.begin(), for_menu.end(), '\\');
    if (newline_count != 0) // newline present inside message
    {
        for (int i = 0; i <= newline_count; i++)
        {
            newline_pos = for_menu.find('\\', index);
            modified_menu += for_menu.substr(index, newline_pos - index) + "\n";
            index = newline_pos + 1;
        }
    }
    while(1)
    {
        menu(*patient, target_admin, "Medication Prescription", "The medication you have prescribed is:\n" + modified_menu, "Are you sure that you want to prescribe this medication for the patient? Do double check before confirming,\nPress y for yes and n to quit: ");
        getline(cin, choice);
        if(!cin || choice == "n" || choice == "N")
            return;
        else if (choice == "y" || choice == "Y")
        {
            success_message(9);
            patient->medical.medication = medication;
            patient->medical.medication_note = note;
            return;
        }
        else
            error_message(2);
    }
    return;
}

bool    get_medication(int *step, string prompt, string *medication, admin target_admin)
{
    string  temporary;
    while(1)
    {
        cout << prompt;
        getline(cin, temporary);
        *medication = temporary;
        if(exit_check(&cin))
            return true;
        else if(*medication == "G" || *medication == "g")
        {
            menu(user(), target_admin, "GUIDE FOR MEDICATION PRESCRIPTION", "The guide for medication prescription is as follows: ", "Press enter to continue.", false, "medication_guide.txt");
            cin.get();
        }
        else if (*step != 1 && (*medication == "B" || *medication == "b"))
        {
            *step -= 1;
            return false;
        }
        else
        {
            if (*step == 5)
            {
                if (*medication == "N" || *medication == "n")
                    *medication = "No extra note";
            }
            *step += 1;
            return false;
        }
    }
    return false;
}
//incomplete
void    set_diet_control(user *patient, admin target_admin) //issue diet
{
    string choice;
    string cancel_choice;

    while(1)
    {
        if (patient->medical.insulin == true) //cancel insulin
        {
            menu(*patient, target_admin, "ISSUE DIET CONTROL", "Patient is already issued with a diet.\nDo you wish to cancel the diet issued?", "Press y to continue or n to return: ");
            getline(cin, cancel_choice);
            if (!cin || cancel_choice == "n" || cancel_choice == "N")
            {
                cin.clear();
                return;
            }
            else if (cancel_choice == "y" || choice == "Y")
            {
                patient->medical.diet = false;
                success_message(22);
                return;
            }
            else
                error_message(2);
        } 
        else
        {   
            menu(*patient, target_admin, "ISSUE DIET CONTROL", "You are about to issue a diet for the patient, continue?", "Press y to continue or n to return: ");
            getline(cin, choice);
            if(!cin || choice == "n" || choice == "N")
            {
                cin.clear();
                return;
            }
            else if (choice == "y" || choice == "Y")
            {
                patient->medical.diet = true;
                success_message(8);
                return;
            }
            else
                error_message(2);
        }    
    }
    return;
}

void    insulin_issue(user *patient, admin target_admin) //issue insulin
{
    string choice;
    string cancel_choice;

    while(1)
    {
        if (patient->medical.insulin == true) //cancel insulin
        {
            menu(*patient, target_admin, "INSULIN ISSUING", "Patient is already issued with insulin.\nDo you wish to cancel the insulin issued?", "Press y to continue or n to return: ");
            getline(cin, cancel_choice);
            if (!cin || cancel_choice == "n" || cancel_choice == "N")
            {
                cin.clear();
                return;
            }
            else if (cancel_choice == "y" || choice == "Y")
            {
                patient->medical.insulin = false;
                success_message(20);
                return;
            }
            else
                error_message(2);
        } 
        else
        {   
            menu(*patient, target_admin, "INSULIN ISSUING", "You are about to issue insulin for the patient, continue?", "Press y to continue or n to return: ");
            getline(cin, choice);
            if(!cin || choice == "n" || choice == "N")
            {
                cin.clear();
                return;
            }
            else if (choice == "y" || choice == "Y")
            {
                patient->medical.insulin = true;
                success_message(21);
                return;
            }
            else
                error_message(2);
        }    
    }
}
//check medical guide
void    check_medical_guides(user* patient, admin target_admin)
{
    string  filename_list[] = {"filler", "t2dm_management.txt", "control_targets.txt", "individualised_hba1c_target.txt", "principle_recommend.txt", "SMBG_recommendation.txt", "medication_guide.txt", "newly_diagnosed_treatment.txt", "clinic_followup_treatment.txt"};
    string  choice_str;
    int     choice_int;

    while(1)
    {
        menu(*patient, target_admin, "Medical Guides Checking", "Please choose one of the following medical guides to check on: \n1. Management of T2DM\n2. T2DM: Targets for control\n3. Individualised HbA1c targets based on patient profile\n4. Principal recommendation: Medical nutrition therapy & lifestyle modification\n5. Recommendations for SMBG\n6. OGLD prescription guide\n7. Treatment algorithm: Newly diagnosed T2DM\n8. Treatment recommendations: Clinic follow-up", "Enter your choice: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        else if (is_number(choice_str, &choice_int))
        {
            if (choice_int >= 1 && choice_int <= 8)
            {
                while(1)
                {
                    menu(*patient, target_admin, "Medical Guides Checking", "The medical guide is as follows: ", "Would you like to change the content of the guide?\nPress y for yes and n for no: ", false, filename_list[choice_int]);
                    getline(cin, choice_str);
                    if (choice_str == "Y" || choice_str == "y")
                    {
                        cout << "Please open the current directory and enter the new content of the medical guide in the text file with the name: " << filename_list[choice_int] << ",\nand change the contents inside the text file.";
                        cout << "\n\nIf you are done, please press enter to continue: ";
                        cin.get();
                        return;
                    }
                    else if (!cin || choice_str == "N" || choice_str == "n")
                    {
                        cin.clear();
                        return;
                    }
                    else
                        error_message(2);
                }   
            }
            else
                error_message(2);
        }
        else
            error_message(1);
    }   
}
//export user data
void    export_data_control(user* patient, user patient_list[], admin target_admin)
{
    string  choice_str;
    int     choice_int;
    map < int, function < void(user*, user[], admin) >> option_list;
    option_list[1] = export_selected_user;
    option_list[2] = export_all_data;

    while(1)
    {
        menu(*patient, target_admin, "PRODUCE USER INFORMATION REPORT", "You can choose to produce:\n1. Current patient information report\n2. All patient information report\n\nThe report shall contain the account details and medical information of all patients.", "Please enter your choice: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        else if (is_number(choice_str, &choice_int))
        {
            if (option_list.find(choice_int) != option_list.end())
            {
                option_list[choice_int](patient, patient_list, target_admin);  // Call the selected function
                return;
            }
            else
                error_message(2);
        }
        else
            error_message(1);
    } 
}

void    export_all_data(user* patient, user patient_list[], admin target_admin)
{
	ofstream out_file_user("patient_medical_report.txt", ios::out);
    //Get current time
    
    time_t current_time = time(nullptr);
    string string_time;
    current_time = time(nullptr);
    string_time  = ctime(&current_time);
	
    
	//File header
	out_file_user << "User Medical Report";
	out_file_user << "\nRequested by: " << target_admin.admin_name;
	out_file_user << "\nDate        : " << string_time << "\n\n";
	out_file_user << "Patient's Medical Condition\n";
	
	//Find array length
	int count = 0;  //Number of patients
	for (int i = 0; patient_list[i].details.name != "" ; i++)
		count++;

	//Loop through patient's list
	for (int idx = 0 ; idx < count ; idx++){
		//Basic details
		out_file_user << idx + 1 << ". " << patient_list[idx].details.name; 
		out_file_user << "\nAge          : " << patient_list[idx].details.age;
		out_file_user << "\nPhone number : " << patient_list[idx].details.phone_number;
		out_file_user << "\nAddress      : " << patient_list[idx].details.home_address;
		//Medical conditions
		out_file_user << "\nCurrent state |  Insulin  |  VPG(%)   State         Time                    |  HBA1c(%)   Time                    |  OGTT(%)   Time\n";
		out_file_user << left;
		//Current state
		out_file_user << setw(14) << patient_list[idx].medical.current_state << "|  ";
		//Insulin
		if (patient_list[idx].medical.insulin == true)
			out_file_user << setw(9) << "Yes" << "|  ";
		else
			out_file_user << setw(9) << "No" << "|  ";
		//VPD details
		if (patient_list[idx].medical.vpg != 0)
            {
			out_file_user << setw(9) << patient_list[idx].medical.vpg; 
            if (patient_list[idx].medical.vpg_fasting == true)
                out_file_user << setw(14) << "Fasting";
            else
                out_file_user << setw(14) << "Random";
			out_file_user << setw(24) << patient_list[idx].medical.vpg_time << "|  ";
            }
		else
			out_file_user << setw(47) << "No record" << "|  ";
		//HBA1c details
		if (patient_list[idx].medical.hba1c != 0)
			out_file_user << setw(11) << patient_list[idx].medical.hba1c << setw(24) 
				  		  << patient_list[idx].medical.hba1c_time << "|  ";
		else 
			out_file_user << setw(35) << "No record" << "|  ";
		//OGTT details
		if (patient_list[idx].medical.ogtt != 0)
			out_file_user << setw(10) << patient_list[idx].medical.ogtt
						  << setw(21) << patient_list[idx].medical.ogtt_time << "\n\n";
		else 
			out_file_user << setw(31) << "No record" << "\n\n" ;
    }   

	out_file_user.close();
    success_message(29);
	return; 
}

void    export_selected_user(user* patient, user patient_list[], admin target_admin)
{
	ofstream out_file_patient((*patient).details.name + "_medical_report.txt", ios::out);

    //Get current time
    time_t current_time = time(nullptr);
    string string_time;
    current_time = time(nullptr);
    string_time  = ctime(&current_time);
	
	//File header
	out_file_patient << (*patient).details.name + "'s Medical Report";
	out_file_patient << "\nDate        : " << string_time << "\n\n";
	out_file_patient << (*patient).details.name + "'s Medical Condition\n";

    //Basic details
    out_file_patient << "Age          : " << (*patient).details.age;
    out_file_patient << "\nPhone number : " << (*patient).details.phone_number;
    out_file_patient << "\nAddress      : " << (*patient).details.home_address;
    //Medical conditions
    out_file_patient << "\nCurrent state |  Insulin  |  VPG(%)   State         Time                    |  HBA1c(%)   Time                    |  OGTT(%)   Time\n";
    out_file_patient << left;
    //Current state
    out_file_patient << setw(14) << (*patient).medical.current_state << "|  ";
    //Insulin
    if ((*patient).medical.insulin == true)
        out_file_patient << setw(9) << "Yes" << "|  ";
    else
        out_file_patient << setw(9) << "No" << "|  ";
    //VPD details
    if ((*patient).medical.vpg != 0)
        {
        out_file_patient << setw(9) << (*patient).medical.vpg; 
        if ((*patient).medical.vpg_fasting == true)
            out_file_patient << setw(14) << "Fasting";
        else
            out_file_patient << setw(14) << "Random";
        out_file_patient << setw(24) << (*patient).medical.vpg_time << "|  ";
        }
    else
        out_file_patient << setw(47) << "No record" << "|  ";
    //HBA1c details
    if ((*patient).medical.hba1c != 0)
        out_file_patient << setw(11) << (*patient).medical.hba1c << setw(24) 
                        << (*patient).medical.hba1c_time << "|  ";
    else 
        out_file_patient << setw(35) << "No record" << "|  ";
    //OGTT details
    if ((*patient).medical.ogtt != 0)
        out_file_patient << setw(10) << (*patient).medical.ogtt
                        << setw(21) << (*patient).medical.ogtt_time << "\n\n";
    else 
        out_file_patient << setw(31) << "No record" << "\n\n" ;

    //Diet details
        out_file_patient << "Diet details:" << "\n";
    //Table header
    out_file_patient << "          | Time       | Carbohydrate | Protein   | Vegetable | Fruit     | Fats" << "\n";
    //Breakfast
    out_file_patient << "Breakfast | "; 
    out_file_patient << left;
    if ((*patient).breakfast.time != "No record")
        out_file_patient << setw(11) << (*patient).breakfast.time << "| " << setw(13) << (*patient).breakfast.carbohydrate <<"| "
                        << setw(10) << (*patient).breakfast.protein << "| " << setw(10) << (*patient).breakfast.vegetable << "| "
                        << setw(10) << (*patient).breakfast.fruit << "| " << (*patient).breakfast.fats << "\n";
    else 
        out_file_patient << "No record"  << "\n";
    //Lunch
    out_file_patient << "Lunch     | ";
    if ((*patient).lunch.time != "No record")
        out_file_patient << setw(11) << (*patient).lunch.time << "| " << setw(13) << (*patient).lunch.carbohydrate << "| "
                        << setw(10) << (*patient).lunch.protein << "| " << setw(10) << (*patient).lunch.vegetable << "| "
                        << setw(10) << (*patient).lunch.fruit << "| " << (*patient).lunch.fats << "\n";
    else
        out_file_patient << "No record" << "\n";
    //Dinner//
    out_file_patient << "Dinner    | ";
    if ((*patient).dinner.time != "No record")
        out_file_patient << setw(11) << (*patient).dinner.time<< "| " << setw(13) <<(*patient).dinner.carbohydrate << "| "
                        << setw(10) << (*patient).dinner.protein << "| " << setw(10) << (*patient).dinner.vegetable << "| "
                        << setw(10) << (*patient).dinner.fruit << "| " << (*patient).dinner.fats << "\n";
    else
        out_file_patient << "No record" << "\n";

	out_file_patient.close();
    success_message(30);
	return; 
}
//add a new admin
void    add_new_admin (admin target_admin, admin admin_list[])
{
    string  choice_str;
    admin   new_admin;
    int     admin_count;

    admin_count = 0;
    for (int i = 0; admin_list[i].admin_name != ""; i++)
        admin_count++;
    while(1)
    {
        menu(user(), target_admin, "NEW ADMIN REGISTRATION", "You can add a new admin to the system here. Continue?\n", "Press Y for yes and N for no: ");
        getline(cin, choice_str);
        if(exit_check(&cin))
            return;
        else if (choice_str == "Y" || choice_str == "y") 
        {
            cout << "Enter the new admin username: ";
            getline(cin, new_admin.admin_name);
            cout << "Enter the new admin password: ";
            getline(cin, new_admin.password);
            admin_list[admin_count] = new_admin;
            success_message(19);
            return;
        }
        else if (choice_str == "N" || choice_str == "n")
            return;
        else
            error_message(1);
    }
    return;
}
#endif