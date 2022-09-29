#pragma once
#include <CommandFramework/ACommand.h>
class BeginHash : public ACommand{
private:
	std::string source;
public:
	std::string getType() override;//return "BeginHash"
	std::string getHashSource();
	BeginHash(std::string source);
};