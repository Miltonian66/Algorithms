#pragma once
#include <functional>
#include <CommandFramework/CommandReceiver.h>
class LinkedList{
private:
   struct Node{
      void *value = nullptr;
      Node *next = nullptr;
      Node *prev = nullptr;
   };
   Node *head = nullptr;
   Node *tail = nullptr;
   void *_remove(Node *node);
   size_t _size = 0;
   CommandReceiver &receiver;
public:
   LinkedList(CommandReceiver &receiver);
   void insert(void *value);
   void *remove(const std::function <bool(void *)> pred);
   void forEach(const std::function <void(void *)> action);
   void *getHead();
   void *getTail();
   void *removeHead();
   void *removeTail();
   size_t size();
   bool empty();
};