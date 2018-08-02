#include "StdAfx.h"
#include <string>
#include <iostream>
#include <processthreadsapi.h>
#include <signal.h>
#include "Master.h"
#include <thread>
#include "WorldRunnable.h"

volatile bool gForceClose = false;
volatile bool ServerTerminated = false;

using namespace std;

#ifdef WIN32
void OnCrash(bool Terminate)
{
		TerminateThread(GetCurrentThread(), 0);

	ServerTerminated = true;
}
#endif

void Master::WaitClose()
{
	if (m_MainloopThread) {
		m_MainloopThread->join();
		delete m_MainloopThread;
		m_MainloopThread = nullptr;
	}
}


Master::~Master() {
	Finalize();
}

Master::Master(const CString&name)
{	
	m_Initialized = Initialize();
}


void Master::OpenServer()
{	
	if (m_Initialized) {

		if (!m_MainloopThread) {
			m_MainloopThread = new std::thread(
				bind(&WorldRunnable::Lunch, &sWorldRunnable)
			);			
			if (m_MainloopThread)
				SetThreadAffinityMask(m_MainloopThread->native_handle(), 2);
		}
	}
	else {
	}
}

void _OnExceptionCallback(PEXCEPTION_POINTERS exceptionInfo) {

}


bool Master::Initialize()
{
	SetConsoleOutputCP(65001);
	
	return true;
}

void Master::Finalize()
{			
}

void Master::OnStart(DWORD argc, TCHAR* argv[])
{	
	OpenServer();
}

void Master::OnStop()
{	
	TerminateServer();
	WaitClose();
	Sleep(1000);
}

void Master::Run()
{
	//sLog.outDebug("gameserver", "Run in console mode...");	
	OpenServer();
	while (!ServerTerminated)
	{
		/*sCmdDispatcher.DispatchCommands();*/
	};
	WaitClose();
	cout << "press any key to close console " << endl;
	system("pause");
}

void Master::RunAsService()
{	

}


void TerminateServer()
{
	ServerTerminated = true;	
	sWorldRunnable.Terminate();
}