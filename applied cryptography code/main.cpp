#include <iostream>
#include <NTL/ZZ.h>

using namespace std;
using namespace NTL;
int main()
{
    ulong i = 1844216546531251666;

    ZZ a = conv<ZZ>("1844216546531251666");

    cout << "\n a :: " << a << endl;

    a++;

    cout << "\n a :: " << a << endl;

    for (int i = 0; i < 10; i++)
    {
        a *= a;
    }

    cout << "\n a :: " << a << endl;

    return 0;

} // namespace std;
