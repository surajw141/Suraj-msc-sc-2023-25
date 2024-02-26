#include "bits/stdc++.h"
typedef struct
{
    std ::string name;
    std ::string email;
    std ::string title;
    unsigned long number;
} info;
class ContactManager
{
public:
    std ::vector<info> data;

    // constructor
    ContactManager();
    // member function
    void add(unsigned long, std::string, std::string, std::string);
    void add();
    void list();

    // fuction to edit details
    void edit();
    void editPhonenumber();
    void editEmail();
    void editName();

    // delete fuction
    void deleteContact();
    void deleteContactname(); // search name and delete contact
    void deleteContactnumber();
    void deleteContactemail();

    void searchName();
    void searchNumber();

    void backup();
    void restore();
};