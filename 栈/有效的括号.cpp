#include <bits/stdc++.h>
using namespace std;

// 空间可以优化，栈可以优化成三个int型变量表示三种括号的左括号数量

class Solution {
public:
    bool isValid(string s) {
        //if(s == "") return true;
        stack <char> S;
        for(auto i : s)
        {
            if(i == '(' || i == '[' || i == '{')
                S.push(i);
            else
            {
                if(S.empty()) return false;
                if(i == ')' && S.top() != '(') return false;
                else if(i == ']' && S.top() != '[') return false;
                else if(i == '}' && S.top() != '{') return false;
                else S.pop();
            }
        }
        if(S.empty()) return true;
        else return false;
    }
};

int main()
{
    string s;
    cin >> s;
    Solution m;
    cout << m.isValid(s);
    return 0;
}