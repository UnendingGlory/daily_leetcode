#include "header.h"

// 每个人可以ban一个人
// 那就默认ban掉从左往右离自己最近的
// RDD -> Dire
// RD -> Radiant
// 注意可以多轮投票，一个议员如果ban过了别人
// 下一轮还有能力ban其他人
// 所以可以用两个模拟的循环队列来解决该问题
// 哪个队列为空哪个队列就输

class Solution {
public:
    string predictPartyVictory(string senate) {
        queue<int> radiant, dire; // 保存下标即可
        for (int i = 0; i < senate.size(); ++i) {
            if (senate[i] == 'R') {
                radiant.push(i);
            } else {
                dire.push(i);
            }
        }
        int n = senate.size();
        while (!radiant.empty() && !dire.empty()) {
            int rindex = radiant.front(); radiant.pop(); // 两者肯定都要出队列
            int dindex = dire.front(); dire.pop();
            // + n保证投票顺序
            if(rindex < dindex) {
                radiant.push(rindex + n);
            } else {
                dire.push(dindex + n);
            }
        }
        return dire.empty() ? "Radiant" : "Dire";
    }
};