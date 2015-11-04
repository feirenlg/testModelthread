#include "testModelSetting.h"

testModelSetting* testModelSetting::m_instance = NULL;

testModelSetting::testModelSetting()
{

}

testModelSetting::~testModelSetting()
{

}

testModelSetting* testModelSetting::instance()
{
	if (NULL == m_instance) {
		m_instance = new testModelSetting();
	}
	return m_instance;
}

void testModelSetting::destory()
{
	if (NULL != m_instance) {
		delete m_instance;
		m_instance = NULL;
	}
}

void testModelSetting::setStatus(bool status)
{
	m_bStatus = status;
}

bool testModelSetting::getStatus()
{
	return m_bStatus;
}