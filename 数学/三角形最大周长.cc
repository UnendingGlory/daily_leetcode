#include "header.h"

// 先从大到小排序，取开头的三个数a, b, c
// 如果b+c>a，则能组成三角形(其他两对条件肯定满足)
// 如果不满足，则取后面的三个数

class Solution {
public:
    int largestPerimeter(vector<int>& A) {
        sort(A.begin(), A.end(), greater<int>());
        for (int i = 0; i < A.size() - 2; ++i)
        {
            if(A[i + 1] + A[i + 2] > A[i]) 
                return A[i] + A[i + 1] + A[i + 2];
        }
        return 0;
    }
};