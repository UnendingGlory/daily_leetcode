#include <bits/stdc++.h>
using namespace std;

// 统计各个数字的个数，求这些个数的最大公约数
class Solution {
    int cnt[10000];
public:
    bool hasGroupsSizeX(vector<int>& deck) {
        for (auto x: deck) cnt[x]++;
        int g = -1;
        for (int i = 0; i < 10000; ++i)if(cnt[i]) {
            if (g != -1) g = gcd(g, cnt[i]);
            else g = cnt[i];
        }
        return g >= 2;
    }
};

int main()
{
    return 0;
}