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

// void ContactManager::backup()
// {
//     ofstream fout("restore.txt");
//     fout << (i + 1)
// }

// void ContactManager::add()

void ContactManager::list()
{
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i].number > 0)
            cout
                << "\n"
                << i + 1 << " " << data[i].title << " " << data[i].name << " " << data[i].email << " " << data[i].number;
    }
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