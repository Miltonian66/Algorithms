#include "RedBlackTree.h"

bool RedBlackTree::isRed(Node* node) {
	return node != nullptr && node->color == Color::RED;
}

RedBlackTree::Node* RedBlackTree::grandParent(Node* current) {
	if (current)
		if (current->parent)
			return current->parent->parent;
	return nullptr;
}

RedBlackTree::Node* RedBlackTree::uncle(Node* current) {
	Node* gp = grandParent(current);
	if (!gp)
		return nullptr;
	if (gp->right == current->parent)
		return gp->left;
	return gp->right;
}

void RedBlackTree::rotateLeft(Node* current) {
	Node* pivot = current->right;
	pivot->parent = current->parent;
	if (current->parent != nullptr) {
		if (current->parent->left == current)
			current->parent->left = pivot;
		else
			current->parent->right = pivot;
	}

	current->right = pivot->left;
	if (pivot->left != NILL)
		pivot->left->parent = current;
	current->parent = pivot;
	pivot->left = current;
}

void RedBlackTree::rotateRight(Node* current) {
	Node* pivot = current->left;//choose pivot left from current
	/*Connect pivot with parent:*/
	pivot->parent = current->parent;
	if (current->parent != nullptr) {
		if (current->parent->left == current)
			current->parent->left = pivot;
		else
			current->parent->right = pivot;
	}
	/*end if pivot-parent connection*/
	/*connection node from the right of pivot to become left from current and create space for current in pivot's right*/
	current->left = pivot->right;
	if (pivot->right != NILL)
		pivot->right->parent = current;
	/*end of space creation*/
	/*connect current as right child of pivot*/
	current->parent = pivot;
	pivot->right = current;
}

RedBlackTree::Node* RedBlackTree::pureInsert(Node *root, AKey *key, void *value) {
	if (root == nullptr) {
		root = new Node(key, value, NILL);
		return root;
	}
	Node* result;
	if ((*key) < (*root->key)) {
		if (root->left != NILL)
			return pureInsert(root->left, key, value);
		result = new Node(key, value, NILL);		
	} 
	else {
		if (root->right != NILL)
			return pureInsert(root->right, key, value);
		result = new Node(key, value, NILL);
	}
	result->parent = root;
	return result;
}

void RedBlackTree::insert(AKey *key, void *value) {
	Node* placed = pureInsert(root, key, value);
	checkRoot(placed);
}

void RedBlackTree::checkRoot(Node *current) {
	if (current->parent == nullptr) {
		current->color = Color::BLACK;
		return;
	}
	checkParentRed(current);
}

void RedBlackTree::checkParentRed(Node* current) {
	if (current->parent->color == Color::BLACK)
		return;
	Node* uncle = this->uncle(current);
	if (uncle->color == Color::RED) {
		current->parent->color = Color::BLACK;
		uncle->color = Color::BLACK;
		uncle->parent->color = Color::RED;
		checkRoot(uncle->parent);
	}
	handleUncleBlack(current);
}

void RedBlackTree::handleUncleBlack(Node *current) {
	Node* gp = grandParent(current);
	if (current == current->parent->right && current->parent == g->left) {
		rotateLeft(current->parent);
		current = current->left;
	}
	else if (current == current->parent->left && current->parent == g->right) {
		rotateRight(current->parent);
		current = current->right;
	}
	handleUncleBlackLinear(current);
}

void RedBlackTree::handleUncleBlackLinear(Node* current) {
	Node* g = grandParent(current);
	current->parent->color = Color::BLACK;
	g->color = Color::RED;
	if (current == current->parent->left)
		rotateRight(g);
	else
		rotateLeft(g);
}


RedBlackTree::RedBlackTree(CommandReceiver &commandReceiver) : commandReceiver(commandReceiver) {
	NILL->color = Color::BLACK;
}