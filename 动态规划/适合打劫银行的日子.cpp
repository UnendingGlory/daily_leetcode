#include "header.h"

// 做法1：暴力，会超时， O(n^2)
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        vector<int> ans;
        for (int i = time; i < n - time; ++i) {
            bool flag = true;

            for (int j = i - time; j < i; ++j) {
                if (security[j] < security[j + 1]) {
                    flag = false;
                }
            }

            for (int j = i; j < i + time; ++j) {
                if (security[j] > security[j + 1]) {
                    flag = false;
                }
            }

            if (flag) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};

// 做法2：dp
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        // dec记录前面递增的数量，inc记录后面递减的数量
        vector<int> ans, dec(n), inc(n);
        dec[0] = inc[n - 1] = 0;
        for (int i = 1; i < n; ++i) {
            if (security[i - 1] >= security[i]) {
                dec[i] = dec[i - 1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (security[i] <= security[i + 1]) {
                inc[i] = inc[i + 1] + 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (dec[i] >= time && inc[i] >= time) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};

// 优化一下，双循环变单循环
class Solution {
public:
    vector<int> goodDaysToRobBank(vector<int>& security, int time) {
        int n = security.size();
        // dec记录前面递增的数量，inc记录后面递减的数量
        vector<int> ans, dec(n), inc(n);
        dec[0] = inc[n - 1] = 0;
        for (int i = 1; i < n; ++i) {
            if (security[i - 1] >= security[i]) {
                dec[i] = dec[i - 1] + 1;
            }

            if (security[n - i - 1] <= security[n - i]) {
                inc[n - i - 1] = inc[n - i] + 1;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (dec[i] >= time && inc[i] >= time) {
                ans.push_back(i);
            }
        }
        return ans;
    }
};