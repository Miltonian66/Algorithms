#pragma once
#include <CommandFramework/CommandReceiver.h>
#include <Algorithms/Util/Hash/Hash.h>

class StringHashMap
{
private:
	CommandReceiver& receiver;
public:
	StringHashMap(CommandReceiver& commandReceiver);


}