#include "HashNextCharacter.h"
char HashNextCharacter::getCharacter() {
	return params.character;
}
size_t HashNextCharacter::getIndex() {
	return params.index;
}
size_t HashNextCharacter::getPower() {
	return params.power;
}
size_t HashNextCharacter::getBefore() {
	return params.before;
}
size_t HashNextCharacter::getAfter() {
	return params.after;
}
std::string HashNextCharacter::getType() {
	return "HashNextCharacter";
}
HashNextCharacter::HashNextCharacter(HashNextCharacterParams params):params(params) {}

