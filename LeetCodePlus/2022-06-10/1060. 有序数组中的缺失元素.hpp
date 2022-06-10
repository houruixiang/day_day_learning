/**
 * @file 1060. 有序数组中的缺失元素.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 现有一个按 升序 排列的整数数组 nums ，其中每个数字都 互不相同 。

给你一个整数 k ，请你找出并返回从数组最左边开始的第 k 个缺失数字。

 

示例 1：

输入：nums = [4,7,9,10], k = 1
输出：5
解释：第一个缺失数字为 5 。
示例 2：

输入：nums = [4,7,9,10], k = 3
输出：8
解释：缺失数字有 [5,6,8,...]，因此第三个缺失数字为 8 。
示例 3：

输入：nums = [1,2,4], k = 3
输出：6
解释：缺失数字有 [3,5,6,7,...]，因此第三个缺失数字为 6 



 * @version 0.1
 * @date 2022-06-10
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


// class Solution {
// public:
//     int missingElement(vector<int>& nums, int k) {
//         for(int i = 1; i < nums.size(); ++i) {
//             int diff = nums[i] - nums[i - 1] - 1;
//             if (diff < k) {
//                 k -= diff;
//             } else {
//                 return nums[i - 1] + k;
//             }
//         }
//         return nums.back() + k;
//     }
// };




class Solution {
    /**
     * 二分查找。
     * 题目并不复杂，线性解法的思路也很容易想到，不过看到数组有序
     * 我们应该尝试比线性更优的算法。
     * 时间复杂度O(logN)
     * 空间复杂度O(1)
     */
public:
    int missingElement(vector<int>& nums, int k) {
        int l = 0, r = nums.size() - 1;
        if (nums[r] - nums[l] - r < k) {
            // 第k个数超过的数组范围
            return nums[l] + k + r;
        }
            
        while (l + 1 < r) { // 注意这里的条件，l总是在r的左边，因为要表示一个范围
            int mid = l + (r - l) / 2;
            int slot = nums[mid] - nums[l] - mid + l;// slot表示l~mid内的空槽
            if (slot < k) { // 空槽数不够k个那么肯定在mid~r内
                l = mid;
                k -= slot;
            } else { // 空槽数够k个那么肯定在l~mid内
                r = mid;
            }
        }
        return nums[l] + k;
    }
};