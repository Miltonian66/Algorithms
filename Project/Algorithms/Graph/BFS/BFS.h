#pragma once
#include <CommandFramework/CommandReceiver.h>
#include <vector>

class BFS
{
private:
	CommandReceiver& receiver;

public:
	BFS(CommandReceiver& receiver) : receiver(receiver) {}
	/// Input:  Graph represented by adjacency matrix, starting vertex
	/// Output: Vector of traversity of vertices
	std::vector<bool> operator()(std::vector<std::vector<bool>> const& graph, size_t start);
};

