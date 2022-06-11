/**
 * @file 124. 二叉树中的最大路径和.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
    路径和 是路径中各节点值的总和。
    给你一个二叉树的根节点 root ，返回其 最大路径和 。

    示例 1：
    输入：root = [1,2,3]
    输出：6
    解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
    示例 2：
    输入：root = [-10,9,20,null,null,15,7]
    输出：42
    解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42
     
    提示：
    树中节点数目范围是 [1, 3 * 104]
    -1000 <= Node.val <= 1000

 * 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <map>
#include <sstream>
#include <string>
#include <limits.h>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;



/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        dfs(root, res);
        return res;
    }

    int dfs(TreeNode* node, int& val)
    {
        if (node == nullptr) {
            return 0;
        }

        int l = dfs(node->left, val);
        int r = dfs(node->right, val);
        int all = node->val + max(0, l) + max(0, r); //选择左子树--节点--右子树为一条可能路径
        int alter = node->val + max({0, l, r}); //左子树--节点  节点--右子树
        val = max({val, all, alter});

        return alter; //返回时，作为一条路径的一部分，只能选择左子树或右子树
    }
};

