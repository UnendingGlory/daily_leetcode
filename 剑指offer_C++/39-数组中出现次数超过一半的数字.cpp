#include "header.h"


// Solution1: 哈希表搜索，时间复杂度O(N)，空间复杂度O(N)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n = nums.size() / 2;
        unordered_map<int, int> um;
        for (int &num: nums) {
            if (++um[num] > n) {
                return num;
            }
        }
        return 0;
    }
};


// Solution2: 排序，时间复杂度O(NlogN)，空间复杂度O(1)
class Solution {
public:
    void quickSort(vector<int>& nums, int l, int r) {
        if (l >= r) return;
        int x = l, y = r, pivot = nums[l];
        while (x < y) {
            while (x < y && nums[y] >= pivot) --y;
            std::swap(nums[x], nums[y]);
            while (x < y && nums[x] <= pivot) ++x;
            std::swap(nums[x], nums[y]);
        }
        quickSort(nums, l, x - 1);
        quickSort(nums, x + 1, r);
    }

    int majorityElement(vector<int>& nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums[nums.size() / 2];
    }
};

// Solution3: 分治法
// 如果一个数是整个数组中的众数，那么必定至少是从中分开的左右一半的众数
// 反证：如果均不是左右两个子数组的众数，那么该数次数肯定不够整个数组的一半

// 递归求解子问题，直到所有子问题都是长度为1的数组，长度为1的子数组中唯一的数显然是众数
// 而合并两个区间，如果两个区间的众数均为num，那么合并后的众数也为num
// 如果两个区间众数不同，那么我们需要比较nums1, nums2在合并后的区间的出现次数
// 出现次数大的那个即为整个区间的结果

// 时间复杂度：O(NlogN)，空间复杂度O(logn)，使用了额外的栈空间
class Solution {
public:
    int countInRange(vector<int>&nums, int l, int r, int target) {
        int cnt = 0;
        for (int i = l; i <= r; ++i) {
            if(nums[i] == target) {
                ++cnt;
            }
        }
        return cnt;
    }

    int divide(vector<int> &nums, int l, int r) {
        if (l == r) {
            return nums[l];
        }
        
        int mid = l + ((r - l) / 2);
        int nl = divide(nums, l, mid), nr = divide(nums, mid + 1, r);
        if (nl == nr) {
            return nl;
        } else {
            if (countInRange(nums, l, r, nl) > (r - l + 1) / 2) {
                return nl;
            } else {
                return nr;
            }
        }
    }

    int majorityElement(vector<int>& nums) {
        return divide(nums, 0, nums.size() - 1);
    } 
};

// Solution4：摩尔投票法
// 维护一个候选人candidate和出现的次数count
// 遍历数组，对于每一个x，如果count = 0，则candidate = x
// 若count != 0，若x == candidate，count++
// x != candidate，count--
// 时间复杂度: O(N)，空间复杂度O(1)
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = -1;
        int count = 0;
        for (int num : nums) {
            if (num == candidate)
                ++count;
            else if (--count < 0) {
                candidate = num;
                count = 1;
            }
        }
        return candidate;
    }
};
