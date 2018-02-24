#pragma once


class c_event
{
private:
	HANDLE m_event;
public:
	c_event();
	virtual ~c_event();
public:
	void signal();
	void wait();
	bool timed_wait(int ms);
};