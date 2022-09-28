#pragma once
#include <CommandFramework/ACommand.h>
#include <vector>

class EndBFS : public ACommand {
private:
	std::vector<bool> result;
public:
	std::string getType() override;
	std::vector<bool> getResult();
	EndBFS(std::vector<bool>const& result);
};