// 最短转换序列长度
// 对单词进行建图，然后求start到end的最短路径
#include <../header.h>


// 建图思想：最朴素的想法就是两两枚举节点
// 如果相差1，则将其加入相邻边，但这样效率过低（枚举和判断差一的时间复杂度都较高）
// 可以通过建立中间虚拟节点的方式来解决
// 如hit，可以建立*it, h*t, hi*三个虚拟节点与其相连
// 如果有单词可以转换到hit，则必然和这三个节点相邻。
// 这使得在最终返回结果时要做一些改变
class Solution {
	int id = 0;
	vector<vector<int>> edge; // 图
	unordered_map<string, int> wordId; // 单词到编号的映射
public:

	void addWord(string& word)
	{
		// 还未加入图
		if(wordId.count(word) == 0)
		{
			wordId[word] = id++;
			edge.emplace_back();
		}
	}

	void addEdge(string &word)
	{
		addWord(word);
		int id1 = wordId[word]; // 获得该word的ID
		for(char &it : word)
		{
			// 先暂时记录下来，等下还要改回去
			char temp = it;
			it = '*';
			addWord(word);
			int id2 = wordId[word];
			// 建立双向边
			edge[id1].emplace_back(id2);
			edge[id2].emplace_back(id1);
			it = temp;
		}
	}

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		for(string &word : wordList)
		{
			addEdge(word);
		}
		addEdge(beginWord);
		if(wordId.count(endWord) == 0) return 0; // endWord不在图中
		// 最短路的dis数组
		vector<int> dis(id, INT_MAX);
		int beginId = wordId[beginWord], endId = wordId[endWord];
		dis[beginId] = 0; // 自己到自己距离为0
		queue<int> q;
		q.push(beginId);
		// 广度优先的过程中维护dis
		while(!q.empty())
		{
			int x = q.front();
			q.pop();
			// 路径-1 + 起点的贡献
			if(x == endId)
				return dis[endId] / 2 + 1;
			// 对x的每一个相邻边
			for(int &it : edge[x])
			{
				// 如果还没有更新
				if(dis[it] == INT_MAX)
				{
					// 更新之
					dis[it] = dis[x] + 1;
					q.push(it);
				}
			}
		}
		return 0;
    }
};