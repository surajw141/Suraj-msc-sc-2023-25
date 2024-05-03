// Sales_item.h (header file)
#ifndef SALES_ITEM_H
#define SALES_ITEM_H

#include <string>
#include <iostream>

class Sales_item
{
public:
    // ... (other member functions and variables)

    // Overloaded operator>>
    friend std::istream &operator>>(std::istream &is, Sales_item &item)
    {
        is >> item.isbn >> item.units_sold >> item.revenue;
        return is;
    }

private:
    std::string isbn;
    int units_sold;
    double revenue;
};

#endif // SALES_ITEM_H
