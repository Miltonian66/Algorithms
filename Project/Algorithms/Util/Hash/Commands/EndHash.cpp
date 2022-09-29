#include "EndHash.h"

std::string EndHash::getType() {
	return "EndHash";
}
std::size_t EndHash::getResult() {
	return result;
}

EndHash::EndHash(std::size_t result) : result(result) {};