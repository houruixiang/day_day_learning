/**
 * @file 737. 句子相似性 II.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 我们可以将一个句子表示为一个单词数组，例如，句子 I am happy with leetcode"可以表示为 arr = ["I","am",happy","with","leetcode"]

    给定两个句子 sentence1 和 sentence2 分别表示为一个字符串数组，并给定一个字符串对 similarPairs ，其中 similarPairs[i] = [xi, yi] 表示两个单词 xi 和 yi 是相似的。

    如果 sentence1 和 sentence2 相似则返回 true ，如果不相似则返回 false 。

    两个句子是相似的，如果:

    它们具有 相同的长度 (即相同的字数)
    sentence1[i] 和 sentence2[i] 是相似的
    请注意，一个词总是与它自己相似，也请注意，相似关系是可传递的。例如，如果单词 a 和 b 是相似的，单词 b 和 c 也是相似的，那么 a 和 c 也是 相似 的。

     

    示例 1:

    输入: sentence1 = ["great","acting","skills"], sentence2 = ["fine","drama","talent"], similarPairs = [["great","good"],["fine","good"],["drama","acting"],["skills","talent"]]
    输出: true
    解释: 这两个句子长度相同，每个单词都相似。
    示例 2:

    输入: sentence1 = ["I","love","leetcode"], sentence2 = ["I","love","onepiece"], similarPairs = [["manga","onepiece"],["platform","anime"],["leetcode","platform"],["anime","manga"]]
    输出: true
    解释: "leetcode" --> "platform" --> "anime" --> "manga" --> "onepiece".
    因为“leetcode”和“onepiece”相似，而且前两个单词是相同的，所以这两句话是相似的。
    示例 3:

    输入: sentence1 = ["I","love","leetcode"], sentence2 = ["I","love","onepiece"], similarPairs = [["manga","hunterXhunter"],["platform","anime"],["leetcode","platform"],["anime","manga"]]
    输出: false
    解释: “leetcode”和“onepiece”不相似。
     

    提示:

    1 <= sentence1.length, sentence2.length <= 1000
    1 <= sentence1[i].length, sentence2[i].length <= 20
    sentence1[i] 和 sentence2[i] 只包含大小写英文字母
    0 <= similarPairs.length <= 2000
    similarPairs[i].length == 2
    1 <= xi.length, yi.length <= 20
    xi 和 yi 只含英文字母
 
 * @version 0.1
 * @date 2022-06-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#pragma once

#include <map>
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
UnionFind(int n)
{
    for (int i = 0; i < n; ++i) {
        roots.push_back(i);
    }
}

int Find(int p)
{
    if (p == roots[p]) {
        return p;
    }
    return roots[p] = Find(roots[p]);
}

void Union(int p, int q)
{
    int x = Find(p);
    int y = Find(q);
    if (x != y) {
        roots[x] = y;
    }
}
private:
    vector<int> roots;
};
class Solution {
public:
    bool areSentencesSimilarTwo(vector<string>& sentence1, vector<string>& sentence2, vector<vector<string>>& similarPairs) {
        if (sentence1.size() != sentence2.size()) {
            return false;
        }

        int idx = 0;
        map<string, int> dict;
        for (const auto& s : sentence1) {
            if (dict.find(s) == dict.end()) {
                dict[s] = idx++;
            }
        }
        for (const auto& s : sentence2) {
            if (dict.find(s) == dict.end()) {
                dict[s] = idx++;
            }
        }
        for (const auto& s : similarPairs) {
            if (dict.find(s[0]) == dict.end()) {
                dict[s[0]] = idx++;
            }
            if (dict.find(s[1]) == dict.end()) {
                dict[s[1]] = idx++;
            }
        }

        UnionFind uf(idx);
        for (const auto& s : similarPairs) {
            uf.Union(dict[s[0]], dict[s[1]]);
        }

        for (int i = 0; i < sentence1.size(); ++i) {
            int x = uf.Find(dict[sentence1[i]]);
            int y = uf.Find(dict[sentence2[i]]);
            if (x != y) {
                return false;
            }
        }
        return true;
    }
};






