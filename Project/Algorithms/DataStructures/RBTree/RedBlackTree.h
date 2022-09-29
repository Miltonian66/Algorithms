#pragma once
#include <CommandFramework/CommandReceiver.h>

class AKey {
public:
	virtual std::string toString() = 0;
	virtual bool operator<(AKey const &other) = 0;
	virtual AKey& operator=(AKey const &other) = 0;
};

class RedBlackTree {
	enum Color {
		RED,
		BLACK
	};
	struct Node {
		AKey *key;
		void *value;
		Color color;// = Color::RED;
		Node *right, *left, *parent;
		Node(AKey* key, void* value, Node* NILL) : Node(NILL) {
			this->key = key;
			this->value = value;
		}
		Node(Node *NILL) : Node() {
			left = right = NILL;
		}
		Node() {
			color = Color::RED;
			right = left = parent = nullptr;
		}
	};
private:
	CommandReceiver& commandReceiver;
	Node * const NILL = new Node();
	Node* root = nullptr;
	bool isRed(Node *node);
	Node* grandParent(Node *current);
	Node* uncle(Node *current);
	void rotateLeft(Node *current);
	void rotateRight(Node *current);
	Node* pureInsert(Node *root, AKey *key, void *value);
	void checkRoot(Node *current);
	void checkParentRed(Node *current);
	void handleUncleBlack(Node *current);
	void handleUncleBlackLinear(Node *current);
public:
	RedBlackTree(CommandReceiver &commandReceiver);
	void insert(AKey *key, void *value);
};


