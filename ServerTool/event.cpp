#include "stdafx.h"
#include "event.h"

c_event::c_event(){m_event = CreateEvent(0, 0, 0, 0);}
//--------------------------------------------------------
c_event::~c_event(){CloseHandle(m_event);}
//--------------------------------------------------------
void c_event::signal()
{
	SetEvent(m_event);
}
//--------------------------------------------------------
void c_event::wait()
{
	WaitForSingleObject(m_event, INFINITE);
}
//--------------------------------------------------------
bool c_event::timed_wait(int ms)
{
	int r = WaitForSingleObject(m_event, ms);
	return (WAIT_TIMEOUT == r) ? false : true;
}