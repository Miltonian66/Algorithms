#pragma once
#include <iostream>
#include "LinkedList.h"

void showLinkedList(LinkedList &list){
   std::cout << "size = " << list.size() << " { ";
   list.forEach([](void *value){std::cout << *(int *) value << "; "; });
   std::cout << "}" << std::endl;
}

void testLinkedList(){
   CommandReceiver receiver;
   LinkedList list(receiver);
   std::cout << (list.size() ? "initial size test FAILED" : "initial size test PASSED") << std::endl;
   if(list.size())
      return;
   std::cout << (list.empty() ? "initial empty test PASSED" : "initial empty test FAILED") << std::endl;
   if(!list.empty())
      return;
   int values[] = {1, 2, 3, 4, 5, 6, 7};
   for(size_t i = 0; i < 7; i++){
      list.insert(&values[i]);
      if(list.size() != i + 1){
         std::cout << "size test " << i << " FAILED" << std::endl;
         return;
      }
      std::cout << "size test " << i << " PASSED" << std::endl;
      if(*(int*)list.getHead() != values[i]){
         std::cout << "head test " << i << " FAILED" << std::endl;
         return;
      }
      std::cout << "head test " << i << " PASSED" << std::endl;
   }
   if(list.empty()){
      std::cout << "empty test after insertion FAILED" << std::endl;
      return;
   }
   std::cout << "empty test after insertion PASSED" << std::endl;
   size_t i = 0;
   bool passed = true;
   list.forEach([&i, &values, &passed](void *value){
      #ifdef SHOW_LINKED_LIST
      std::cout << "value #" << i << " is " << *(int *) value << std::endl;
      #endif
      std::cout << "order test " << i;
      if(values[6 - i] == *(int *) value){
         std::cout << " is PASSED" << std::endl;
      }
      else{
         std::cout << " is FAILED" << std::endl;
         passed = false;
      }
      i++;
                });
   std::cout << "forEach test 1 is ";
   if(passed)
       std::cout << "PASSED" << std::endl;
   else{
      std::cout << "FAILED" << std::endl;
      return;
   }
   LinkedList removed = list.removeAll([](void *value)->bool{return *(int *) value != 5; });
   #ifdef SHOW_LINKED_LIST
   std::cout << "removed: ";
   showLinkedList(removed);
   std::cout << "source: ";
   showLinkedList(list);
   #endif
   std::cout << "remove test ";
   passed = removed.forEach([&passed](void *value){
      if(*(int *) value == 5)
         passed = false;
                            }).size() == 6 && passed;
   if(!passed){
      std::cout << "is FAILED - removed list is broken" << std::endl;
      return;
   }
   if(list.size() != 1 || *(int *) list.getHead() != 5){
      std::cout << "is FAILED - source list is broken" << std::endl;
      return;
   }
   std::cout << "is PASSED" << std::endl;
   removed.clear();
   if(removed.size() != 0){
      std::cout << "clear test is FAILED" << std::endl;
      return;
   }
   std::cout << "clear test is PASSED" << std::endl;
   list.insert(&values[0]).insert(&values[1]);
   if(*(int *) list.getTail() != 5){
      std::cout << "tail test FAILED" << std::endl;
      return;
   }
   std::cout << "tail test PASSED" << std::endl;
   int tail = *(int *) list.removeTail();
   int head = *(int *) list.removeHead();
   if(tail != 5){
      std::cout << "removeTail FAILED" << std::endl;
      return;
   }
   if(head != 2){
      std::cout << "removeHead FAILED" << std::endl;
      return;
   }
   if(list.size() != 1){
      std::cout << "removeHead or removeTail failed because of size" << std::endl;
      return;
   }
   if(*(int *) list.getHead() != *(int *) list.getTail()){
      std::cout << "head of 1 element list != tail of 1 element list which is FAILED" << std::endl;
      return;
   }
   std::cout << "removeHead and removeTail PASSED" << std::endl;
   std::cout << "all tests of LINKED LIST PASSED" << std::endl;
   // removeAll returns removed list to be able to handle deletion of void*
   // designed to be something like this but it's commented since our values aren't dynamic
   //removed.forEach([](void *value){delete (int *) value; }).clear();
}