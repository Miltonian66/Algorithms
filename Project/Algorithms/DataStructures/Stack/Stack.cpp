#include "Stack.h"

Stack::Stack(CommandReceiver &receiver) : receiver(receiver), store(new LinkedList(receiver)){}

Stack::~Stack(){
   delete store;
}

Stack &Stack::insert(void *value){
   store->insert(value);
   return *this;
}

void *Stack::top(){
   return store->getHead();
}

void *Stack::removeTop(){
   return store->removeHead();
}

Stack &Stack::forEach(std::function<void(void *)> action){
   store->forEach(action);
   return *this;
}

size_t Stack::size(){
   return store->size();
}

bool Stack::empty(){
   return store->empty();
}