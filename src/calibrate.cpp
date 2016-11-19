#include <keyboard/Flasher.h>

#include <megaheader.h>

#include <algorithm>
#include <chrono>
#include <string>
#include <thread>



std::unordered_map<char, cv::Vec2i> calibrateKeyboard(std::string alphabet)
{
	using namespace std::chrono_literals;

	static const keyboard::DurationMs duration = 10;
	
	keyboard::Flasher flasher;
	std::this_thread::sleep_for(1s);

	std::for_each(alphabet.begin(), alphabet.end(), [&](const char ch) {
		keyboard::KeyNum key = ch;

		flasher.flashKey(key, duration);

		std::this_thread::sleep_for(std::chrono::milliseconds(duration*2));
	});

	return std::unordered_map<char, cv::Vec2i>();
}


