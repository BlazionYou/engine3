/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include "Thread.h"

#ifndef PLATFORM_WIN
#include <unistd.h>
#endif

#ifdef PLATFORM_MAC
#include <sched.h>
#endif

#ifdef PLATFORM_WIN
#include <process.h>
#endif

std::atomic<int> Thread::threadCounter;
UniqueReference<ThreadInitializer*> Thread::threadInitializer;

pthread_once_t Thread::initThread = PTHREAD_ONCE_INIT;

void threadDtor(void*) {

}

ThreadLocal<Thread*> Thread::currentThread(threadDtor);

void Thread::initializeThread(Thread* thread) {
	currentThread.set(thread);
}

void* Thread::executeThread(void* th) {
	Thread* impl = (Thread*) th;

	currentThread.set(impl);

	if (threadInitializer)
		threadInitializer->onThreadStart(impl);//mysql_thread_init();

	impl->run();

	if (impl->isDetached())
		delete impl;

	if (threadInitializer)
		threadInitializer->onThreadEnd(impl);//mysql_thread_end();

	return nullptr;
}

//#ifndef PLATFORM_WIN
pid_t Thread::getProcessID() {
#ifdef PLATFORM_WIN
	return _getpid();
#else
	return getpid();
#endif
}
//#endif

Thread::Thread() {
	pthread_attr_init(&attributes);

	name = "Thread " + String::valueOf(++threadCounter);
}

Thread::~Thread() {
	pthread_attr_destroy(&attributes);
}

void Thread::start() {
	pthread_create(&thread, &attributes, executeThread, this);
}

void Thread::cancel() {
	pthread_cancel(thread);
}

void Thread::kill(int signal) {
	pthread_kill(thread, signal);
}

void Thread::join() {
	if (isDetached())
		setJoinable();

	pthread_join(thread, nullptr);
}

void Thread::detach() {
	pthread_detach(thread);
}

void Thread::sleep(uint64 millis) {
	#ifndef PLATFORM_WIN
		struct timespec tm, trem;

		tm.tv_sec = (uint32) millis / 1000;
		tm.tv_nsec = (uint32) (millis % 1000) * 1000000;

		nanosleep(&tm, &trem);
	#else
		Sleep(millis);
	#endif
}

void Thread::sleep(uint64 millis, uint64 nanos) {
	#ifndef PLATFORM_WIN
		struct timespec tm, trem;

		if (millis != 0) {
			tm.tv_sec = (uint32) millis / 1000;
			tm.tv_nsec = (uint32) ((millis % 1000) * 1000000 + nanos);
		} else {
			tm.tv_sec = 0;
			tm.tv_nsec = (uint32) nanos;
		}

		nanosleep(&tm, &trem);
	#else
		//TODO find appropriate method for win32
		assert(0 && "Method not supported in windows");
		Sleep(millis);
	#endif
}

void Thread::yield() {
#ifdef PLATFORM_WIN
	SwitchToThread();
#elif defined(PLATFORM_MAC)
	sched_yield();
#else
	pthread_yield();
#endif
}

bool Thread::isDetached() {
	int state;
	pthread_attr_getdetachstate(&attributes, &state);

	return state == PTHREAD_CREATE_DETACHED;
}

Thread* Thread::getCurrentThread() {
	return currentThread.get();
}

void Thread::setDetached() {
	pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_DETACHED);
}

void Thread::setJoinable() {
	pthread_attr_setdetachstate(&attributes, PTHREAD_CREATE_JOINABLE);
}

void Thread::setSchedulingPolicy(int policy) {
	pthread_attr_setschedpolicy(&attributes, policy);
}

void Thread::assignToCPU(int cpu) {
//	Disabling this, new kernels are smart enough usually
	/*
#ifndef VERSION_PUBLIC
#ifdef PLATFORM_LINUX
	cpu_set_t cpuSet;

	CPU_ZERO(&cpuSet);
	CPU_SET(cpu, &cpuSet);

	if (sched_setaffinity(0, sizeof(cpuSet), &cpuSet) < 0) {
		perror("sched_setaffinity");
	}
#endif
#endif*/
}