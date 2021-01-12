/***************************************************************************
 *  @file       ListNode.h
 *  @author     Wilosn.Wang
 *  @date       12  Jan 2021
 *  @remark     可以以相对路径将该头文件包含进目标文件使用
				也可以#include <ListNode.h>，然后以gcc -I加入路径的方式组合编译
 *  @note
 ***************************************************************************/

#ifndef LISTNODE_H
#define LISTNODE_H
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
#endif