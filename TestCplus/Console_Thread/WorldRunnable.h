#pragma once

class WorldRunnable
{
private:
	std::thread *m_MonitorThread = nullptr;
	volatile bool m_Running = true;
	void Initialize();
	void Finalize();
	bool StartDB();
	void StopDB();
	void Open();
	void Close();
	void Monitor();
	void CloseMonitor();
public:
	//static std::thread::id __MainThreadID;
	WorldRunnable();
	void WaitForClose();
	void Run();
	void Lunch();
	void Terminate();
};

extern WorldRunnable sWorldRunnable;
