#include "Worker.hpp"

#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
	Worker w;

	w.addTask([]() {
		for (int i = 0; i < 10; ++i) {
			std::cout << "Hello\n";
		}
	});

	w.addTask([]() {
		for (int i = 0; i < 10; ++i) {
			std::cout << "world!\n";
		}
	});

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(10s);

	return 0;
}