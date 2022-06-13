/**
 * @file 94. 二叉树的中序遍历.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。

    示例 1：
        输入：root = [1,null,2,3]
        输出：[1,3,2]
    
    示例 2：
        输入：root = []
        输出：[]

    示例 3：
        输入：root = [1]
        输出：[1]

    提示：
        树中节点数目在范围 [0, 100] 内
        -100 <= Node.val <= 100
         

        进阶: 递归算法很简单，你可以通过迭代算法完成吗？

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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    // void dfs(TreeNode* node, vector<int> &res){
    //     if(!node) return;
    //     if(node->left) dfs(node->left, res);
    //     res.push_back(node->val);
    //     if(node->right) dfs(node->right, res);
    // }
    // vector<int> inorderTraversal(TreeNode* root) {
    //     vector<int> res;
    //     dfs(root, res);
    //     return res;
    // }
    
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> res;
        stack<TreeNode*> ss;
        TreeNode* node = root;
        if(!node) return res;
        while(!ss.empty() || node){
           while(node){
               ss.push(node);
               node = node->left;
           }
            node = ss.top(); ss.pop();
            res.push_back(node->val);
            node = node->right;        
        }
        return res;
    }
};

