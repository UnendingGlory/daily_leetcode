#include <bits/stdc++.h>
using namespace std;

// 给定两个矩形点的坐标，判断是否有重叠区域
// 数学方法，将坐标点分别投影到x轴和y轴
// 若有重叠，那么右边界中小的会比左边界中大的还要大
// 且下边界中小的会比上边界中大的还要大

class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return (min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) &&
                min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]));
    }
};
