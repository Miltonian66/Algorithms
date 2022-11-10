#include "Commands/BeginInsertion.h"
#include "LinkedList.h"

void LinkedList::insert(void* value) {
    Node* newValue = new Node();
    newValue->value = value;
    newValue->next = head;
    head = newValue;
}

void LinkedList::* remove(const std::function <bool(void*)> pred) {
    Node* current = first;
    while (current) {
        if (pred(current->value)) {
            remove(current);
            return(value);
        }
        current = current->next;
    }
    return(nullptr)
}

void LinkedList::* remove(Node* node) {
    Node* prev = node->prev;
    Node* next = node->next;
    if (prev != nullptr) prev->next = next;
    if (next != nullptr) next->prev = prev;
    delete node;
}

void LinkedList:: forEach(const std::function<bool(void*)> action) {
    Node* current = first;
    while (current) {
        action(current->value);
        curent = current->next;
    }
}
