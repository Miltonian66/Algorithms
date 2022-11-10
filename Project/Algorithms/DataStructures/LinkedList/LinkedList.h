#pragma once
#include <functional>
class LinkedList {
private:
	struct Node {
		void* value;
		Node* next;
		Node* prev;
	};
	Node* head;
	remove(Node* node);
public:
	LinkedList();
	void insert(void* value);
	void* remove(const std::function <bool(void*)> pred);
	void forEach(const std::function<bool(void*)> action);
};