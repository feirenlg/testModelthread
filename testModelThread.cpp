#include <testModelThread.h>

testModelThread::testModelThread()
	: m_tid(0)
	, m_attr(0)
	, m_bThreadEndFlag(false)
	, m_bThreadQuitFlag(false)
	, m_syncObj(NULL)
{
	int ret = pthread_attr_init(&m_attr);

	if(0 != ret) {
	    return;
	}
}

testModelThread::~testModelThread()
{

}

void testModelThread::startModelThread()
{
	if (m_tid) {
	    join();
	}

	if(NULL == m_syncObj) {
		m_syncObj = new testModelSyncObj();
	}

	int ret = pthread_create(&m_tid, &m_attr, (void *)threadProc, this);

	if(ret != 0) {
		printf("thread create failed \n");
	}

}

void testModelThread::stopModelThread()
{
	if(!m_tid) {
	    return;
	}
	else {
	    join();
	}
	m_bThreadQuitFlag = true;
}

bool testModelThread::checkModelThreadJobEnd()
{
	if(false == m_bThreadEndFlag) {
	    return false;
	}
	return true;
}

void testModelThread::pushModelJob2Thread(testModelJobBase *ModelJob)
{
	m_syncObj.syncStart();
	m_bThreadEndFlag = false;
	threadJobList.push_back(ModelJob);
	m_syncObj.syncEnd();
}

void * testModelThread::threadProc(void * p)
{
	if(threadJobList.empty()) {
		return NULL;
	}
	if(NULL == p) {
		return NULL;
	}

	testModelJobBase *threadJob = NULL;
	m_syncObj.syncStart();
	threadJob = threadJobList.pop_front();
	m_syncObj.syncEnd();

	while(1) {

		if(p->checkModelThreadQuit()) {
			break;
		}

		if(threadJob != NULL) {
			threadJob->JobThreadRun();	
		}

		if(p->checkModelThreadJobEnd()) {
			sleep(1);
		}

		if(threadJobList.empty()) {
			m_bThreadEndFlag = true;
		}


		

	}
}

void testModelThread::join()
{
    if(!m_tid) {
        return;
    }

    int ret = pthread_join(m_tid, NULL);

    if(ret !=0) {
        return;
    }
    else {
       m_tid = 0; 
    }
}

bool testModelThread::checkModelThreadQuit()
{
	if(!m_bThreadQuitFlag) {
		return false;
	}
	return true;
}