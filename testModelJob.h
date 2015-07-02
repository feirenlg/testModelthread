

class testModelJobBase
{
public:
	testModelJobBase(){};
	virtual ~testModelJobBase(){};
public:
	virtual void  JobThreadRun();
};


class testModelJob1::public testModelJobBase
{
public:
	testModelJob1();
	virtual ~testModelJob1();	

public:
	virtual void JobThreadRun();
};

class testModelJob2::public testModelJobBase
{
public:
	testModelJob2();
	virtual ~testModelJob();

public:
	virtual void JobThreadRun();
	/* data */
};

