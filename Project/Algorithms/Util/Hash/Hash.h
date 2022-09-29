#pragma once
#include <CommandFramework/CommandReceiver.h>
//257 is prime > 2^8
class Hash
{
private:
	const size_t base = 257;//prime greater then 2^8
	CommandReceiver& commandReceiver;
public:
	Hash(CommandReceiver& commandReceiver);
	std::size_t operator()(std::string source);
};
