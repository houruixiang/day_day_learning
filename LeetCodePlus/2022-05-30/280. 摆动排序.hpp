/**
 * @file 280. 摆动排序.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 280. 摆动排序
        给你一个的整数数组 nums, 将该数组重新排序后使 nums[0] <= nums[1] >= nums[2] <= nums[3]... 

        输入数组总是有一个有效的答案。

        示例 1:

        输入：nums = [3,5,2,1,6,4]
        输出：[3,5,1,6,2,4]
        解释：[1,6,2,5,3,4]也是有效的答案
        示例 2:

        输入：nums = [6,6,5,6,3,8]
        输出：[6,6,5,6,3,8]
        

        提示：

        1 <= nums.length <= 5 * 104
        0 <= nums[i] <= 104
        输入的 nums 保证至少有一个答案。

        进阶：你能在 O(n) 时间复杂度下解决这个问题吗？
 * 
 * @version 0.1
 * @date 2022-05-30
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

// class Solution {
// public:
//     void wiggleSort(vector<int>& nums) {
//         sort(begin(nums), end(nums));
//         for (int i = 1; i < nums.size() - 1; i += 2) {
//             swap(nums[i], nums[i + 1]);
//         }
//     }
// };


class Solution {
public:
    void wiggleSort(vector<int>& nums) {
        bool less = true;
        for (int i = 0; i < nums.size() - 1; ++i) {
            if (less) {
                if (nums[i + 1] < nums[i]) {
                    swap(nums[i + 1], nums[i]);
                }
            } else {
                if (nums[i] < nums[i + 1]) {
                    swap(nums[i + 1], nums[i]);
                }
            }
            less = !less;
        }
    }
};