/**
 * @file 360. 有序转化数组.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个已经 排好序 的整数数组 nums 和整数 a 、 b 、 c 。对于数组中的每一个元素 nums[i] ，计算函数值 f(x) = ax2 + bx + c ，请 按升序返回数组 。
S
        示例 1：

        输入: nums = [-4,-2,2,4], a = 1, b = 3, c = 5
        输出: [3,9,15,33]
        示例 2：

        输入: nums = [-4,-2,2,4], a = -1, b = 3, c = 5
        输出: [-23,-5,1,7]
         

        提示：

        1 <= nums.length <= 200
        -100 <= nums[i], a, b, c <= 100
        nums 按照 升序排列
 
 
 * 
 * @version 0.1
 * @date 2022-06-06
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
    vector<int> sortTransformedArray(vector<int>& nums, int a, int b, int c) {
        if (nums.empty()) {
            return {};
        }

        int N = nums.size();
        vector<int> res(N, 0);
        auto fx = [&](const auto& x) {
            return a * x * x + b * x + c;
        };

        int i = 0;
        int j = N - 1;
        int index = (a >= 0) ? N - 1 : 0; // a > 0, backward, a < 0, forward
        while (i <= j) {
            if (a >= 0) { //向上的抛物线,合并a=0为直线，单调增减情况到a>0（合并到a < 0也行）
                res[index--] = fx(nums[i]) >= fx(nums[j]) ? fx(nums[i++]) : fx(nums[j--]);
            } else { // (a < 0)
                res[index++] = fx(nums[i]) > fx(nums[j]) ? fx(nums[j--]) : fx(nums[i++]);
            }
        }

        return res;
    }
};


