#pragma once
#include <map>
#include <string>

class ACommand {
public:
	virtual std::string getType() = 0;
};