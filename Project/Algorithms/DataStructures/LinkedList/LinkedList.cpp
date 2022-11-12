#include "LinkedList.h"
#include <stdexcept>

LinkedList::LinkedList(CommandReceiver &receiver) : receiver(receiver){}

LinkedList::~LinkedList(){
   clear();
}

LinkedList::LinkedList(LinkedList &&list) noexcept : receiver(list.receiver){
   head = list.head;
   tail = list.tail;
   _size = list._size;
   list.head = list.tail = nullptr;
   list._size = 0;
}

LinkedList &LinkedList::operator=(LinkedList &&other) noexcept{
   if(_size != 0)//can not assign to non-empty list - user need to handle clearing first
      return *this;
   head = other.head;
   tail = other.tail;
   _size = other._size;
   other._size = 0;
   other.head = other.tail = nullptr;
   return *this;
}

bool LinkedList::empty(){
   return !_size;
}

size_t LinkedList::size(){
   return _size;
}

LinkedList &LinkedList::clear(){
   Node *current = head;
   while(current){
      Node *next = current->next;
      delete current;
      current = next;
   }
   _size = 0;
   head = tail = nullptr;
   return *this;
}

LinkedList &LinkedList::insert(void *value){
   Node *newValue = new Node();
   newValue->value = value;
   newValue->next = head;
   if(head)
      head->prev = newValue;
   else
      tail = newValue;
   head = newValue;
   _size++;
   return *this;
}

void *LinkedList::removeFirst(const std::function <bool(void *)> pred){
   Node *current = head;
   while(current){
      if(pred(current->value))
         return(_remove(current));
      current = current->next;
   }
   return(nullptr);
}

LinkedList LinkedList::removeAll(const std::function <bool(void *)> pred){
   Node *current = head;
   LinkedList result(receiver);
   while(current){
      Node *nxt = current->next;
      if(pred(current->value)){
         Node *tmp = _extract(current);
         tmp->next = result.head;
         if(!result.tail)
            result.tail = tmp;
         if(result.head)
            result.head->prev = tmp;
         result.head = tmp;
         result._size++;
      }
      current = nxt;
   }
   return result;
}

LinkedList::Node *LinkedList::_extract(Node *node){
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
   node->prev = node->next = nullptr;
   _size--;
   return node;
}

void *LinkedList::_remove(Node *node){
   node = _extract(node);
   if(!node)
      return nullptr;
   void *value = node->value;
   delete node;
   return value;
}

LinkedList &LinkedList::forEach(const std::function<void(void *)> action){
   Node *current = head;
   while(current){
      action(current->value);
      current = current->next;
   }
   return *this;
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