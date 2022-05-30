/**
 * @file 298. 二叉树最长连续序列.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 给你一棵指定的二叉树的根节点 root ，请你计算其中 最长连续序列路径 的长度。

    最长连续序列路径 是依次递增 1 的路径。该路径，可以是从某个初始节点到树中任意节点，通过「父 - 子」关系连接而产生的任意路径。且必须从父节点到子节点，反过来是不可以的。

     
    示例 1：


    输入：root = [1,null,3,2,4,null,null,null,5]
    输出：3
    解释：当中，最长连续序列是 3-4-5 ，所以返回结果为 3 。
    示例 2：


    输入：root = [2,null,3,2,null,1]
    输出：2
    解释：当中，最长连续序列是 2-3 。注意，不是 3-2-1，所以返回 2 。
     

    提示：

    树中节点的数目在范围 [1, 3 * 104] 内
    -3 * 104 <= Node.val <= 3 * 104
    通过次数7,024提交次数11,853

 
 * @version 0.1
 * @date 2022-05-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <map>
#include <string>
#include <limits.h>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


// class Solution {
// public:
//     int longestConsecutive(TreeNode* root) {
//         if (root == nullptr) {
//             return 0;
//         }
//         int res = 1;
//         int ans = 1;
//         dfs(root, res, ans);
//         return res;
//     }

//     void dfs(TreeNode* node, int& res, int ans)
//     {
//         if (node == nullptr) {
//             return;
//         }
//         if (node->left != nullptr) {
//             if ((node->val + 1) == node->left->val) {
//                 dfs(node->left, res, ans + 1);
//             } else {
//                 dfs(node->left, res, 1);
//             }
//         }
//         if (node->right != nullptr) {
//             if ((node->val + 1) == node->right->val) {
//                 dfs(node->right, res, ans + 1);
//             } else {
//                 dfs(node->right, res, 1);
//             }
//         }
//         res = max(res, ans);
//     }
// };



class Solution {
public:
    int longestConsecutive(TreeNode* root) {
        int res = 0;
        int ans = 1;
        dfs(root, res, ans);
        return res;
    }

    void dfs(TreeNode* node, int& res, int ans)
    {
        if (node == nullptr) {
            return;
        }
        if (node->left != nullptr) {
            dfs(node->left, res, ((node->val + 1) == node->left->val) ? ans + 1 : 1);
        }
        if (node->right != nullptr) {
            dfs(node->right, res, ((node->val + 1) == node->right->val) ? ans + 1 : 1);
        }
        res = max(res, ans);
    }
};