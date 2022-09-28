#pragma once
#include <cmath>
#include <stack>
#include <initializer_list>
#include <CommandFramework/CommandReceiver.h>

class BinaryTree {
private:
	struct Node {
		long long value;
		Node *left = nullptr, *right = nullptr;
	};

	Node* root = nullptr;

	void remove(Node* Node);
	CommandReceiver receiver;

public:
	void insert(long long val);
	void remove(long long val);

	/// <param name="val">value to check</param>
	/// <returns>-1, if BinaryTree does not contain element with such value,
	///			number of traversed vertices, otherwise</returns>
	long long contains(long long val);

	BinaryTree(std::initializer_list<long long> _arr, CommandReceiver receiver);
	~BinaryTree();
};