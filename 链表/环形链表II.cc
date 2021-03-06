#include "header.h"
#include "ListNode.h"

// Solution 1
// 哈希表

// Solution 2
// 快慢指针追击问题
// 快慢指针一开始都指向表头
// 快慢指针最终会在环内的某个地方相遇
// 判断条件写快指针不为空（因为可能没有环）
// 假设环外部分长度为a
// 从入口点到环内相遇点长度为b
// 慢指针进入环后，在还未跑完一圈前就会和快指针相遇
// 环的剩余长度为c
// 此时，快指针已经走完了环的n圈
// 则慢指针dis = a + b
// 快指针dis = a + n(b + c) + b
// 快指针走过的距离是满指针的两倍
// a + n(b + c) + b = 2(a + b)
// a = (n - 1)(b + c) + c
// 所以当快慢指针相遇的时候，我们再额外使用一个指针ptr指向表头
// 慢指针继续往前走，慢指针和ptr相遇的位置即入口

