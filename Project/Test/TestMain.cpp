#include "TestConfig.h"
#include <Algorithms/Util/Hash/Test.h>
#include <Algorithms/DataStructures/RBTree/Test.h>
#include <Algorithms/Graph/Dijkstra/Test.h>
#include <Algorithms/Sort/HeapSort/Test.h>
#include <Algorithms/DataStructures/LinkedList/Test.h>
#include <Algorithms/DataStructures/Stack/Test.h>
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

   #ifdef TEST_DIJKSTRA
   showAndTestDijkstra();
   #endif

   #ifdef TEST_HEAPSORT
   testHeapSort();
   #endif

   #ifdef TEST_LINKED_LIST
   testLinkedList();
   #endif

   #ifdef TEST_STACK
   testStack();
   #endif
}