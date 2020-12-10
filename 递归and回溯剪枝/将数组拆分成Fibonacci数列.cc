#include "header.h"

class Solution {
    using ll = long long;
    int len;
public:

    bool backtrack(vector<int> &res, const string & s, int index, ll sum, int prev) {
        if (index == len) {
            return res.size() >= 3;
        }
        ll curr = 0;
        for (int i = index; i < len; ++i) {
            // 剩下的部分以0开头
            if (i > index && s[index] == '0') {
                return false;
            }
            curr = curr * 10 + s[i] - '0';
            if (curr > INT_MAX) {
                return false;
            }
            if (res.size() >= 2) {
                if (curr < sum) {
                    continue;
                }
                else if (curr > sum) {
                    return false;
                }
            }
            res.push_back(curr);
            // 如果之前能分割成功，就return True，跳过pop的环节
            if (backtrack(res, s, index + 1, prev + curr, curr)) {
                return true;
            }
            res.pop_back();
        }
        return false;
    }

    vector<int> splitIntoFibonacci(string S) {
        len = S.size();
        vector<int> res;
        backtrack(res, S, 0, 0, 0);
        return res;
    }
};