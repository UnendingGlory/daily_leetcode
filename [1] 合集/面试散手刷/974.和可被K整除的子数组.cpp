#include "header.h"

// 给定一个整数数组 nums和一个整数 k，返回其中元素之和可被 k整除的（连续、非空）子数组的数目。
// [子数组] 是数组的 [连续] 部分。

// 和 hot100第 560题 [和为 K的子数组]非常类似。

// Solution1：前缀和 + 双层循环。
// pre[i] 代表 nums[0] + ... nums[i - 1]之和
// pre[i] - pre[i - 1] = nums[i - 1]
// 时间复杂度：O(n^2)，空间复杂度：O(n)。
// 会超时。
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> pre(n + 1);
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            sum += nums[i - 1];
            pre[i] = sum;
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                if (pre[j] - pre[i] == k) {
                    ++ans;
                }
            }
        }
        return ans;
    }
};

// Solution2：哈希表优化。
// (pre[j] - pre[i]) % k = 0。
// 根据同余定理的充分性，如果 a, b, m均为正整数，
// 若有 a % m = b % m，那么(a - b) % m = 0。
// 即 pre[j] % k = pre[i] % k。
// 因此对于某一个前缀和的下标 i，只需要去查找前缀合数组里前面有多少个数和 pre[i] % k的结果相同即可。
// 可以用哈希表存储 pre[i] % k和个数的映射。

// 注意，对于负数需要特殊处理，假如 pre[j] = 4, pre[i] = -6, k = 5
// 那么 (pre[j] - pre[i]) % k = 10 % 5 = 0。
// 而 4 % 5 = 4, -6 % 5 = -1，两者的余数不相同，因此对负数的余数需要转换为同模的正数。
// (-6 % 5 + 5) % 5 = (-1 + 5) % 5 = 4。可由此得到正确的结果。
// 即 (pre[i] % k + k) % k。

// 时间复杂度：O(n)，空间复杂度：O(n)。
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, int> hashtable;
        int sum = 0, ans = 0, remainder;
        // 余为 0的个数设置为1，比如[5] 余 5就是 0，应该统计该数。
        hashtable[0] = 1;
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            remainder = (sum % k + k) % k; // 这步操作很关键
            if (hashtable.find(remainder) != hashtable.end()) {
                ans += hashtable[remainder];
            }
            hashtable[remainder]++;
        }
        return ans;
    }
};


int main() {
    vector<int> vec{2, -2, 2, -4};
    int k = 6;
    Solution s;
    cout << s.subarraysDivByK(vec, k) << endl;
    return 0;
}
