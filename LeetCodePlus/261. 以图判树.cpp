/**
 * @file 261. 以图判树.cpp
 * @author your name (you@domain.com)
 * @brief 
 
    给定编号从 0 到 n - 1 的 n 个结点。给定一个整数 n 和一个 edges 列表，
    其中 edges[i] = [ai, bi] 表示图中节点 ai 和 bi 之间存在一条无向边。

    如果这些边能够形成一个合法有效的树结构，则返回 true ，否则返回 false 。

    示例 1：
    输入: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
    输出: true

    示例 2:
    输入: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
    输出: false

    提示：
        1 <= n <= 2000
        0 <= edges.length <= 5000
        edges[i].length == 2
        0 <= ai, bi < n
        ai != bi
        不存在自循环或重复的边

 * @version 0.1
 * @date 2022-05-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <limits.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class UnionFind {
public:
    UnionFind(int n) : cnt(n)
    {
        cnt = n;
        for (int i = 0; i < n; ++i) {
            roots.push_back(i);
        }
    }

    bool Union(int x, int y)
    {
        int p = Find(x);
        int q = Find(y);
        if (p == q) {
            return false;
        }
        roots[p]= q;
        --cnt;
        return true;
    }

    int Find(int x) 
    {
        if (roots[x] == x) {
            return x;
        }
        roots[x] = Find(roots[x]); //importance
        return roots[x];
    }

    bool IsTree()
    {
        return cnt == 1;
    }

private:
    int cnt = 0;
    vector<int> roots;
};

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& edges) {
        UnionFind uf(n);
        for (const auto& edge : edges) {
            if (!uf.Union(edge[0], edge[1])) {
                return false;
            }
        }
        return uf.IsTree();
    }
};
