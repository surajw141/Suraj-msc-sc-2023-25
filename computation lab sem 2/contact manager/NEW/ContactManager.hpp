#include "bits/stdc++.h"
#include <string>
struct Contact
{
    int id;
    std::string title, name, email;
    long number;
};

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
    void rmbyname(std::string name); // search name and delete contact
    void rmbynumber(unsigned long number);
    void rmbyemail(std::string email);

    void searchbyname(std::string name);
    void searchbyemail(std::string email);

    void backup();
    void restore();
};