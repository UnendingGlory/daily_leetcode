# cpp
# class Solution {
# public:
#     vector<int> twoSum(vector<int>& nums, int target) {
#         unordered_map<int, int> hashtable;
#         int diff;
#         for (int i = 0; i < nums.size(); ++i) {
#             diff = target - nums[i];
#             if (hashtable.find(diff) != hashtable.end()) {
#                 return {hashtable[diff], i};
#             }
#             hashtable[diff] = i;
#         }
#         return {};
#     }
# };

# 首选cpp，做过的用py
# 在该数组中找出和为目标值target的那两个整数，并返回下标
# 使用一个hashtable记录当前数
# python3
from typing import List
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        hashtable = {}
        for i, num in enumerate(nums):
            diff = target - num
            if diff in hashtable:
                return [hashtable[diff], i]
            hashtable[num] = i
        return []
