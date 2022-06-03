/**
 * @file 340. 至多包含 K 个不同字符的最长子串.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个字符串 s ，找出 至多 包含 k 个不同字符的最长子串 T。

 

示例 1:

输入: s = "eceba", k = 2
输出: 3
解释: 则 T 为 "ece"，所以长度为 3。
示例 2:

输入: s = "aa", k = 1
输出: 2
解释: 则 T 为 "aa"，所以长度为 2。
 

提示：

1 <= s.length <= 5 * 104
0 <= k <= 50

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


// // 哈希表 + 滑动窗口
// class Solution {
// public:
//     int lengthOfLongestSubstringKDistinct(string s, int k)
//     {
//         if (s.size() == 0 || k == 0) {
//             return 0;
//         }
    
//         map<char, int> dict;
//         int l = 0, r = 0;
//         int ans = 1;
//         while (r < s.size()) {
//             dict[s[r]] = r;
//             if (dict.size() == k + 1) {
//                 auto idx = GetMinElem(dict); //o(size(dict))
//                 l = idx + 1;
//             }
//             ans = max(ans, ++r - l);
//         }
//         return ans;
//     }

//     int GetMinElem(map<char, int>& dict)
//     {
//         auto it = dict.begin();
//         auto iter = dict.begin();
//         while (it != dict.end()) {
//             if (it->second < iter->second) {
//                 iter = it;
//             }
//             ++it;
//         }
//         int idx = iter->second;
//         dict.erase(iter);
//         return idx;
//     }
// };


// 哈希表 + 双指针
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k)
    {
        if (s.size() == 0 || k == 0) {
            return 0;
        }
        map<char, int> dict;
        int ans = 0;
        for (int l = 0, r = 0; r < s.size(); ++r) {
            ++dict[s[r]];
            while(dict.size() > k) {
                if (--dict[s[l]] == 0) {
                    dict.erase(s[l]);
                }
                ++l;
            }
            ans = max(ans, r - l + 1);
        }
        return ans;
    }
};