// Rank : 590
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(vector<string>& logs) {
        stack<string> s;
        for(auto i : logs)
        {
            if(!s.empty() && i == "../") s.pop();
            else if(i != "../" && i != "./")
            {
                s.push(i);
            }
        }
        return s.size();
    }
};

// 模拟算法，一次轮转一周
class Solution {
public:
    int minOperationsMaxProfit(vector<int>& customers, int boardingCost, int runningCost) {
        int await = 0, maxrevenue = 0, maxi = 0, boarding = 0;
        bool flag = true;
        int i;
        for(i = 0; flag || await > 0 || i < customers.size(); ++i) // 标记时刻
        {
            int revenue = 0;
            flag = false;
            if(i < customers.size()) await += customers[i];
            if(await < 4) boarding += await;
            else boarding += 4; 
            revenue += boarding * boardingCost;
            revenue -= (i + 1) * runningCost; // 每次转一圈
            // cout << revenue << '\n';
            if(revenue > maxrevenue)
            {
                maxrevenue = revenue;
                maxi = i;
            }
            if(await >= 4) await -= 4;
            else await = 0;
        }
        if(maxrevenue <= 0) return -1;
        return maxi + 1;
    }
};


class Tree
{
    public:
        string name;
        vector<Tree*> child; // 孩子
        unsigned alive = 1; // 默认活着
        Tree() = default;
        Tree(string name):name(name){};
};

// 树的先根遍历，根左右
class ThroneInheritance {
    Tree *root;
    vector<string> ans;
    unordered_map<string, Tree*> m; // 标记string到Tree
public:

    ThroneInheritance(string kingName) {
        root = new Tree(kingName);
        m[kingName] = root;
    }
    
    // birth即向树中插入
    void birth(string parentName, string childName) {
        auto tr = m[parentName];
        if(tr)
        {
            auto temp = new Tree(childName);
            tr->child.emplace_back(temp);
            m[childName] = temp;
        }
    }
    
    // 标记该人为死人
    void death(string name) 
    {
        auto tr = m[name];
        if(tr) tr->alive = 0; // 死人
    }
    
    // 先根遍历该树，输出所有活着的人
    vector<string> getInheritanceOrder() {
        ans.clear(); // 先清空
        preOrder(root);
        return ans;
    }

    // 先根遍历该树
    void preOrder(Tree *r)
    {
        if(r == nullptr) return;
        if(r->alive) ans.emplace_back(r->name);
        for(int i = 0; i < r->child.size(); ++i)
            preOrder(r->child[i]);
    }

};

/**
 * Your ThroneInheritance object will be instantiated and called as such:
 * ThroneInheritance* obj = new ThroneInheritance(kingName);
 * obj->birth(parentName,childName);
 * obj->death(name);
 * vector<string> param_3 = obj->getInheritanceOrder();
 */

// 图的问题，传递平衡
class Solution {
public:
    int maximumRequests(int n, vector<vector<int>>& requests) {
        int a[n] = {0};
        for(auto t : requests)
        {
            int i = t[0], j = t[1];

        }

    }
};