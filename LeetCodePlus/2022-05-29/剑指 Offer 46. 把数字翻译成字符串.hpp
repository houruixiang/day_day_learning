/**
 * @file 剑指 Offer 46. 把数字翻译成字符串.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 剑指 Offer 46. 把数字翻译成字符串
        给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。
        一个数字可能有多个翻译。
        请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。

        示例 1:
            输入: 12258
            输出: 5
            解释: 12258有5种不同的翻译，分别是"bccfi", "bwfi", "bczi", "mcfi"和"mzi"

 * @version 0.1
 * @date 2022-05-29
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

class Solution {
public:
    int translateNum(int num) {
        std::string str = std::to_string(num);

        const int n = str.size();
        std::vector<int> dp(n + 1, 0);
        dp[0] = 1;

        for (int i = 1; i <= str.size(); ++i) {
            dp[i] += dp[i - 1];
            if (i >= 2) {
                int num = (str[i - 2] - '0') * 10 + (str[i - 1] - '0');
                if (10 <= num && num <= 25) {
                    dp[i] += dp[i - 2];
                } 
            }
        }
        return dp.back();
    }
};

