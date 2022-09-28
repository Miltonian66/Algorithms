#include "EndDFS.h"

std::string EndDFS::getType() {
	return "EndDFS";
}

std::vector<bool> EndDFS::getResult() {
	return result;
}

EndDFS::EndDFS(std::vector<bool> const& result) : result(result) {}