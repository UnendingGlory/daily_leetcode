#include <cstdio>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        // 每个元素左边乘右边
        vector<int> ans;
        int n = nums.size();
        vector<int> L(n), R(n);
        L[0] = 1; // 0 的左边是1
        for(int i = 1; i < n; ++i)
            L[i] = nums[i - 1] * L[i - 1];
        R[n - 1] = 1;
        for(int i = n - 2; i >= 0; --i)
            R[i] = nums[i + 1] * R[i + 1];
        for(int i = 0; i < n; ++i)
            ans.push_back(L[i] * R[i]);
        return ans;
    }
};