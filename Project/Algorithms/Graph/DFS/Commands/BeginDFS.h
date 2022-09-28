#pragma once
#include <CommandFramework/ACommand.h>

class BeginDFS : public ACommand {
private:
	size_t vertex;
public:
	std::string getType() override;
	size_t getVertex();
	BeginDFS(size_t vertex);
};