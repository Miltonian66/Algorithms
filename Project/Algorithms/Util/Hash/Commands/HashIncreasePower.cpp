#include "HashIncreasePower.h"

HashIncreasePower::HashIncreasePower(size_t before, size_t after, size_t base) :before(before), after(after), base(base) {}

std::string HashIncreasePower::getType() {
	return "HashIncreasePower";
}

size_t HashIncreasePower::getPowerBefore() {
	return before;
}

size_t HashIncreasePower::getPowerAfter() {
	return after;
}

size_t HashIncreasePower::getBase() {
	return base;
}