#include "BeginHash.h"

std::string BeginHash::getType() {
	return "BeginHash";
}
std::string BeginHash::getHashSource() {
	return source;
}

BeginHash::BeginHash(std::string source) : source(source) {};