/**
 * @file 1229. 安排会议日程.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定两个人的空闲时间表：slots1 和 slots2，以及会议的预计持续时间 duration，
   请你为他们安排 时间段最早 且合适的会议时间。

    如果没有满足要求的会议时间，就请返回一个 空数组。

    「空闲时间」的格式是 [start, end]，由开始时间 start 和结束时间 end 组成，表示从 start 开始，到 end 结束。 

    题目保证数据有效：同一个人的空闲时间不会出现交叠的情况，也就是说，对于同一个人的两个空闲时间 [start1, end1] 和 [start2, end2]，要么 start1 > end2，要么 start2 > end1。

    示例 1：

    输入：slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 8
    输出：[60,68]
    示例 2：

    输入：slots1 = [[10,50],[60,120],[140,210]], slots2 = [[0,15],[60,70]], duration = 12
    输出：[]
     

    提示：

    1 <= slots1.length, slots2.length <= 104
    slots1[i].length, slots2[i].length == 2
    slots1[i][0] < slots1[i][1]
    slots2[i][0] < slots2[i][1]
    0 <= slots1[i][j], slots2[i][j] <= 109
    1 <= duration <= 106

 * 
 * @version 0.1
 * @date 2022-06-18
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
    vector<int> minAvailableDuration(vector<vector<int>>& slots1, vector<vector<int>>& slots2, int duration) {
        sort(begin(slots1), end(slots1));
        sort(begin(slots2), end(slots2));

        int idx1 = 0, idx2 = 0;
        while (idx1 < slots1.size() && idx2 < slots2.size()) {
            int start = max(slots1[idx1][0], slots2[idx2][0]);
            int end1 = slots1[idx1][1];
            int end2 = slots2[idx2][1];
            int end  = min(end1, end2);
            // std::cout << start << " " << end1 << " " << end2 << std::endl;
            if (duration <= end - start) {
                return {start, start + duration};
            }
            if (end1 <= end2) {
                ++idx1;
            }
            if (end2 <= end1) {
                ++idx2;
            }
        }

        return {};
    }
};



