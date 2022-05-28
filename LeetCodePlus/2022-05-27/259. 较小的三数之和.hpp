/**
 * @file 259. 较小的三数之和.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 *259. 较小的三数之和
    给定一个长度为 n 的整数数组和一个目标值 target ，
    寻找能够使条件 nums[i] + nums[j] + nums[k] < target 成立的三元组  i, j, k 个数（0 <= i < j < k < n）。

    示例 1：
        输入: nums = [-2,0,1,3], target = 2
        输出: 2 
        解释: 因为一共有两个三元组满足累加和小于 2:
            [-2,0,1]
            [-2,0,3]
   
    示例 2：
        输入: nums = [], target = 0
        输出: 0 
        示例 3：

        输入: nums = [0], target = 0
        输出: 0 
        

    提示:
        n == nums.length
        0 <= n <= 3500
        -100 <= nums[i] <= 100
        -100 <= target <= 100
 * 
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
    int threeSumSmaller(vector<int>& nums, int target) {
        sort(begin(nums), end(nums));

        int res = 0;
        for (int i = 0; i < nums.size(); ++i) {
            int l = i + 1;
            int r = nums.size() - 1;
            while (l < r) {
                if (nums[i] + nums[l] + nums[r] < target) {
                    res += r - l;
                    ++l;
                } else {
                    --r;
                }
            }
        }
        return res;
    }
};