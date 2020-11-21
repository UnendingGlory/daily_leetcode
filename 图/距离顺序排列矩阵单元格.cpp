#include "../header.h"

class Solution {
public:
    // BFS? 首先是自己
    vector<vector<int>> allCellsDistOrder(int R, int C, int r0, int c0) {
        int dx[]{0, -1, 1, 0}, dy[]{1, 0, 0, -1};
		vector<vector<int>> ans, vis(R, vector<int>(C, 0));
		int x = r0, y = c0; // 起始点
		queue<pair<int, int>> q;
		q.push({x, y});
		ans.push_back({x, y});
		vis[x][y] = 1;
		while(!q.empty())
		{
			int size = q.size();
			for(int i = 0; i < size; ++i)
			{
				auto temp = q.front();
				q.pop();
				for(int k = 0; k < 4; ++k)
				{
					int newX = temp.first + dx[k], newY = temp.second + dy[k];
					if(newX >= 0 && newX < R && newY >= 0 && newY < C && !vis[newX][newY])
					{
						q.push({newX, newY});
						vis[newX][newY] = 1;
						ans.push_back({newX, newY});
					}
				}
			}
		}
		return ans;
    }
};