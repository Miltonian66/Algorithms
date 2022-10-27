#include "RedBlackTree.h"

RedBlackTree::Node::Node(){
   color = Color::RED;
   right = left = parent = nullptr;
   key = nullptr;
   value = nullptr;
}

RedBlackTree::Node::Node(RedBlackTree::Node *NILL) : RedBlackTree::Node::Node(){
   left = right = NILL;
}

RedBlackTree::Node::Node(AKey *key, void *value, Node *NILL) : RedBlackTree::Node::Node(NILL){
   this->key = key;
   this->value = value;
}

RedBlackTree::Node::Node(const RedBlackTree::Node &other, 
                         RedBlackTree::Node *oNILL, 
                         RedBlackTree::Node *NILL, 
                         AKey *(*copyKey)(AKey *), 
                         void *(*copyValue)(void *)){
   parent = nullptr;
   if(copyKey)
      key = copyKey(other.key);
   else
      key = other.key;
   if(copyValue)
      value = copyValue(other.value);
   else
      value = other.value;
   color = other.color;
   if(other.right != oNILL){
      right = new Node(*other.right, oNILL, NILL, copyKey, copyValue);
      right->parent = this;
   }
   else
      right = NILL;
   if(other.left != oNILL){
      left = new Node(*other.left, oNILL, NILL, copyKey, copyValue);
      left->parent = this;
   }
   else
      left = NILL;
}

RedBlackTree::Node::~Node(){
   if(left && left->parent && left->parent == this)
      delete left;
   if(right && right->parent && right->parent == this)
      delete right;
}

RedBlackTree::RedBlackTree(CommandReceiver &commandReceiver)
	: commandReceiver(commandReceiver){
	NILL->color = Color::BLACK;
   _size = 0;
}

RedBlackTree::RedBlackTree(const RedBlackTree &other, AKey* (*copyKey)(AKey *), void* (*copyValue)(void *)) : commandReceiver(other.commandReceiver){
   NILL->color = Color::BLACK;
   if(other.root)
      root = new Node(*other.root, other.NILL, NILL, copyKey, copyValue);
   _size = other._size;
}

RedBlackTree::~RedBlackTree(){
   delete root;
   delete NILL;
}

size_t RedBlackTree::size(){
   return _size;
}

bool RedBlackTree::empty(){
   return root == nullptr || root == NILL;
}

bool RedBlackTree::isValid(){
   if(!root)
      return true;
   if(root->color != Color::BLACK)
      return false;
   return _isValid(root) != (size_t) (-1);
}

size_t RedBlackTree::_isValid(Node *current){
   if(current == NILL)
      return 1;
   if((current->color == Color::RED && (current->right->color == Color::RED || current->left->color == Color::RED)))
      return -1;
   if(current->right != NILL && current->left != NILL && *(current->right->key) < *(current->left->key))
      return -1;
   if(current->right != NILL && current->right->parent != current)
      return -1;
   if(current->left != NILL && current->left->parent != current)
      return -1;
   size_t r = _isValid(current->right), l = _isValid(current->left);
   if(r != l || r == (size_t) (-1) || l == (size_t) (-1))
      return -1;
   return l + (current->color == Color::BLACK);
}

void RedBlackTree::insert(AKey *key, void *value){
   _size++;
   if(!root){
      root = new Node(key, value, NILL);
      root->color = Color::BLACK;
      return;
   }
	Node *placed = _insert(root, key, value);
	checkRoot(placed);
}

RedBlackTree::Node *RedBlackTree::_insert(Node *root, AKey *key,
											 void *value){
	if(root == nullptr){
		root = new Node(key, value, NILL);
		return root;
	}
	Node *result;
	if((*key) < (*root->key)){
		if(root->left != NILL) 
         return _insert(root->left, key, value);
		result = new Node(key, value, NILL);
      root->left = result;
	}
	else{
		if(root->right != NILL) 
         return _insert(root->right, key, value);
		result = new Node(key, value, NILL);
      root->right = result;
	}
	result->parent = root;
	return result;
}

void RedBlackTree::checkRoot(Node *current){
	if(current->parent == nullptr){
		current->color = Color::BLACK;
		return;
	}
	checkParentRed(current);
}

void RedBlackTree::checkParentRed(Node *current){
	if(current->parent->color == Color::BLACK) return;
	Node *uncle = this->uncle(current);

	if(uncle->color == Color::RED){
		current->parent->color = Color::BLACK;
		uncle->color = Color::BLACK;
		uncle->parent->color = Color::RED;
		checkRoot(uncle->parent);
      return;
	}
	handleUncleBlack(current);
}

void RedBlackTree::handleUncleBlack(Node *current){
	Node *gp = grandParent(current);
	if(current == current->parent->right && current->parent == gp->left){
		rotateLeft(current->parent);
		current = current->left;
	}
	else if(current == current->parent->left && current->parent == gp->right){
		rotateRight(current->parent);
		current = current->right;
	}
	handleUncleBlackLinear(current);
}

void RedBlackTree::handleUncleBlackLinear(Node *current){
	Node *gp = grandParent(current);
	current->parent->color = Color::BLACK;
	gp->color = Color::RED;
	if(current == current->parent->left)
		rotateRight(gp);
	else
		rotateLeft(gp);
}

void *RedBlackTree::find(AKey *key){
   if(!root)
      return nullptr;
   Node *res = _find(key, root);
   if(res)
      return res->value;
   return nullptr;
}

RedBlackTree::Node *RedBlackTree::_find(AKey *key, Node *root){
   if(root == NILL || root == nullptr)
      return nullptr;
   if((*key) == (*root->key))
      return root;
   if((*key) < (*root->key))
      return _find(key, root->left);
   return _find(key, root->right);
}

RedBlackTree::Node *RedBlackTree::_find(AKey *key, Node *root, void *value, bool (*equals)(void *, void *)){
   if(root == NILL || root == nullptr)
      return nullptr;
   if((*key) == (*root->key)){
      if(equals(value, root->value))
         return root;
      Node *res = _find(key, root->left, value, equals);
      return res ? res : _find(key, root->right, value, equals);
   }
   if((*key) < (*root->key))
      return _find(key, root->left, value, equals);
   return _find(key, root->right, value, equals);
}

std::pair<AKey *, void *> RedBlackTree::getMax(){
   Node *r = _max(root);
   if(r == NILL || r == nullptr)
      return {nullptr, nullptr};
   return std::pair<AKey *, void *>(r->key, r->value);
}

std::pair<AKey *, void *> RedBlackTree::getMin(){
   Node *r = _min(root);
   if(r == NILL || r == nullptr)
      return {nullptr, nullptr};
   return std::pair<AKey *, void *>(r->key, r->value);
}

std::pair<AKey *, void *> RedBlackTree::removeMax(){
   Node *r = _max(root);
   if(r == NILL || r == nullptr)
      return {nullptr, nullptr};
   _size--;
   Node *removed = _remove(r);
   std::pair<AKey *, void *> res = {removed->key, removed->value};
   delete removed;
   return res;
}

std::pair<AKey *, void *> RedBlackTree::removeMin(){
   Node *r = _min(root);
   if(r == NILL || r == nullptr)
      return {nullptr, nullptr};
   _size--;
   Node *removed = _remove(r);
   std::pair<AKey *, void *> res = {removed->key, removed->value};
   delete removed;
   return res;
}

RedBlackTree::Node *RedBlackTree::_max(Node *root){
   if(!root || root == NILL)
      return nullptr;
   return root->right == NILL ? root : _max(root->right);
}

RedBlackTree::Node *RedBlackTree::_min(Node *root){
   if(!root || root == NILL)
      return nullptr;
   return root->left == NILL ? root : _min(root->left);
}

void *RedBlackTree::remove(AKey *key){
   Node *rm = _find(key, root);
   if(!rm)
      return nullptr;
   _size--;
   Node *removed = _remove(rm);
   void *res = removed->value;
   if(removed == root)
      root = nullptr;
   delete removed;
   return res;
}

void *RedBlackTree::remove(AKey *key, void *value, bool (*equals)(void *, void *)){
   Node *rm = _find(key, root, value, equals);
   if(!rm)
      return nullptr;
   _size--;
   Node *removed = _remove(rm);
   void *res = removed->value;
   if(removed == root)
      root = nullptr;
   delete removed;
   return res;
}

RedBlackTree::Node *RedBlackTree::_remove(Node *toRemove){
   if(toRemove == root && root->right == NILL && root->left == NILL){
      root = nullptr;
      return toRemove;
   }
   if(toRemove->color == Color::RED)
      return _removeRed(toRemove);
   return _removeBlack(toRemove);
}

RedBlackTree::Node *RedBlackTree::_removeRed(Node *red){
   //cant happen that red node has no parent since root is always black
   if(red->right == NILL && red->left == NILL){
      if(red == red->parent->left)
         red->parent->left = NILL;
      else
         red->parent->right = NILL;
      red->left = red->right = nullptr;
      return red;
   }
   //cant happen that red node have one NILL child
   Node *l = _max(red->left);
   swapContent(l, red);
   if(l->color == Color::RED)
      return _removeRed(l);
   return _removeBlack(l);
}

RedBlackTree::Node *RedBlackTree::_removeBlack(Node *black){
   if(black->right != NILL && black->left != NILL){
      Node *l = _max(black->left);
      swapContent(black, l);
      if(l->color == Color::RED)
         return _removeRed(l);
      return _removeBlack(l);
   }
   if(black->right != NILL){
      swapContent(black, black->right);
      return _removeRed(black->right);
   }
   if(black->left != NILL){
      swapContent(black, black->left);
      return _removeRed(black->left);
   }
   //?
   if(black != NILL && black->parent == nullptr){
      return root;
   }
   Node *parent = black->parent;
   black->parent = nullptr;
   if(parent->right == black)
      parent->right = NILL;
   else
      parent->left = NILL;
   balance(parent, NILL);
   return black;
}

void RedBlackTree::balance(Node *pt, Node *ub){
   Node *left = pt->left, *right = pt->right;
   if(ub->color == RED){
      ub->color = BLACK;
      return;
   }
   if(right == ub){
      if(pt->color == RED){//1
         if(left->left->color == BLACK && left->right->color == BLACK){//1.1
            left->color = RED;
            pt->color = BLACK;
            return;
         }
         if(left->left->color == RED){//1.2 1.3
            pt->color = BLACK;
            left->color = RED;
            left->left->color = BLACK;
            rotateRight(pt);
            return;
         }
         if(left->right->color == RED){//1.4
            pt->color = BLACK;
            rotateLeft(left);
            rotateRight(pt);
            return;
         }
      }
      //2
      if(left->color == RED){
         if(left->right->left->color == BLACK && left->right->right->color == BLACK){//2.1.1
            left->right->color = RED;
            left->color = BLACK;
            rotateRight(pt);
            return;
         }
         //2 recursive
         Node *one = left->right->left;
         rotateLeft(left);
         rotateRight(pt);
         if(one->color == RED){
            one->color = BLACK;
            return;
         }
         balance(left, one);
         return;
      }
      //2.2
      if(left->left->color == RED){
         left->left->color = BLACK;
         rotateRight(pt);
         return;
      }
      //2.2.1
      if(left->right->color == RED){
         left->right->color = BLACK;
         rotateLeft(left);
         rotateRight(pt);
         return;
      }
      left->color = RED;
      if(pt == root)
         return;
      balance(pt->parent, pt);
      return;
   }
   if(left == ub){
      if(pt->color == RED){//1
         if(right->left->color == BLACK && right->right->color == BLACK){//1.1
            right->color = RED;
            pt->color = BLACK;
            return;
         }
         if(right->right->color == RED){//1.2 1.3
            pt->color = BLACK;
            right->color = RED;
            right->right->color = BLACK;
            rotateLeft(pt);
            return;
         }
         if(right->left->color == RED){//1.4
            pt->color = BLACK;
            rotateRight(right);
            rotateLeft(pt);
            return;
         }
      }
      //2
      if(right->color == RED){
         if(right->left->right->color == BLACK && right->left->left->color == BLACK){//2.1.1
            right->left->color = RED;
            right->color = BLACK;
            rotateLeft(pt);
            return;
         }
         //2 recursive
         Node *one = right->left->right;
         rotateRight(right);
         rotateLeft(pt);
         if(one->color == RED){
            one->color = BLACK;
            return;
         }
         balance(right, one);
         return;
      }
      //2.2
      if(right->right->color == RED){
         right->right->color = BLACK;
         rotateLeft(pt);
         return;
      }
      //2.2.1
      if(right->left->color == RED){
         right->left->color = BLACK;
         rotateRight(right);
         rotateLeft(pt);
         return;
      }
      right->color = RED;
      if(pt == root)
         return;
      balance(pt->parent, pt);
      return;
   }
}

RedBlackTree::Node *RedBlackTree::grandParent(Node *current){
   if(current)
      if(current->parent)
         return current->parent->parent;
   return nullptr;
}

RedBlackTree::Node *RedBlackTree::uncle(Node *current){
   Node *gp = grandParent(current);
   if(!gp)
      return nullptr;
   if(gp->right == current->parent)
      return gp->left;
   return gp->right;
}

RedBlackTree::Node *RedBlackTree::sibling(Node *current){
   if(!current->parent)
      return nullptr;
   if(current == current->parent->left)
      return current->parent->right;
   return current->parent->left;
}

void RedBlackTree::rotateLeft(Node *current){
   if(current == NILL)
      return;
   Node *pivot = current->right;
   if(current->parent != nullptr)
      pivot->parent = current->parent;
   else{
      pivot->parent = nullptr;
      root = pivot;
   }
   if(current->parent != nullptr){
      if(current->parent->left == current)
         current->parent->left = pivot;
      else
         current->parent->right = pivot;
   }

   current->right = pivot->left;
   if(pivot->left != NILL) pivot->left->parent = current;
   current->parent = pivot;
   pivot->left = current;
   if(current == root)
      root = pivot;
}

void RedBlackTree::rotateRight(Node *current){
   if(current == NILL)
      return;
   Node *pivot = current->left;  // choose pivot left from current
   /*Connect pivot with parent:*/
   if(current->parent != nullptr)
      pivot->parent = current->parent;
   else{
      pivot->parent = nullptr;
      root = pivot;
   }
   if(current->parent != nullptr){
      if(current->parent->left == current)
         current->parent->left = pivot;
      else
         current->parent->right = pivot;
   }
   /*end if pivot-parent connection*/
   /*connection node from the right of pivot to become left from current and
    * create space for current in pivot's right*/
   current->left = pivot->right;
   if(pivot->right != NILL) pivot->right->parent = current;
   /*end of space creation*/
   /*connect current as right child of pivot*/
   current->parent = pivot;
   pivot->right = current;
   if(current == root)
      root = pivot;
}

void RedBlackTree::swapContent(Node *l, Node *r){
   void *tmpv = l->value;
   AKey *tmpk = l->key;
   l->value = r->value;
   l->key = r->key;
   r->value = tmpv;
   r->key = tmpk;
}