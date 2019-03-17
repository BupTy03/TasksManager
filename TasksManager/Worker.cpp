#include "Worker.hpp"

Worker::Worker()
	: thread_(
		[this]()
		{
			while (true) {
				std::unique_lock<std::mutex> lk(mtx_); // lock
				cv_.wait(lk, [this] { return stopped_ || !tasks_.empty(); });

				if (stopped_) {
					return;
				}

				std::function<void()> tsk(std::move(tasks_.front()));
				tasks_.pop();

				lk.unlock(); // unlock

				tsk(); // execute task;
			}
		}
	)
{}

Worker::~Worker()
{
	{
		std::lock_guard<std::mutex> lk(mtx_);
		stopped_ = true;
		cv_.notify_all();
	}

	if (thread_.joinable()) {
		thread_.join();
	}
}

void Worker::addTask(std::function<void()> f)
{
	std::unique_lock<std::mutex> lk(mtx_);

	const bool empty = tasks_.empty();
	tasks_.push(std::move(f));

	if (empty) {
		cv_.notify_all();
	}
}

std::size_t Worker::countTasks() const
{
	return tasks_.size();
}
