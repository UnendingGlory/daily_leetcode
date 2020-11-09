#include "../header.h"

class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		// 保存小的应该用大顶堆，默认大顶堆
		using ll = long long;
		// 存储编号和距离，pair自带()，有可调用对象
		// 但是注意，pair自带的是优先比较第一个对象，所以距离要放在第一维
        priority_queue<pair<ll, size_t>> pq;
		for(int i = 0; i < points.size(); ++i)
		{
			int size = pq.size();
			ll dis = points[i][0]*points[i][0] + points[i][1]*points[i][1];
			if(size < K) pq.push({dis, i});
			else if(dis < pq.top().first) // 也要判断处理
			{
				pq.pop();
				pq.push({dis, i});
			}
		}
		vector<vector<int>> ans;
		// pq和队列一样无begin，只能通过while pop来遍历
		while(!pq.empty())
		{
			ans.emplace_back(points[pq.top().second]);
			pq.pop();
		}
		return ans;
    }
};

// 对于优先级队列可以预处理，修改成无监督的方式
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		// 保存小的应该用大顶堆，默认大顶堆
		using ll = long long;
		// 存储编号和距离，pair自带()，有可调用对象
		// 但是注意，pair自带的是优先比较第一个对象，所以距离要放在第一维
        priority_queue<pair<ll, size_t>> pq;
		// 先将前k个打入
		for(int i = 0; i < K; ++i)
		{
			ll dis = points[i][0]*points[i][0] + points[i][1]*points[i][1];
			pq.push({dis, i});
		}
		for(int i = K; i < points.size(); ++i)
		{
			ll dis = points[i][0]*points[i][0] + points[i][1]*points[i][1];
			if(dis < pq.top().first) // 也要判断处理
			{
				pq.pop();
				pq.push({dis, i});
			}
		}
		vector<vector<int>> ans;
		// pq和队列一样无begin，只能通过while pop来遍历
		while(!pq.empty())
		{
			ans.emplace_back(points[pq.top().second]);
			pq.pop();
		}
		return ans;
    }
};



// 编写自己的可调用对象
// 这里不能再用pair，因为不知道如何对pair的()重载
// cc没有构造函数，没有私有成员，所以是一个聚合类，可以用花括号初始化
using ll = long long;
struct cc
{
	size_t id;
	ll dis;
};

class compare
{
public:
	bool operator()(const cc& a, const cc& b) const
	{
		return a.dis < b.dis;
	}
};

class Solution1 {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		// 保存小的应该用大顶堆，默认大顶堆
		// 编写自己的可调用对象，将dis放在第二维
        priority_queue<cc, vector<cc>, compare> pq;
		// 先将前k个打入
		for(size_t i = 0; i < K; ++i)
		{
			ll dis = points[i][0]*points[i][0] + points[i][1]*points[i][1];
			pq.push({i, dis});
		}
		for(size_t i = K; i < points.size(); ++i)
		{
			ll dis = points[i][0]*points[i][0] + points[i][1]*points[i][1];
			if(dis < pq.top().dis) // 也要判断处理
			{
				pq.pop();
				pq.push({i, dis});
			}
		}
		vector<vector<int>> ans;
		// pq和队列一样无begin，只能通过while pop来遍历
		while(!pq.empty())
		{
			ans.emplace_back(points[pq.top().id]);
			pq.pop();
		}
		return ans;
    }
};


int main()
{
	Solution1 s;
	vector<vector<int>> points{{1, 3}, {-2, 2}, {2, -2}};
	auto ans = s.kClosest(points, 2);
	for(auto i : ans)
		std::cout << i[0] << i[1] << '\n';
	return 0;
}