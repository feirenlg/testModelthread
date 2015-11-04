


class testModelSetting
{
public:
	static testModelSetting* instance();
	static void destory();

public:
	void setStatus(bool status);
	bool getStatus();

private:
	testModelSetting();
	~testModelSetting();

	testModelSetting& operator =(const testModelSetting& rhs);
	testModelSetting(const testModelSetting& rhs);

private:
	static testModelSetting* m_instance;
	bool m_bStatus;



};