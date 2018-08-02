
#pragma once

class Master
{	
private:	
	std::thread *m_MainloopThread = nullptr;	
	bool m_Initialized = false;
	bool Initialize();
	void Finalize();
	void OpenServer();	
	void WaitClose();		
public:
	Master(const CString&name);
	~Master();
private:
	void OnStart(DWORD argc, TCHAR* argv[]);	
	void OnStop();
public:	
	void Run();
	void RunAsService();
};

void TerminateServer();