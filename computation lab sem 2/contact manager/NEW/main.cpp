#include "ContactManager.hpp"
using namespace std;
int main()
{
    ContactManager cm;
    cm.add(98999999, "Rahul", "rahul@gmail.com", "Mr.");
    cm.add(98999998, "Rohit", "rohit@gmail.com", "Mr.");
    cm.add(98999997, "Raj", "Raj@gmail.com", "Mr.");
    cm.add(98999996, "Rakesh", "Rakesh@gmail.com", "Mr.");
    cm.list();
    cm.edit();
    cm.list();
    cm.deleteContact();
    cm.list();
    return 0;
}
