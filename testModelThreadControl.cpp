#include "testModelThreadControl.h"
#include "testModelJob.h"
#include "testModelSetting.h"

testModelThreadControl::testModelThreadControl()
	:m_thread(new testModelThread())

{

}

testModelThreadControl::~testModelThreadControl()
{
	if (NULL != m_thread) {
		delete m_thread;
		m_thread = NULL;
	}
}

void testModelThreadControl::onInit()
{
	m_thread->init();
}

void testModelThreadControl::onStart()
{
	m_thread->startModelThread();
	m_stepType = TestModel_step_1;
}

void testModelThreadControl::onStop()
{

}

void testModelThreadControl::onDestroy()
{

}

void testModelThreadControl::enterLoop()
{
	bool loopStatus = testModelSetting::instance()->getStatus();
	while(loopStatus) {
		switch(m_stepType) {
			case TestModel_step_1:
			{
				if (1) {
					testModelJob1* Job1 = new testModelJob1();
					m_thread->pushModelJob2Thread(Job1);
					m_stepType = step_2;
				}
				break;
			}
			case TestModel_step_2:
			{
				if (1) {
					testModelJob2* Job2 = new testModelJob2();
					m_thread->pushModelJob2Thread(Job2);
					m_stepType = step_3;
				}
				break;
			}
			case TestModel_step_3:
			{
				if (0) {

				}
				break;
			}
			default:
			    break;

		}
		loopStatus = testModelSetting::instance()->getStatus();
	}
}
