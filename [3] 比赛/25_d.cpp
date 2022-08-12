#include<bits/stdc++.h>
using namespace std;

//T1
class Solution {
public:
    vector<bool> kidsWithCandies(vector<int>& candies, int extraCandies) {
        int max = 0;
        vector<bool> ans;
        for(auto i : candies)
        {
            if(i > max) max = i;
        }
        for(auto i : candies)
        {
            if(i + extraCandies >= max) ans.push_back(true);
            else ans.push_back(false);
        }
        return ans;
    }
};

// T2，贪心策略，a从高位开始寻找，将第一个非9的数字修改成9
// b从高位开始寻找，若第一位非1，则将第一位修改为1，否则将第一个非0的数字修改成0

class Solution {
public:
    int maxDiff(int num) {
        vector<int> ss;
        while(num)
        {
            int rem = num % 10;
            ss.push_back(rem);
            num /= 10;
        }
        vector<int> resa(ss), resb(ss);
        int change, flag = 0;
        for(int i = ss.size() - 1; i >= 0; --i)
        {
            if(ss[i] != 9 && flag == 0)
            {
                flag = 1;
                change = resa[i];
                resa[i] = 9;
            }
            if(ss[i] == change) resa[i] = 9;
        }
        flag = 0;
        for(int i = ss.size() - 1; i >= 0; --i)
        {
            if(i == ss.size() - 1 && ss[i] != 1 && flag == 0)
            {
                flag = 1;
                change = resb[i];
                resb[i] = 1;
            }
            if(i != ss.size() - 1 && ss[i] != 0 && flag == 0)
            {
                if(ss.back() == 1 && ss[i] == 1) continue;
                flag = 2;
                change = resb[i];
                resb[i] = 0;
            }
            if(ss[i] == change)
            {
                if(flag == 1) resb[i] = 1;
                if(flag == 2) resb[i] = 0;
            }
        }  
        int res = 0, ret = 1;
        for(int i = 0; i < ss.size(); ++i)
        {
            res += (resa[i] - resb[i]) * ret;
            ret *= 10;
        }
        return res;
    }
};
// T3
class Solution {
public:
    bool checkIfCanBreak(string s1, string s2) {
        sort(s1.begin(), s1.end());
        sort(s2.begin(), s2.end());
        int s = 0;
        for(int i = 0; i < s1.size(); ++i)
        {
            if(s1[i] == s2[i]) continue;
            else
            {
                if(s == 0) s1[i] < s2[i] ? s = 1: s = 2;
                if(s == 1 && s1[i] > s2[i]) return false;
                if(s == 2 && s1[i] < s2[i]) return false;
            }
        }
        return true;
    }
};

// T4

class Solution {
public:
    int numberWays(vector<vector<int>>& hats) {

    }
};

int main()
{
    Solution a;
    //int res = a.maxDiff(1101057);
    //printf("%d\n", res);
    return 0;
}

