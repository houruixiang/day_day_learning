/**
 * @file 1228. 等差数列中缺失的数字.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 
 * 在某个数组 arr 中，值符合等差数列的数值规律：在 0 <= i < arr.length - 1 的前提下，arr[i+1] - arr[i] 的值都相等。

我们会从该数组中删除一个 既不是第一个 也 不是最后一个的值，得到一个新的数组  arr。

给你这个缺值的数组 arr，返回 被删除的那个数 。

 

示例 1：

输入：arr = [5,7,11,13]
输出：9
解释：原来的数组是 [5,7,9,11,13]。
示例 2：

输入：arr = [15,13,12]
输出：14
解释：原来的数组是 [15,14,13,12]。
 

提示：

3 <= arr.length <= 1000
0 <= arr[i] <= 105
给定的数组 保证 是一个有效的数组。

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/missing-number-in-arithmetic-progression
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * @version 0.1
 * @date 2022-06-28
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
    int missingNumber(vector<int>& arr) {
        int sum = accumulate(arr.begin(), arr.end(), 0);
        return (arr[0] + arr.back()) * (arr.size() + 1) / 2 - sum;
    }
};

