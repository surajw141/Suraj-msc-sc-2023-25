#include <iostream>
using namespace std;
int f(int n1, int n2)
{
    int result, diff;
    diff = n1 - n2;
    result = n1 / diff;
    return result;
}

int main()
{
    int value, div, result, i, total;
    value = 10;
    div = 6;

    total = 0;

    for (i = 0; i < 10; i++)
    {
        result = f(value, div);
        total += result;
        div++;
        value--;
    }
    cout << "value=" << value << "div=" << div << "total=" << total << endl;
    return 0;
}