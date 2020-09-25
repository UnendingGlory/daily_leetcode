#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 非递归
    vector<int> divingBoard(int shorter, int longer, int k) {
        vector<int> ans;
        // 如果两者一样长怎么选都一样
        if(k == 0) return ans;
        if(shorter == longer) 
        {
            ans.push_back(k * shorter);
            return ans;
        }
        for(int i = 0; i <= k; ++i)
        {
            int len = i * longer + (k - i) * shorter;
            ans.push_back(len);
        }
        return ans;
    }
};

// 递归