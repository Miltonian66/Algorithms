#pragma once
#include <CommandFramework/ACommand.h>
class EndHash : public ACommand {
private:
	std::size_t result;
public:
	std::string getType() override;
	std::size_t getResult();
	EndHash(std::size_t result);
};

