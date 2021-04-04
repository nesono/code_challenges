#include <cstdio>

struct Node {
    explicit Node(int n_value=0) { value = n_value; }
    int value;
    Node* next = nullptr;
};

Node* rec_reverse_helper(Node* list, Node** end=nullptr) {
    auto tail = list->next;
    auto head = list;
    head->next = nullptr; // terminate every head before appending to reversed tail
    if (tail) {
        auto p = rec_reverse_helper(tail, end);
        (*end)->next = head;
        *end = head;
        return p; // p is our new list
    }
    else {
        *end = list;
        return list;
    }
}

Node* rec_reverse(Node* list) {
    if (!list) {
        return nullptr;
    }
    Node* end{nullptr};
    return rec_reverse_helper(list, &end);
}

Node* reverse(Node* list) {
    // if list is empty or has only one entry
    if (!list || !list->next) {
        return list;
    }

    auto prev = list;
    auto cur = prev->next;
    auto tail = cur->next;
    prev->next = nullptr; // terminate the new end
    cur->next = prev;

    while(tail) {
        prev = cur;
        cur = tail;
        tail = tail->next;
        cur->next = prev;
    }
    return cur;
}

void print_list(Node* list) {
    if (list) {
        do {
            printf("%d", list->value);
            if(list->next) {
                printf(" --> ");
            }
            list = list->next;
        } while(list);
        printf("\n");
    }
}

int main() {
    Node* list = new Node(1);
    list->next = new Node(2);
    list->next->next = new Node(3);
    list->next->next->next = new Node(4);
    print_list(list);
    auto rev_list = reverse(list);
    print_list(rev_list);
    rev_list = rec_reverse(rev_list);
    print_list(rev_list);
}
