/**
 * @file 76. 最小覆盖子串.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

     

    注意：

    对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
    如果 s 中存在这样的子串，我们保证它是唯一的答案。
     

    示例 1：

    输入：s = "ADOBECODEBANC", t = "ABC"
    输出："BANC"
    示例 2：

    输入：s = "a", t = "a"
    输出："a"
    示例 3:

    输入: s = "a", t = "aa"
    输出: ""
    解释: t 中两个字符 'a' 均应包含在 s 的子串中，
    因此没有符合条件的子字符串，返回空字符串。
     

    提示：

    1 <= s.length, t.length <= 105
    s 和 t 由英文字母组成
     

    进阶：你能设计一个在 o(n) 时间内解决此问题的算法吗？

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/minimum-window-substring
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 
 * 
 * @version 0.1
 * @date 2022-06-24
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
    string minWindow(string s, string t) {
        map<char, int> dict;
        for (const auto& ch : t) {
            ++dict[ch];
        }

        int start = 0, lens = INT_MAX;
        int left = 0, num = t.size();
        for (int i = 0; i < s.size(); ++i) {
            if (dict[s[i]]-- > 0) {
                --num;
            }

            while (num == 0) {
                if (i - left + 1 < lens) {
                    start = left;
                    lens = i - left + 1;
                }

                if (dict[s[left++]]++ == 0) {
                    ++num;
                }
            }
        }
        return lens == INT_MAX ? "" : s.substr(start, lens);
    }
};

