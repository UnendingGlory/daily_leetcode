#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // 每次轮流，选择拿1-3块，我先手，拿掉最后一块的胜
    // 必败点：到你的回合只剩4块石子，其他不论什么情况都能获胜
    // 因此只要不能被4整除就胜利
    bool canWinNim(int n) {
        return n % 4;
    }
};