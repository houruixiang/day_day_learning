/**
 * @file 266. 回文排列.cpp
 * @author ruihou
 * @brief 
 * 266. 回文排列
        给定一个字符串，判断该字符串中是否可以通过重新排列组合，形成一个回文字符串。

        示例 1：
            输入: "code"
            输出: false

        示例 2：
            输入: "aab"
            输出: true

        示例 3：
            输入: "carerac"
            输出: true
 * 
 * @version 0.1
 * @date 2022-05-28
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
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canPermutePalindrome(string s) {
        map<char, int> dict;
        for (const auto& ch : s) {
            ++dict[ch];
        }

        int odds = 0;
        for (const auto& it : dict) {
            if (it.second % 2) {
                ++odds;
            }
        }
        return odds == 0 || odds == 1;
    }
};