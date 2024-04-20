#include "ContactManager.hpp"
using namespace std;
int main()
{
    ContactManager cm;
    // cm.add(123, "Rahul", "rahul@gmail.com", "Mr.");
    // cm.add(234, "Rohit", "rohit@gmail.com", "Mr.");
    // cm.add(345, "Raj", "Raj@gmail.com", "Mr.");
    // cm.add(456, "Rakesh", "Rakesh@gmail.com", "Mr.");
    // cm.list();
    // cm.edit();
    // cm.list();

    // int contactNumber;
    // std::cout << "Enter number: ";
    // std::cin >> contactNumber;

    // cm.rmbynumber(contactNumber);
    // string email;
    // cm.list();
    // std::cout << "Enter email: ";
    // std::cin >> email;
    // cm.rmbyemail(email);

    // string name;
    // std::cout << "Enter name: ";
    // std::cin >> name;
    // cm.rmbyemail(name);
    // cm.searchbyname(name);

    // string email;
    // std::cout << "Enter email: ";
    // std::cin >> email;

    // cm.searchbyemail(email);

    // cm.backup();

    cm.restore();

    cm.list();
    return 0;
}