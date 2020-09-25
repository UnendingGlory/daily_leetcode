#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int sumOddLengthSubarrays(vector<int>& arr) {
        int n = arr.size(), ans = 0;
        if(n % 2 == 0)
        {
            int t = n / 2;
            for(int i = n / 2, j = n / 2 + 1; i >= 0 && j < n; --i, ++j)
                ans += t * (arr[i] + arr[j]), --t;
        }
        else
        {
            int t = n / 2 + 1;
            for(int i = n / 2 + 1, j = n / 2 + 1; i >= 0 && j < n; --i, ++j)
                ans += t * (arr[i] + arr[j]), --t;
            ans -= arr[n / 2 + 1];
        }
        return ans;
    }
};