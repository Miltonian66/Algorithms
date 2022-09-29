#include "Hash.h"
#include "Commands/BeginHash.h"
#include "Commands/EndHash.h"
#include "Commands/HashNextCharacter.h"
#include "Commands/HashIncreasePower.h"

Hash::Hash(CommandReceiver& commandReceiver) : commandReceiver(commandReceiver) {}

std::size_t Hash::operator()(std::string source) {
	commandReceiver.addCommand(new BeginHash(source));
	size_t result = 0, power = 1;
	for (size_t i = 0; i < source.length(); i++) {
		size_t before = result;
		result += power * (size_t)(source[i]);
		commandReceiver.addCommand(new HashNextCharacter({ source[i], i, power, before, result }));
		//IncreasePower(power, base);
		commandReceiver.addCommand(new HashIncreasePower(power, power * base, base));
		power *= base;
	}

	commandReceiver.addCommand(new EndHash(result));
	return result;
}
