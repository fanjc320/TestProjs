#include "StdAfx.h"
#include "WorldRunnable.h"
#include <stdlib.h>
#include <time.h>
//#include <synchapi.h>
//#include <vcruntime_exception.h>
#include <thread>
#include <exception>

using namespace std;

WorldRunnable sWorldRunnable;

void WorldRunnable::Initialize()
{
	m_Running = true;
	srand(time(nullptr));
}

void WorldRunnable::Finalize()
{
}

bool WorldRunnable::StartDB()
{
	return true;
}

void WorldRunnable::StopDB()
{
}

void WorldRunnable::Open()
{
	/*UserSession::InitPacketHandlerTable();
	DBRunnable::InitPacketHandlerTable();
	sHttpRpcService.SetRemote(sWorldConfig.RpcServer.Host, sWorldConfig.RpcServer.Port);
	sHttpRpcService.Open();

	ThreadPool.Startup();*/

#ifdef SyncDB
	sDBService.Open();
	sPlayerSavingService.Open();
	sOnlineDBService.Open();
	sIDIPDBService.Open();
#else
	//ThreadPool.ExecuteTask(sDBRunnable.getSingletonPtr(), "DBRuning Thread");
#endif

	/*ThreadPool.ExecuteTask(sRedisManager.getSingletonPtr(), "RedisManager");
	ThreadPool.ExecuteTask(sRedisDBRunnable.getSingletonPtr(), "RedisDb");
	ThreadPool.ExecuteTask(sLogonManag.getSingletonPtr(), "Login Session");
	ThreadPool.ExecuteTask(sPayManager.getSingletonPtr(), "PayServer Session");
	ThreadPool.ExecuteTask(sSvrReportMgr.getSingletonPtr(), "ServerReport Thread");
	ThreadPool.ExecuteTask(sIDIPManager.getSingletonPtr(), "IDIP Thread");*/

}

void WorldRunnable::Close()
{
	m_Running = false;
}

void WorldRunnable::Monitor()
{
}

WorldRunnable::WorldRunnable()
{

}


void WorldRunnable::Run()
{
	typedef unsigned __int64 TickInt;
	TickInt a_Tick = 0;
	TickInt now = 0;
	TickInt lastexe = 0;

	while (m_Running)
	{
		Sleep(500);
		//Ã¿ÃëË¢ÐÂ
		if (time(nullptr) > lastexe)
		{
			cout << "worlrunnable Run" << endl;
			lastexe = time(nullptr) + 5;
		}

	}

}

void WorldRunnable::CloseMonitor()
{
	if (m_MonitorThread) {
		m_MonitorThread->join();
		delete m_MonitorThread;
		m_MonitorThread = nullptr;
	}
}

void WorldRunnable::Lunch()
{
	//__MainThreadID = std::this_thread::get_id();
	/*try
	{*/
	Initialize();
	Open();
	Run();
	/*}
	catch (const exception& e)
	{
		system("pause");
	}*/

	//TerminateServer();
	Close();
	Finalize();
	m_Running = false;
}

void WorldRunnable::Terminate()
{
	m_Running = false;
}

void WorldRunnable::WaitForClose()
{
	while (m_Running)
	{
		Sleep(1000);
	}
}
