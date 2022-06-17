/**
 * @file 1101. 彼此熟识的最早时间.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 在一个社交圈子当中，有 n 个人。每个人都有一个从 0 到 n - 1 的唯一编号。我们有一份日志列表 logs，其中 logs[i] = [timestampi, xi, yi] 表示 xi 和 yi 将在同一时间 timestampi 成为朋友。

    友谊是 相互 的。也就是说，如果 a 和 b 是朋友，那么 b 和 a 也是朋友。同样，如果 a 和 b 是朋友，或者 a 是 b 朋友的朋友 ，那么 a 和 b 是熟识友。

    返回圈子里所有人之间都熟识的最早时间。如果找不到最早时间，就返回 -1 。

    示例 1：

    输入：logs = [[20190101,0,1],[20190104,3,4],[20190107,2,3],[20190211,1,5],[20190224,2,4],[20190301,0,3],[20190312,1,2],[20190322,4,5]], N = 6
    输出：20190301
    解释：
    第一次结交发生在 timestamp = 20190101，0 和 1 成为好友，社交朋友圈如下 [0,1], [2], [3], [4], [5]。
    第二次结交发生在 timestamp = 20190104，3 和 4 成为好友，社交朋友圈如下 [0,1], [2], [3,4], [5].
    第三次结交发生在 timestamp = 20190107，2 和 3 成为好友，社交朋友圈如下 [0,1], [2,3,4], [5].
    第四次结交发生在 timestamp = 20190211，1 和 5 成为好友，社交朋友圈如下 [0,1,5], [2,3,4].
    第五次结交发生在 timestamp = 20190224，2 和 4 已经是好友了。
    第六次结交发生在 timestamp = 20190301，0 和 3 成为好友，大家都互相熟识了。
    示例 2:

    输入: logs = [[0,2,0],[1,0,1],[3,0,3],[4,1,2],[7,3,1]], n = 4
    输出: 3
     

    提示：

        2 <= n <= 100
        1 <= logs.length <= 104
        logs[i].length == 3
        0 <= timestampi <= 109
        0 <= xi, yi <= n - 1
        xi != yi
        timestampi 中的所有时间戳 均不同
        所有的对 (xi, yi) 在输入中最多出现一次

 * 
 * @version 0.1
 * @date 2022-06-17
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


class UnionFind{
public:
    UnionFind(int n)
    {
        for(int i = 0; i < n; i++) {
            roots[i] = i;
            rank[i]  = 1;
            size[i]  = 1;
        }
        maxSize = 1;
    }

    int Find(int x)
    {
        return x == roots[x] ? x : roots[x] = Find(roots[x]);
    }

    void Union(int i, int j){
        int x=Find(i);
        int y=Find(j);
        if (x == y) return;

        if (rank[x] <= rank[y]) {
            roots[x] = y;
            size[y] += size[x];
            maxSize  = max(maxSize, size[y]);
        } else {
            roots[y] = x;
            size[x] += size[y];
            maxSize  = max(maxSize, size[x]);
        }
    }

    int GetMaxSize()
    {
        return maxSize;
    }

private:
    static constexpr int LENS = 1e4 + 1;
    int roots[LENS], rank[LENS], size[LENS];
    int maxSize;
};


class Solution {
public:
    int earliestAcq(vector<vector<int>>& logs, int n) {
        sort(logs.begin(),logs.end());

        UnionFind uf(n);
        for (int i = 0; i < logs.size(); i++) {
            int date = logs[i][0], person1 = logs[i][1], person2 = logs[i][2];
            uf.Union(person1, person2);
            if (uf.GetMaxSize() == n) {
                return date;
            }
        }
        return -1;
    }
};

