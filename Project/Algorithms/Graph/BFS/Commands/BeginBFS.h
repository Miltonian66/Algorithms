#pragma once
#include <CommandFramework/ACommand.h>

class BeginBFS : public ACommand {
private:
	size_t vertex;
public:
	std::string getType() override;
	size_t getVertex();
	BeginBFS(size_t vertex);
};