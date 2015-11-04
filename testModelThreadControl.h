#include "testModelThread.h"
#include "testModelDefine.h"

class testModeThreadControl
{
public:
	testModeThreadControl()
	~testModeThreadControl();

public:
	void onInit();
	void onStart();
	void onStop();
	void onDestroy();
	void enterLoop();

private:
	testModelThread *m_thread;
	TestModelStepType m_stepType;
};