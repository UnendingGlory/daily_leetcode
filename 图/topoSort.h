/***************************************************************************
 *  @file       topoSort.h
 *  @author     Wilosn.Wang
 *  @date       12  Jan 2021
 *  @remark     可以以相对路径将该头文件包含进目标文件使用
				也可以#include <topoSort.h>，然后以gcc -I加入路径的方式组合编译
 *  @note
 ***************************************************************************/

#ifndef TOPOSORT_H
#define TOPOSORT_H
#include "header.h"

vector<int> topSort(vector<int>& deg, vector<vector<int>>& graph, vector<int>& items) {
    queue<int> Q;
    for (auto& item: items) {
        if (deg[item] == 0) {
            Q.push(item);
        }
    }
    vector<int> res;
    while (!Q.empty()) {
        int u = Q.front(); 
        Q.pop();
        res.emplace_back(u);
        for (auto& v: graph[u]) {
            if (--deg[v] == 0) {
                Q.push(v);
            }
        }
    }
    return res.size() == items.size() ? res : vector<int>{};
}

#endif