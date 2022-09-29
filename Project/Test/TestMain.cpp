#include "TestConfig.h"
#include <Algorithms/Hash/Test.h>

int main() {
#ifdef TEST_HASH
	testHash();
#endif
}