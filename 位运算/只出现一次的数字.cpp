// 经典题，全部异或即可
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0; // 0异或a = a
        for(int i : nums) res ^= i;
        return res;
    }
};