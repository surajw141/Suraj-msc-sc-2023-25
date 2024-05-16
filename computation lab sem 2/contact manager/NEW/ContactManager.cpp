#include "ContactManager.hpp"
using namespace std;
ContactManager::ContactManager()
{
    cout << "\n Welcome to contact manager";
    cout << "\n Press 1 to add a new contact";
}
/**
 * @brief Function to add
 *
 * @param number
 * @param name
 * @param email
 * @param title
 *
 */

void ContactManager::add(unsigned long number, std::string name, std::string email, std::string title)
{
    info tmp;
    tmp.number = number;
    tmp.name = name;
    tmp.email = email;
    tmp.title = title;

    data.push_back(tmp);
}

void ContactManager::backup()
{

    ofstream backupFile("backup.txt");

    for (info &contact : data)
    {

        backupFile << "\n"
                   << contact.name << "\t"
                   << contact.email << "\t"
                   << contact.number;
    }

    backupFile.close();

    cout << "Data backed up to backup.txt!" << endl;
}

void ContactManager::list()
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].number > 0)
            cout
                << "\n"
                << i + 1 << " " << data[i].title << " " << data[i].name << " " << data[i].email << " " << data[i].number;
    }
    cout << "\n";
}

<<<<<<< Updated upstream
void ContactManager::searchbyname(std::string name)
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].name == name)
            cout
                << "\n"
                << i + 1 << " " << data[i].title << " " << data[i].name << " " << data[i].email << " " << data[i].number;
    }
}

void ContactManager::searchbyemail(std::string email)
{

    for (int i = 0; i < data.size(); i++)
    {

        if (data[i].email == email)
        { // check for match

            cout << "\n"
                 << i + 1 << " " << data[i].title << " " << data[i].name << " " << data[i].email << " " << data[i].number;
        }
    }
}

void ContactManager::restore()
{
    ifstream backupFile("backup.txt");

    info temp;
    while (!backupFile.eof())
    {
        backupFile >> temp.name >> temp.email >> temp.number;
        cout << "\n name :: " << temp.name << endl;
        data.push_back(temp);
    }
}

void ContactManager::rmbynumber(unsigned long contactNumber)
{

    for (int i = 0; i < data.size(); i++)
    {

        if (data[i].number == contactNumber)
        {

            data.erase(data.begin() + i);
            std::cout << "Contact '" << contactNumber << "' deleted successfully.\n";
            return;
        }
    }

    std::cout << "Contact '" << contactNumber << "' not found.\n";
}

void ContactManager::rmbyemail(std::string email)
{

    for (int i = 0; i < data.size(); i++)
    {

        if (data[i].email == email)
        {

            data.erase(data.begin() + i);
            std::cout << "Contact '" << email << "' deleted successfully.\n";
            return;
        }
    }

    std::cout << "Contact '" << email << "' not found.\n";
}

void ContactManager::rmbyname(std::string name)
{

    for (int i = 0; i < data.size(); i++)
    {

        if (data[i].name == name)
        {

            data.erase(data.begin() + i);
            std::cout << "Contact '" << name << "' deleted successfully.\n";
            return;
        }
    }

=======
void rmbynumber(string name)
{
    for (int i = 0; i < data.size();)
    {
        if (data[i].name == name)
        {
            data.erase(data.begin() + i);
            std::cout << "Contact '" << name << "' deleted successfully.\n";
            return; // exit the function after deleting the contact
        }
        else
        {
            ++i; // Move to the next element if the current one doesn't match
        }
    }
>>>>>>> Stashed changes
    std::cout << "Contact '" << name << "' not found.\n";
}

void ContactManager::edit()
{
    cout << "\n Enter the index of the user you want to edit";

    // show list users in the system
    list();

    //  ask user to select the index of the user he want to edit
    int id;
    cout << "\n Choose id";
    cin >> id;

    cout << "\n Enter the new number";

    cin >> data[id - 1].number;
    cout << "\n Enter the new name";
    cin >> data[id - 1].name;
    cout << "\n Enter the new email";
    cin >> data[id - 1].email;
    cout << "\n Enter the new title";
    cin >> data[id - 1].title;
}

// void editContactNumber(string name, long newNumber)
// {

//     int index = searchbyname(std::string name);

//     if (index != -1)
//     {

//         info &contact = data[index];
//         contact.number = newNumber;
//     }
//     else
//     {
//         cout << "Contact not found" << endl;
//     }
// }

void ContactManager::deleteContact()
{
    list();
    cout << "\n Enter the index of the user you want to delete";
    int id;
    cin >> id;
    data[id - 1].name = "";
    data[id - 1].email = "";
    data[id - 1].title = "";
    data[id - 1].number = 0;
}