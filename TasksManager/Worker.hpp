#pragma once
#ifndef WORKER_HPP
#define WORKER_HPP

#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <thread>

struct Worker
{
	Worker();
	virtual ~Worker();

	void addTask(std::function<void()>);
	std::size_t countTasks() const;

private:
	std::queue<std::function<void()>> tasks_;
	std::mutex mtx_;
	std::condition_variable cv_;
	bool stopped_{ false };
	std::thread thread_;
};

#endif // !WORKER_HPP
