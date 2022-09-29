#pragma once
#include <iostream>
#include "Hash.h"
#include "Commands/BeginHash.h"
#include "Commands/EndHash.h"
#include "Commands/HashNextCharacter.h"
#include "Commands/HashIncreasePower.h"
#include <CommandFramework/AListener.h>



class HashBeginListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "BeginHash")
			return;
		BeginHash* bh = (BeginHash*)command;
		std::cout << "Begin Hash for " << bh->getHashSource() << ":\n";
	}
};

class HashEndListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "EndHash")
			return;
		EndHash* eh = (EndHash*)command;
		std::cout << "Hash calculated, result is " << eh->getResult() << ";\n\n";
	}
};

class HashUpdateListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "HashNextCharacter")
			return;
		HashNextCharacter* nh = (HashNextCharacter*)command;
		std::cout << "--Next Character added to hash: updatedHash = " << nh->getBefore() << " + ( source[" << nh->getIndex() << "] = "
			 << nh->getCharacter() << ") * " << nh->getPower() << " = " << nh->getAfter() << std::endl;
	}
};

class HashPowerListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "HashIncreasePower")
			return;
		HashIncreasePower* ip = (HashIncreasePower*)command;
		std::cout << "--Power of " << ip->getBase() << " has been increased from " << ip->getPowerBefore() << " to " << ip->getPowerAfter() << std::endl;
	}
};

int testHash() {
	CommandReceiver cr;
	cr.addListener("begin", new HashBeginListener());
	cr.addListener("end", new HashEndListener());
	cr.addListener("update", new HashUpdateListener());
	cr.addListener("pow", new HashPowerListener());
	Hash hash(cr);
	std::cout << hash("abc") << std::endl;
	return 0;
}
