/**
 * @file 531. 孤独像素 I.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个大小为 m x n 的图像 picture ，图像由黑白像素组成，'B' 表示黑色像素，'W' 表示白色像素，请你统计并返回图像中 黑色 孤独像素的数量。

    黑色孤独像素 的定义为：如果黑色像素 'B' 所在的同一行和同一列不存在其他黑色像素，那么这个黑色像素就是黑色孤独像素。

    示例 1：
    输入：picture = [["W","W","B"],["W","B","W"],["B","W","W"]]
    输出：3
    解释：全部三个 'B' 都是黑色的孤独像素
    示例 2：
    输入：picture = [["B","B","B"],["B","B","W"],["B","B","B"]]
    输出：0
     
    提示：
    m == picture.length
    n == picture[i].length
    1 <= m, n <= 500
    picture[i][j] 为 'W' 或 'B'
 * 
 * 
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
    int findLonelyPixel(vector<vector<char>>& picture) {
        int m = picture.size();
        int n = picture[0].size();
        vector<int> rows(m, 0);
        vector<int> cols(n, 0);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (picture[i][j] == 'B') {
                    ++rows[i];
                    ++cols[j];
                }
            } 
        }

        int res = 0;
        for (int i = 0; i < m; ++i) {
            if (rows[i] != 1) {
                continue;
            }  
            for (int j = 0; j < n; ++j) {
                if (picture[i][j] == 'B') {
                    res += cols[j] == 1;
                }
            }
        }
        return res;
    }
};


