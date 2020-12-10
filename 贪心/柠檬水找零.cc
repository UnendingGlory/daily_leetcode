#include "header.h"

// 客户会支付的面值有三种
// 5$：直接收下即可
// 10$：找零5美元
// 20$：找零10 + 5美元或者5 + 5 + 5美元
// 显然前者更合适，尽可能保留5美元，5美元的用处大
// 20美元的面值收下后就只能收下了，不能找零

class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for (int i = 0; i < bills.size(); ++i) {
            if (bills[i] == 5) { 
                ++five;
            } else if (bills[i] == 10) {
                if(!five) {
                    return false;
                }
                --five, ++ten;
            } else {
                if(five && ten) {
                    --five, --ten;
                }
                else if(five >= 3) {
                    five -= 3;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
};