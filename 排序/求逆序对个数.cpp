#include "header.h"
using namespace std;

/** 使用归并排序，分治法
首先考虑两个有序区间[l1, r1],[l2,r2]在归并过程中如何考虑计算逆序对
2 3 5 7 | 1 4 6 8
首先1和2中选小的，选中右半段的1，加入结果数组，1对逆序对个数贡献为4
2 3 5 7 | 4 6 8
然后2和4中选小的，选中2
3 5 7 | 4 6 8
然后3和4中选小的，选中3
5 7 | 4 6 8
然后5和4中选小的，选中4，4对逆序对个数贡献为2
以此类推。。。
可以看出，只有[l2,r2]区间内的元素加入时才对逆序对个数有贡献，因为[l1, r1]区间内的元素是有序的
贡献的逆序对个数刚好是前面区间的长度

1. 划分问题，将序列划分成元素个数尽量相等的两半
2. 当递归划分到一个元素的时候，则肯定是有序数组
3. 递归求解，分别统计两边的逆序对个数
4. 合并问题，统计i在左边，j在右边的逆序对个数，如上

这样如何能保证正确性？假如原序列为 2 7 3 5 4 1 2
则递归到底层，2 | 7 | 3 | 5 | 4 | 1 | 2
第一层递归返回，2 | 3 7 | 4 5 | 1 2
在这里停顿，注意，只有组内的顺序变了，组间的相对顺序还保持。
所以能保存最终计算出的逆序对个数的正确性。

o(nlogn)
*/
class Solution {
public:
    int ans = 0;
    void mergeSort(vector<int>& nums, int left, int right)
    {
        if(left < right)
        {
            int mid = left + ((right - left) >> 1); // 注意，移位运算符优先级很低
            mergeSort(nums, left, mid);
            mergeSort(nums, mid + 1, right);
            merge(nums, left, mid, mid + 1, right);
        }
    }

    // merge two sorted lists
    void merge(vector<int>& nums, int l1, int r1, int l2, int r2)
    {
        vector<int> temp;
        int i = l1, j = l2;
        while(i <= r1 && j <= r2)
        {
            // 如果右边的更小，则左边的均比其大，则逆序对个数均累加
            if(nums[i] <= nums[j]) temp.push_back(nums[i++]);
            else
            {
                temp.push_back(nums[j++]);
                // 归并的时候统计即可
                ans += (r1 - i + 1);
            }
        }
        while(i <= r1) temp.push_back(nums[i++]);
        while(j <= r2) temp.push_back(nums[j++]);
        for(int i = 0; i < temp.size(); ++i) nums[l1 + i] = temp[i];
    }

    int reversePairs(vector<int>& nums) {
        int n = nums.size();
        mergeSort(nums, 0, n - 1);
        return ans;
    }
};