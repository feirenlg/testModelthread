#include <testModelThread.h>





testModelSyncObj::testModelSyncObj()
{
	init();
}

testModelSyncObj::~testModelSyncObj()
{
	destroy();
}

testModelThread::testModelThread()
	: m_tid(0)
	, m_attr(0)
	, m_bThreadEndFlag(true)
	, m_bThreadQuitFlag(false)
	, m_syncObj(NULL)
{
	
}

testModelThread::~testModelThread()
{

}

void testModelThread::init()
{
	int ret = pthread_attr_init(&m_attr);
	if(0 != ret) {
	    return;
	}

	ret = pthread_mutex_init(&m_mutex, NULL);
	if(0 != ret) {
	    return;
	}

	pthread_condattr_init(&m_condattr);

	ret = pthread_cond_init(&m_cond, &m_condattr);
	if(0 != ret) {
	    return;
	}
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
	setJobThreadIsQuit(true);
	notify();
}


void testModelThread::pushModelJob2Thread(testModelJobBase *ModelJob)
{
	m_syncObj.syncStart();
	if (!getJobThreadIsQuit()) {
	    threadJobList.push_back(ModelJob);	
	}
	notify();
	m_syncObj.syncEnd();
}

void * testModelThread::threadProc(void * p)
{
	testModelThread *thread = static_cast<testModelThread*>p;
	thread->setJobThreadIsQuit(false);

	while(!thread->getJobThreadIsQuit()){
        wait();
	    while(!threadJobList.empty()) {
	        testModelJobBase *threadJob = NULL;
	        m_syncObj.syncStart();
	        threadJob = threadJobList.front();
	        m_syncObj.syncEnd();

	        if (NULL != threadJob) {
	        	threadJob->JobThreadRun();

	        	if (threadJob->isAutoRemove()) {
	        		m_syncObj.syncStart();
	        	    threadJobList.pop_front();
	        	    m_syncObj.syncEnd();
	        		delete threadJob;
	        		threadJob = NULL;
	        	}
	        }

	        if (thread->getJobThreadIsQuit()) {
	        	break;
	        }
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

void testModelThread::wait()
{
    pthread_mutex_lock(&m_mutex);
	pthread_cond_wait(&m_cond, &mutex);
	pthread_mutex_unlock(&pthread_mutex);
}

void testModelThread::notify()
{
	pthread_mutex_lock(&m_mutex);
	pthread_cond_signal(&m_cond);
	pthread_mutex_unlock(&pthread_mutex);
}

void testModelThread::setJobThreadIsQuit(bool isQuit)
{
	m_bThreadQuitFlag = isQuit;
}

bool testModelThread::getJobThreadIsQuit()
{
	return m_bThreadQuitFlag;
}