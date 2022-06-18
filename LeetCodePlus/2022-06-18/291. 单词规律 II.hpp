/**
 * @file 291. 单词规律 II.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一种规律 pattern 和一个字符串 s，请你判断 s 是否和 pattern 的规律相匹配。

    如果存在单个字符到字符串的 双射映射 ，那么字符串 s 匹配 pattern ，
    即：如果pattern 中的每个字符都被它映射到的字符串替换，那么最终的字符串则为 s 。
    双射 意味着映射双方一一对应，不会存在两个字符映射到同一个字符串，
    也不会存在一个字符分别映射到两个不同的字符串。

    示例 1：

    输入：pattern = "abab", s = "redblueredblue"
    输出：true
    解释：一种可能的映射如下：
    'a' -> "red"
    'b' -> "blue"
    示例 2：

    输入：pattern = "aaaa", s = "asdasdasdasd"
    输出：true
    解释：一种可能的映射如下：
    'a' -> "asd"
    示例 3：

    输入：pattern = "aabb", s = "xyzabcxzyabc"
    输出：false
     

    提示：

    1 <= pattern.length, s.length <= 20
    pattern 和 s 由小写英文字母组成

 * 
 * @version 0.1
 * @date 2022-06-18
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
    bool wordPatternMatch(string pattern, string s) {
        return dfs(pattern, s, 0, 0);
    }

    bool dfs(const string& p, const string& s, int pStart, int sStart)
    {
        if (p.size() <= pStart) {
            return s.size() <= sStart; //越界
        }
        if (s.size() <= sStart) {
            return p.size() <= pStart; //越界
        }

        auto it = p2s.find(p[pStart]); //寻找pattern当前字符对应的字符串
        if (it != p2s.end()) {
            auto word = it->second;
            if (s.size() < sStart + word.size()) {
                return false; //越界
            }
            if (word != s.substr(sStart, word.size())) {
                return false; //不等
            }
            return dfs(p, s, pStart + 1, sStart + word.size()); //继续递归
        }

        //没有记录过,则尝试s的所有可能
        for (int i = 1; i + sStart <= s.size(); ++i) {
            auto word = s.substr(sStart, i); // 当前字符串
            if (s2p.find(word) != s2p.end()) {
                continue; //之前有记录则跳出
            }
            p2s[p[pStart]] = word; //记录
            s2p[word] = p[pStart];
            auto match = dfs(p, s, pStart + 1, sStart + i);
            if (match) { //满足跳出
                return true;
            }
            p2s.erase(p[pStart]); //不满足擦除记录
            s2p.erase(word);
        }
        return false;
    }

private:
    map<char, string> p2s;
    map<string, char> s2p;
};


