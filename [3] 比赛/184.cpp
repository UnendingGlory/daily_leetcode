#include <bits/stdc++.h>
using namespace std;

// T1
class Solution {
public:
    vector<string> stringMatching(vector<string>& words) {
        set<string> ans;
        for(int i = 0; i < words.size(); ++i)
        {
            string temp = words[i];
            for(int j = 0; j < words.size(); ++j)
            {
                // 找不到返回string :: npos
                if(j != i && words[j].find(temp) != string::npos) ans.insert(temp);
            }
        }
        return vector<string>(ans.begin(),ans.end());
    }
};

// T2
class Solution {
    int p[1001], idx[1002];
public:
    void update(int id) // 将id位置的前面后移一个单位，id位置的移到第一个位置
    {
        int temp = p[id];
        for(int i = id; i >= 1; --i)
        {
            p[i] = p[i - 1];
            idx[p[i]] = i;
        }
        p[0] = temp;
        idx[temp] = 0;
    }

    vector<int> processQueries(vector<int>& queries, int m) {
        vector<int> ans;
        for(int i = 0; i < m; ++i) p[i] = i + 1, idx[i + 1] = i;
        for(int i = 0; i < queries.size(); ++i)
        {
            ans.push_back(idx[queries[i]]);
            update(idx[queries[i]]);;
        }
        return ans;
    }
};

// T3
class Solution {
public:
    string entityParser(string text) {
        // 解析器起手都是&符号,4长度的2个，5长度的1个，6长度的两个，7长度的1个
        string ans = "";
        int idx1 = -1, idx2 = -1; //  & 符号和 紧接的;符号的位置
        bool flag1 = false, flag2 = false; // flag1表示是第一个&符号
        for(int i = 0; i < text.size(); ++i)
        {
            if(text[i] != '&') ans.push_back(text[i]);
            if(text[i] == '&')
            {
                idx1 = i;
                while(i < text.size() && text[i] != ';') ++i;
                // 执行到这里i指向分号或者末尾
                if(i == text.size()) ans += text.substr(i);
                else
                {
                    string temp = text.substr(idx1 + 1, i - idx1 - 1);
                    if(temp == "gt") ans.push_back('>');
                    else if(temp == "lt") ans.push_back('<');
                    else if(temp == "amp") ans.push_back('&');
                    else if(temp == "apos") ans.push_back('\'');
                    else if(temp == "quot") ans.push_back('\"');
                    else if(temp == "frasl") ans.push_back('/');
                    else ans += '&' + temp + ';';
                }  
            }
        }
        return ans;
    }
};

// T4