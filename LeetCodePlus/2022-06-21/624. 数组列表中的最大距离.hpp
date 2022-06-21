/**
 * @file 624. 数组列表中的最大距离.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定 m 个数组，每个数组都已经按照升序排好序了。现在你需要从两个不同的数组中选择两个整数（每个数组选一个）并且计算它们的距离。两个整数 a 和 b 之间的距离定义为它们差的绝对值 |a-b| 。你的任务就是去找到最大距离

    示例 1：

    输入： 
    [[1,2,3],
    [4,5],
    [1,2,3]]
    输出： 4
    解释：
    一种得到答案 4 的方法是从第一个数组或者第三个数组中选择 1，同时从第二个数组中选择 5 。
     

    注意：

    每个给定数组至少会有 1 个数字。列表中至少有两个非空数组。
    所有 m 个数组中的数字总数目在范围 [2, 10000] 内。
    m 个数组中所有整数的范围在 [-10000, 10000] 内。

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/maximum-distance-in-arrays
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * 
 * 
 * @version 0.1
 * @date 2022-06-21
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
    int maxDistance(vector<vector<int>>& arrays) {
        int res = 0;
        int prevMin = arrays[0][0];
        int prevMax = arrays[0].back();

        for (int i = 1; i < arrays.size(); ++i) {
            int x = abs(prevMax - arrays[i][0]);
            int y = abs(prevMin - arrays[i].back());
            res = max({res, x, y});
            prevMin = min(prevMin, arrays[i][0]);
            prevMax = max(prevMax, arrays[i].back());
        }

        return res;
    }
};

