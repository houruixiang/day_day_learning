/**
 * @file 265. 粉刷房子 II.cpp
 * 
 * @author ruihou
 * @brief 
 * 265. 粉刷房子 II
    假如有一排房子共有 n 幢，每个房子可以被粉刷成 k 种颜色中的一种。房子粉刷成不同颜色的花费成本也是不同的。
    你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。

    每个房子粉刷成不同颜色的花费以一个 n x k 的矩阵表示。

    例如，costs[0][0] 表示第 0 幢房子粉刷成 0 号颜色的成本；costs[1][2] 表示第 1 幢房子粉刷成 2 号颜色的成本，以此类推。
    返回 粉刷完所有房子的最低成本 。

    示例 1：

    输入: costs = [[1,5,3],[2,9,4]]
    输出: 5
    解释: 
    将房子 0 刷成 0 号颜色，房子 1 刷成 2 号颜色。花费: 1 + 4 = 5; 
    或者将 房子 0 刷成 2 号颜色，房子 1 刷成 0 号颜色。花费: 3 + 2 = 5. 
    示例 2:

    输入: costs = [[1,3],[2,4]]
    输出: 5
    

    提示：

    costs.length == n
    costs[i].length == k
    1 <= n <= 100
    2 <= k <= 20
    1 <= costs[i][j] <= 20
 
 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <limits.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCostII(vector<vector<int>>& costs) {
        const int n = costs.size();
        const int k = costs[0].size();
        vector<vector<int>> dp(n, vector<int>(k, INT_MAX));
        for (int i = 0; i < k; ++i) {
            dp[0][i] = costs[0][i];
            // std::cout << dp[0][i] << std::endl;
        }
    
        for (int i = 1; i < costs.size(); ++i) {
            for (int j = 0; j < k; ++j) {
                for (int t = 0; t < k; ++t) {
                    if (t == j) {
                        continue;
                    }
                    dp[i][j] = min(dp[i][j], dp[i - 1][t] + costs[i][j]);
                }
                // std::cout << dp[i][j] << std::endl;
            }
        }
        int res = INT_MAX;
        for (int i = 0; i < k; ++i) {
            res = min(res, dp.back()[i]);
            // std::cout << dp.back()[i] << std::endl;
        }
        return res;
    }
};
