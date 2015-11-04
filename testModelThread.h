
#include <pthread.h>
#include <testModelJob.h>
#include <list>

class testModelSyncObj
{
public:
	testModelSyncObj();
	~testModelSyncObj();

public:
	void init() {
		pthread_mutexattr_init(&m_attr);
		pthread_mutex_init(&mutex, &m_attr);
		pthread_mutexattr_setpshared(&m_attr, PTHREAD_MUTEX_RECURSIVE_NP);
	}

	void syncStart() {
		pthread_mutex_lock(&mutex);
	}

	void syncEnd() {
		pthread_mutex_unlock(&mutex);
	}

	void destroy() {
		pthread_mutex_destroy(&mutex);
		pthread_mutexattr_destroy(&m_attr);
	}

private:
	testModelSyncObj(const testModelSyncObj &obj){};

	testModelSyncObj& operator = (const testModelSyncObj &obj){};

private:
	pthread_mutex_t mutex;
	pthread_mutexattr_t  m_attr;

};

class testModelThread
{
public:
	testModelThread();
	~testModelThread();
public:
	// void creatModelThread();
	void pushModelJob2Thread(testModelJobBase *ModelJob);
	void startModelThread();
	void stopModelThread();
	void notify();
	void join();
	void wait();
	void init();

protected:
	 static void * threadProc(void *p);
	 void setJobThreadIsQuit(bool isQuit);
	 bool getJobThreadIsQuit();

private:
	std::list<testModelJobBase *> threadJobList;
	pthread_t m_tid;
	pthread_attr_t  m_attr;
	pthread_cond_t m_cond;
	pthread_mutex_t m_mutex;
	pthread_condattr_t m_condattr; 
	bool  m_bThreadEndFlag;
	bool m_bThreadQuitFlag;
	testModelSyncObj *m_syncObj;
};