#pragma once
#include "Dijkstra.h"
#include <iostream>

class IntWeight : public AWeight{
private:
   int weight;
   bool isInfinity = false;
public:
   IntWeight(int weight) : weight(weight){}
   bool operator<(const Comparable &other) override{
      const IntWeight *w = dynamic_cast<const IntWeight *>(&other);
      if(!w || w->isInfinity)
         return true;
      if(isInfinity)
         return false;
      return weight < w->weight;
   }
   bool operator==(const Equalable &other) override{
      const IntWeight *w = dynamic_cast<const IntWeight *>(&other);
      if(!w)
         return false;
      if(w->isInfinity && isInfinity)
         return true;
      if(w->isInfinity || isInfinity)
         return false;
      return weight == w->weight;
   }
   Additivable *operator+(const Additivable &other) override{
      const IntWeight *w = dynamic_cast<const IntWeight *>(&other);
      return (Additivable *)((w->isInfinity ? w : new IntWeight(w->weight + weight)));
   }
   std::string toString() override{
      return isInfinity ? "infinity" : std::to_string(weight);
   }
   AWeight *zero() override{
      return new IntWeight(0);
   }
   AWeight *infinity() override{
      auto res = new IntWeight(-1);
      res->isInfinity = true;
      return res;
   }
};

void makeGraph(std::vector<std::vector<std::pair<AWeight *, size_t>>> &graph, std::vector<IntWeight *> &weights);
void printResult(std::vector<std::pair<AWeight *, std::vector<size_t> *>> &distances,
                 std::vector<std::vector<std::pair<AWeight *, size_t>>> &graph);

void clear(std::vector<IntWeight *> &weights, std::vector<std::pair<AWeight *, std::vector<size_t>*>> &distances){
   for(auto x : weights){
      delete x;
   }
   for(auto x : distances){
      delete x.first;
      delete x.second;
   }
}

void showAndTestDijkstra(){
   /*graph:
   * 0: 1/5 2/2 3/11
   * 1: 0/5 2/2 3/2 5/15 6/1 7/5 8/3
   * 2: 0/2 1/2 3/9 4/12 5/5
   * 3: 0/11 1/2 2/9 5/6 6/4 7/9
   * 4: 2/12 5/2
   * 5: 1/15 2/5 3/6 4/2 6/1 8/4
   * 6: 1/1 3/4 5/1 7/1
   * 7: 1/5 3/9 6/1 8/1
   * 8: 1/3 5/4 7/1
   */
   std::vector<std::vector<std::pair<AWeight *, size_t>>> graph(9);
   std::vector<IntWeight *> weights;
   makeGraph(graph, weights);
   CommandReceiver receiver;
   Dijkstra dijkstra(receiver);
   std::vector<std::pair<AWeight *, std::vector<size_t>*>> distances = dijkstra(graph, 0);
   IntWeight exp[] = {IntWeight(0), IntWeight(4), IntWeight(2), IntWeight(6), IntWeight(8),
                      IntWeight(6), IntWeight(5), IntWeight(6), IntWeight(7)};
   std::vector<IntWeight *> expected = {exp, exp + 1, exp + 2, exp + 3, exp + 4, exp + 5, exp + 6, exp + 7, exp + 8};
   for(size_t i = 0; i < distances.size(); i++){
      if(!(*distances[i].first == *expected[i])){
         std::cout << "Dijkstra test failed" << std::endl;
         clear(weights, distances);
         return;
      }
   }
   std::cout << "Dijkstra test passed" << std::endl;
   #ifdef SHOW_DIJKSTRA
   printResult(distances, graph);
   #endif
   clear(weights, distances);
}

void printResult(std::vector<std::pair<AWeight *, std::vector<size_t>*>> &distances,
                 std::vector<std::vector<std::pair<AWeight *, size_t>>> &graph){
   for(size_t i = 0; i < distances.size(); i++){
      std::cout << "distance to vertex #" << i << " is " << distances[i].first->toString() << std::endl;
      std::cout << "path to vertex #" << i << " is:" << std::endl;
      for(size_t j = 0; j < distances[i].second->size(); j++){
         std::vector<size_t> &path = (*distances[i].second);
         std::string dist = "";
         size_t nextNode = path[j];
         if(j != 0)
            dist = std::find_if(graph[path[j - 1]].begin(), graph[path[j - 1]].end(), 
                             [nextNode](const std::pair<AWeight *, size_t> &elem) -> bool{
                                 return nextNode == elem.second;
                             })->first->toString();
         if(!(j % 4) && j)
            std::cout << "--" << std::endl;
         std::cout << (j != 0 ? "--(" + dist + ")->" : "") << path[j];         
      }
      std::cout << '\n' << std::endl;
   }
}

void makeGraph(std::vector<std::vector<std::pair<AWeight *, size_t>>> &graph, std::vector<IntWeight *> &weights){
   weights.push_back(new IntWeight(5));
   graph[0].push_back({weights[weights.size() - 1], 1});
   weights.push_back(new IntWeight(2));
   graph[0].push_back({weights[weights.size() - 1], 2});
   weights.push_back(new IntWeight(11));
   graph[0].push_back({weights[weights.size() - 1], 3});
   weights.push_back(new IntWeight(5));
   graph[1].push_back({weights[weights.size() - 1], 0});
   weights.push_back(new IntWeight(2));
   graph[1].push_back({weights[weights.size() - 1], 2});
   weights.push_back(new IntWeight(2));
   graph[1].push_back({weights[weights.size() - 1], 3});
   weights.push_back(new IntWeight(15));
   graph[1].push_back({weights[weights.size() - 1], 5});
   weights.push_back(new IntWeight(1));
   graph[1].push_back({weights[weights.size() - 1], 6});
   weights.push_back(new IntWeight(5));
   graph[1].push_back({weights[weights.size() - 1], 7});
   weights.push_back(new IntWeight(3));
   graph[1].push_back({weights[weights.size() - 1], 8});
   weights.push_back(new IntWeight(2));
   graph[2].push_back({weights[weights.size() - 1], 0});
   weights.push_back(new IntWeight(2));
   graph[2].push_back({weights[weights.size() - 1], 1});
   weights.push_back(new IntWeight(9));
   graph[2].push_back({weights[weights.size() - 1], 3});
   weights.push_back(new IntWeight(12));
   graph[2].push_back({weights[weights.size() - 1], 4});
   weights.push_back(new IntWeight(5));
   graph[2].push_back({weights[weights.size() - 1], 5});
   weights.push_back(new IntWeight(11));
   graph[3].push_back({weights[weights.size() - 1], 0});
   weights.push_back(new IntWeight(2));
   graph[3].push_back({weights[weights.size() - 1], 1});
   weights.push_back(new IntWeight(9));
   graph[3].push_back({weights[weights.size() - 1], 2});
   weights.push_back(new IntWeight(6));
   graph[3].push_back({weights[weights.size() - 1], 5});
   weights.push_back(new IntWeight(4));
   graph[3].push_back({weights[weights.size() - 1], 6});
   weights.push_back(new IntWeight(9));
   graph[3].push_back({weights[weights.size() - 1], 7});
   weights.push_back(new IntWeight(12));
   graph[4].push_back({weights[weights.size() - 1], 2}); 
   weights.push_back(new IntWeight(2));
   graph[4].push_back({weights[weights.size() - 1], 5});
   weights.push_back(new IntWeight(15));
   graph[5].push_back({weights[weights.size() - 1], 1});
   weights.push_back(new IntWeight(5));
   graph[5].push_back({weights[weights.size() - 1], 2});
   weights.push_back(new IntWeight(6));
   graph[5].push_back({weights[weights.size() - 1], 3});
   weights.push_back(new IntWeight(2));
   graph[5].push_back({weights[weights.size() - 1], 4});
   weights.push_back(new IntWeight(1));
   graph[5].push_back({weights[weights.size() - 1], 6});
   weights.push_back(new IntWeight(4));
   graph[5].push_back({weights[weights.size() - 1], 8});
   weights.push_back(new IntWeight(1));
   graph[6].push_back({weights[weights.size() - 1], 1});
   weights.push_back(new IntWeight(4));
   graph[6].push_back({weights[weights.size() - 1], 3});
   weights.push_back(new IntWeight(1));
   graph[6].push_back({weights[weights.size() - 1], 5});
   weights.push_back(new IntWeight(1));
   graph[6].push_back({weights[weights.size() - 1], 7});
   weights.push_back(new IntWeight(5));
   graph[7].push_back({weights[weights.size() - 1], 1});
   weights.push_back(new IntWeight(9));
   graph[7].push_back({weights[weights.size() - 1], 3});
   weights.push_back(new IntWeight(1));
   graph[7].push_back({weights[weights.size() - 1], 6});
   weights.push_back(new IntWeight(1));
   graph[7].push_back({weights[weights.size() - 1], 8});
   weights.push_back(new IntWeight(3));
   graph[8].push_back({weights[weights.size() - 1], 1});
   weights.push_back(new IntWeight(4));
   graph[8].push_back({weights[weights.size() - 1], 5});
   weights.push_back(new IntWeight(1));
   graph[8].push_back({weights[weights.size() - 1], 7});
}