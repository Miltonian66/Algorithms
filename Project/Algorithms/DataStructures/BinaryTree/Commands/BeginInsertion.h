#pragma once
#include <CommandFramework/ACommand.h>

class BeginInsertion : public ACommand {
private:
	long long key;
public:
	std::string getType() override;

	long long getKey();

	BeginInsertion(long long key);
};