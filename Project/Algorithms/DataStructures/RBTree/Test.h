#include <iostream>
#include <random>
#include <algorithm>
#include "RedBlackTree.h"

//#define SHOW_DETAILED_LOG
//#define ENABLE_COPIES_FOR_DEBUG

class IntKey : public AKey{
public:
   IntKey(int key) : key(key){};
   IntKey(const IntKey &other) :key(other.key){};
   bool operator<(Comparable const &other) override{
      IntKey const *oth = dynamic_cast<IntKey const *>(&other);
      if(!oth)
         return false;
      return key < oth->key;
   }

   bool operator==(Equalable const &other) override{
      IntKey const *oth = dynamic_cast<IntKey const *>(&other);
      if(!oth)
         return false;
      return key == oth->key;
   }

   std::string toString() override{
      return std::to_string(key);
   }
   int key;   
};

void clear(std::vector<std::pair<IntKey *, void *>> &keys){
   for(auto x : keys){
      delete x.first;
      delete x.second;
   }
}

void testRBTree(){
   CommandReceiver cr;
   RedBlackTree rbtree(cr);
   std::random_device dev;
   std::mt19937 rng(dev());
   auto rng2 = std::default_random_engine{dev()};
   std::uniform_int_distribution<std::mt19937::result_type> dist(1, 6000);
   std::vector<std::pair<IntKey *, void *>> keys;
   int amount = 10000;
   int i = amount;
   int step = -1;

   while(i--){
      int key = dist(rng);
      keys.push_back({new IntKey(key), new int(key)});
      #ifdef ENABLE_COPIES_FOR_DEBUG
      RedBlackTree cpy(rbtree, [](AKey *key) -> AKey *{return new IntKey(*dynamic_cast<IntKey *>(key)); }, nullptr);
      #endif
      rbtree.insert(keys[keys.size() - 1].first, keys[keys.size() - 1].second);
      if(!rbtree.isValid()){
         #ifdef ENABLE_COPIES_FOR_DEBUG
         cpy.insert(keys[keys.size() - 1].first, keys[keys.size() - 1].second);
         #endif
         step = amount - i + 1;
         break;
      }
   }

   std::cout << "INSERTION IS " << (step == -1 ? "correct" : "failed: step " + std::to_string(step) + "\nNo reason to test removing") << std::endl;
   if(step != -1){
      clear(keys);
      return;
   }
      
   std::shuffle(keys.begin(), keys.end(), rng2);

   for(int i = 0; i < keys.size(); i++){
      #ifdef ENABLE_COPIES_FOR_DEBUG
      RedBlackTree cpy(rbtree, nullptr, nullptr);
      #endif
      rbtree.remove(keys[i].first);
      if(!rbtree.isValid()){
         #ifdef ENABLE_COPIES_FOR_DEBUG
         cpy.remove(keys[i].first);
         cpy.isValid();
         #endif
         step = i + 1;
         break;
      }
   }
   std::cout << "REMOVING IS " << (step == -1 ? "correct" : "failed: step " + std::to_string(step) + "\nNo reason to test max") << std::endl;
   if(step != -1){
      clear(keys);
      return;
   }
   for(auto i : keys){
      rbtree.insert(i.first, i.second);
   }

   sort(keys.begin(), keys.end(), 
        [](std::pair<IntKey *, void *> const &l, std::pair<IntKey *, void *> const &r){return *l.first < *r.first; });

   for(int i = keys.size() - 1; i > -1; i--){
      #ifdef ENABLE_COPIES_FOR_DEBUG
      RedBlackTree cpy(rbtree, nullptr, nullptr);
      #endif
      int *v = (int *) (rbtree.removeMax().second);
      #ifdef SHOW_DETAILED_LOG
      std::cout << i << " : " << *v << std::endl;
      #endif
      if(*v != keys[i].first->key){
         #ifdef ENABLE_COPIES_FOR_DEBUG
         cpy.removeMax();
         #endif
         std::cout << "ORDER FROM MAX failed: step " << amount - i << std::endl;
         clear(keys);
         return;
      }
   }
   std::cout << "REMOVING MAX IS " << (step == -1 ? "correct" : "failed: step " + std::to_string(step) + "\nNo reason to test min") << std::endl;
   if(step != -1){
      clear(keys);
      return;
   }

   for(auto x : keys){
      #ifdef ENABLE_COPIES_FOR_DEBUG
      RedBlackTree cpy(rbtree, nullptr, nullptr);
      #endif
      try{
         rbtree.insert(x.first, x.second);
      }
      catch(...){
         #ifdef ENABLE_COPIES_FOR_DEBUG
         cpy.insert(x.first, x.second);
         #endif
      }      
   }

   for(int i = 0; i < keys.size(); i++){
      #ifdef ENABLE_COPIES_FOR_DEBUG
      RedBlackTree cpy(rbtree, nullptr, nullptr);
      #endif
      int *v = nullptr;
      try{
         v = (int *) (rbtree.removeMin().second);
      }
      catch(...){
         #ifdef ENABLE_COPIES_FOR_DEBUG
         cpy.removeMin();
         #endif
      }
      #ifdef SHOW_DETAILED_LOG
      std::cout << i << " : " << *v << std::endl;
      #endif
      if(*v != keys[i].first->key){
         #ifdef ENABLE_COPIES_FOR_DEBUG
         cpy.removeMin();
         #endif
         std::cout << "ORDER FROM MIN failed: step " << amount - i << std::endl;
         clear(keys);
         return;
      }
   }

   std::cout << "REMOVING MIN IS " << (step == -1 ? "correct" : "failed: step " + std::to_string(step)) << std::endl;
   if(step != -1){
      clear(keys);
      return;
   };

   size_t beg = keys.size();
   keys.push_back({new IntKey(-1), new int(1)});
   keys.push_back({new IntKey(-1), new int(2)});
   for(auto x : keys){
      rbtree.insert(x.first, x.second);
   }
   auto res = rbtree.remove(keys[beg].first, keys[beg].second, [](void *l, void *r){
      int *li = (int*) (l), *ri = (int*) (r);
      return li && ri && *li == *ri;
                            });
   auto n1 = rbtree.remove(keys[beg + 1].first);
   auto n2 = rbtree.remove(keys[beg + 1].first);
   if(*(int *) res == 1 && *(int *) n1 == 2 && !n2)
      std::cout << "REMOVING BY K/V is correct" << std::endl;
   else{
      std::cout << "REMOVING BY K/V is failed" << std::endl;
      clear(keys);
      return;
   }
   std::cout << "ALL TESTS FOR RED-BLACK TREE PASSED!" << std::endl;
   clear(keys);
}