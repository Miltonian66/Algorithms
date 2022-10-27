#include "Dijkstra.h"
#include <Algorithms/DataStructures/RBTree/RedBlackTree.h>

class WeightKey : public AKey{
public:
   AWeight *weight;
   size_t nodeId;
   WeightKey(AWeight *weight, size_t nodeId) : weight(weight), nodeId(nodeId){}

   bool operator<(Comparable const &other) override{
      WeightKey const *owk = dynamic_cast<WeightKey const *>(&other);
      if(!owk)
         return false;
      return *weight < *owk->weight || *weight == *owk->weight && nodeId < owk->nodeId;
   }

   bool operator==(Equalable const &other) override{
      WeightKey const *owk = dynamic_cast<WeightKey const *>(&other);
      if(!owk)
         return false;
      return *weight == *owk->weight && nodeId == owk->nodeId;
   }

   std::string toString() override{
      return "{weight = " + weight->toString() + ", nodeId = " + std::to_string(nodeId) + "}";
   }
};

Dijkstra::Dijkstra(CommandReceiver &receiver) : receiver(receiver){}

std::vector<std::pair<AWeight *, std::vector<size_t>*>> Dijkstra::operator()(std::vector < std::vector<std::pair<AWeight *, size_t>>> &graph, size_t startId){
   RedBlackTree distQ(receiver);
   std::vector<std::pair<AWeight *, std::vector<size_t>*>> distances(graph.size());

   AWeight *infinity = graph[0][0].first->infinity();
   AWeight *zero = graph[0][0].first->zero();

   std::vector<WeightKey *> keys;
   std::vector<AWeight *> weights;
   std::vector<std::vector<size_t> *> pathes;
   for(size_t i = 0; i < graph.size(); i++){
      pathes.push_back(new std::vector<size_t>);
      distances[i] = {infinity, pathes[pathes.size() - 1]};
   }
   
   weights.push_back(zero);
   weights.push_back(infinity);
   keys.push_back(new WeightKey(zero, startId));
   std::vector<size_t> *opath = new std::vector<size_t>;
   opath->push_back(startId);
   pathes.push_back(opath);
   pathes[0]->push_back(startId);
   distQ.insert(keys[0], nullptr);//, pathes[0]);
   distances[startId] = {zero, pathes[0]};
   while(!distQ.empty()){
      auto kv = distQ.removeMin();
      WeightKey *cur = (WeightKey *) kv.first;
      //std::vector<size_t> *curPath = (std::vector<size_t> *) kv.second;
      for(size_t i = 0; i < graph[cur->nodeId].size(); i++){
         auto node = graph[cur->nodeId][i];
         weights.push_back((AWeight *) (*(cur->weight) + *(node.first)));
         if(*weights[weights.size() - 1] < *distances[node.second].first){

            keys.push_back(new WeightKey(distances[node.second].first, node.second));
            distQ.remove(keys[keys.size() - 1]);

            distances[node.second].first = weights[weights.size() - 1];
            std::vector<size_t> *newPath = new std::vector<size_t>(*distances[cur->nodeId].second);
            newPath->push_back(node.second);
            pathes.push_back(newPath);
            distances[node.second].second = newPath;

            keys.push_back(new WeightKey(distances[node.second].first, node.second));           
            distQ.insert(keys[keys.size() - 1], nullptr);
         }
      }
   }
   for(auto &x : distances){
      x.first = (AWeight *) (*x.first + *zero);
      x.second = new std::vector<size_t>(*x.second);
   }
   for(auto x : pathes){
      delete x;
   }
   for(auto x : keys){
      if(x)
         delete x;
   }
   for(auto x : weights){
      if(x)
         delete x;
   }
   return distances;
}