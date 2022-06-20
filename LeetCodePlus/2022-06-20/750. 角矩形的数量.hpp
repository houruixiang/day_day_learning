/**
 * @file 750. 角矩形的数量.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个只包含 0 和 1 的 m x n 整数矩阵 grid ，返回 其中 「角矩形 」的数量 。

    一个「角矩形」是由四个不同的在矩阵上的 1 形成的轴对称的矩形。注意只有角的位置才需要为 1。

    注意：4 个 1 的位置需要是不同的。
     

    示例 1：
    输入：grid = [[1,0,0,1,0],[0,0,1,0,1],[0,0,0,1,0],[1,0,1,0,1]]
    输出：1
    解释：只有一个角矩形，角的位置为 grid[1][2], grid[1][4], grid[3][2], grid[3][4]。
    
    示例 2：
    输入：grid = [[1,1,1],[1,1,1],[1,1,1]]
    输出：9
    解释：这里有 4 个 2x2 的矩形，4 个 2x3 和 3x2 的矩形和 1 个 3x3 的矩形。

    示例 3：
    输入：grid = [[1,1,1,1]]
    输出：0
    解释：矩形必须有 4 个不同的角。
     

    提示：
        m == grid.length
        n == grid[i].length
        1 <= m, n <= 200
        grid[i][j] 不是 0 就是 1
        网格中 1 的个数在 [1, 6000] 范围内

 * 
 * @version 0.1
 * @date 2022-06-20
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
    int countCornerRectangles(vector<vector<int>>& grid) {
        int sum = 0;
        vector<int> haveOne;

        for (int i = 0; i < grid[0].size(); ++i) {
            for (int j = i + 1; j < grid[0].size(); ++j) {
                int cnt = 0;
                for (int row = 0; row < grid.size(); ++row) {
                    if (grid[row][i] == 1 && grid[row][j] == 1) {
                        ++cnt;
                    }
                }
                if (cnt >= 2) {
                    sum += cnt * (cnt - 1) / 2;
                }
            }
        }
        return sum;
    }
};



