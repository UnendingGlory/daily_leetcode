#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:

	int sum(int x)
	{
		int ret = 0;
		while(x)
		{
			ret += x % 10;
			x = x/ 10;
		}
		return ret;
	}

    int countLargestGroup(int n) {
		unordered_map<int, int> m; // 整数，次数
		int max_n = -1, ans = 0;
		for(int i = 1; i <= n; ++i)
		{
			int x = sum(i);
			++m[x];
			if(m[x] == max_n) ++ans;
			else if(m[x] > max_n)
			{
				max_n = m[x];
				ans = 1;
			}
		}
		return ans;
    }
};

// T2
class Solution {
public:
    bool canConstruct(string s, int k) {
        if(s.size() < k) return false;
		int cnt[26] = {0}, odd_n = 0;
		for(auto c : s)
			++cnt[c - 'a'];
		for(int i = 0; i < 26; ++i)
			if(cnt[i] & 1) // 是奇数
				++odd_n;
		if(odd_n > k) return false;
		return true;
    }
};

// T3
// 遍历矩阵的每一个点
class Solution {
public:
    bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
		//bool flag = false; // 一开始没有交点
		int r = radius * radius;
        for(int i = x1; i <= x2; ++i)
		{
			for(int j = y1; j <= y2; ++j)
			{
				if((i - x_center) * (i - x_center) + (j - y_center) * (j - y_center) <= r)
					return true; // 重叠
			}
		}
		return false;
    }
};

// T4