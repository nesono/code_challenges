#include <cstdio>
#include <search.h>

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
class Solution1 {
public:
    static ListNode* advance(ListNode* node) {
        if (node != nullptr) {
            if (node->next != nullptr) {
                return node->next;
            }
        }
        return nullptr;
    }

    static void calculate_sum_and_carryover(ListNode* l1,
                                            ListNode* l2,
                                            int* sum,
                                            int* carryover) {
        *sum = *carryover;
        if (l1) {
            *sum += l1->val;
        }
        if (l2) {
            *sum += l2->val;
        }

        if (*sum >= 10) {
            *sum -= 10;
            *carryover = 1;
        }
        else {
            *carryover = 0;
        }
    }

    static ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }

        ListNode* result = new ListNode();
        ListNode* runner = result;

        int sum = 0;
        int carryover = 0;

        calculate_sum_and_carryover(l1, l2, &sum, &carryover);
        runner->val = sum;

        while (carryover > 0 ||
                (l1 != nullptr && l1->next != nullptr) ||
                (l2 != nullptr && l2->next != nullptr)) {
            l1 = advance(l1);
            l2 = advance(l2);

            calculate_sum_and_carryover(l1, l2, &sum, &carryover);
            runner->next = new ListNode(sum);
            runner = runner->next;
        }

        return result;
    }
};

void print_list(ListNode* node) {
    while (node != nullptr) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

int main() {
    {
        auto l1 = new ListNode(2, new ListNode(4, new ListNode(3)));
        auto l2 = new ListNode(5, new ListNode(6, new ListNode(4)));

        auto result = Solution1::addTwoNumbers(l1, l2);
        print_list(result);
    }
    {
        auto l1 = new ListNode(0);
        auto l2 = new ListNode(0);

        auto result = Solution1::addTwoNumbers(l1, l2);
        print_list(result);
    }
    {
        auto l1 = new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9)))))));
        auto l2 = new ListNode(9, new ListNode(9, new ListNode(9, new ListNode(9))));

        auto result = Solution1::addTwoNumbers(l1, l2);
        print_list(result);
    }
    {
        // [2,4,9]
        // [5,6,4,9]
        auto l1 = new ListNode(2, new ListNode(4, new ListNode(9)));
        auto l2 = new ListNode(5, new ListNode(6, new ListNode(4, new ListNode(9))));

        auto result = Solution1::addTwoNumbers(l1, l2);
        print_list(result);
    }
}