#pragma once
#include "Stack.h"
#include <iostream>

void testStack(){
   CommandReceiver receiver;
   Stack stack(receiver);
   int values[] = {0, 1, 2, 3};
   stack.insert(&values[3]).insert(&values[2]).insert(&values[1]).insert(&values[0]);
   for(size_t i = 0; i < 4; i++){
      int value = *(int *) stack.removeTop();
      if(value != i){
         std::cout << "stack test FAILED" << std::endl;
         return;
      }
   }
   std::cout << "stack test PASSED" << std::endl;
}