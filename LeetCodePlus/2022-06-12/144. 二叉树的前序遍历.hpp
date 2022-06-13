/**
 * @file 144. 二叉树的前序遍历.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你二叉树的根节点 root ，返回它节点值的 前序 遍历。

        示例 1：


        输入：root = [1,null,2,3]
        输出：[1,2,3]
        示例 2：

        输入：root = []
        输出：[]
        示例 3：

        输入：root = [1]
        输出：[1]
        示例 4：


        输入：root = [1,2]
        输出：[1,2]
        示例 5：


        输入：root = [1,null,2]
        输出：[1,2]
         

        提示：

        树中节点数目在范围 [0, 100] 内
        -100 <= Node.val <= 100
         

        进阶：递归算法很简单，你可以通过迭代算法完成吗？

 * 
 * 
 * @version 0.1
 * @date 2022-06-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

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



#pragma once

#include <map>
#include <stack>
#include <sstream>
#include <string>
#include <limits.h>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;


// class Solution {
// public:
//     vector<int> preorderTraversal(TreeNode* root) {
//         vector<int> res;
//         dfs(root, res);
//         return res;
//     }

//     void dfs(TreeNode* node, vector<int>& res)
//     {
//         if (node == nullptr) {
//             return;
//         }
//         res.push_back(node->val);
//         dfs(node->left, res);
//         dfs(node->right, res);
//     }
// };


class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }

        vector<int> res;
        stack<TreeNode*> sk;
        TreeNode* node = root;
        while (!sk.empty() || node != nullptr) {
            while (node != nullptr) {
                res.emplace_back(node->val);
                sk.push(node);
                node = node->left;
            }
            node = sk.top();
            sk.pop();
            node = node->right;
        }
        return res;
    }
};


