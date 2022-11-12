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
   Node *_extract(Node *node);
   size_t _size = 0;
   CommandReceiver &receiver;
   
public:
   LinkedList(CommandReceiver &receiver);
   ~LinkedList();
   LinkedList(LinkedList &list) = delete;//need to solve CommandReceiver copy problem to allow copy
   LinkedList(LinkedList &&list) noexcept;
   LinkedList &operator=(LinkedList &&other) noexcept;
   LinkedList &operator=(const LinkedList &other) = delete;
   LinkedList &insert(void *value);//chaining
   void *removeFirst(const std::function <bool(void *)> pred);
   LinkedList removeAll(const std::function <bool(void *)> pred);//returns list of removed items
   LinkedList &forEach(const std::function <void(void *)> action);//chaining
   void *getHead();
   void *getTail();
   void *removeHead();
   void *removeTail();
   size_t size();
   bool empty();
   LinkedList &clear();//chaining
};