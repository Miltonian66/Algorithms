#pragma once
#include <CommandFramework/ACommand.h>
struct HashNextCharacterParams {
	char character;
	size_t index;
	size_t power;
	size_t before;
	size_t after;
};

class HashNextCharacter : public ACommand {
private:
	HashNextCharacterParams params;
public:
	std::string getType() override;
	HashNextCharacter(HashNextCharacterParams params);
	char getCharacter();
	size_t getIndex();
	size_t getPower();
	size_t getBefore();
	size_t getAfter();
};

