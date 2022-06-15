/**
 * @file 1063. 有效子数组的数目.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个整数数组 nums ，返回满足下面条件的 非空、连续 子数组的数目：

        子数组 是数组的 连续 部分。
        子数组最左边的元素不大于子数组中的其他元素 。
         

        示例 1：

        输入：nums = [1,4,2,5,3]
        输出：11
        解释：有 11 个有效子数组，分别是：[1],[4],[2],[5],[3],[1,4],[2,5],[1,4,2],[2,5,3],[1,4,2,5],[1,4,2,5,3] 。
        示例 2：

        输入：nums = [3,2,1]
        输出：3
        解释：有 3 个有效子数组，分别是：[3],[2],[1] 。
        示例 3：

        输入：nums = [2,2,2]
        输出：6
        解释：有 6 个有效子数组，分别为是：[2],[2],[2],[2,2],[2,2],[2,2,2] 。
         

        提示：

        1 <= nums.length <= 5 * 104
        0 <= nums[i] <= 105

        来源：力扣（LeetCode）
        链接：https://leetcode.cn/problems/number-of-valid-subarrays
        著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * 
 * @version 0.1
 * @date 2022-06-15
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
    int validSubarrays(vector<int>& nums) {
        int res = 0;
        int n = nums.size();
        stack<int> sk;
        for (int i = n - 1; i >= 0; --i) {
            while (!sk.empty() && nums[i] <= nums[sk.top()]) {
                sk.pop(); // 找到<= nums[i]的第一个元素
            }
            if (sk.empty()) {
                res += n - i;
            } else {
                res += sk.top() - i;
            }
            sk.push(i);
        }
        return res;
    }
};