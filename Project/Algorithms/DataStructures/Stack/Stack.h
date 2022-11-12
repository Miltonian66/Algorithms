#pragma once
#include <functional>
#include <CommandFramework/CommandReceiver.h>
#include "../LinkedList/LinkedList.h"

class Stack{
private:
   CommandReceiver &receiver;
   LinkedList * const store;
public:
   Stack(CommandReceiver &receiver);
   Stack(Stack &stack) = delete;
   Stack(Stack &&stack) = delete;
   ~Stack();
   Stack &operator=(Stack &other) = delete;
   Stack &operator=(Stack &&other) = delete;
   void *top();
   void *removeTop();
   Stack &insert(void *value);
   Stack &forEach(std::function<void(void *)> action);
   size_t size();
   bool empty();
};