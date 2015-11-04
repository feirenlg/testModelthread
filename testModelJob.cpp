
#include <testModelJob.h>

testModelJobBase::testModelJobBase()
    :m_isAutoRemoveFlag(true)
{

}

bool testModelJobBase::isAutoRemove()
{
	return m_isAutoRemoveFlag;
}

void testModelJobBase::setAutoRemove(bool isAuto)
{
	m_isAutoRemoveFlag = isAuto;
}

testModelJob1::testModelJob1()
{

}

testModelJob1::~testModelJob1()
{

}

void testModelJob1::JobThreadRun()
{
	printf("testModelJob1 | JobThreadRun\n");
}

void testModelJob2::JobThreadRun()
{
	printf("testModelJob2 | JobThreadRun\n");
}
