#pragma once
#include <CommandFramework/CommandReceiver.h>
#include <CommandFramework/Interfaces.h>

class HeapSort{
public:
   HeapSort(CommandReceiver &receiver);
   void operator()(Comparable *begin, Comparable *end, size_t elemSize);
private:
   CommandReceiver &receiver;
   void makeTree(Comparable *begin, Comparable *end, size_t size, size_t elemSize);
   void bubbleDown(Comparable *cur, Comparable *begin, Comparable *end, size_t elemSize);
};