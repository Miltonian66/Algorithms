#pragma once
#include <CommandFramework/CommandReceiver.h>
#include <CommandFramework/Interfaces.h>
#include <vector>


class AWeight : public Comparable, public Equalable, public Stringable, public Additivable{
public:
   //no dynamic memory allocation required:
   virtual AWeight *infinity() = 0;
   virtual AWeight *zero() = 0;
};

class Dijkstra{
private:
   CommandReceiver &receiver;
   std::vector<AWeight *> spawnedWeights;
public:
   Dijkstra(CommandReceiver &receiver);
   std::vector<std::pair<AWeight *, std::vector<size_t>*>> operator()(std::vector < std::vector<std::pair<AWeight *, size_t>>> &graph, size_t startId);
};