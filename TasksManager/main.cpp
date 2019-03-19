#include "TasksManager.hpp"

#include <iostream>
#include <chrono>

int main(int argc, char* argv[])
{
	TasksManager tm(4);

	tm.addTask([]() {
		for (int i = 0; i < 1000; ++i) {
			std::cout << "Hello\n";
		}
	});

	tm.addTask([]() {
		for (int i = 0; i < 100; ++i) {
			std::cout << "world!\n";
		}
	});

	using namespace std::chrono_literals;
	std::this_thread::sleep_for(100s);

	return 0;
}