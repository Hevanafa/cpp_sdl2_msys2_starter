#include "panic.hpp"

void panicHalt(std::string msg) {
	printf("%s\n", msg.c_str());
	exit(1);
}
