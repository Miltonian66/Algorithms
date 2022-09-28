#include "EndBFS.h"

std::string EndBFS::getType() {
	return "EndBFS";
}

std::vector<bool> EndBFS::getResult() {
	return result;
}

EndBFS::EndBFS(std::vector<bool> const& result) : result(result) {}