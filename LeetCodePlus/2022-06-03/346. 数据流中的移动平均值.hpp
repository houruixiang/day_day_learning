/**
 * @file 346. 数据流中的移动平均值.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给定一个整数数据流和一个窗口大小，根据该滑动窗口的大小，计算其所有整数的移动平均值。

实现 MovingAverage 类：

MovingAverage(int size) 用窗口大小 size 初始化对象。
double next(int val) 计算并返回数据流中最后 size 个值的移动平均值。
 

示例：

输入：
["MovingAverage", "next", "next", "next", "next"]
[[3], [1], [10], [3], [5]]
输出：
[null, 1.0, 5.5, 4.66667, 6.0]

解释：
MovingAverage movingAverage = new MovingAverage(3);
movingAverage.next(1); // 返回 1.0 = 1 / 1
movingAverage.next(10); // 返回 5.5 = (1 + 10) / 2
movingAverage.next(3); // 返回 4.66667 = (1 + 10 + 3) / 3
movingAverage.next(5); // 返回 6.0 = (10 + 3 + 5) / 3
 

提示：

1 <= size <= 1000
-105 <= val <= 105
最多调用 next 方法 104 次

来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/moving-average-from-data-stream
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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


class MovingAverage {
public:
    MovingAverage(int size) : size(size) {}
    
    double next(int val) {
        dq.push_back(val);
        sum += val;
        if (dq.size() > size) {
            sum -= dq.front();
            dq.pop_front();
        }
        return sum / (dq.size() + .0);
    }
private:
    int size = 0;
    double sum = 0.0;
    deque<int> dq;
};

/**
 * Your MovingAverage object will be instantiated and called as such:
 * MovingAverage* obj = new MovingAverage(size);
 * double param_1 = obj->next(val);
 */