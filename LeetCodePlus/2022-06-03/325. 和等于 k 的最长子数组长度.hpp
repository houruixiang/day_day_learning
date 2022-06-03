/**
 * @file 325. 和等于 k 的最长子数组长度.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个数组 nums 和一个目标值 k，找到和等于 k 的最长连续子数组长度。如果不存在任意一个符合要求的子数组，则返回 0。

 

示例 1:

输入: nums = [1,-1,5,-2,3], k = 3
输出: 4 
解释: 子数组 [1, -1, 5, -2] 和等于 3，且长度最长。
示例 2:

输入: nums = [-2,-1,2,1], k = 1
输出: 2 
解释: 子数组 [-1, 2] 和等于 1，且长度最长。
 

提示：

1 <= nums.length <= 2 * 105
-104 <= nums[i] <= 104
-109 <= k <= 109

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/maximum-size-subarray-sum-equals-k
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
    int maxSubArrayLen(vector<int>& nums, int k) {
        long long sum = 0;
        int ans = 0;
        map<long long, int> dict;
        dict[0] = -1;
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            auto it = dict.find(sum - k);
            if (it != dict.end()) {
                ans = max(ans, i - it->second);
            } 
            dict.insert({sum, i});
            // if (dict.find(sum) == dict.end()) {
            //     dict[sum] = i; //保证最长，无需更新
            // }
        }
        return ans;
    }
};