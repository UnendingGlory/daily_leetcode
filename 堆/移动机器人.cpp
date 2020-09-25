#include <bits/stdc++.h>
using namespace std;

class s_hash
{
    public:
        // 定义为inline提高速度
        inline size_t operator()(const pair<int, int> &p)const 
        // 重载()，内部无对象被修改，函数和参数均定义为const
        {
            return (p.first + p.second) % 29123; 
            // 哈希函数的设计问题。。想不到什么好的哈希函数=。=
            // 所以简单粗暴地相加然后模了一个素数
        }   
};

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int dx = 0, dy = 1, temp; // 一开始向北
        int cur_x = 0, cur_y = 0, ans = 0;
        unordered_set<pair<int, int>, s_hash> s; // 不用自动排序加快速度
        // unordered_set底层是哈希表，对于非基本数据类型要重写hash函数
        // 该使得其作为参数时的有返回结果，set返回结果需要唯一
        // unordered_set返回结果可以不唯一,处理冲突时采用链地址法
        for(auto o : obstacles) s.insert(make_pair(o[0], o[1]));
        for(auto c : commands)
        {
            if(c == -1) {temp = dx; dx = dy;  dy = -temp;}
            if(c == -2) {temp = dx; dx = -dy;  dy = temp;}
            for(int i = 0; i < c; i++) // 一步步模拟
            {
                // 无障碍，则更新，前方有障碍则等待转弯
                if(s.find(make_pair(cur_x + dx, cur_y + dy)) == s.end())
                {
                    cur_x += dx;
                    cur_y += dy;
                    ans = max(ans, cur_x * cur_x + cur_y * cur_y)
                }
            }
        }
        return ans;
    }
};