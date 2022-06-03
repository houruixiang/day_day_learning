/**
 * @file 285. 二叉搜索树中的中序后继.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一棵二叉搜索树和其中的一个节点 p ，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 null 。

节点 p 的后继是值比 p.val 大的节点中键值最小的节点。

 

示例 1：



输入：root = [2,1,3], p = 1
输出：2
解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。
示例 2：



输入：root = [5,3,6,2,4,null,null,1], p = 6
输出：null
解释：因为给出的节点没有中序后继，所以答案就返回 null 了。
 

提示：

树中节点的数目在范围 [1, 104] 内。
-105 <= Node.val <= 105
树中各节点的值均保证唯一。
 * 
 * 
 * @version 0.1
 * @date 2022-06-03
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
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
        vector<TreeNode*> vec;
        inorder(vec, root);

        for (int i = 0; i < vec.size(); ++i) {
            if ((vec[i] == p) && (i < vec.size() - 1)) {
                return vec[i + 1];
            }
        }
        return nullptr;
    }
    void inorder(vector<TreeNode*>& vec, TreeNode* node)
    {
        if (node == nullptr) {
            return;
        }
        inorder(vec, node->left);
        vec.push_back(node);
        inorder(vec, node->right);
    }
};