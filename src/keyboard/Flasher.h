#pragma once

#include <keyboard/Key.h>

namespace keyboard {
	
typedef int DurationMs;

class Flasher {
public:
	Flasher();
	virtual ~Flasher();

	void flashKey(KeyNum key, DurationMs duration);
	
};

}
