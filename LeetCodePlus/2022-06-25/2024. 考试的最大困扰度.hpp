/**
 * @file 2024. 考试的最大困扰度.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 一位老师正在出一场由 n 道判断题构成的考试，每道题的答案为 true （用 'T' 表示）或者 false （用 'F' 表示）。老师想增加学生对自己做出答案的不确定性，方法是 最大化 有 连续相同 结果的题数。（也就是连续出现 true 或者连续出现 false）。

    给你一个字符串 answerKey ，其中 answerKey[i] 是第 i 个问题的正确结果。除此以外，还给你一个整数 k ，表示你能进行以下操作的最多次数：

    每次操作中，将问题的正确答案改为 'T' 或者 'F' （也就是将 answerKey[i] 改为 'T' 或者 'F' ）。
    请你返回在不超过 k 次操作的情况下，最大 连续 'T' 或者 'F' 的数目。

     

    示例 1：

    输入：answerKey = "TTFF", k = 2
    输出：4
    解释：我们可以将两个 'F' 都变为 'T' ，得到 answerKey = "TTTT" 。
    总共有四个连续的 'T' 。
    示例 2：

    输入：answerKey = "TFFT", k = 1
    输出：3
    解释：我们可以将最前面的 'T' 换成 'F' ，得到 answerKey = "FFFT" 。
    或者，我们可以将第二个 'T' 换成 'F' ，得到 answerKey = "TFFF" 。
    两种情况下，都有三个连续的 'F' 。
    示例 3：

    输入：answerKey = "TTFTTFTT", k = 1
    输出：5
    解释：我们可以将第一个 'F' 换成 'T' ，得到 answerKey = "TTTTTFTT" 。
    或者我们可以将第二个 'F' 换成 'T' ，得到 answerKey = "TTFTTTTT" 。
    两种情况下，都有五个连续的 'T' 。
     

    提示：

    n == answerKey.length
    1 <= n <= 5 * 104
    answerKey[i] 要么是 'T' ，要么是 'F'
    1 <= k <= n

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/maximize-the-confusion-of-an-exam
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
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




// class Solution {
// public:
//     int maxConsecutiveAnswers(string answerKey, int k) {
//         int res = 0;
//         // map<char, int> dict;?
//         int l = 0;
//         for (int r = 0; r < answerKey.size(); ++r) {
//             ++dict[answerKey[r]]; //记录出现次数
//             if (min(dict['T'], dict['F']) > k) {
//                 --dict[answerKey[l++]]; //如果任意值出现次数个数>k，这个时候就可以将左指针右移
//             }
//             res = max(res, r - l + 1); //求值
//         }

//         return res;
//     }
// };



class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int res = 0;
        int t = 0, f = 0;
        int l = 0;
        for (int r = 0; r < answerKey.size(); ++r) {
            answerKey[r] == 'T' ? ++t : ++f;
            // ++dict[answerKey[r]]; //记录出现次数
            if (min(t, f) > k) {
                answerKey[l++] == 'T' ? --t : --f;
                // --dict[answerKey[l++]]; //如果任意值出现次数个数>k，这个时候就可以将左指针右移
            }
            res = max(res, r - l + 1); //求值
        }

        return res;
    }
};


