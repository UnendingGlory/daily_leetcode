#include "header.h"

// Solution1: dp
// dp[i]代表 [0...i] 子问题的操作次数
// nums[i]不超过 nums[i-1]时，i-1位置拿出 nums[i]次操作带上i位置
// nums[i]超过 nums[i-1]时，i-1位置拿出 nums[i-1]次操作带上i位置
// i位置剩下的 nums[i] - nums[i-1]次操作只能自己做


// Solution2: 差分数组
