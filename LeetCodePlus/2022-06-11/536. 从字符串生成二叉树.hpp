/**
 * @file 536. 从字符串生成二叉树.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 你需要用一个包括括号和整数的字符串构建一棵二叉树。

输入的字符串代表一棵二叉树。它包括整数和随后的 0 、1 或 2 对括号。整数代表根的值，一对括号内表示同样结构的子树。

若存在子结点，则从左子结点开始构建。

 

示例 1:


输入： s = "4(2(3)(1))(6(5))"
输出： [4,2,6,3,1,5]
示例 2:

输入： s = "4(2(3)(1))(6(5)(7))"
输出： [4,2,6,3,1,5,7]
示例 3:

输入： s = "-4(2(3)(1))(6(5)(7))"
输出： [-4,2,6,3,1,5,7]
 

提示：

0 <= s.length <= 3 * 104
输入字符串中只包含 '(', ')', '-' 和 '0' ~ '9' 
空树由 "" 而非"()"表示。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/construct-binary-tree-from-string
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
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
    TreeNode* str2tree(string s) {
        if (s.size() == 0) {
            return nullptr;
        }
        int pos = s.find('('); //寻找根节点数字部分
        int val = stoi(s.substr(0, pos)); //转换成数字
        TreeNode* root = new TreeNode(val);

        // if (pos == string::npos) { //没有左右子树
        //     return root;
        // }

        
        int start = pos;
        int count = 0;
        for (int i = pos; i < s.size(); ++i) {
            if (s[i] == '(') {
                ++count;
            } else if (s[i] == ')') {
                --count;
            }

            if (count == 0) {
                if (start == pos) {
                    root->left = str2tree(s.substr(start + 1, i - start - 1));
                    start = i + 1;
                } else {
                    root->right = str2tree(s.substr(start + 1, i - start - 1));
                }
            }
        }

        return root;
    }
};



