#include <keyboard/Flasher.h>

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>

namespace calibrate {

void runCalibration()
{
	using namespace std::chrono_literals;

	static const std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
	static const keyboard::DurationMs duration = 500;
	
	keyboard::Flasher flasher;
	std::this_thread::sleep_for(1s);

	std::for_each(alphabet.begin(), alphabet.end(), [&](const char ch) {
		keyboard::KeyNum key = ch;

		flasher.flashKey(key, duration);

		std::this_thread::sleep_for(std::chrono::milliseconds(duration*2));
	});
}

}