/**
 * @file 339. 嵌套列表权重和.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个嵌套的整数列表 nestedList ，每个元素要么是整数，要么是列表。同时，列表中元素同样也可以是整数或者是另一个列表。

    整数的 深度 是其在列表内部的嵌套层数。例如，嵌套列表 [1,[2,2],[[3],2],1] 中每个整数的值就是其深度。

    请返回该列表按深度加权后所有整数的总和。

     

    示例 1：



    输入：nestedList = [[1,1],2,[1,1]]
    输出：10 
    解释：因为列表中有四个深度为 2 的 1 ，和一个深度为 1 的 2。
    示例 2：


    输入：nestedList = [1,[4,[6]]]
    输出：27 
    解释：一个深度为 1 的 1，一个深度为 2 的 4，一个深度为 3 的 6。所以，1 + 4*2 + 6*3 = 27。
    示例 3：

    输入：nestedList = [0]
    输出：0
     

    提示：

    1 <= nestedList.length <= 50
    嵌套列表中整数的值在范围 [-100, 100] 内
    任何整数的最大 深度 都小于或等于 50

 * 
 * @version 0.1
 * @date 2022-06-19
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

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Constructor initializes an empty nested list.
 *     NestedInteger();
 *
 *     // Constructor initializes a single integer.
 *     NestedInteger(int value);
 *
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Set this NestedInteger to hold a single integer.
 *     void setInteger(int value);
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     void add(const NestedInteger &ni);
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class Solution {
public:
    int depthSum(vector<NestedInteger>& nestedList) {
        int res = 0;
        int weight = 1;
        for (const auto& lt : nestedList) {
            helper(lt, weight, res);
        }
    
        return res;
    }

    void helper(const NestedInteger& lt, int weight, int& res)
    {
        if (lt.isInteger()) {
            res += lt.getInteger() * weight;
            return;
        }
            
        for (const auto& item : lt.getList()) {
            helper(item, weight + 1, res);
        }
    }
};


