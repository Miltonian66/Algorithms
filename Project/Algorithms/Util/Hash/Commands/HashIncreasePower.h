#pragma once
#include <CommandFramework/ACommand.h>
class HashIncreasePower : public ACommand {
private:
	size_t before;
	size_t after;
	size_t base;
public:
	HashIncreasePower(size_t before, size_t after, size_t base);
	std::string getType() override;
	size_t getPowerBefore();
	size_t getPowerAfter();
	size_t getBase();
};

