#include <bits/stdc++.h>
using namespace std;

// 边数为n - 1的无向图是树
// 除了根节点，每个节点入度为1，且边数为n - 1

// 只根据入度判断是典型的错误算法，有向图中可能存在环或者非联通
// 可以先用DFS / BFS / 并查集判断是否是联通图
// 再通过边数和入度来判断即可，满足边数 = n - 1的连通图一定不存在环，一定是树
class Solution {
public:
    void DFS(int x, vector<int>& leftChild, vector<int>& rightChild, bool vis[])
    {
        if(vis[x]) return;
        vis[x] = 1;
        if(leftChild[x] != -1) DFS(leftChild[x], leftChild, rightChild, vis);
        if(rightChild[x] != -1) DFS(rightChild[x], leftChild, rightChild, vis);
    }
    
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        if(n == 1) return true; // 特例，单独处理
        int indegree[n], e = 0;
        bool vis[n];
        memset(indegree, 0, sizeof(indegree));
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < n; ++i)
            if(leftChild[i] != -1 || rightChild[i] != -1)
            {
                DFS(i, leftChild, rightChild, vis);
                break; // 注意DFS一个即可
            }
        for(int i = 0; i < n; ++i)
        {
            if(!vis[i]) return false; // 若还有节点未访问到则非联通
            if(leftChild[i] != -1) ++indegree[leftChild[i]], ++e;
            if(rightChild[i] != -1) ++indegree[rightChild[i]], ++e;
        }
        for(int i = 0; i < n; ++i)
            if(indegree[i] > 1) // 若入度大于1
                return false; 
        return e == n - 1; 
    }
};

int main()
{
    return 0;
}