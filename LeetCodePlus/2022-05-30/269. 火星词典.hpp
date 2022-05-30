/**
 * @file 269. 火星词典.hpp
 * 
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 269. 火星词典
        现有一种使用英语字母的火星语言，这门语言的字母顺序与英语顺序不同。

        给你一个字符串列表 words ，作为这门语言的词典，words 中的字符串已经 按这门新语言的字母顺序进行了排序 。

        请你根据该词典还原出此语言中已知的字母顺序，并 按字母递增顺序 排列。若不存在合法字母顺序，返回 "" 。若存在多种可能的合法字母顺序，返回其中 任意一种 顺序即可。

        字符串 s 字典顺序小于 字符串 t 有两种情况：

        在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t 中字母之前，那么 s 的字典顺序小于 t 。
        如果前面 min(s.length, t.length) 字母都相同，那么 s.length < t.length 时，s 的字典顺序也小于 t 。
        

        示例 1：

        输入：words = ["wrt","wrf","er","ett","rftt"]
        输出："wertf"
        示例 2：

        输入：words = ["z","x"]
        输出："zx"
        示例 3：

        输入：words = ["z","x","z"]
        输出：""
        解释：不存在合法字母顺序，因此返回 "" 。
        

        提示：

        1 <= words.length <= 100
        1 <= words[i].length <= 100
        words[i] 仅由小写英文字母组成
 * 
 * @version 0.1
 * @date 2022-05-30
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
    string alienOrder(vector<string>& words) {
        unordered_map<char, int> indegree;
        unordered_map<char, vector<int>> edge;
        for (const auto& word : words) {
            for (const auto& ch : word) {
                indegree[ch] = 0;
            }
        }

        for (int i = 0; i < words.size() - 1; ++i) {
            auto& curr = words[i];
            auto& next = words[i + 1];
            // ["abc", "ab"]
            if ((next.size() < curr.size()) && (curr.substr(0, next.size()) == next)) {
                return "";
            }
            int lens = min(curr.size(), next.size());
            for (int k = 0; k < lens; ++k) {
                if (curr[k] != next[k]) {
                    ++indegree[next[k]];
                    edge[curr[k]].push_back(next[k]);
                    break;
                }
            }
        }
    
        string ans;
        for (int i = 0; i < indegree.size(); ++i) {
            char ch = ' ';
            for (const auto& in : indegree) {
                if (in.second == 0) {
                    ch = in.first;
                    break;
                }
            }
            if (ch == ' ') {
                return "";
            }
            ans += ch;
            --indegree[ch];
            for (const auto& e : edge[ch]) {
                --indegree[e];
            }
        }

        return ans;
    }
};

