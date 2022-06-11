/**
 * @file 487. 最大连续1的个数 II.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个二进制数组 nums ，如果最多可以翻转一个 0 ，则返回数组中连续 1 的最大个数。

    示例 1：

    输入：nums = [1,0,1,1,0]
    输出：4
    解释：翻转第一个 0 可以得到最长的连续 1。
         当翻转以后，最大连续 1 的个数为 4。
    示例 2:

    输入：nums = [1,0,1,1,0,1]
    输出：4
     

    提示:

    1 <= nums.length <= 105
    nums[i] 不是 0 就是 1.
     

    进阶：如果输入的数字是作为 无限流 逐个输入如何处理？换句话说，内存不能存储下所有从流中输入的数字。您可以有效地解决吗？

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/max-consecutive-ones-ii
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * @version 0.1
 * @date 2022-06-11
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
//     int findMaxConsecutiveOnes(vector<int>& nums) {
//         int res = 0;
//         vector<vector<int>> dp(nums.size() + 1, vector<int>(2, 0));
//         for (int i = 0; i < nums.size(); ++i) {
//             if (nums[i] == 1) {
//                 dp[i + 1][0] = dp[i][0] + 1; //dp[i][0] 没有使用反转一次的机会
//                 dp[i + 1][1] = dp[i][1] + 1;
//             } else {
//                 dp[i + 1][0] = 0;
//                 dp[i + 1][1] = dp[i][0] + 1;
//             }
//             res = max({res, dp[i + 1][0], dp[i + 1][1]});
//         }
//         return res;
//     }
// };


// class Solution {
// public:
//     int findMaxConsecutiveOnes(vector<int>& nums) {
//         int res = 0;
//         int dp0 = 0, dp1 = 0;
//         for (int i = 0; i < nums.size(); ++i) {
//             if (nums[i] == 1) {
//                 ++dp0;
//                 ++dp1;
//             } else {
//                 dp1 = dp0 + 1;
//                 dp0 = 0;
//             }
//             res = max({res, dp0, dp1});
//         }
//         return res;
//     }
// };




class Solution {
public:
    int findMaxConsecutiveOnes(vector<int>& nums) {
        int res = 0;
        int last_zero = -1;
        int start = -1;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == 0) {
                start = last_zero; //精妙之处，start和last_zero之前构成一个指向0的错位
                last_zero = i;
            }
            res = max(res, i - start);
        }
        return res;
    }
};


