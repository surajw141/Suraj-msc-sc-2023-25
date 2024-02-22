#include "ContactManager.hpp"

using namespace std;

int main()
{
    ContactManager CM;
    CM.Add("john", "doe", "XXXXXXXXXXXX", 1234567890);
    CM.Add("john2", "doe2", "XXXXXXXXXXXX", 1234567890);
    CM.Add("john3", "doe3", "XXXXXXXXXXXX", 1234567890);

    CM.listAllContact();
    // unsigned long num = 432123;
    // ContactManager CM;
    // ContactManager c;
    // ContactManager c1("Chandra", "Patil", "cp@gmail.com", num);

    unsigned long num;
    cout << sizeof(num) << "\t" << sizeof(int) << endl;

    // c.Display();
    // c1.Display();
}