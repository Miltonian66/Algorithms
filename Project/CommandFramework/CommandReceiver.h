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

	CommandReceiver(CommandReceiver&& other) = delete;

	CommandReceiver(CommandReceiver& other) = delete;

	void operator=(CommandReceiver& other) = delete;

	CommandReceiver() = default;

	~CommandReceiver();
};