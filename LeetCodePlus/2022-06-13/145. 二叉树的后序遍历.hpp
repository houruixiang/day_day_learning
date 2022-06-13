/**
 * @file 145. 二叉树的后序遍历.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 给你一棵二叉树的根节点 root ，返回其节点值的 后序遍历 。
 * 
        示例 1：
            输入：root = [1,null,2,3]
            输出：[3,2,1]

        示例 2：
            输入：root = []
            输出：[]

        示例 3：S
            输入：root = [1]
            输出：[1]
         

        提示：
            树中节点的数目在范围 [0, 100] 内
            -100 <= Node.val <= 100
             

            进阶：递归算法很简单，你可以通过迭代算法完成吗？

 * 
 * 
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
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
// class Solution {
// public:
//     vector<int> postorderTraversal(TreeNode* root) {
//         vector<int> res;
//         dfs(root, res);
//         return res;
//     }
//     void dfs(TreeNode* node, vector<int>& res)
//     {
//         if (node == nullptr) {
//             return;
//         }
//         dfs(node->left, res);
//         dfs(node->right, res);
//         res.push_back(node->val);
//     }
// };



class Solution {
public:
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> res;
        if (root == nullptr) {
            return res;
        }

        stack<TreeNode *> stk;
        TreeNode *prev = nullptr;
        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.emplace(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            if (root->right == nullptr || root->right == prev) {
                res.emplace_back(root->val);
                prev = root;
                root = nullptr;
            } else {
                stk.emplace(root);
                root = root->right;
            }
        }
        return res;
    }
};



