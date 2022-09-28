#include "CommandReceiver.h"

void CommandReceiver::addListener(std::string key, AListener* listener) {
	listeners[key] = listener;
}

void CommandReceiver::removeListener(std::string key) {
	listeners.erase(key);
}

void CommandReceiver::addCommand(ACommand* command) {
	commands.push_back(command);
	for (auto &i : listeners) {
		(*i.second)(command);
	}
}

CommandReceiver::~CommandReceiver() {
	for (auto& i : commands)
		delete i;
	for (auto& i : listeners)
		delete i.second;
}