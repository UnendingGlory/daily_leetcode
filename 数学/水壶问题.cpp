#include <bits/stdc++.h>
using namespace std;

// 1. 深搜，由于深搜层数太多，会爆栈，我们需要手动建栈
//    递归边界：用unordered_map将深搜过的状态都记录下来，访问过return
//    若x == z或 y == z 或 x + y == z时停止搜索，返回true

class hash_Func
{
    size_t operator()(const pair<int,int> p)const
    {
        return p.first ^ p.second;
    }
};

class Solution {
    unordered_set<pair<int, int>, hash_Func> m;
    int X, Y, Z;
public:

    bool DFS(int x, int y)
    {
        if(m.find({x, y}) != m.end()) return false;
        m.insert({x, y});
        if(x == Z || y == Z || x + y == Z) return true;
        DFS(X, y);
        DFS(x, Y);
        DFS(0, y);
        DFS(x, 0);
        DFS(x - min(x, Y - x), y + min(x, Y - y));
        DFS(x + min(X - x, y), y - min(X - x, y));
        return false;
    }

    bool canMeasureWater(int x, int y, int z) {
        X = x, Y = y, Z = z;

    }
};

class Solution {
public:
    int gcd(int x, int y)
    {
        return y == 0? x: gcd(y, x % y);
    }

    bool canMeasureWater(int x, int y, int z)
    {
        if(z == 0) return true;
        if(x + y >= z && z % gcd(x, y) == 0) return true;
        return false;
    }
};

using PII = pair<int, int>;

class Solution {
public:
    bool canMeasureWater(int x, int y, int z) {
        stack<PII> stk;
        stk.emplace(0, 0);
        auto hash_function = [](const PII& o) {return hash<int>()(o.first) ^ hash<int>()(o.second);};
        unordered_set<PII, decltype(hash_function)> seen(0, hash_function);
        while (!stk.empty()) {
            if (seen.count(stk.top())) {
                stk.pop();
                continue;
            }
            seen.emplace(stk.top());
            
            auto [remain_x, remain_y] = stk.top();
            stk.pop();
            if (remain_x == z || remain_y == z || remain_x + remain_y == z) {
                return true;
            }
            // 把 X 壶灌满。
            stk.emplace(x, remain_y);
            // 把 Y 壶灌满。
            stk.emplace(remain_x, y);
            // 把 X 壶倒空。
            stk.emplace(0, remain_y);
            // 把 Y 壶倒空。
            stk.emplace(remain_x, 0);
            // 把 X 壶的水灌进 Y 壶，直至灌满或倒空。
            stk.emplace(remain_x - min(remain_x, y - remain_y), remain_y + min(remain_x, y - remain_y));
            // 把 Y 壶的水灌进 X 壶，直至灌满或倒空。
            stk.emplace(remain_x + min(remain_y, x - remain_x), remain_y - min(remain_y, x - remain_x));
        }
        return false;
    }
};