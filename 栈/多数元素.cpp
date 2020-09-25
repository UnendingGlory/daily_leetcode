#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> m;
        for(auto i:nums) m[i]++;
        for(auto it:m)
            if(m[it.second] > nums.size() / 2) return it.first;
    }
};

int main()
{
    return 0;
}