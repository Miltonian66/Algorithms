#include "BinaryTree.h"
#include "Commands/BeginInsertion.h"

void BinaryTree::remove(Node* Node) {
    if (Node) {
        remove(Node->left);
        remove(Node->right);

        delete Node;
    }
}

void BinaryTree::remove(long long val) {
    Node* current = root;

    while (current) {
        if (val == current->value)
            remove(current);
        if (val < current->value)
            current = current->left;
        else
            current = current->right;
    }
}

void BinaryTree::insert(long long val) {
    receiver.addCommand(new BeginInsertion(val));
    Node* current = root;

    while (current) {
        if (val < current->value)
            current = current->left;
        else
            current = current->right;
    }

    current = new Node{ val };
}

long long BinaryTree::contains(long long val) {
    long long count = 0;

    Node* current = root;

    while (current) {
        ++count;
        if (val == current->value)
            return count;
        if (val < current->value)
            current = current->left;
        else
            current = current->right;
    }

    return -1;
}

BinaryTree::BinaryTree(std::initializer_list<long long> _arr, CommandReceiver) : receiver(receiver) {
    for (long long i : _arr) {
        insert(i);
    }
}

BinaryTree::~BinaryTree() {
    this->remove(root);
}
