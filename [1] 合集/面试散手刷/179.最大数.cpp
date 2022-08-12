#include "header.h"

// 给定一组非负整数 nums，重新排列每个数的顺序（每个数不可拆分）使之组成一个最大的整数。
// 注意：输出结果可能非常大，所以你需要返回一个字符串而不是整数。

// 输入：nums = [10,2]
// 输出："210"
// 输入：nums = [3,30,34,5,9]
// 输出："9534330"

// Solution1：贪心，将首位大的数放在前面，首位小的数放在后面。
// 和剑指 offer45题类似。
// 比如 110, 21, 将 21放在 110的前面。
// 即计数排序的概念。
// 特殊情况处理：如果有相同首位的数，比如 3, 30。
// 应该将 3放在 30的前面。
// 此时应该比较 330和 303的大小（直接取330即可，满足传递性）。

// 比较方法：对于两个数 x, y，比较 x后接 y和 y后接 x的大小。
// 先统计两个数的基数 dx, dy, x = 110 -> dx = 100, y = 21 -> dy = 10
// 比较 x * dy + y 和 y * dx + x即可。
// 时间复杂度：O(nlogn * logm)，m是 32位整数的最大值。
// 空间复杂度：O(logn)
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // 计数排序
        sort(nums.begin(), nums.end(), [](int x, int y) {
            // 排序方法：比如 x = 110, y = 21。
            // 不能修改 x 和 y，因为需要原值传入排序。
            // 初始基数需要为 10，这样可以避免特例错误。
            long dx = 10, dy = 10;
            while (dx <= x) {
                dx *= 10;
            }
            while (dy <= y) {
                dy *= 10;
            }
            return x * dy + y > y * dx + x;
        });
        if (nums[0] == 0) { // 特例
            return "0";
        }
        string ans;
        for (auto &num: nums) {
            ans += to_string(num);
        }
        return ans;
    }
};

// Solution2: 贪心 + 字符串预处理，利用字符串特性直接比较。
// 转成字符串后
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // 计数排序
        vector<string> strs;
        for (auto num: nums) {
            strs.push_back(to_string(num));
        }
        sort(strs.begin(), strs.end(), [](string x, string y) {
            return x + y > y + x;
        });
        if (strs[0] == "0") { // 特例
            return "0";
        }
        string ans;
        for (auto &str: strs) {
            ans += str;
        }
        return ans;
    }
};
