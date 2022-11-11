#include "LinkedList.h"

LinkedList::LinkedList(CommandReceiver &receiver) : receiver(receiver){}

bool LinkedList::empty(){
   return head;
}

size_t LinkedList::size(){
   return _size;
}

void LinkedList::insert(void *value){
   Node *newValue = new Node();
   newValue->value = value;
   newValue->next = head;
   if(head)
      head->prev = newValue;
   else
      tail = newValue;
   head = newValue;
   _size++;
}

void *LinkedList::remove(const std::function <bool(void *)> pred){
   Node *current = head;
   while(current){
      if(pred(current->value))
         return(_remove(current));
      current = current->next;
   }
   return(nullptr);
}

void *LinkedList::_remove(Node *node){
   if(!node)
      return nullptr;
   Node *prev = node->prev;
   Node *next = node->next;
   if(prev != nullptr)
      prev->next = next;
   else
      head = next;
   if(next != nullptr)
      next->prev = prev;
   else
      tail = prev;
   void *value = node->value;
   delete node;
   _size--;
   return value;
}

void LinkedList::forEach(const std::function<void(void *)> action){
   Node *current = head;
   while(current){
      action(current->value);
      current = current->next;
   }
}

void *LinkedList::getHead(){
   return head ? head->value : nullptr;
}

void *LinkedList::getTail(){
   return tail ? tail->value : nullptr;
}

void *LinkedList::removeHead(){
   return _remove(head);
}

void *LinkedList::removeTail(){
   return _remove(tail);
}