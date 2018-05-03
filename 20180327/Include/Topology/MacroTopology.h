#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MacroDefineEx.h"
#include "Date.h"
#include "RandomPack.h"

NS_TOOL_FRAME_BEGIN

//����ID
struct XTopologyID
{
	uint16	uGtID;		//���ط�����ID
	uint32	uID;		//���ط����ID
	uint32	uUserID;	//�û��Լ���ID

	XTopologyID(){
		uGtID	= INVALID_ID;
		uID		= INVALID_ID;
		uUserID	= INVALID_ID;
	}
	XTopologyID(uint16 uServerID,uint uAssID){
		uGtID	= uServerID;
		uID		= uAssID;
		uUserID	= INVALID_ID;
	}
	//�����ж��Ƿ���ʱID�Ƿ�һ��
	bool operator<(const XTopologyID& other)const{
		if (uGtID != other.uGtID)
			return uGtID < other.uGtID;

		return uID < other.uID;
	}

	bool operator == (const XTopologyID& other)const
	{
		return uGtID == other.uGtID && uID == other.uID;
	}

	bool operator != (const XTopologyID& other)const
	{
		return !(*this == other);
	}

	//��ȫ���
	bool IsEqual(const XTopologyID& other )const
	{
		if (uGtID != other.uGtID || uID != other.uID)return false;
		if (INVALID_ID != uUserID && uUserID != other.uUserID)return false;
		return true;
	}
};

const static XTopologyID TOPOLOGY_ID_INVAILD;//��Ч����ID

typedef std::vector<XTopologyID> VectorTopologyID;

SERIALIZE_DECLARE(XTopologyID);


//������ʽ
enum ERunType{
	RUN_TYPE_INVAILD=0,
	RUN_TYPE_RANDOM,		//���
	RUN_TYPE_HASH,			//��ϣ
	RUN_TYPE_UNIQUE,		//Ψһ
	RUN_TYPE_BALANCE,		//ƽ��
	RUN_TYPE_SEQUENCE,		//˳��
	RUN_TYPE_MAX,
};

//�ͻ�������
enum EClientType{
	CLIENT_TYPE_INVAILD,
	CLIENT_TYPE_PHYSICAL,	//���������
	CLIENT_TYPE_LOGIC,		//�߼�������
	CLIENT_TYPE_CONTROL,	//���ƶ�
	CLIENT_TYPE_MAX,
};

//������״̬
enum EServerConnectState
{
	CONNECT_STATE_INVAILD=0,

	CONNECT_STATE_INIT,			//��ʼ����
	CONNECT_STATE_NORMAL,		//����״̬
	CONNECT_STATE_STOP_SERVICE,	//ֹͣ����
	CONNECT_STATE_OFFLINE,		//����

	CONNECT_STATE_MAX,
};

//�����߼������� 
struct XConfigLogic{
	uint8		eSrvType;		//����������
	uint8		eRunType;		//���з�ʽ
	uint8		uThread;		//�߳���(���)
	uint16		uRunOnce;		//����ִ��ʱ�� ����(���)
	uint32		uTimeInterval;	//�㱨ʱ����(����)
	uint8		uHashCount;		//��ϣ��
	std::string sExePath;		//Exe·��
	std::string sWorkingDir;	//����Ŀ¼
	uint32		uRecvSize;		//���ջ���ش�С
	uint32		uSendSize;		//���ͻ���ش�С
	uint32		uBlockSize;		//����ص��η����С
	uint16		uSaveTime;		//����ʱ��

	uint32		uPublicRecv;	//���� ���ջ���ش�С
	uint32		uPublicSend;	//���� ���ͻ���ش�С
	uint32		uPublicBlock;	//���� ����ص��η����С
	
	std::string sRemark;		//��ע

	XConfigLogic(){
		eSrvType		= INVALID_ID;
		eRunType		= INVALID_ID;
		uThread			= 0;
		uRunOnce		= 0;
		uTimeInterval	= 0;
		uHashCount		= 0;
		uRecvSize		= 0;
		uSendSize		= 0;
		uSaveTime		= 0;
		uPublicRecv		= 0;
		uPublicSend		= 0;
		uPublicBlock	= 0;
	}
};

//�����߼�����
struct XConfigLink{
	uint8 eSrcSrv;//ESrvType	��ʼ���ӷ���������
	uint8 eDesSrv;//ESrvType	Ŀ�����ӷ���������
	uint8 uCount;//������

	bool operator < (const XConfigLink& t)const{
		if (eSrcSrv == t.eSrcSrv)
			return eDesSrv<t.eDesSrv;

		return eSrcSrv < t.eSrcSrv;
	}
};

//���˷�����
struct XConfigServer{
	uint32			uPhysicalID;	//���������ID
	uint32			uServerID;		//������ID
	uint8			eSrvType;		//����������
	uint16			uPort;			//�˿�
	VectorUint16	vPublicPort;	//���Ŷ˿�
	int16			uPublicConnect;	//���� ������
	uint8			uHash;			//��ϣֵ
	std::string		sCommand;		//�Զ�������

	XConfigServer(){
		uPhysicalID		= INVALID_ID;
		uServerID		= INVALID_ID;
		eSrvType		= INVALID_ID;
		uPort			= 0;
		uPublicConnect	= 0;
		uHash			= 0;
	}
};

//�����������Ϣ
struct XPhysicalUpdate
{
	uint8		eState;				//״̬
	uint8		uCpuUsage;			//CPUռ����
	uint64		uMemoryUsed;		//�ڴ�ʹ����
	uint64		uMemoryFree;		//�ڴ�ʣ����
	uint8		uMemoryUsage;		//�ڴ�ʹ����
	uint32		uSendBytes;			//�����ֽ���
	uint32		uRecvBytes;			//�����ֽ���
	uint32		uSystemCleanUp;		//�������ʱ��

	XPhysicalUpdate(){
		eState			= 0;
		uCpuUsage		= 0;
		uMemoryUsed		= 0;
		uMemoryFree		= 0;
		uMemoryUsage	= 0;
		uSendBytes		= 0;
		uRecvBytes		= 0;
		uSystemCleanUp	= 0;
	}
};

struct XLogicUpdate
{
	uint8	eState;			//״̬
	uint32	uTimeReport;	//�㱨ʱ��
	uint16	uTimeRunOnce;	//����ִ��ʱ��
	uint16	uTimeRunOnceMax;//����ִ��ʱ�� ��ֵ
	uint32	uCacheVaild;	//��Ч����
	uint32	uCacheTotal;	//�ܻ���
	uint32	uProcesserCount;//��������
	uint32	uQueueProcess;	//�߼�����
	uint64	uCpuUseTime;	//CPUʹ��ʱ��
	uint8	uCpuUsage;		//CPUʹ����
	uint64	uMemoryUsed;	//�ڴ�ռ��
	uint8	uThreads;		//�߳���
	uint32	nSessionNum;	//�Ự��
	uint32	nPacketProcess;	//�������
	uint32	nLogicProcess;	//�߼��������
	uint32	nNetProcess;	//���紦�����
	uint32	nLogicCmd;		//�߼�����
	uint32	nNetCmd;		//�������
	uint32	uSendBytes;		//�����ֽ���
	uint32	uRecvBytes;		//�����ֽ���
	uint32	uFreeTime;		//����ʱ��(����)
	uint32	uTimeSave;		//�������ʱ��
	uint32	uTimeCleanUp;	//�������ʱ��
	uint32	uSystemCleanUp;	//ϵͳ����

	uint32	uProcessMax;	//��������ʱ�� ��ֵ
	uint32	uProcessAvg;	//��������ʱ�� ��ֵ

	uint32	uTimeSendMax;	//����ʱ�� ��ֵ
	uint32	uTimeSendAvg;	//����ʱ�� ��ֵ

	uint32	uTimeSendingMax;//������ʱ�� ��ֵ
	uint32	uTimeSendingAvg;//������ʱ�� ��ֵ

	XLogicUpdate(){
		eState			= 0;	//״̬
		uTimeReport		= 0;	//�㱨ʱ��
		uTimeRunOnce	= 0;	//����ִ��ʱ��
		uTimeRunOnceMax = 0;	//����ִ��ʱ�� ��ֵ
		uCacheVaild		= 0;	//��Ч����
		uCacheTotal		= 0;	//�ܻ���
		uProcesserCount = 0;	//��������
		uQueueProcess	= 0;	//�߼�����
		uCpuUseTime		= 0;	//CPUʹ��ʱ��
		uCpuUsage		= 0;	//CPUʹ����
		uMemoryUsed		= 0;	//�ڴ�ռ��
		uThreads		= 0;	//�߳���
		nSessionNum		= 0;	//�Ự��
		nPacketProcess	= 0;	//�������
		nLogicProcess	= 0;	//�߼��������
		nNetProcess		= 0;	//���紦�����
		nLogicCmd		= 0;	//�߼�����
		nNetCmd			= 0;	//�������
		uSendBytes		= 0;	//�����ֽ���
		uRecvBytes		= 0;	//�����ֽ���
		uFreeTime		= 0;	//����ʱ��
		uTimeSave		= 0;	//�������ʱ��
		uTimeCleanUp	= 0;	//�������ʱ��
		uSystemCleanUp	= 0;	//ϵͳ����

		uProcessMax		= 0;	//��������ʱ�� ��ֵ
		uProcessAvg		= 0;	//��������ʱ�� ��ֵ

		uTimeSendMax	= 0;	//����ʱ�� ��ֵ
		uTimeSendAvg	= 0;	//����ʱ�� ��ֵ

		uTimeSendingMax	= 0;	//������ʱ�� ��ֵ
		uTimeSendingAvg	= 0;	//������ʱ�� ��ֵ
	}
};

//�߼���������Ϣ
struct XServerLogic{
	uint32			uServerID;
	uint8			eSrvType;
	uint32			uTimeStartUp;
	uint16			uReconnect;		//��������
	XLogicUpdate	xUpdate;

	bool			bUpdated;
	std::string		sDebugString;
	uint			uClientID;		//ClientID

	mutable CMutexReadWrite mutex;

	XServerLogic(){
		uServerID		= INVALID_ID;
		eSrvType		= 0;
		uTimeStartUp	= 0;
		uReconnect		= 0;

		bUpdated		= false;
		uClientID		= INVALID_ID;
	}

	XServerLogic(const XServerLogic& xLogic){
		*this = xLogic;
	}

	bool operator = (const XServerLogic& xLogic){
		uServerID		= xLogic.uServerID;
		eSrvType		= xLogic.eSrvType;
		uTimeStartUp	= xLogic.uTimeStartUp;
		uReconnect		= xLogic.uReconnect;
		xUpdate			= xLogic.xUpdate;
		bUpdated		= xLogic.bUpdated;
		uClientID		= xLogic.uClientID;
		return true;
	}
};

//�����������Ϣ
struct XServerPhysical{
	uint32			uPhysicalID;	//����ID
	std::string		sMac;			//������ַ
	std::string		sIP;			//IP��ַ
	VectorString128	vAddress;		//IP
	uint16			uReconnect;		//��������
	XPhysicalUpdate xUpdate;

	bool			bUpdated;
	uint			uClientID;		//ClientID

	XServerPhysical(){
		uPhysicalID		= INVALID_ID;
		uReconnect		= 0;

		bUpdated		= false;
		uClientID		= INVALID_ID;
	}
};        

//���ƶ���Ϣ
struct XServerControl 
{
	uint uClientID;			//ClientID
};

struct XServerArg
{
	uint			uServerID;		//ID
	uint			eSrvType;		//����:���� ע�� ��
	uint			uClientID;
	XTopologyID		xSrcID;
	uint			uUserID;
	XServerArg(){
		uServerID = INVALID_ID;
		eSrvType  = INVALID_ID;
		uClientID = INVALID_ID;
		uUserID = INVALID_ID;
	}
};

const static XServerArg SERVER_ARG_INVAILD;

struct XServerHashKey
{
	uint			eSrvType;		//����:���� ע�� ��
	uint			uHash;
	bool operator <(const XServerHashKey& xHash)const{
		if (eSrvType == xHash.eSrvType)return uHash < xHash.uHash;
		return eSrvType < xHash.eSrvType;
	}
};

typedef std::vector<XServerLogic*>				VectorLogicPtr;
typedef std::map<uint32,XServerLogic>			MapLogic;	//<ServerID,>
typedef std::map<uint,VectorLogicPtr>			MapTypeLogic;
typedef std::map<XServerHashKey,uint>			MapLogicHash;
typedef std::map<uint,CRandomPack>				MapTypeRandom;
typedef std::map<uint32,XServerPhysical>		MapPhysical;//<ServerID,>
typedef std::map<uint32,XServerControl>			MapControl;	//<ClientID,>

typedef std::vector<XServerLogic>				VectorLogic;
typedef std::vector<XServerPhysical>			VectorPhysical;
typedef std::vector<XServerControl>				VectorControl;	

typedef std::map<uint32,XConfigLogic>			MapConfigLogic;		//<eSrvType,XConfigLogic>
typedef std::set<XConfigLink>					MapConfigLink;
typedef std::map<uint32,XConfigServer>			MapConfigServer;	//<uServerID,XConfigServer>

typedef std::map<uint32,XPhysicalUpdate>		MapPhysicalUpdate;
typedef std::map<uint32,XLogicUpdate>			MapLogicUpdate;

NS_TOOL_FRAME_END
	