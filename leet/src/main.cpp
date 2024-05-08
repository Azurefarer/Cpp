// Linked List

#include <iostream>

struct Listnode {
    int val;
    Listnode *next;
    Listnode() : val(0), next(nullptr) {}
    Listnode(int x) : val(x), next(nullptr) {}
    Listnode(int x, Listnode *next) : val(x), next(next) {}
};

int main() {
    Listnode* node = new Listnode();
    for (int i = 0; i < 10; i++) {
        Listnode* next = new Listnode(i);
        std::cout << "node value: " << node->val << std::endl;
        node->next = next;
        std::cout << "node next: " << node->next << std::endl;
        node = node->next;
    }
    return 0;
}