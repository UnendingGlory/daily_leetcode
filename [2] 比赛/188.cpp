#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    vector<string> buildArray(vector<int>& target, int n) {
        vector<string> ans;
        int ss[n];
        for(int i = 0; i < n; ++i) ss[i] = i + 1;
        printf("1");
        int j = 0;
        for(int i = 0; j < target.size() && i < n; ++i)
        {
            if(ss[i] == target[j])
            {
                ans.push_back("Push");
                ++j;
            }
            else
            {
                ans.push_back("Push");
                ans.push_back("Pop");
            }
        }
        return ans;
    }
};

// 暴力
class Solution {
public:
    int countTriplets(vector<int>& arr) {
        int ans = 0, n = arr.size();
        for(int i = 0; i < n; ++i)
        {
            for(int k = i + 1; k < n; ++k)
            {
                for(int j = i + 1; j < k; ++j)
                {
                    //int temp1 = arr[i], temp2 = ;
                    //for(int ii = i; ii < j; ++ii) temp1 ^= 
                }
            }
        }
        
    }
};


int main()
{
    return 0;
}