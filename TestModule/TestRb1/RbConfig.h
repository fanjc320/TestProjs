#pragma once

#pragma pack(push, 1)
struct MapInfo {
	short int tileHeight;
	short int splitHeight;
	short int splitWidth;
	short int mapWidth;
	short int mapHeight;
	short int x_maxcells;
	short int y_maxcells;
	int cellCount;
};

struct CellInfo {
	enum
	{
		CellMask_Walkable = 1
	};
	short int x;
	short int y;
	unsigned char attr;
};
#pragma pack(pop)

struct WorldCfg
{
	uint16 maxRobotCount;		//����������
	uint32 beginAcctNameId;		//��ʼʵ��id
	uint16 maxNumberOfLink;	    //���Ӹ�������
	uint16 linkSpace;			//���Ӽ��
};

struct RobotCfg
{
	bool  ableToReconnection;		//�������
	uint16 reconnectionSpace;		//�������
	uint16 moveSpace;
	uint16 sendMoveSpace;
	uint16 moveWave;
};

struct RobotSpeakCfg
{
	bool  ableSpeak;				//
	uint16 speakchannel;			//Ƶ��
	uint16 speakSpeed;
	string speakContent;
};

struct RobotCopyCfg
{
	bool  ableEnterCopy;				//
	uint16 mazeStyle;			//�Թ���ͼ
};

struct RobotGuildPVPCfg
{
	bool  ableEnterGuildPVP;		//
	uint16 enterMaxPeople;			//����ս�������
	uint16 maxGuildCount;			//һ����������
	bool ableActRepeat;				//���û�Ƿ��ظ�
};

struct RobotReportCfg
{
	bool  ablePerforReport;		//
	bool showPerforReport = false;
	uint32 checkPacket = 0;
};

struct RobotQuestCfg
{
	bool  ableQuest;		//
	uint32  questId;		//
	uint32  questStepId;		//
};

struct RobotTeamCfg
{
	bool  ableTeam;		//
};

struct AddItemCfg
{
	uint32 itemID;
	uint32 itemNum;
	uint32 sendPacketSpace;
};

struct RobotShopCfg
{
	bool isShop = false;
	uint32 ticket = 0;
};

struct ServerRobotCfg
{
	bool isTeam = false;
	uint32 teamNum = 0;
};

typedef std::unordered_map<uint32, string> MapNameCfg;
class StressCfg : public Singleton<StressCfg>
{
public:
	StressCfg();
	~StressCfg();
	bool LoadCfg();
	WorldCfg* GetWorldCfg() { return &m_worldCfg; }
	RobotCfg* GetRobotCfg() { return &m_robotCfg; }
	RobotSpeakCfg* GetRobotSpeakCfg() { return &m_robotSpeakCfg; }
	RobotCopyCfg* GetRobotCopyCfg() { return &m_robotCopyCfg; }
	RobotGuildPVPCfg* GetRobotGuildPvPCfg() { return &m_robotGuildPvPCfg; }
	RobotReportCfg* GetRobotReportCfg() { return &m_robotReportCfg; }
	RobotQuestCfg* GetRobotQuestCfg() { return &m_robotQuestCfg; }
	RobotTeamCfg* GetRobotTeamCfg() { return &m_robotTeamCfg; }
	RobotShopCfg& GetRobotShopCfg() { return m_RobotShopCfg; }
	ServerRobotCfg& GetServerRobotCfg() { return m_ServerRobotCfg; }
	uint32 GetDestinateMapId() { return m_destinateMapId; }
	bool GetMapInfo(uint32 mapId, MapInfo& mapInfo, vector<Coordinate>& walkCoord);
	void LoadOpenId();
	string GetOpenIdByIndex(uint32 index);
private:
	string GetMapNameByID(uint32 id);
	uint32 ConvertMapId(uint32 originalMapId);
	void LoadBaseCfg();
	bool LoacMapCfg();
private:
	WorldCfg m_worldCfg;
	RobotCfg m_robotCfg;
	RobotSpeakCfg m_robotSpeakCfg;
	RobotCopyCfg m_robotCopyCfg;
	RobotGuildPVPCfg m_robotGuildPvPCfg;
	RobotReportCfg m_robotReportCfg;
	RobotQuestCfg m_robotQuestCfg;
	RobotTeamCfg m_robotTeamCfg;
	MapNameCfg m_mapIdToNameCfg;
	uint32 m_destinateMapId;
	RobotShopCfg m_RobotShopCfg;
	ServerRobotCfg m_ServerRobotCfg;
	vector<string> m_openIdList;
};


#define sStressCfg StressCfg::getSingleton()

BOOL ParseParaString(std::vector<std::string>& vectString, const char* buf, int len, char chSeparator);