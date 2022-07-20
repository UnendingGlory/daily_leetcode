#include "header.h"

// 二分
// 分界点的右边的元素即要寻找的值
// 如果num[mid] < num[high]，则在左半段查找, high = mid
// 如果num[mid] > num[high]，则在右半段查找，low = mid + 1
// 如果num[mid] == num[high]，则无法确定目标值在哪半段，high -= 1
// 注意只有移右指针，算法才是正确的，因为右边的左移不会把最小值移掉
// 最后返回num[low]
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int low = 0, high = numbers.size() - 1;
        while (low < high) {
            // 使用移位运算符一定要打括号，优先级低
            int mid = low + ((high - low) >> 1);
            if (numbers[mid] < numbers[high]) {
                high = mid;
            }
            else if (numbers[mid] > numbers[high]) {
                low = mid + 1;
            }
            else {
                high -= 1;
            }
        }
        return numbers[low];
    }
};