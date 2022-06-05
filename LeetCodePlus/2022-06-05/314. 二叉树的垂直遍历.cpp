/**
 * @file 314. 二叉树的垂直遍历.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个二叉树的根结点，返回其结点按 垂直方向（从上到下，逐列）遍历的结果。

        如果两个结点在同一行和列，那么顺序则为 从左到右。

        示例 1：


        输入：root = [3,9,20,null,null,15,7]
        输出：[[9],[3,15],[20],[7]]
        示例 2：


        输入：root = [3,9,8,4,0,1,7]
        输出：[[4],[9],[3,0,1],[8],[7]]
        示例 3：


        输入：root = [3,9,8,4,0,1,7,null,null,null,2,5]
        输出：[[4],[9,5],[3,0,1],[8,2],[7]]
         

        提示：

        树中结点的数目在范围 [0, 100] 内
        -100 <= Node.val <= 100

 * 
 * @version 0.1
 * @date 2022-06-05
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
#include <string>
#include <limits.h>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;


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
    vector<vector<int>> verticalOrder(TreeNode* root) {
        inoder(root, 0, 0);
        vector<vector<int>> res;
        int idx = 0;
        for (auto it = ans.rbegin(); it != ans.rend(); ++it, ++idx) {
            res.push_back({});
            for (auto iter = (it->second).begin(); iter != (it->second).end(); ++iter) {
                for (const auto& val : iter->second) {
                    res[idx].push_back(val);
                }
            }
        }
        return res;
    }

    void inoder(TreeNode* node, int rank, int v)
    {
        if (node == nullptr) {
            return;
        }
        ans[rank][v].push_back(node->val);
        inoder(node->left, rank + 1, v + 1);
        inoder(node->right, rank - 1, v + 1);
    }

private:
    map<int, map<int, vector<int>>> ans;
};