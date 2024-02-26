//
#include <bits/stdc++.h>
using namespace std;
int main()
{
    vector<int> nums = {1, 8, 6, 2, 5, 4, 8, 3, 7};
    int sz = nums.size();
    int area = 0;
    // print all combinations of pole heights
    for (int i = 0; i < sz; i++)
    {

        for (int j = i + 1; j < sz; j++)
        {

            int height1 = nums[i];
            int height2 = nums[j];

            double tmp = (height2 - height1) * (j - i);

            cout << "i: " << height1 << " j: " << height2 << " area: " << tmp << endl;

            if (tmp > area)
            {
                area = tmp;
            }
        }
    }

    cout << "Max area: " << area << endl;

    return 0;
}

//