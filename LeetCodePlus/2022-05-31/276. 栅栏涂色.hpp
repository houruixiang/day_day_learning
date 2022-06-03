/**
 * @file 276. 栅栏涂色.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 有 k 种颜色的涂料和一个包含 n 个栅栏柱的栅栏，请你按下述规则为栅栏设计涂色方案：
        每个栅栏柱可以用其中 一种 颜色进行上色。
        相邻的栅栏柱 最多连续两个 颜色相同。
        给你两个整数 k 和 n ，返回所有有效的涂色 方案数 。

        示例 1：
        输入：n = 3, k = 2
        输出：6
        解释：所有的可能涂色方案如上图所示。注意，全涂红或者全涂绿的方案属于无效方案，因为相邻的栅栏柱 最多连续两个 颜色相同。
        示例 2：
        输入：n = 1, k = 1
        输出：1
        示例 3：

        输入：n = 7, k = 2
        输出：42
 
 * 
 * @version 0.1
 * @date 2022-05-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */


// 这道题最多允许连续两个栅栏的颜色相同
// 也就是说，当前状态只有两种情况
// 末尾两个栅栏颜色不同
// 末尾两个栅栏颜色相同
// 在1的情况下，末尾可添加任意颜色的栅栏
// 而在2的情况下，末尾不能再添加重复颜色的栅栏

 
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


class Solution {
public:
    int numWays(int n, int k) {
        // 分别考虑上一次是否为重复色的情况
        vector<vector<int>> dp(n, vector<int>(2, 0));
        dp[0][0] = k;
        dp[0][1] = 0;
        for (int i = 1; i < n; ++i) {
            dp[i][0] = (k - 1) * (dp[i - 1][0] + dp[i - 1][1]);
            dp[i][1] = dp[i - 1][0];
        }
        return dp.back()[0] + dp.back()[1];
    }
};
