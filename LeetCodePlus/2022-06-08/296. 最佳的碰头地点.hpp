/**
 * @file 296. 最佳的碰头地点.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个 m x n  的二进制网格 grid ，其中 1 表示某个朋友的家所处的位置。返回 最小的 总行走距离 。

总行走距离 是朋友们家到碰头地点的距离之和。

我们将使用 曼哈顿距离 来计算，其中 distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y| 。

 

示例 1：



输入: grid = [[1,0,0,0,1],[0,0,0,0,0],[0,0,1,0,0]]
输出: 6 
解释: 给定的三个人分别住在(0,0)，(0,4) 和 (2,2):
     (0,2) 是一个最佳的碰面点，其总行走距离为 2 + 2 + 2 = 6，最小，因此返回 6。
示例 2:

输入: grid = [[1,1]]
输出: 1
 

提示:

m == grid.length
n == grid[i].length
1 <= m, n <= 200
grid[i][j] == 0 or 1.
grid 中 至少 有两个朋友

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/best-meeting-point
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
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


// // TLE
// class Solution {
// public:
//     int minTotalDistance(vector<vector<int>>& grid)
//     {
//         for (int i = 0; i < grid.size(); ++i) {
//             for (int j = 0; j < grid[0].size(); ++j) {
//                 if (grid[i][j] == 1) {
//                     dict.insert({i, j});
//                 }
//             }
//         }

//         int res = INT_MAX;
//         for (int i = 0; i < grid.size(); ++i) {
//             for (int j = 0; j < grid[0].size(); ++j) {
//                 res = min(res, ComputeDis(i, j));
//             }
//         }  
//         return res;
//     }

//     int ComputeDis(int x, int y)
//     {
//         int dis = 0;
//         for (const auto& it : dict) {
//             dis += abs(x - it.first) + abs(y - it.second);
//         }
//         return dis;
//     }

// private:
//     set<pair<int, int>> dict;
// };


// class Solution {
// public:
//     int minTotalDistance(vector<vector<int>>& grid)
//     {
//         for (int i = 0; i < grid.size(); ++i) {
//             for (int j = 0; j < grid[0].size(); ++j) {
//                 if (grid[i][j] == 1) {
//                     dict.insert({i, j});
//                 }
//             }
//         }

//         int xDis = INT_MAX;
//         for (int i = 0; i < grid.size(); ++i) {
//             int dis = 0;
//             for (const auto& it : dict) {
//                 dis += abs(i - it.first);
//             }
//             xDis = min(xDis, dis);
//         }

//         int yDis = INT_MAX;
//         for (int i = 0; i < grid[0].size(); ++i) {
//             int dis = 0;
//             for (const auto& it : dict) {
//                 dis += abs(i - it.second);
//             }
//             yDis = min(yDis, dis);
//         }
//         return xDis + yDis;
//     }

// private:
//     set<pair<int, int>> dict;
// };


class Solution {
public:
int minTotalDistance(vector<vector<int>>& grid)
{
	vector<int> X, Y;
	int row = grid.size(), col = grid[0].size();
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (grid[i][j] == 1) {
				X.emplace_back(i);
				Y.emplace_back(j);
			}
		}
	}

	sort(X.begin(), X.end());
	sort(Y.begin(), Y.end());
	
	int r = 0;
    int n = X.size();
	for (int i = 0; i < n / 2; ++i) {
		r += X[n - i - 1] - X[i] + Y[n - i - 1] - Y[i];
	}
	return r;
}
};

 


