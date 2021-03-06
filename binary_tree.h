/***************************************************************************
 *  @file       binary_tree.h
 *  @author     Wilosn.Wang
 *  @date       12  Jan 2021
 *  @remark     可以以相对路径将该头文件包含进目标文件使用
				也可以#include <binary_tree.h>，然后以gcc -I加入路径的方式组合编译
 *  @note
 ***************************************************************************/

#ifndef BINARY_TREE_H
#define BINART_TREE_H
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif