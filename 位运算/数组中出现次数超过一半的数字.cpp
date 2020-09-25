#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> m; // 不知道数的范围
        int x = nums.size() >> 1;
        for(int i : nums)
            if(++m[i] > x) 
                return i;
        return 0;
    }
};

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        //unordered_map<int, int> m; // 不知道数的范围
        sort(nums.begin(), nums.end());
        return nums[nums.size() >> 1];
        return 0;
    }
};

int main()
{
    return 0;
}