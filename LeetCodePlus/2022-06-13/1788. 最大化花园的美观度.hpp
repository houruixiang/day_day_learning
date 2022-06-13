/**
 * @file 1788. 最大化花园的美观度.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 有一个花园，有 n 朵花，这些花都有一个用整数表示的美观度。这些花被种在一条线上。
 * 给定一个长度为 n 的整数类型数组 flowers ，每一个 flowers[i] 表示第 i 朵花的美观度。

        一个花园满足下列条件时，该花园是有效的。

        花园中至少包含两朵花。
        第一朵花和最后一朵花的美观度相同。
        作为一个被钦定的园丁，你可以从花园中去除任意朵花（也可以不去除任意一朵）。你想要通过一种方法移除某些花朵，使得剩下的花园变得有效。花园的美观度是其中所有剩余的花朵美观度之和。

        返回你去除了任意朵花（也可以不去除任意一朵）之后形成的有效花园中最大可能的美观度。

         

        示例 1：

        输入: flowers = [1,2,3,1,2]
        输出: 8
        解释: 你可以修整为有效花园 [2,3,1,2] 来达到总美观度 2 + 3 + 1 + 2 = 8。
        示例 2：

        输入: flowers = [100,1,1,-3,1]
        输出: 3
        解释: 你可以修整为有效花园 [1,1,1] 来达到总美观度 1 + 1 + 1 = 3。
        示例 3：

        输入: flowers = [-1,-2,0,-1]
        输出: -2
        解释: 你可以修整为有效花园 [-1,-1] 来达到总美观度 -1 + -1 = -2。
         

        提示：

        2 <= flowers.length <= 105
        -104 <= flowers[i] <= 104
        去除一些花朵（可能没有）后，是有可能形成一个有效花园的。

 * 
 * @version 0.1
 * @date 2022-06-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#pragma once

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
    int maximumBeauty(vector<int>& flowers) {
        int res = INT_MIN;
        int preSum = 0;
        map<int, int> dict;
        for (const auto& flower : flowers) {
            if (flower > 0) {
                preSum += flower; //忽略 < 0的flower
            }
            if (dict.find(flower) == dict.end()) {
                dict[flower] = preSum; // 仅仅保存第一次出现时的
            } else {
                int value= flower > 0 ? flower : flower * 2; //加上多减去的
                res = max(res, preSum - dict[flower] + value);
            }
        }
        return res;
    }
};



