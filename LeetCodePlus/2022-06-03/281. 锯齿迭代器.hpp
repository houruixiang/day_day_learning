/**
 * @file 281. 锯齿迭代器.cpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给出两个一维的向量，请你实现一个迭代器，交替返回它们中间的元素。

示例:

输入:
v1 = [1,2]
v2 = [3,4,5,6] 

输出: [1,3,2,4,5,6]

解析: 通过连续调用 next 函数直到 hasNext 函数返回 false，
     next 函数返回值的次序应依次为: [1,3,2,4,5,6]。
拓展：假如给你 k 个一维向量呢？你的代码在这种情况下的扩展性又会如何呢?

拓展声明：
 “锯齿” 顺序对于 k > 2 的情况定义可能会有些歧义。所以，假如你觉得 “锯齿” 这个表述不妥，也可以认为这是一种 “循环”。例如：

输入:
[1,2,3]
[4,5,6,7]
[8,9]

输出: [1,4,8,2,5,9,3,6,7].
 * 
 * @version 0.1
 * @date 2022-06-03
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

class ZigzagIterator {
public:
    ZigzagIterator(vector<int>& v1, vector<int>& v2) {
        int i, j = 0;
        while (i < v1.size() && j < v2.size()) {
            dq.push_back(v1[i++]);
            dq.push_back(v2[j++]);
        }
        while (i < v1.size()) {
            dq.push_back(v1[i++]);
        }
        while (j < v2.size()) {
            dq.push_back(v2[j++]);
        }
    }

    int next() {
        int val = dq.front();
        dq.pop_front();
        return val;
    }

    bool hasNext() {
        return !dq.empty();
    }
private:
    deque<int> dq;
};

/**
 * Your ZigzagIterator object will be instantiated and called as such:
 * ZigzagIterator i(v1, v2);
 * while (i.hasNext()) cout << i.next();
 */