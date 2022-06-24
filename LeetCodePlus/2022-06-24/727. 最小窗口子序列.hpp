/**
 * @file 727. 最小窗口子序列.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 给定字符串 S and T，找出 S 中最短的（连续）子串 W ，使得 T 是 W 的 子序列 。

    如果 S 中没有窗口可以包含 T 中的所有字符，返回空字符串 ""。如果有不止一个最短长度的窗口，返回开始位置最靠左的那个。

    示例 1：

    输入：
    S = "abcdebdde", T = "bde"
    输出："bcde"
    解释：
    "bcde" 是答案，因为它在相同长度的字符串 "bdde" 出现之前。
    "deb" 不是一个更短的答案，因为在窗口中必须按顺序出现 T 中的元素。
     

    注：

    所有输入的字符串都只包含小写字母。All the strings in the input will only contain lowercase letters.
    S 长度的范围为 [1, 20000]。
    T 长度的范围为 [1, 100]。

 * 
 * @version 0.1
 * @date 2022-06-24
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once

#include <set>
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

class Solution {
public:
    string minWindow(string s, string t) {
        int m = s.size();
        int n = t.size();
        s = ' ' + s;
        t = ' ' + t;
        // vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int dp[200002][102]; //记录初始位置
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (s[i] == t[j]) {
                    if (j == 1) {
                        dp[i][j] = i; //只记录第一个和t首字母相等的位置
                    }  else {
                        dp[i][j] = dp[i - 1][j -1]; //递推，上一个记录的位置
                    }
                } else {
                    dp[i][j] = dp[i - 1][j]; //递推，s向前一个记录的位置
                }
            }
        }

        string res;
        for (int i = 1; i <= m; ++i) {
            if (s[i] == t.back() && dp[i][n] != 0) {
                int lens = i - dp[i][n] + 1; //根据最后一个字符等于t的末尾进行倒推
                if (res.empty() || (lens < res.size()) ) {
                    res = s.substr(dp[i][n], lens);
                }
            }
        }
        return res;
    }
};