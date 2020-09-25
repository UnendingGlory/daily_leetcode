#include <bits/stdc++.h>
using namespace std;

class Solution {
    int m[10005];
public:
    vector<int> sortByBits(vector<int>& arr) {
        memset(m, 0, sizeof(m));
        for(int i : arr)
        {
            int x = i; // 不改变原数组
            if(!m[x]) // 未计算过的数字
            {
                while(x) // 除基取余法
                {
                    if(x & 1) ++m[i];
                    x >>= 1;
                }
            }
        }
        sort(arr.begin(), arr.end(),
            [&](const int a, const int b){return m[a] == m[b] ? a < b : m[a] < m[b];});
        return arr;
    }
};