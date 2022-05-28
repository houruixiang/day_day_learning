/**
 * @file 270. 最接近的二叉搜索树值.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 270. 最接近的二叉搜索树值
    给定一个不为空的二叉搜索树和一个目标值 target，请在该二叉搜索树中找到最接近目标值 target 的数值。

    注意：

    给定的目标值 target 是一个浮点数
    题目保证在该二叉搜索树中只会存在一个最接近目标值的数
    示例：

    输入: root = [4,2,5,1,3]，目标值 target = 3.714286

 * @version 0.1
 * @date 2022-05-28
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
//     int closestValue(TreeNode* root, double target)
//     {
//         int res = INT_MAX;
//         double diff = INT_MAX + .0;
//         dfs(root, res, diff, target);
//         return res;
//     }

//     void dfs(TreeNode* root, int& res, double& diff, double target)
//     {
//         if (root == nullptr) {
//             return;
//         }
//         if (abs(root->val -target) < diff) {
//             diff = abs(root->val -target);
//             res  = root->val;
//         }
//         dfs(root->left, res, diff, target);
//         dfs(root->right, res, diff, target);
//     }
// };

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int closestValue(TreeNode* root, double target)
    {
        int closest = root->val;
        TreeNode* node = root;

        while (node != nullptr) {
            closest = fabs(closest - target) < fabs(node->val - target) ? closest : node->val;
            node = target < node->val ? node->left : node->right;
        }
        return closest;
    }
};