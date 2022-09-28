#include "BeginDFS.h"

std::string BeginDFS::getType() {
	return "BeginDFS";
}

size_t BeginDFS::getVertex() {
	return vertex;
}

BeginDFS::BeginDFS(size_t vertex) : vertex(vertex) {}