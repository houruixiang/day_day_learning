/**
 * @file 146. LRU 缓存.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 
 * 
 * 请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
        实现 LRUCache 类：
        LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
        int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
        void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；
        如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，
        则应该 逐出 最久未使用的关键字。
        函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。

        示例：
            输入
            ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
            [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
            输出
            [null, null, null, 1, null, -1, null, -1, 3, 4]

        解释
            LRUCache lRUCache = new LRUCache(2);
            lRUCache.put(1, 1); // 缓存是 {1=1}
            lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
            lRUCache.get(1);    // 返回 1
            lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
            lRUCache.get(2);    // 返回 -1 (未找到)
            lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
            lRUCache.get(1);    // 返回 -1 (未找到)
            lRUCache.get(3);    // 返回 3
            lRUCache.get(4);    // 返回 4
         
        提示：
            1 <= capacity <= 3000
            0 <= key <= 10000
            0 <= value <= 105
            最多调用 2 * 105 次 get 和 put

 
 * @version 0.1
 * @date 2022-05-29
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <list>
#include <unordered_map>

class LRUCache {
public:
    LRUCache(int cap) : cap(cap) {}

    int get(int key)
    {
        auto it = dict.find(key);
        if (it == dict.end()) {
            return -1;
        }
        
        int value = it->second->second;

        // std::pair<int, int> node = *(it->second);
        // cache.erase(it->second);
        // cache.push_front(node);
        // dict[key] = cache.begin();

        cache.splice(cache.begin(), cache, it->second);

        return value;
    }

    void put(int key, int value)
    {
        if (dict.find(key) != dict.end()) {
            cache.erase(dict[key]);
        } else {
            if (cap == dict.size()) {
                dict.erase(cache.back().first);
                cache.pop_back();
            }
        }
        cache.emplace_front(key, value);
        dict[key] = cache.begin();
    }

private:
    int cap {0};
    std::list<std::pair<int, int>> cache;
    std::unordered_map<int, std::list<std::pair<int, int>>::iterator> dict;

};