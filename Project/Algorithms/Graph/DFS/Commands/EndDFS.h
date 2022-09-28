#pragma once
#include <CommandFramework/ACommand.h>
#include <vector>

class EndDFS : public ACommand {
private:
	std::vector<bool> result;
public:
	std::string getType() override;
	std::vector<bool> getResult();
	EndDFS(std::vector<bool>const& result);
};