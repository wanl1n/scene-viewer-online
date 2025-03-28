#include "IETSemaphore.h"

IETSemaphore::IETSemaphore(int available)
{
	semaphore = new Semaphore(available);
}

IETSemaphore::~IETSemaphore()
{
	delete semaphore;
}

void IETSemaphore::acquire() const
{
	this->semaphore->acquire();
}

void IETSemaphore::acquire(int permits) const
{
	for (int i = 0; i < permits; i++)
	{
		this->semaphore->acquire();
	}
}

void IETSemaphore::release() const
{
	this->semaphore->release();
}

void IETSemaphore::release(int permits) const
{
	for (int i = 0; i < permits; i++)
	{
		this->semaphore->release();
	}
}
