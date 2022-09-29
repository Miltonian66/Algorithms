#include "TestConfig.h"
#include <Algorithms/Util/Hash/Test.h>

int main() {
#ifdef TEST_HASH
	testHash();
#endif
}