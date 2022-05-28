/**
 * @file 272. 最接近的二叉搜索树值 II.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 272. 最接近的二叉搜索树值 II
        给定二叉搜索树的根 root 、一个目标值 target 和一个整数 k ，返回BST中最接近目标的 k 个值。你可以按 任意顺序 返回答案。

        题目 保证 该二叉搜索树中只会存在一种 k 个值集合最接近 target

        示例 1：
        输入: root = [4,2,5,1,3]，目标值 = 3.714286，且 k = 2
        输出: [4,3]
  
        示例 2:
        输入: root = [1], target = 0.000000, k = 1
        输出: [1]
        
        提示：
        二叉树的节点总数为 n
        1 <= k <= n <= 104
        0 <= Node.val <= 109
        -109 <= target <= 109

        进阶：假设该二叉搜索树是平衡的，请问您是否能在小于 O(n)（ n = total nodes ）的时间复杂度内解决该问题呢？

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
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

 // 中序遍历 + 双头队列限制长度为k
class Solution {
public:
    vector<int> closestKValues(TreeNode* root, double target, int k) {
        deque<int> dq;
        inorder(dq, root, target, k);

        vector<int> res;
        while(!dq.empty()) {
            res.push_back(dq.front());
            dq.pop_front();
        }
        return res;
    }

    void inorder(deque<int>& dq, TreeNode* root, double target, int k)
    {
        if (root == nullptr) {
            return;
        }
        inorder(dq, root->left, target, k);
        if (dq.size() == k) {
            if (fabs(root->val - target) < fabs(dq.front() - target)) {
                dq.pop_front();
                dq.push_back(root->val);
            }
        } else {
            dq.push_back(root->val);
        }
        inorder(dq, root->right, target, k);
    }
};