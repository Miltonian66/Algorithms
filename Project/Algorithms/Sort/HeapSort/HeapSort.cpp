#include "HeapSort.h"

inline void swap(Comparable *l, Comparable *r, size_t elemSize){
   char *cl = (char *) l, *cr = (char *) r;
   size_t sz = elemSize * sizeof(Comparable);
   char tmp;
   for(size_t i = 0; i < sz; i++){
      tmp = *(cl + i);
      *(cl + i) = *(cr + i);
      *(cr + i) = tmp;
   }
}

inline Comparable *max(Comparable *l, Comparable *r){
   if(*l < *r)
      return r;
   return l;
}

HeapSort::HeapSort(CommandReceiver &receiver) : receiver(receiver){}

void HeapSort::operator()(Comparable *begin, Comparable *end, size_t elemSize){
   elemSize /= sizeof(Comparable);
   size_t size = (end - begin) / elemSize;
   if(size <= 1)
      return;
   makeTree(begin, end, size, elemSize);
   for(size_t i = size - 1;; i--){
      swap(begin, begin + i * elemSize, elemSize);
      bubbleDown(begin, begin, begin + i * elemSize, elemSize);
      if(i == 1)
         break;
   }
}

void HeapSort::makeTree(Comparable *begin, Comparable *end, size_t size, size_t elemSize){
   size_t r = size - 1 - ((size - 1) % 2);
   if(r != size - 1){
      if(*(begin + ((r) / 2) * elemSize) < *(begin + (r + 1) * elemSize))
         swap((begin + (r / 2) * elemSize), (begin + (r + 1) * elemSize), elemSize);
   }
   for(size_t i = r; i > 0; i-=2){
      size_t p = i / 2 - 1;
      if(*(begin + p * elemSize) < *max(begin + i * elemSize, begin + (i - 1) * elemSize)){
         bubbleDown(begin + p * elemSize, begin, end, elemSize);
      }
   }
}

void HeapSort::bubbleDown(Comparable *cur, Comparable *begin, Comparable *end, size_t elemSize){
   size_t i = (cur - begin) / elemSize;
   if(begin + (2 * i + 1) * elemSize >= end)
      return;
   if(begin + (2 * i + 2) * elemSize >= end){
      if(*cur < *(begin + (2 * i + 1) * elemSize))
         swap(cur, begin + (2 * i + 1) * elemSize, elemSize);
      return;
   }
   Comparable *mx = max(begin + (2 * i + 2) * elemSize, begin + (2 * i + 1) * elemSize);
   if(*cur < *mx){
      swap(cur, mx, elemSize);
      bubbleDown(mx, begin, end, elemSize);
   }
}




