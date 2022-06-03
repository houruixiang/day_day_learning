/**
 * @file 311. 稀疏矩阵的乘法.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定两个 稀疏矩阵 ：大小为 m x k 的稀疏矩阵 mat1 和大小为 k x n 的稀疏矩阵 mat2 ，返回 mat1 x mat2 的结果。你可以假设乘法总是可能的。

 

示例 1：



输入：mat1 = [[1,0,0],[-1,0,3]], mat2 = [[7,0,0],[0,0,0],[0,0,1]]
输出：[[7,0,0],[-7,0,3]]
 示例 2:

输入：mat1 = [[0]], mat2 = [[0]]
输出：[[0]]
 

提示:

m == mat1.length
k == mat1[i].length == mat2.length
n == mat2[i].length
1 <= m, n, k <= 100
-100 <= mat1[i][j], mat2[i][j] <= 100

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/sparse-matrix-multiplication
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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

class Solution {
public:
    vector<vector<int>> multiply(vector<vector<int>>& mat1, vector<vector<int>>& mat2) {
        const int m = mat1.size();
        const int n = mat2[0].size();
        auto v1 = GetParseVec(mat1);
        auto v2 = GetParseVec(mat2);
    
        vector<vector<int>> res(m, vector<int>(n, 0));
        for (const auto& x : v1) {
            for (const auto& y : v2) {
                if (x[1] == y[0]) {
                    res[x[0]][y[1]] += x[2] * y[2];
                }
            }
        }
        return res;
    }

    vector<vector<int>> GetParseVec(vector<vector<int>>& mat)
    {
        vector<vector<int>> res;
        for (int i = 0; i < mat.size(); ++i) {
            for (int j = 0; j < mat[0].size(); ++j) {
                if (mat[i][j] != 0) {
                    res.push_back({i, j, mat[i][j]});
                }
            }
        }
        return res;
    }
};