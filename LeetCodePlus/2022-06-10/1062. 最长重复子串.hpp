/**
 * @file 1062. 最长重复子串.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定字符串 S，找出最长重复子串的长度。如果不存在重复子串就返回 0。

 

示例 1：

输入："abcd"
输出：0
解释：没有重复子串。
示例 2：

输入："abbaba"
输出：2
解释：最长的重复子串为 "ab" 和 "ba"，每个出现 2 次。
示例 3：

输入："aabcaabdaab"
输出：3
解释：最长的重复子串为 "aab"，出现 3 次。
示例 4：

输入："aaaaa"
输出：4
解释：最长的重复子串为 "aaaa"，出现 2 次。
 

提示：

字符串 S 仅包含从 'a' 到 'z' 的小写英文字母。
1 <= S.length <= 1500

 * 
 * @version 0.1
 * @date 2022-06-10
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

class Solution {
public:
    int longestRepeatingSubstring(string s) {
        int res = 0;
        const int n = s.size();
        //dp[i][j] 分别以s[i]和s[j]结尾的重复子串的长度
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i + 1][j + 1] = dp[i][j] + 1;
                    res = max(res, dp[i + 1][j + 1]);
                }
            }
        }
        return res;
    }
};