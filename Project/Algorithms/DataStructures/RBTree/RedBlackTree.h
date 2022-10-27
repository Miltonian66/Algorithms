#pragma once
#include <CommandFramework/CommandReceiver.h>
#include <CommandFramework/Interfaces.h>

//AKey meant to make user guarantee that key is comparable (<, =) and it has string view
class AKey: public Comparable, public Stringable, public Equalable{};

class RedBlackTree{
   enum Color{
      RED, BLACK
   };
   struct Node{
      AKey *key;
      void *value;
      Color color;  // = Color::RED;
      Node *right, *left, *parent;

      Node();
      Node(Node *NILL);
      Node(AKey *key, void *value, Node *NILL);
      Node(const Node &other, Node *oNILL, Node *NILL, AKey *(*copyKey)(AKey *), void *(*copyValue)(void *));
      ~Node();
   };

public:
   RedBlackTree(CommandReceiver &commandReceiver);
   RedBlackTree(const RedBlackTree &other) = delete;
   RedBlackTree(const RedBlackTree &other, AKey *(*copyKey)(AKey *), void *(*copyValue)(void *));
   ~RedBlackTree();   
   size_t size();
   bool empty();
   bool isValid();
   void insert(AKey *key, void *value);
   void *remove(AKey *key);
   void *remove(AKey *key, void *value, bool (*equals)(void *, void *));
   void *find(AKey *key);
   std::pair<AKey *, void *> getMin();
   std::pair<AKey *, void *> getMax();
   std::pair<AKey *, void *> removeMin();
   std::pair<AKey *, void *> removeMax();

private:
   CommandReceiver &commandReceiver;
   Node *const NILL = new Node();
   Node *root = nullptr;
   size_t _size = 0;

   Node *_insert(Node *root, AKey *key, void *value);
   Node *_remove(Node *toRemove);
   Node *_find(AKey *key, Node *root);
   Node *_find(AKey *key, Node *root, void *value, bool (*equals)(void *, void *));
   void checkRoot(Node *current);
   void checkParentRed(Node *current);
   void handleUncleBlack(Node *current);
   void handleUncleBlackLinear(Node *current);
   Node *_removeRed(Node *red);
   Node *_removeBlack(Node *black);
   void balance(Node *parent, Node *unbalanced);
   Node *_max(Node *root);
   Node *_min(Node *root);
   size_t _isValid(Node *current);
   Node *grandParent(Node *current);
   Node *uncle(Node *current);
   Node *sibling(Node *current);
   void rotateLeft(Node *current);
   void rotateRight(Node *current);
   void swapContent(Node *l, Node *r);
};