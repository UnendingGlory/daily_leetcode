#include "../header.h"


// 给定k和L，输出长度为L的第k个回文数
// queries = [1,2,3,4,5,90], intLength = 3
// [101,111,121,131,141,999]

// 只需要知道回文数的前面一半即可
// 前面一半为 10 ^ ((L - 1) // 2) + k - 1

// 如果L是奇数，只复制前面 L / 2 - 1位
// 如果L是偶数，则复制L/2位

// 直接用字符串反转或者自己手写

class Solution {
public:
    vector<long long> kthPalindrome(vector<int>& queries, int intLength) {
        vector<long long> ans;
        int base = pow(10, (intLength - 1) / 2);
        int maxcnt  = 9 * base; // 最多有第几个
        for (int &q: queries) {
            if (q > maxcnt) {
                ans.emplace_back(-1);
                continue;
            }
            int num = base + q - 1;
            string left = to_string(num), right = left, tmp;
            if (intLength % 2) {
                left.pop_back();
            }
            std::reverse(right.begin(), right.end()); // 原地操作
            tmp = left + right;
            long long panlindrome = stol(tmp);
            ans.emplace_back(panlindrome);
        }
        return ans;
    }
};

int main() {
    vector<int> vec = {1,2,3,4,5,90}, vec1 = {2,201429812,8,520498110,492711727,339882032,462074369,9,7,6};
    
    int k = 1;
    Solution s;
    s.kthPalindrome(vec1, k);
    return 0;
}
