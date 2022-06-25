/**
 * @file 465. 最优账单平衡.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 一群朋友在度假期间会相互借钱。比如说，小爱同学支付了小新同学的午餐共计 10 美元。如果小明同学支付了小爱同学的出租车钱共计 5 美元。我们可以用一个三元组 (x, y, z) 表示一次交易，表示 x 借给 y 共计 z 美元。用 0, 1, 2 表示小爱同学、小新同学和小明同学（0, 1, 2 为人的标号），上述交易可以表示为 [[0, 1, 10], [2, 0, 5]]。

    给定一群人之间的交易信息列表，计算能够还清所有债务的最小次数。

    注意：

    一次交易会以三元组 (x, y, z) 表示，并有 x ≠ y 且 z > 0。
    人的标号可能不是按顺序的，例如标号可能为 0, 1, 2 也可能为 0, 2, 6。
     

    示例 1：

    输入：
    [[0,1,10], [2,0,5]]

    输出：
    2

    解释：
    人 #0 给人 #1 共计 10 美元。
    人 #2 给人 #0 共计 5 美元。

    需要两次交易。一种方式是人 #1 分别给人 #0 和人 #2 各 5 美元。
     

    示例 2：

    输入：
    [[0,1,10], [1,0,1], [1,2,5], [2,0,5]]

    输出：
    1

    解释：
    人 #0 给人 #1 共计 10 美元。Person #0 gave person #1 $10.
    人 #1 给人 #0 共计 1 美元。Person #1 gave person #0 $1.
    人 #1 给人 #2 共计 5 美元。Person #1 gave person #2 $5.
    人 #2 给人 #0 共计 5 美元。Person #2 gave person #0 $5.

    因此，人 #1 需要给人 #0 共计 4 美元，所有的债务即可还清。

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/optimal-account-balancing
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * @version 0.1
 * @date 2022-06-25
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
    int minTransfers(vector<vector<int>>& transactions) {
        map<int, int> debt;
        for (const auto& transaction : transactions) {
            debt[transaction[0]] -= transaction[2];
            debt[transaction[1]] += transaction[2]; //平账过程
        }

        vector<int> balance;
        for (const auto& d : debt) {
            if (d.second != 0) {
                balance.push_back(d.second); //记录账务不平衡的账单
            }
        }

        int res = INT_MAX;
        dfs(0, 0, balance, res);
        return res;
    }

    void dfs(int now, int cnt, vector<int>& balance, int& res)
    {
        if (cnt >= res) {
            return; // 剪枝
        }

        while ((now < balance.size()) && (balance[now] == 0)) now++; //跳过账务不平衡的账单

        if (now == balance.size()) {
            res = min(res, cnt); //越界，记录当前最优
            return;
        }

        for (int i = now + 1; i < balance.size(); ++i) {
            if (balance[i] * balance[now] < 0) {
                balance[i] += balance[now]; //now 一次性清还账务
                dfs(now + 1, cnt + 1, balance, res); //递归
                balance[i] -= balance[now]; //回溯
            }
        }
    }
};