/**
 * @file 1061. 按字典序排列最小的等效字符串.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 给出长度相同的两个字符串s1 和 s2 ，还有一个字符串 baseStr 。

    其中  s1[i] 和 s2[i]  是一组等价字符。

    举个例子，如果 s1 = "abc" 且 s2 = "cde"，那么就有 'a' == 'c', 'b' == 'd', 'c' == 'e'。
    等价字符遵循任何等价关系的一般规则：

     自反性 ：'a' == 'a'
     对称性 ：'a' == 'b' 则必定有 'b' == 'a'
     传递性 ：'a' == 'b' 且 'b' == 'c' 就表明 'a' == 'c'
    例如， s1 = "abc" 和 s2 = "cde" 的等价信息和之前的例子一样，那么 baseStr = "eed" , "acd" 或 "aab"，这三个字符串都是等价的，而 "aab" 是 baseStr 的按字典序最小的等价字符串

    利用 s1 和 s2 的等价信息，找出并返回 baseStr 的按字典序排列最小的等价字符串。

    示例 1：

    输入：s1 = "parker", s2 = "morris", baseStr = "parser"
    输出："makkek"
    解释：根据 A 和 B 中的等价信息，我们可以将这些字符分为 [m,p], [a,o], [k,r,s], [e,i] 共 4 组。每组中的字符都是等价的，并按字典序排列。所以答案是 "makkek"。
    示例 2：

    输入：s1 = "hello", s2 = "world", baseStr = "hold"
    输出："hdld"
    解释：根据 A 和 B 中的等价信息，我们可以将这些字符分为 [h,w], [d,e,o], [l,r] 共 3 组。所以只有 S 中的第二个字符 'o' 变成 'd'，最后答案为 "hdld"。
    示例 3：

    输入：s1 = "leetcode", s2 = "programs", baseStr = "sourcecode"
    输出："aauaaaaada"
    解释：我们可以把 A 和 B 中的等价字符分为 [a,o,e,r,s,c], [l,p], [g,t] 和 [d,m] 共 4 组，因此 S 中除了 'u' 和 'd' 之外的所有字母都转化成了 'a'，最后答案为 "aauaaaaada"。
     

    提示：

    1 <= s1.length, s2.length, baseStr <= 1000
    s1.length == s2.length
    字符串s1, s2, and baseStr 仅由从 'a' 到 'z' 的小写英文字母组成。

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/lexicographically-smallest-equivalent-string
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。    
 * 
 * @version 0.1
 * @date 2022-06-22
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



struct UnionFind {
public:
    UnionFind(int n) : n(n) {
        for (int i = 0; i < n; ++i) {
            roots.push_back(i);
        }
    }

    int Find(int p) {
        return p == roots[p] ? p : Find(roots[p]);
    }

    void Union(int p, int q) {
        int x = Find(p);
        int y = Find(q);
        if (x == y) {
            return;
        }
        if (x < y) {
            roots[y] = x;
        } else {
            roots[x] = y;
        }
    }

private:
    int n;
    vector<int> roots;
};


class Solution {
public:
    string smallestEquivalentString(string s1, string s2, string baseStr) {
        UnionFind uf(26);
        for (int i = 0; i < s1.size(); ++i) {
            uf.Union(s1[i] - 'a', s2[i] - 'a');
        }

        string res;
        for (const auto& ch : baseStr) {
            res += (uf.Find(ch - 'a') + 'a');
        }
        return res;
    }
};



