#pragma once




struct ExchangeItemInfo
{
	uint16 idx;
	uint8  type;
	uint32 id;

	uint16 firstType;
	uint16 secondType;
	uint16 thirdType;
	uint8 sellable;	//�Ƿ�ɼ��ۣ�0Ϊ���ɼ���
	uint32 price;
	uint32 lowerPrice;
	uint32 uperPrice;
	uint32 bottomPrice;
	uint32 topPrice;
	uint32 showTime;	//Ϊ0����Ҫ��ʾ����
	uint32	currencyType;	//��������
};



struct ItemTypeCfg
{
	uint32 id;
	uint32 pos1;
	uint32 pos2;
	bool isEqu = false;
};

struct ItemCfg
{
	uint32 id;
	uint32 type;
};

struct ModleCfg
{
	uint32 id;
	uint32 headId;
};


enum QuestType {
	QTeach = 10,			// ��ѧ����
	QMain = 20,				// ��������
	QDaily = 30,			// ÿ������
	QBranch = 40,			// ֧������
	QZhenZhong = 50,		// ��������ģʽ
	QLoop = 60,				// ������
	QShiLian = 70,			// ð��������
	QJiaZu = 80,			// ��������
	QUndead = 90,			// �����ɧ��
	QJobJinJie = 100,		// ְҵ����
	Qmine = 120,			// �ɿ�����
	QKing = 130,			// ����ί��
	QDoubleTeam = 140,		// ����ɽ��˫����Ů��������
	QZhiYeGongHui = 150,	// ְҵ����
	QJobBranch = 160,		// ְҵ��֧����
	QQiYu = 180,			// ��������
	QPartnerJobLv = 200,	// ְҵ��֧����
	QKnightTask = 210,		// ��ʿ�ճ�
	QWeekTask = 220			// �ܳ�����
};

enum TeamType {
	TeamMain = 1,      //��������
	TeamZhenZhong = 2, //δ�ҵ����������������
	TeamDaily = 3,     //ÿ������
};

enum TeamBy : unsigned char {
	Normal = 1,			//��ͨ���
	Knight = 2,			//��ʿ�����
};

enum QuestStepType {
	QStepTalk = 1,   //�Ի�
	QStepBattle = 2, //ս��
	QStepCollect = 3, //�ɼ�
	QStepBuy = 4,     //�������
	QStepPaid = 5,      //�Ͻ�
	QStepPatrol = 6,    //Ѳ��
	QStepHit = 7,       //��ּ���  
	QStepSprite = 9,    //�ű�����
	QStepADDSKill = 10, //ѧϰ�����������
	QStepMining = 11,	//�ɿ�
	QAnswer = 12,	    //����ģʽ����
	QAnimation = 13,    //�ű�����ģʽ
	QGuide = 14,        //�����ģʽ
	QStepJobBranch = 15,		// ѡ��ְҵ��֧����ģʽ
	QItemHave = 16,	    // �������е��ߣ�װ��������Ʒ�����ԣ�
	QItemTakeOn = 17,	// ������װ����
	QItemUse = 18,	// ʹ�õ��ߣ�װ��������Ʒ�����ԣ�
	QMoveBattle = 19, //Ѱ·����ս��
	QOpenDig = 20, //�����(�ͻ��˼��)
	QMoney = 21, //��Ҽ��
	QStepHitByMap = 22,       //��ּ���(�ض���ͼ��ּ���) 
	QBattleCount = 23,		  //ս�����μ�������
	QMazeHitCount = 24,		  //�Թ���ּ���
};


struct QuestMain {
	uint32 id;
	uint32 preId;
	uint32 allowLv;
	uint32 allowJob;
	QuestType type;
	uint32 activityID;
	uint32 count;
	uint32 countType;
	uint32 limitTime;
	uint32 prizeId;
	uint32 npcId;
	uint32 isDynamicNpc;
	uint32 CanGiveUp;
	std::vector<uint32> NextIds;
	bool autoGet;
	std::string name;
	uint32 nextTaskID; //��һ������ID
};

struct QuestMonCountInfo
{
	std::string name;
	uint32 count;
};

struct QuestStepBase
{
	uint32 id;			//����ID
	uint32 stepId;	    //����
	QuestStepType type;		//��������
	uint32 para1;
	uint32 para2;
	uint32 para3;
	uint32 para4;
	uint32 para5;
	string para6;

	std::vector<QuestMonCountInfo> monIds;
	uint32 uncount;					// ��0ʱ monIds����֮��Ϊ0ʱ��QuestMonCountInfo �����ﵽ

	uint32 sendItemId;
	uint32 sendItemNum;
	uint32 recycleItemId;
	uint32 recycleItemNum;
	uint32 limitTime;	//������ʱ
	uint32 StepPrize;
	uint32 objectNpc = 0;
	bool isComboBattle = false;
};


struct QuestFinish
{
	uint32 Finishtime;  //���ʱ��
	uint32 FinishNub;   //��ɴ���
	QuestMain QuestM;
};

struct Quest
{
	QuestStepBase QuestStep;
	uint32 Taskprogress1;
	uint32 Taskprogress2;
	uint32 Taskprogress3;
	bool isfinish;
};

struct QuestWillGet
{
	QuestStepBase QuestStep;
	uint32 Tim;
	uint32 Type;
	uint32 data;
};


struct QuestRewardBase
{
	uint32 groupId;
	uint32 id;
	uint32 weight;
	uint32 prizeType;
	uint32 prizeId;
	uint32 prizeNum;
	uint32 prizeJob = 0;
	uint32 lv_min = 0;
	uint32 lv_max = 0;
	uint8  bind = 0;  //��Ʒ�Ƿ��
};

struct QuestRewardList
{
	vector<QuestRewardBase>  QuestRewards;
};

struct NpcInfo {
	uint32 id = 0;
	std::string name;
	uint32 stand;
	uint32 model;
	uint32 icon;
	uint32 mapId;
	uint32 x;
	uint32 y;
	uint32 direct;
	uint32 type;
	//uint32 fun1;
	//uint32 fun2;
	uint32 isPrivate;
	std::vector<std::string> npcTalks;
	std::string  script;
	uint32 isDynamicNpc;
	uint32 dynamicPara;
	int32 job;
	std::string GetRandTalk()
	{
		if (npcTalks.size() == 0)
			return "";
		int32 i = rand() % npcTalks.size();
		return npcTalks[i];
	}
	uint8 GetRandId()
	{
		size_t tSize = npcTalks.size();
		if (0 == tSize)
		{
			return 0;
		}
		return (uint8)(rand() % tSize);
	}
	std::string GetTalkById(uint8 id)
	{
		size_t tSize = npcTalks.size();
		if (0 == tSize || id >= (uint8)tSize)
			return "";
		return npcTalks[id];
	}

	bool IsMonster(void)
	{
		return type == (uint32)ObjectType::Monnpc || type == (uint32)ObjectType::MapBoss || type == (uint32)ObjectType::ElementMonst;
	}
};

struct MapPointInfo {
	uint32 id = 0;
	uint16 mapId=0;
	uint16 x = 0;
	uint16 y = 0;
	uint32 dest = 0;
};


struct SceneData
{
	uint32 id = 0;
	string name;
	string sceneMapName;
	MapType type = NormalMap;
	uint32 maxnumber = 0;
	uint32 timetype = 0;
	string time;
	uint32 startH = 0;
	uint32 startS = 0;
	uint32 endH = 0;
	uint32 endS = 0;

	uint32 SealLv = 0;
	uint32 SealTaskId = 0;
	uint32 SeaItemId = 0;
	uint32 SeaTitleId = 0;
	uint32 UnsealPrize = 0;
	std::string SealHint;
	uint32 AutoRecover = 1;
	bool PK_Disabled = false;
	uint32 guaji = 0;
};

typedef unordered_map<uint32, QuestStepBase> MapQuestSteps;
typedef unordered_map<uint32, MapQuestSteps> MapQuestStepsList;
typedef unordered_map<uint32, QuestMain> MapQuestMainList;
typedef unordered_map<uint32, NpcInfo> NpcList;
typedef unordered_map<uint32, SceneData> SceneMapList;
typedef vector<MapPointInfo> MapPtList;

class InstanceMgr 
{
public:
	void Load();
	 
	ItemCfg* GetItemCfg(uint32 id);
	ItemTypeCfg* GetItemTypeCfg(uint32 id);
	NpcInfo * GetNpcById(uint32 id);
	QuestStepBase * GetQuestStep(uint32 Id, uint32 astepId);
	QuestMain* GetQuestMain(uint32 Id);
	MapPointInfo* GetMapPoint(uint32 MapId);
	string GetMapNameById(uint32 id);
	ModleCfg* GetModleCfg(uint32 id);
protected:
	void LoadItemTypeCfg();
	void LoadItemCfg();
	void LoadQuestMainList();
	void LoadQuestStepsList();
	void LoadNpcsList();

	void LoadMapPointList();
	void LoadSceneMapList();

	void LoadModleNameCfg();

protected:
	//JsonBase m_json;
	std::map<uint32, ExchangeItemInfo> itemCfg;
	std::map<uint32, ExchangeItemInfo> equipmentCfg;
	std::map<uint32, ExchangeItemInfo> petCfg;

	std::map<uint32, ItemTypeCfg> mItemTypeCfg;
	std::map<uint32, ItemCfg> mItemCfg;
	std::map<uint32, ModleCfg> mMapModleCfg;

	MapQuestMainList m_QuestMainList;
	MapQuestStepsList m_MapQuestStepsList;
	NpcList   m_NpcList[1000];
	MapPtList   m_MapPointList[1000];
	SceneMapList m_sceneMapList;
};

extern InstanceMgr sInsMgr;