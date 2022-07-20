#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    string reformat(string s) {
		vector<char> ss, t; // ss数字,t字母
		for(int i = 0; i < s.size(); ++i)
		{
			if(s[i] >= '0' && s[i] <= '9') ss.push_back(s[i]);
			else t.push_back(s[i]);
		}
		// 注意这里的int格式转换，非常坑
        if(abs(int(ss.size() - t.size())) >= 2) return "";
		string ans;
		if(ss.size() > t.size())
		{
			ans.push_back(ss.back()), ss.pop_back();
			while(t.size() > 0)
			{
				ans.push_back(t.back());
				ans.push_back(ss.back());
				t.pop_back();
				ss.pop_back();			
			}
		}
		if(t.size() > ss.size())
		{
			ans.push_back(t.back()), t.pop_back();
			while(ss.size() > 0)
			{
				ans.push_back(ss.back());
				ans.push_back(t.back());
				ss.pop_back();
				t.pop_back();
			}
    	}
		if(t.size() == ss.size())
		{
			while(ss.size() > 0)
			{
				ans.push_back(ss.back());
				ans.push_back(t.back());
				ss.pop_back();
				t.pop_back();
			}
    	}
		return ans;
	}
};

// T2
struct table
{
	string num; // table号码
	unordered_map<string, int> m; // 每个桌子对应菜和量
};


class Solution {
public:
    vector<vector<string>> displayTable(vector<vector<string>>& orders) {
		map<int, table> ss;
		set<string> menu; // 菜
		for(auto i : orders)
		{
			int id = stoi(i[1]);
			ss[id].num = to_string(id);
			++ss[id].m[i[2]];
			menu.insert(i[2]);
		}

		// map转table
		vector<table> ssr;
		for(auto i : ss)
		{
			ssr.push_back(i.second);
		}
		
		vector<string> ans1;
		ans1.push_back("Table");
		for(auto j : menu) ans1.push_back(j);

		vector<vector<string>> ans2;
		for(auto i : ssr)
		{
			vector<string> q;
			q.push_back(i.num);
			for(auto j : menu)
			{
				q.push_back(to_string(i.m[j]));
			}
			ans2.push_back(q);
		}

		vector<vector<string>> ans;
		ans.push_back(ans1);
		for(auto i : ans2)
			ans.push_back(i);

		return ans;
    }
};

// T3

// T4