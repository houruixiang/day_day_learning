/**
 * @file 562. 矩阵中最长的连续1线段.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 给定一个 m x n 的二进制矩阵 mat ，返回矩阵中最长的连续1线段。

这条线段可以是水平的、垂直的、对角线的或者反对角线的。

 

示例 1:



输入: mat = [[0,1,1,0],[0,1,1,0],[0,0,0,1]]
输出: 3
示例 2:



输入: mat = [[1,1,1,1],[0,1,1,0],[0,0,0,1]]
输出: 4
 

提示:

m == mat.length
n == mat[i].length
1 <= m, n <= 104
1 <= m * n <= 104
mat[i][j] 不是 0 就是 1.



 * @version 0.1
 * @date 2022-06-08
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
    int longestLine(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();
        int res = 0;
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(n + 1, vector<int>(4, 0)));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (mat[i - 1][j -1] == 1) {
                    dp[i][j][0] = dp[i - 1][j][0] + 1;
                    dp[i][j][1] = dp[i][j - 1][1] + 1;
                    dp[i][j][2] = dp[i - 1][j - 1][2] + 1;
                    if (j < n) dp[i][j][3] = dp[i - 1][j + 1][3] + 1;
                    res = max({res, dp[i][j][0], dp[i][j][1], dp[i][j][2], dp[i][j][3]});             
                }
            } 
        }
        return res;
    }
};