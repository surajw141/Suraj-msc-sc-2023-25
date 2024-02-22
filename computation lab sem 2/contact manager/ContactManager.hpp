#include <bits/stdc++.h>

struct data
{
    std::string firstName;
    std::string lastName;
    std::string email;
    unsigned long Number;
};

class ContactManager
{
public:
    ContactManager();
    //    ContactManager(std::string, std::string, std::string, unsigned long);

    void Add(std::string, std::string, std::string, unsigned long);
    void listAllContact();
    void Display();

    std::vector<struct data> info;
};
