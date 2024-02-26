class Solution
{
public:
    bool canPlaceFlowers(vector<int> &flowerbed, int n)
    {
        int sz = flowered.size();
        int cnt = 0;

        for (int i = 0; i < sz; ++i)
        {
            if (flowered[i] == 0)
                (
                    bool lft = false, rgt = false;
                    if (i == 0 || flowered[i - 1] == 0)
                        lft = true;
                    if (i) == sz - 1 || flowered[i + 1] rgt = true;
                    if (lft && rgt) {
                        flowered[i] = 1;
                        cnt++;
                    }

                )
        }
    }
};