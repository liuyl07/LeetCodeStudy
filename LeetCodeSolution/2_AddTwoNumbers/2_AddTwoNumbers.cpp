#include <iostream>
#include <time.h>

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    // 99.54% faster and 56.64% space
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) 
    {
        ListNode *head = NULL, *cur = NULL;
        int add1 = 0;
        int value1, value2;

        do
        {
            if (l1 == NULL)
            {
                value1 = 0;
            }
            else
            {
                value1 = l1->val;
                l1 = l1->next;
            }

            if (l2 == NULL)
            {
                value2 = 0;
            }
            else
            {
                value2 = l2->val;
                l2 = l2->next;
            }

            value1 += value2 + add1;

            if (value1 > 9)
            {
                add1 = 1; 
                value1 -= 10;
            }
            else
            {
                add1 = 0;
            }

            if (head == NULL)
            {
                head = cur = new ListNode(value1);
            }
            else
            {
                cur->next = new ListNode(value1);
                cur = cur->next;
            }
            
        } while (l1 != NULL || l2 != NULL);

        if (add1)
        {
            cur->next = new ListNode(1);
            cur = cur->next;
        }

        return head;
    }

    // 99.92% faster and 98.50% space
    // by reuse the nodes from l1 and l2 and there is no need to creat new nodes
    ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2)
    {
        ListNode *head;
        int add1 = 0;

        for (head = l1; l1; l1 = l1->next, l2 = l2 ? l2->next : NULL)
        {
            l1->val += add1 + (l2 ? l2->val : 0);

            if (l1->val > 9)
            {
                add1 = 1;
                l1->val -= 10;
            }
            else
            {
                add1 = 0;
            }

            // l2 is longer than l1
            if (!l1->next && l2 && l2->next)
            {
                l1->next = l2->next;
                l2->next = NULL;
            }

            // the last loop
            if (!l1->next && add1)
            {
                l1->next = new ListNode(1);
            }
        }

        return head;
    }

    ListNode* constructList(int a[], int count)
    {
        ListNode *head = NULL, *cur = NULL;

        for (size_t i = 0; i < count; i++)
        {
            ListNode* temp = new ListNode(a[i]);
            if (i == 0)
            {
                head = temp;
                cur = temp;
            }
            else
            {
                cur->next = temp;
                cur = temp;
            }
        }
        return head;
    }
};


int main(int argc, char **argv)
{
    Solution myClass;

    // construct the first linked list
    int param1[] = { 5 };
    ListNode* head1 = myClass.constructList(param1, sizeof(param1)/sizeof(param1[0]));

    // construct the second one
    int param2[] = { 5 };
    ListNode* head2 = myClass.constructList(param2, sizeof(param2) / sizeof(param2[0]));

    ListNode* cur = myClass.addTwoNumbers1(head1, head2);

    while (cur != NULL)
    {
        printf("%4d", cur->val);
        cur = cur->next;
    }

    // construct the second linked list

    return 0;
}