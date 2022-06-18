/**
 * @file 1271. 十六进制魔术数字.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 你有一个十进制数字，请按照此规则将它变成「十六进制魔术数字」：首先将它变成字母大写的十六进制字符串，然后将所有的数字 0 变成字母 O ，将数字 1  变成字母 I 。

    如果一个数字在转换后只包含 {"A", "B", "C", "D", "E", "F", "I", "O"} ，那么我们就认为这个转换是有效的。

    给你一个字符串 num ，它表示一个十进制数 N，如果它的十六进制魔术数字转换是有效的，请返回转换后的结果，否则返回 "ERROR" 。

     

    示例 1：

    输入：num = "257"
    输出："IOI"
    解释：257 的十六进制表示是 101 。
    示例 2：

    输入：num = "3"
    输出："ERROR"
     

    提示：

    1 <= N <= 10^12
    给定字符串不会有前导 0 。
    结果中的所有字母都应该是大写字母。

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/hexspeak
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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
    string toHexspeak(string num) {
        stringstream ss;
        ss << hex << stol(num); //core
        string num_hex = ss.str();
        unordered_map<char, char> transform = {
            {'0', 'O'},
            {'1', 'I'},
            {'a', 'A'},
            {'b', 'B'},
            {'c', 'C'},
            {'d', 'D'},
            {'e', 'E'},
            {'f', 'F'},
        };

        string ans;
        for (char ch: num_hex) {
            if (!transform.count(ch)) {
                return "ERROR";
            }
            ans += transform[ch];
        }
        return ans;
    }
};




