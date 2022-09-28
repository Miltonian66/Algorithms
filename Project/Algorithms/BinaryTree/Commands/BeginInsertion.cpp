#include "BeginInsertion.h"

std::string BeginInsertion::getType() {
	return "BeginInsertion";
}

long long BeginInsertion::getKey() {
	return key;
}

BeginInsertion::BeginInsertion(long long key) : key(key) {}


