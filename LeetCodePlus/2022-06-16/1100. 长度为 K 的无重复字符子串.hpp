/**
 * @file 1100. 长度为 K 的无重复字符子串.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给你一个字符串 S，找出所有长度为 K 且不含重复字符的子串，请你返回全部满足要求的子串的 数目。

        示例 1：

        输入：S = "havefunonleetcode", K = 5
        输出：6
        解释：
        这里有 6 个满足题意的子串，分别是：'havef','avefu','vefun','efuno','etcod','tcode'。
        示例 2：

        输入：S = "home", K = 5
        输出：0
        解释：
        注意：K 可能会大于 S 的长度。在这种情况下，就无法找到任何长度为 K 的子串。
         

        提示：

        1 <= S.length <= 10^4
        S 中的所有字符均为小写英文字母
        1 <= K <= 10^4

        来源：力扣（LeetCode）
        链接：https://leetcode.cn/problems/find-k-length-substrings-with-no-repeated-characters
        著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * 
 * @version 0.1
 * @date 2022-06-16
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
    int numKLenSubstrNoRepeats(string s, int k) {
        int res = 0;
        unordered_map<char, int> dict;
        int l = -1;
        for (int r = 0; r <= s.size(); ++r) {
            if (r == s.size() || dict.find(s[r]) != dict.end()) {
                if (k <= r - l) {
                    res += (r - l - k);
                }
                //非常关键条件判断，l表示不后退，r - k表示超过k个距离视为无效，dict[s[r]]表示重复字符的位置
                l = max({l, r - k, dict[s[r]]}); 
            }
            dict[s[r]] = r;
        }
        return res;

    }
};


