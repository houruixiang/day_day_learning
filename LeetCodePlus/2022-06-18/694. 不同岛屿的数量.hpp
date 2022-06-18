/**
 * @file 694. 不同岛屿的数量.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 给定一个非空 01 二维数组表示的网格，一个岛屿由四连通（上、下、左、右四个方向）的 1 组成，你可以认为网格的四周被海水包围。

    请你计算这个网格中共有多少个形状不同的岛屿。两个岛屿被认为是相同的，当且仅当一个岛屿可以通过平移变换（不可以旋转、翻转）和另一个岛屿重合。
    示例 1：

    11000
    11000
    00011
    00011
    给定上图，返回结果 1 。

    示例 2：

    11011
    10000
    00001
    11011
    给定上图，返回结果 3 。

    注意：

    11
    1
    和

    1
    11
    是不同的岛屿，因为我们不考虑旋转、翻转操作。

    提示：二维数组每维的大小都不会超过 50 。

 * 
 * 
 * @version 0.1
 * @date 2022-06-18
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
    int numDistinctIslands(vector<vector<int>>& grid) {
        set<string> dict;
        m = grid.size();
        n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    string s = "4";
                    dfs(i, j, grid, s);
                    dict.insert(s);
                }
            }
        }
        return dict.size();
    }

    void dfs(int i, int j, vector<vector<int>>& grid, string& s)
    {
        if (i < 0 || i >= m || j < 0 || j >= n) {
            return;
        }
    
        grid[i][j] = 0;
        for (int k = 0; k < 4; ++k) {
            int x = i + dx[k];
            int y = j + dy[k];
            if (x < 0 || x >= m || y < 0 || y >= n) {
                continue;
            }
            if (grid[x][y] == 0) {
                continue;
            }
            s.push_back(char('0' + k));
            dfs(x, y, grid, s);
        } 
        s.push_back('#'); // 在每个端点加结束 标志
    }
private:
    int m, n;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};
};

