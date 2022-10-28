#pragma once
#include "HeapSort.h"
#include <Algorithms/DataStructures/RBTree/Test.h>

void print(IntKey *begin, IntKey *end){
   #ifdef SHOW_HEAPSORT
   while(begin < end){
      std::cout << begin->toString() << ' ';
      begin++;
   }
   std::cout << std::endl;
   #endif
}

bool isCorrect(IntKey *begin, IntKey *end){
   size_t size = end - begin;
   for(size_t i = 1; i < size; i++){
      if(begin[i] < begin[i - 1])
         return false;
   }
   return true;
}

void testHeapSort(){
   IntKey keys[] = {IntKey(2), IntKey(1)};
   CommandReceiver r;
   HeapSort sort(r);
   sort(keys, keys + 2, sizeof(IntKey));
   bool res = isCorrect(keys, keys + 2);
   std::cout << "ARRAY OF 2 sort " << (res ? "passed" : "failed") << std::endl;
   if(!res)
      return;
   print(keys, keys + 2);

   IntKey moreKeys[10] = {IntKey(3), IntKey(3), IntKey(1), IntKey(7), IntKey(2), IntKey(5), IntKey(-123), IntKey(0), IntKey(121), IntKey(7)};
   sort(moreKeys, moreKeys + 10, sizeof(IntKey));
   res = isCorrect(moreKeys, moreKeys + 10);
   std::cout << "ARRAY OF 10 sort " << (res ? "passed" : "failed") << std::endl;
   if(!res)
      return;
   print(moreKeys, moreKeys + 10);
}