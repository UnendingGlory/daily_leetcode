// 元素右移
// 给你一个长度固定的整数数组 arr，请你将该数组中出现的每个零都复写一遍，并将其余的元素向右平移。
// 注意：请不要在超过该数组长度的位置写入元素。
// 要求：请对输入的数组 就地 进行上述修改，不要从函数返回任何东西。
// 示例 1：
// 输入：[1,0,2,3,0,4,5,0]
// 输出：null
// 解释：调用函数后，输入的数组将被修改为：[1,0,0,2,3,0,0,4]
// 示例 2：
// 输入：[1,2,3]
// 输出：null
// 解释：调用函数后，输入的数组将被修改为：[1,2,3]
#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    void duplicateZeros(vector<int>& arr) {
        int i, cnt = 0, cnt_zero = 0, non_zero = 0;
        for(i = 0; cnt < arr.size() && i < arr.size(); i++) // 先统计位置和数量
        {
            if(arr[i] == 0) {cnt += 2; cnt_zero++;}
            else {cnt++; non_zero++;}
        }
        i--;
        printf("%d\n", i);
        for(int j = arr.size() - 1; j >= 0; j--, i--) 
        {
            if(arr[i] == 0) 
            {
                if(j == arr.size() - 1 && cnt_zero * 2 + non_zero != arr.size()) // 注意最后一个元素，避免重复复制
                {
                    arr[j] = 0;
                    continue;
                }
                if(j) arr[j] = arr[j--] = 0;
                else arr[j] = 0;
            }
            else arr[j] = arr[i];
        }
    }
};

// 时间复杂度：2*arr.size()即o(n)