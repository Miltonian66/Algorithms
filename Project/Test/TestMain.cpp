#include "TestConfig.h"
#include <Algorithms/Util/Hash/Test.h>
#include <Algorithms/DataStructures/RBTree/Test.h>
#include <CommandFramework/Test.h>



int main() {
   #ifdef SHOW_HASH_EXAMPLE
   testHash();
   #endif

   #ifdef SHOW_INTERFACES_EXAMPLE
   interfacesExample();
   #endif

   #ifdef TEST_RBTREE
   testRBTree();
   #endif
}