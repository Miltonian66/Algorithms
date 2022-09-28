#pragma once
#include <string>
#include <vector>
#include <map>
#include "AListener.h"

class CommandReceiver {
private:
	std::vector<ACommand*> commands;
	std::map<std::string, AListener*> listeners;

public:
	//~CommandReceiver();//todo remove commands and listeners
	void addListener(std::string key, AListener* listener);

	void removeListener(std::string key);

	void addCommand(ACommand* command);
};