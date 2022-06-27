/**
 * @file 2046. 给按照绝对值排序的链表排序.hpp
 * @author your name (you@domain.com)
 * @brief 
 * 给你一个链表的头结点 head ，这个链表是根据结点的绝对值进行升序排序, 返回重新根据节点的值进行升序排序的链表。
 
    示例 1:


    输入: head = [0,2,-5,5,10,-10]
    输出: [-10,-5,0,2,5,10]
    解释:
    根据结点的值的绝对值排序的链表是 [0,2,-5,5,10,-10].
    根据结点的值排序的链表是 [-10,-5,0,2,5,10].
    示例 2：



    输入: head = [0,1,2]
    输出: [0,1,2]
    解释:
    这个链表已经是升序的了。
    示例 3：

    输入: head = [1]
    输出: [1]
    解释:
    这个链表已经是升序的了。
     

    提示:

    链表节点数的范围是 [1, 105].
    -5000 <= Node.val <= 5000
    head 是根据结点绝对值升序排列好的链表.
     

    进阶:
    你可以在O(n)的时间复杂度之内解决这个问题吗?

    来源：力扣（LeetCode）
    链接：https://leetcode.cn/problems/sort-linked-list-already-sorted-using-absolute-values
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
 * 
 * 
 * @version 0.1
 * @date 2022-06-27
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
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
   
class Solution {
public:
    ListNode* sortLinkedList(ListNode* head) {
        ListNode* prev = head;
        ListNode* curr = head->next;
        while (curr != nullptr) {
            if (curr->val < 0) {
                ListNode* tmp = curr->next;
                prev->next = tmp;
                curr->next = head;
                head = curr;
                curr = tmp;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }
        return head;
    }
};
