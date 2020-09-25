#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 由于只删除一个，所以剩下的可以用原回文方法判断
    bool isPalin(string &s, int i, int j)
    {
        for(; i < j; ++i, --j)
        {
            if(s[i] != s[j]) return false;
        }
        return true;
    }

    // 双指针法，如果左右指针指向的字符相同，则继续。若不相同，则选择左指针或者右指针中的一个删除
    // 由于两个指针同时操作，因为时间复杂度会下降
    bool validPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while(i < j)
        {
            if(s[i] != s[j]) 
            {
                return isPalin(s, i + 1, j) || isPalin(s, i, j - 1);
            }
            ++i, --j;
        }
        return true;
    }
};