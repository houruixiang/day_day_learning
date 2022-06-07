/**
 * @file 1099. 小于 K 的两数之和.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个整数数组 nums 和整数 k ，返回最大和 sum ，满足存在 i < j 使得 nums[i] + nums[j] = sum 且 sum < k 。如果没有满足此等式的 i,j 存在，则返回 -1 。

        示例 1：

        输入：nums = [34,23,1,24,75,33,54,8], k = 60
        输出：58
        解释：
        34 和 24 相加得到 58，58 小于 60，满足题意。
        示例 2：

        输入：nums = [10,20,30], k = 15
        输出：-1
        解释：
        我们无法找到和小于 15 的两个元素。
         

        提示：

        1 <= nums.length <= 100
        1 <= nums[i] <= 1000
        1 <= k <= 2000

 * 
 * @version 0.1
 * @date 2022-06-07
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
    int twoSumLessThanK(vector<int>& nums, int k) {
        if (nums.size() < 2) {
            return -1;
        }

        int res = INT_MIN;
        sort(begin(nums), end(nums));
        int i = 0, j = nums.size() - 1;
        while (i < j) {
            int sum = nums[i] + nums[j];
            if (sum < k) {
                ++i;
                res = max(res, sum);
            } else {
                --j;
            }
        }
        return (res != INT_MIN) ? res : -1;
    }
};


