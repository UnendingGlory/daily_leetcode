#include "header.h"

// 输入一个整数数组，实现一个函数来调整该数组中数字的顺序，
// 使得所有奇数在数组的前半部分，所有偶数在数组的后半部分。

// Solution1: 其实就是快排的基础算法。
// 双指针 left 和 right 从数组两边寻找。
// left从左往右寻找偶数，right从右往左寻找奇数。
// 寻找到了直接交换即可。
// 可以始终保证，left左侧的元素均是奇数，right右侧的元素均是偶数。
class Solution {
public:
    vector<int> exchange(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            while (l < r && (nums[l] & 1)) {
                ++l;
            }
            while (l < r && !(nums[r] & 1)) {
                --r;
            }
            swap(nums[l], nums[r]);
        }
        return nums;
    }
};

// Solution2: 新建一个数组，第一遍加入奇数，第二遍加入偶数

// 追加问题：保持偶数和偶数，奇数和奇数之间的相对位置不变。
// https://www.nowcoder.com/practice/beb5aa231adc45b2a5dcc5b62c93f593?tpId=13&tqId=11164&rp=1&ru=/ta/coding-interviews&qru=/ta/coding-interviews/question-ranking
// 如果要考虑相对位置的话，那么双指针就需要从头开始走。
// 其实转换成了一个插排的问题。
// i = 0, j = 0
// 1. ++i前进，直到 i碰到偶数停下来（外层循环 while）。
//    令 j = i + 1，j++前进，直到 j碰到奇数停下来。
// 2. 此时 [i...j-1]之间均是 偶数。
// 3. 此时需要将 j位置的奇数放在 i位置，将 [i...j-1]位置的偶数
//    往后挪动一个位置。
//    tmp = nums[j], nums[i...j-1]->nums[i+1...j], nums[i] = tmp

// 循环结束条件：如果 j到了数组末尾还没碰到奇数，那么说明 i，j之间均是偶数。
// 即可返回。
// 由于均是从头开始访问，且没有交换操作，即可保证相对位置不变。
class Solution {
public:
    void reOrderArray(vector<int> &array) {
        int n = array.size();
        if (n <= 1) { // 如果数组长度为1，直接返回
            return;
        }
        int i = 0, j = 0;
        while (i < n) {
            if ((array[i] & 1) == 0) { // 若 a[i]是偶数
                int j = i + 1;
                while ((array[j] & 1) == 0) { // a[j]是偶数，前进
                    if (j == n - 1) { // [i...j]均是偶数，退出
                        return;
                    }
                    ++j;
                }
                // 到达该位置，[i...j-1]位置均为偶数，j位置为奇数
                // 执行插入
                int temp = array[j];
                for (int k = j; k > i; --k) {
                    array[k] = array[k - 1];
                }
                array[i] = temp;
            }
            ++i;
        }
    }
};
