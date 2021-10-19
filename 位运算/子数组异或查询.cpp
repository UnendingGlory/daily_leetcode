#include "header.h"

// 利用异或运算的性质，类似于前缀和
// 假设a1 ^ a2 ^ a3 = h
// 则a2 ^ a3 = h ^ a1
// Xor(i, j) = Xor(0, j) ^ Xor(0, i - 1), 其中i >= 1

class Solution {
public:
    vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
        int n = arr.size(), q = queries.size();
        vector<int> xor_serial(n), res(q);
        xor_serial[0] = arr[0];
        for (int i = 1; i < n; ++i) {
            xor_serial[i] = xor_serial[i - 1] ^ arr[i];
        }
        for (int i = 0; i < queries.size(); ++i) {
            int left = queries[i][0], right = queries[i][1];
            if (left) { // 左边端点为0另行判断
                res[i] = xor_serial[right] ^ xor_serial[left - 1];
            }
            else {
                res[i] = xor_serial[right];
            }
        }
        return res;
    }
};
