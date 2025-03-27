#pragma once

#include <semaphore>
#include <mutex>

class IETSemaphore
{
public:
	IETSemaphore(int available);
	~IETSemaphore();

public:
	void acquire() const;
	void acquire(int permits) const;
	void release() const;
	void release(int permits) const;

private:
	const static int GLOBAL_MAX_PERMITS = 50; // set max permits to anticipated max threads

	typedef std::counting_semaphore<GLOBAL_MAX_PERMITS> Semaphore; // C++ 20 requires permits to be known during compile-time
	Semaphore* semaphore;
};

