#include "BeginBFS.h"

std::string BeginBFS::getType() {
	return "BeginBFS";
}

size_t BeginBFS::getVertex() {
	return vertex;
}

BeginBFS::BeginBFS(size_t vertex) : vertex(vertex) {}