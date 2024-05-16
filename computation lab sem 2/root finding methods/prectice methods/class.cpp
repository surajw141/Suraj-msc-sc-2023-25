#include <iostream>
using namespace std;

class Sales_Items
{
public:
    void Book()
    {
        std::string isbn;
        unsigned sale_quantity;
        int revenue;
        cin << isbn << sale_quantity << revenue << endl;
        }
};

int main()
{
    Sales_Items Book1;
    Book1.Book();
    return 0;
}