#include "header.h"

// 给定一个整数数组 asteroids，表示在同一行的行星。
// 对于数组中的每一个元素，其绝对值表示行星的大小，正负表示行星的移动方向（正表示向右移动，负表示向左移动）。每一颗行星以相同的速度移动。
// 找出碰撞后剩下的所有行星。碰撞规则：两个行星相互碰撞，较小的行星会爆炸。
// 如果两颗行星大小相同，则两颗行星都会爆炸。两颗移动方向相同的行星，永远不会发生碰撞。

// Solution: 简单栈模拟，栈中存正向的，遍历数组，如果遇到负向的数则小的爆炸。
// 相等则两个都爆炸。
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> stk;
        for (int star: asteroids) {
            if (star > 0) {
                stk.push_back(star);
            } else {
                bool equal = false;
                while (!stk.empty() && stk.back() > 0 && stk.back() <= -star) {
                    // 相等情况要特殊处理。
                    if (stk.back() == -star) { 
                        stk.pop_back();
                        equal = true;
                        break;
                    }
                    stk.pop_back();
                }
                if (!equal && (stk.empty() || stk.back() < 0)) {
                    stk.push_back(star);
                }
            }
        }
        return stk;
    }
};
