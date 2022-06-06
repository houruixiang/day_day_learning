/**
 * @file 395. 至少有 K 个重复字符的最长子串.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个字符串 s 和一个整数 k ，请你找出 s 中的最长子串， 要求该子串中的每一字符出现次数都不少于 k 。返回这一子串的长度。S
 S
        示例 1：

        输入：s = "aaabb", k = 3
        输出：3
        解释：最长子串为 "aaa" ，其中 'a' 重复了 3 次。
        示例 2：

        输入：s = "ababbc", k = 2
        输出：5
        解释：最长子串为 "ababb" ，其中 'a' 重复了 2 次， 'b' 重复了 3 次。
         

        提示：

        1 <= s.length <= 104
        s 仅由小写英文字母组成
        1 <= k <= 105

 * 
 * @version 0.1
 * @date 2022-06-06
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
    int longestSubstring(string s, int k) {
        if (s.size() < k) {
            return 0;
        }
        unordered_map<char, int> dict; //统计出现次数
        for (auto& ch : s) {
            ++dict[ch];
        }

        for (const auto& it : dict) {
            vector<string> strs;
            if (it.second < k) {
                splite(s, strs, it.first); //it.first字符分割得到所有字符串
                int res = 0;
                for (auto& str : strs) {
                    res = max(res, longestSubstring(str, k)); //递归
                }
                return res;
            }
            strs.clear();
        }

        return s.size();
    }

    void splite(const string& s, vector<string>& strs, const char delimter = ' ')
    {
        istringstream ss(s);
        string tmp;
    
        while (getline(ss, tmp, delimter)) {
            strs.push_back(tmp);
        }
    }
};

