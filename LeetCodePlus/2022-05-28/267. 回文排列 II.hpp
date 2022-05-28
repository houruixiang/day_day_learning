/**
 * @file 267. 回文排列 II.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 267. 回文排列 II
        给定一个字符串 s ，返回 其重新排列组合后可能构成的所有回文字符串，并去除重复的组合 。
        你可以按 任意顺序 返回答案。如果 s 不能形成任何回文排列时，则返回一个空列表。

        示例 1：
        输入: s = "aabb"
        输出: ["abba", "baab"]

        示例 2：
        输入: s = "abc"
        输出: []
        
        提示：
        1 <= s.length <= 16
        s 仅由小写英文字母组成
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
    vector<string> generatePalindromes(string s) {
        int odds = 0;
        char odds_ch = ' ';
        for (const auto& ch : s) {
            ++dict[ch];
        }
        for (const auto& it : dict) {
            if (it.second % 2) {
                ++odds;
                odds_ch = it.first;
            }
        }
        if (odds > 1) {
            return {};
        }

        vector<string> res;
        string ans;
        if (odds == 1) {
            ans += odds_ch;
            --dict[odds_ch];
        }
        solver(res, ans, s.size());
        return res;
    }

    void solver(vector<string>& res, string &ans, int lens)
    {
        if (ans.size() == lens) {
            res.push_back(ans);
            return;
        }
        for (auto &[k, v] : dict) {
            if (v > 0) {
                ans = k + ans + k;
                dict[k] -= 2;

                solver(res, ans, lens);

                ans = ans.substr(1, ans.size() - 2);
                dict[k] += 2;
            }
        }
    }

private:
    map<char, int> dict;
};