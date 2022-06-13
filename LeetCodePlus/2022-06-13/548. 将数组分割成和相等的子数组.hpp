/**
 * @file 548. 将数组分割成和相等的子数组.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 
 * 
 * 
 * @version 0.1
 * @date 2022-06-13
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



// o(n^3)
class Solution {
public:
    bool splitArray(vector<int>& nums) {
        const int n = nums.size();
        vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + nums[i];
        }

        for (int i = 1; i < n - 1; ++i) {
            int sum0 = prefixSum[i];
            for (int k = n - 2; k > i + 1; --k) {
                // std::cout << i << " " << k << " ";
                int sum1 = prefixSum[n] - prefixSum[k + 1];
                // std::cout << sum0 << " " << sum1 << std::endl;
                if (sum0 != sum1) {
                    continue;
                }
                for (int j = i + 2; j + 1 < k; ++j) {
                    int sum2 = prefixSum[k] - prefixSum[j + 1];
                    int sum3 = prefixSum[j] - prefixSum[i + 1];
                    // std::cout << sum2 << std::endl;
                    if ((sum2 == sum3) && (sum0 == sum2)) {
                        return true;
                    }
                } 
            }
        }
        return false;
    }
};


 
//  // o(n^2) hash
//  // 搞笑了这个数据集，居然没有O(n^3)算法速度快
// class Solution {
// public:
//     bool splitArray(vector<int>& nums) {
//         const int n = nums.size();
//         vector<int> prefixSum(n + 1, 0);
//         for (int i = 0; i < n; ++i) {
//             prefixSum[i + 1] = prefixSum[i] + nums[i];
//         }

//         for (int j = 3; j < n - 1; ++j) {
//             set<int> sum;
//             for (int i = 1; i + 1 < j; ++i) {
//                 if (prefixSum[i] == (prefixSum[j] - prefixSum[i + 1])) {
//                     sum.insert(prefixSum[i]);
//                 }
//             }
//             if (sum.size() == 0) {
//                 continue;
//             }

//             for (int k = j + 2; k < n - 1; ++k) {
//                 int sum0 = prefixSum[k] - prefixSum[j + 1];
//                 int sum1 = prefixSum[n] - prefixSum[k + 1];
//                 if ((sum0 == sum1) && (sum.find(sum0) != sum.end())) {
//                     return true;
//                 }
//             }
//         }
//         return false;
//     }
// };


