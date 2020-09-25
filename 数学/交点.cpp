#include <bits/stdc++.h>
using namespace std;

/** 求两条线段的交点==这种手工很简单的事情，计算机真的难写。。。恶心人呗！
 *  线段的三种表示方法：一般方程法，截距法，参数方程法
 *  一般方程法不易表示与y轴平行的，截距法不直观
 *  参数方程法可表示任何直线，且通过参数可以知道点是否在线段上，最佳
 *  参数方程法： x = x1 + t * (x2 - x1), 0 <= t <= 1
 *              y = y1 + t * (y2 - y1), 0 <= t <= 1
 *  先讨论两条线段平行的情况，平行的条件：(y4 - y3) / (x4 - x3) = (y2 - y1) / (x2 - x1)，转换为乘法
 *  平行的时候也有可能有交点（重叠），此时x1=x2=x3=x4或者y1=y2=y3=y4
 *  若x1=x2=x3=x4，则线段y轴端点分别是y1,y2;y3,y4有交点的条件是 min(y2, y4) > max(y1, y3) || min(y1, y3) > max(y2, y4)
 *  若y1=y2=y3=y4，则同理
 *  由于x4可能等于x3，x2可能等于x1，所以将除法转换为乘法：(y4 - y3) * (x2 - x1) == (y2 - y1) * (x4 - x3)
 *  不平行的时候，两条线段的参数方程联立，求出t1,t2（注意，求出的参数式带分母，此时是不平行的情况）
 *  真的挺难解的==。。。t1 = ((y2-y4)*(x2-x1) + (x3-x1)*(y2-y1)) / ((y4-y3)*(x2-x1) - (x4-x3)*(y2-y1))
 *  t2 = ((y4-y2)*(x4-x3) + (x1-x3)*(y4-y3)) / ((x4-x3)*(y2-y1) - (x2-x1)*(y4-y3))
 *  若t1,t2均在[0,1]区间内，则带入原方程求出交点，否则没有交点（交点在线段外）
 */

class Solution {
public:
    // 判断 (xk, yk) 是否在「线段」(x1, y1)~(x2, y2) 上
    // 这里的前提是 (xk, yk) 一定在「直线」(x1, y1)~(x2, y2) 上
    bool inside(int x1, int y1, int x2, int y2, int xk, int yk) {
        // 若与 x 轴平行，只需要判断 x 的部分
        // 若与 y 轴平行，只需要判断 y 的部分
        // 若为普通线段，则都要判断
        return (x1 == x2 || (min(x1, x2) <= xk && xk <= max(x1, x2))) && (y1 == y2 || (min(y1, y2) <= yk && yk <= max(y1, y2)));
    }

    void update(vector<double>& ans, double xk, double yk) {
        // 将一个交点与当前 ans 中的结果进行比较
        // 若更优则替换
        if (!ans.size() || xk < ans[0] || (xk == ans[0] && yk < ans[1])) {
            ans = {xk, yk};
        }
    }

    vector<double> intersection(vector<int>& start1, vector<int>& end1, vector<int>& start2, vector<int>& end2) {
        int x1 = start1[0], y1 = start1[1];
        int x2 = end1[0], y2 = end1[1];
        int x3 = start2[0], y3 = start2[1];
        int x4 = end2[0], y4 = end2[1];

        vector<double> ans;
        // 判断 (x1, y1)~(x2, y2) 和 (x3, y3)~(x4, y3) 是否平行
        if ((y4 - y3) * (x2 - x1) == (y2 - y1) * (x4 - x3)) {
            // 若平行，则判断 (x3, y3) 是否在「直线」(x1, y1)~(x2, y2) 上
            if ((y2 - y1) * (x3 - x1) == (y3 - y1) * (x2 - x1)) {
                // 判断 (x3, y3) 是否在「线段」(x1, y1)~(x2, y2) 上
                if (inside(x1, y1, x2, y2, x3, y3)) {
                    update(ans, (double)x3, (double)y3);
                }
                // 判断 (x4, y4) 是否在「线段」(x1, y1)~(x2, y2) 上
                if (inside(x1, y1, x2, y2, x4, y4)) {
                    update(ans, (double)x4, (double)y4);
                }
                // 判断 (x1, y1) 是否在「线段」(x3, y3)~(x4, y4) 上
                if (inside(x3, y3, x4, y4, x1, y1)) {
                    update(ans, (double)x1, (double)y1);
                }
                // 判断 (x2, y2) 是否在「线段」(x3, y3)~(x4, y4) 上
                if (inside(x3, y3, x4, y4, x2, y2)) {
                    update(ans, (double)x2, (double)y2);
                }
            }
            // 在平行时，其余的所有情况都不会有交点
        }
        else {
            // 联立方程得到 t1 和 t2 的值
            double t1 = (double)(x3 * (y4 - y3) + y1 * (x4 - x3) - y3 * (x4 - x3) - x1 * (y4 - y3)) / ((x2 - x1) * (y4 - y3) - (x4 - x3) * (y2 - y1));
            double t2 = (double)(x1 * (y2 - y1) + y3 * (x2 - x1) - y1 * (x2 - x1) - x3 * (y2 - y1)) / ((x4 - x3) * (y2 - y1) - (x2 - x1) * (y4 - y3));
            // 判断 t1 和 t2 是否均在 [0, 1] 之间
            if (t1 >= 0.0 && t1 <= 1.0 && t2 >= 0.0 && t2 <= 1.0) {
                ans = {x1 + t1 * (x2 - x1), y1 + t1 * (y2 - y1)};
            }
        }
        return ans;
    }
};