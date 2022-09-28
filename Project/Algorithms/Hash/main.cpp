#include <iostream>
#include <Algorithms/Hash/Hash.h>
#include <Algorithms/Hash/Commands/BeginHash.h>
#include <Algorithms/Hash/Commands/EndHash.h>
#include <Algorithms/Hash/Commands/HashNextCharacter.h>
#include <Algorithms/Hash/Commands/HashIncreasePower.h>
#include <CommandFramework/AListener.h>

using namespace std;

class HashBeginListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "BeginHash")
			return;
		BeginHash* bh = (BeginHash*)command;
		cout << "Begin Hash for " << bh->getHashSource() << ":\n";
	}
};

class HashEndListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "EndHash")
			return;
		EndHash* eh = (EndHash*)command;
		cout << "Hash calculated, result is " << eh->getResult() << ";\n\n";
	}
};

class HashUpdateListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "HashNextCharacter")
			return;
		HashNextCharacter* nh = (HashNextCharacter*)command;
		cout << "--Next Character added to hash: updatedHash = " << nh->getBefore() << " + ( source[" << nh->getIndex() << "] = "
			 << nh->getCharacter() << ") * " << nh->getPower() << " = " << nh->getAfter() << endl;
	}
};

class HashPowerListener : public AListener {
	void operator()(ACommand* command) override {
		if (command->getType() != "HashIncreasePower")
			return;
		HashIncreasePower* ip = (HashIncreasePower*)command;
		cout << "--Power of " << ip->getBase() << " has been increased from " << ip->getPowerBefore() << " to " << ip->getPowerAfter() << endl;
	}
};

int main() {
	CommandReceiver cr;
	cr.addListener("begin", new HashBeginListener());
	cr.addListener("end", new HashEndListener());
	cr.addListener("update", new HashUpdateListener());
	cr.addListener("pow", new HashPowerListener());
	Hash hash(cr);
	cout << hash("abc") << endl;
	return 0;
}