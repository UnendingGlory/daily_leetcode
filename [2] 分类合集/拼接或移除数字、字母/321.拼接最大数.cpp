#include "header.h"

// 给定长度分别为 m 和 n 的两个数组，其元素由 0-9 构成，表示两个自然数各位上的数字。
// 现在从这两个数组中选出 k (k <= m + n) 个数字拼接成一个新的数，要求从同一个数组中取出的数字保持其在原数组中的相对顺序。
// 求满足该条件的最大数。结果返回一个表示该最大数的长度为 k 的数组。
// 说明: 请尽可能地优化你算法的时间和空间复杂度。

// 输入:
// nums1 = [3, 4, 6, 5]
// nums2 = [9, 1, 2, 5, 8, 3]
// k = 5
// 输出:
// [9, 8, 6, 5, 3]

// 输入:
// nums1 = [6, 7]
// nums2 = [6, 0, 4]
// k = 5
// 输出:
// [6, 7, 6, 0, 4]

// 402题的扩展问题，不同的是，402题是在一个数组中选取，而该题是两个数组。
// Solution：贪心 + 单调栈 + 归并。
// 贪心 + 单调栈解决在单独的数组中选择 k个数。
// i从 0-k 枚举，代表能在数组 nums1中选取的数字个数，k - i即在nums2中选取的数字个数。
// 需要注意，i需要 < nums1.size(), k - i < nums2.size()
// 得到选取出的两个数组后，采用归并的方式得到最终的数字，并取最大值。
// 归并方法：nums1 = [3, 4, 6, 5] nums2 = [9, 1, 2, 5, 8, 3], k = 5
// 第一趟从 num1中选取 0个，从 num2中选取5个，[9, 2, 5, 8, 3]
// 第二趟从 num1中选取 1个 [6]，从 nums2中选取4个, [9, 5, 8, 3]
//      归并：类似两个有序链表合并，9 -> 6 -> 5 -> 8 -> 3
// 第三趟从 num1中选取 2个 [6, 5]，从 nums2中选取3个, [9, 8, 3]
//      归并：类似两个有序链表合并，9 -> 8 -> 6 -> 5 -> 3
// ...
// 比较这 n个数，发现 98653最大。
// 比较方法：数字依次比较，vector可以直接比较。
// 时间复杂度：O()，空间复杂度
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int len1 = nums1.size(), len2 = nums2.size();
        vector<int> picked1, picked2, ans{0};
        for (int i = 0; i <= k; ++i) {
            if (i <= len1 && k - i <= len2) { // 需要满足数组长度条件
                picked1 = pickMax(nums1, i);
                picked2 = pickMax(nums2, k - i);
                picked1 = merge(picked1, picked2);
                ans = max(ans, picked1);
            }
        }
        return ans;
    }
    
    // 从 nums中选取 k个组成最大数，贪心 + 单调栈。
    // 需保证 k < nums.size()
    vector<int> pickMax(vector<int> &nums, int k) {
        k = nums.size() - k;
        vector<int> stk;
        for (int num: nums) {
            while (k && !stk.empty() && stk.back() < num) {
                --k;
                stk.pop_back();
            }
            stk.push_back(num);
        }

        // 有可能选取的不足 k个
        while (k) {
            stk.pop_back();
            --k;
        }
        return stk;
    }

    // 判断大小, picked[i] 是否大于 picked[j]
    // 某个情况下，需要特判，比如 [6, 6, 8, 4] 和 [6, 6, 7]，第一个6和第二个6应该选第一个数组的。
    // [6, 6] 和 [6, 6, 7]，第一个6和第二个6应该选第二个数组的。
    // [6, 6] 和 [6, 6, 4]，第一个6和第二个6也可以选第二个数组的。
    // 因此，如果比较的元素一直相等，假设是 i走到了数组末尾，就选j。
    // 如果有不相等的，则选大的那个对应的下标。
    int compare(vector<int>& picked1, int i, vector<int>& picked2, int j) {
        int len1 = picked1.size(), len2 = picked2.size();
        while (i < len1 && j < len2) {
            int difference = picked1[i] - picked2[j];
            if (difference != 0) {
                return difference;
            }
            i++;
            j++;
        }
        if (i == len1) {
            return -1;
        }
        if (j == len2) {
            return 1;
        }
        return 0;
    }

    // merge
    vector<int> merge(vector<int> &picked1, vector<int> picked2) {
        int i = 0, j = 0, len1 = picked1.size(), len2 = picked2.size();
        vector<int> merged;
        int x, y;
        while (i < len1 && j < len2) {
            if (compare(picked1, i, picked2, j) > 0) {
                merged.push_back(std::move(picked1[i++])); // 使用 std::move节省内存
            } else {
                merged.push_back(std::move(picked2[j++]));
            }
        }
        while (i < len1) {
            merged.push_back(std::move(picked1[i++]));
        }
        while (j < len2) {
            merged.push_back(std::move(picked2[j++]));
        }
        return merged;
    }
};

int main() {
    vector<int> nums1{1, 2, 3}, nums2{3, 4, 5};
    std::cout << nums1 < nums2 << std::endl;
    return 0;
}
