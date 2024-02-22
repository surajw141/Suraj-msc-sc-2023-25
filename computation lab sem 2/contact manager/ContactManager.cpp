#include "ContactManager.hpp"
using namespace std;
ContactManager::ContactManager()
{
    // ctor
    //     firstName = "";
    //     lastName = "";
    //     number = 0;
    //     email = "";
    // }

    // ContactManager::ContactManager(string firstName, string lastName, string email, unsigned long number)
    // {
    //     this->firstName = firstName;
    //     this->lastName = lastName;
    //     this->email = email;
    //     this->number = number;
    // }

    // void ContactManager::Display()
    // {

    //     // cout << "\n First Name :: " << firstName << "\t lastName :: " << lastName << "\t email ::" << email << "\t number ::" << number << endl;
    // }
}
void ContactManager::Add(string firstName, string lastName, string email, unsigned long number)
{
    struct data tmp;
    tmp.firstName = firstName;
    tmp.lastName = lastName;
    tmp.email = email;
    tmp.Number = number;

    info.push_back(tmp);
}
void ContactManager::listAllContact()
{
    for (int i = 0; i < info.size(); ++i)
    {
        cout << i + 1 << "First Name :: " << info[i].firstName << "\t Last Name :: " << info[i].lastName << "\t Email :: " << info[i].email << "\t Number :: " << info[i].Number << endl;
    }
};