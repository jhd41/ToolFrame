#pragma once

#include "MacroTopology.h"

#include "ToolFrame.h"
#include "IMsgStream.h"

//���˲�Э��
SERIALIZE_CLASS(XTopologyID,		t.uGtID & t.uID & t.uUserID);

SERIALIZE_CLASS(XPhysicalUpdate,	t.eState & t.uCpuUsage & t.uMemoryUsed & t.uMemoryFree & t.uMemoryUsage & t.uSendBytes & t.uRecvBytes & t.uSystemCleanUp);
SERIALIZE_CLASS(XLogicUpdate,		t.eState & t.uTimeReport & t.uTimeRunOnce & t.uTimeRunOnceMax & t.uRunTimes & t.uRunTimeOutRate & t.uRunElapsed & t.uTimeSave & t.uTimeCleanUp & t.uSystemCleanUp & t.uCacheVaild & t.uCacheTotal & t.uProcesserCount & t.uQueueSize & t.uQueueProcess & t.uCpuUseTime & t.uCpuUsage & t.uMemoryUsed & t.uThreads & t.nSessionNum & t.nPacketProcess & t.nLogicProcess & t.nNetProcess & t.nLogicCmd & t.nNetCmd & t.uSendBytes & t.uRecvBytes & t.uFreeTime & t.uTimeSendMax & t.uTimeSendAvg & t.uTimeSendingMax & t.uTimeSendingAvg & t.uProcessMax & t.uProcessAvg);

SERIALIZE_CLASS(XServerLogic,		t.uServerID & t.eSrvType & t.uProcessID & t.uTimeStartUp & t.uReconnect & t.xUpdate);
SERIALIZE_CLASS(XServerPhysical,	t.uPhysicalID & t.sMac & t.sIP & t.vAddress & t.uReconnect & t.xUpdate);

SERIALIZE_CLASS(XConfigLogic,		t.eSrvType & t.eRunType & t.uThread & t.uRunOnce & t.uTimeInterval & t.uHashCount & t.sExePath & t.sWorkingDir & t.uRecvSize & t.uSendSize & t.uBlockSize & t.uSaveTime & t.uPublicRecv & t.uPublicSend & t.uPublicBlock & t.sRemark);
SERIALIZE_CLASS(XConfigLink,		t.eSrcSrv & t.eDesSrv & t.uCount);
SERIALIZE_CLASS(XConfigServer,		t.uPhysicalID & t.uServerID & t.eSrvType & t.uPort & t.vPublicPort & t.uPublicConnect & t.uHash & t.sCommand);


NS_TOOL_FRAME_BEGIN

enum EServerOpCode
{
	MSG_INVAILD=0,

	MSG_CENTER_AUTHORIZATION,		//������Ȩ
	MSG_CENTER_AUTHORIZATION_REP,	//������Ȩ����
	MSG_CENTER_NTF,					//�㲥
	MSG_CENTER_REP,

	MSG_PHYSICAL_REGIST,
	MSG_PHYSICAL_REGIST_REP,
	MSG_PHYSICAL_UPDATE_REQ,
	MSG_PHYSICAL_UPDATE_NTF,
	MSG_CONTROL_REGIST,
	MSG_CONTROL_SET_SERVER,		//���÷���������

	MSG_CONTROL_LOGIC_SAVE,
	MSG_CONTROL_LOGIC_CLEAN_UP,
	MSG_CONTROL_LOGIC_STOP_SERVICE,
	MSG_CONTROL_LOGIC_SHUTDOWN,
	MSG_CONTROL_LOGIC_DEBUG,
	
	MSG_CONTROL_PHYSICAL_START_SERVER,	//����������
	MSG_CONTROL_PHYSICAL_MEMORY_CLEAR,	//���������:�ڴ�����
	MSG_CONTROL_PHYSICAL_REBOOT,		//���������:����
	MSG_CONTROL_PHYSICAL_SET_TIME,		//���������:����ʱ��

	MSG_LOGIC_REGIST,
	MSG_LOGIC_REGIST_REP,
	MSG_LOGIC_UPDATE_REQ,	//����״̬
	MSG_LOGIC_UPDATE_NTF,
	MSG_LOGIC_DEBUG,		
	MSG_LINK_CONNECT_REQ,	//�߼�������֮������Э��
	MSG_LINK_CONNECT_REP,
	MSG_LINK_TRAN,		//�߼�������֮�䴫��Э��

	MSG_MANAGER_AUTHORIZATION,		//������Ȩ
	MSG_MANAGER_AUTHORIZATION_REP,	//������Ȩ����
	MSG_MANAGER_NTF,				//�㲥
	MSG_MANAGER_REP,

	MSG_MAX,
};

//������Ȩ
struct MsgCenterAuthorization
	:public IMsgStream
{
	uint8		eClientType;//�ͻ�������
	String64	sPassword;	//��������

	MSG_CONSTRUCT_SERIALIZE(MsgCenterAuthorization,MSG_CENTER_AUTHORIZATION,eClientType & sPassword);
};

//������Ȩ
struct MsgCenterAuthorizationRep
	:public IMsgStream
{
	uint8	bAuthorized;//�Ƿ���֤ͨ��
	uint32	uTimeStart;	//����������ʱ��
	MSG_CONSTRUCT_SERIALIZE(MsgCenterAuthorizationRep,MSG_CENTER_AUTHORIZATION_REP,bAuthorized & uTimeStart);
};

//��������� - ע��
struct MsgPhysicalRegist
	:public IMsgStream
{
	//�����������Ϣ
	uint32			uPhysicalID;//ID
	String128		sMac;		//������ַ
	String128		sIP;		//IP��ַ
	VectorString128	vAddress;
	XPhysicalUpdate xUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalRegist,MSG_PHYSICAL_REGIST,uPhysicalID & sMac & sIP & vAddress & xUpdate);
};

//��������� - ע��
struct MsgPhysicalRegistRep
	:public IMsgStream
{
	uint32			uPhysicalID;		//ID
	uint8			bSucceed;			//�ɹ�
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalRegistRep,MSG_PHYSICAL_REGIST_REP,uPhysicalID & bSucceed);
};

//��������� - ����
struct MsgPhysicalUpdateReq
	:public IMsgStream
{
	uint32			uPhysicalID;		//ID
	XPhysicalUpdate xUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalUpdateReq,MSG_PHYSICAL_UPDATE_REQ,uPhysicalID & xUpdate);
};

struct MsgPhysicalUpdateNtf
	:public IMsgStream
{
	MapPhysicalUpdate vUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgPhysicalUpdateNtf,MSG_PHYSICAL_UPDATE_NTF,vUpdate);
};

//���ķ�����-�㲥���з�����
struct MsgCenterNtf
	:public IMsgStream
{
	enum {
		TYPE_INVAILD,
		TYPE_ALL_SERVER,
		TYPE_ADD_PHYSICAL,
		TYPE_ADD_LOGIC,
		TYPE_REMOVE_PHYSICAL,
		TYPE_REMOVE_LOGIC,
		TYPE_LOGIC_SAVE,			//�߼�������:���������
		TYPE_LOGIC_CLEAN_UP,		//�߼�������:���������
		TYPE_LOGIC_STOP_SERVICE,	//�߼�������:ֹͣ����
		TYPE_LOGIC_SHUT_DOWN,		//�߼�������:�رշ�����
		TYPE_LOGIC_DEBUG,			//�߼�������:���Է�����
		TYPE_PHYSICAL_START_SERVER,	//���������:��������
		TYPE_PHYSICAL_MEMORY_CLEAR,	//���������:�ڴ�����
		TYPE_PHYSICAL_REBOOT,		//���������:����
		TYPE_PHYSICAL_SET_TIME,		//���������:ͳһʱ��
		TYPE_MAX,
	};
	uint8					uType;

	VectorLogic				vLogic;		//�߼�������
	VectorPhysical			vPhysical;	//���������

	uint32					uID;

	MapConfigLink			vConfigLink;	//�߼����������ӷ�ʽ
	MapConfigLogic			vConfigLogic;
	MapConfigServer			vConfigServer;	

	String128				sServerGroupID;	//��������ID
	String128				sServerZoneID;	//����������ID
	String128				sServerName;	//����������
	CDate					xServerOpen;	//����ʱ��
	String64				sServerTag;		//���������

	uint32					uServerID;		//������ID
	uint8					eSrvType;		//����������
	uint8					uThread;		//�߳���
	uint16					uRunOnce;		//����ʱ��
	uint16					uPort;			//�˿�
	String1024				sExePath;		//Exe·��
	String1024				sWorkingDir;	//����Ŀ¼
	uint32					uRecvSize;		//���ջ���ش�С
	uint32					uSendSize;		//���ͻ���ش�С
	uint32					uBlockSize;		//����ص��η����С
	uint64					uSaveTime;		//����ʱ��
	uint32					uPhysicalID;	//����ID
	VectorUint16			vPublicPort;	//���Ŷ˿�
	uint32					uPublicRecv;	//���Ž��ջ����
	uint32					uPublicSend;	//���ŷ��ͻ����
	uint32					uPublicBlock;	//����� ���ʷ����С
	uint16					uPublicConnect;	//�����������
	uint8					uHash;			//��ϣֵ
	uint8					uHashCount;		//��ϣ��
	String8192				sCommand;		//������

	VectorString			vDebug;			//����ģ��

	uint64					uMillTime;
	
	MSG_SERIALIZE_BEGIN
		
	MSG_SERIALIZE_ARG(uType)
	MSG_SERIALIZE_IF(uType,TYPE_ALL_SERVER,				vLogic & vPhysical & vConfigLink & vConfigLogic & vConfigServer & sServerGroupID & sServerZoneID & sServerName & xServerOpen)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_PHYSICAL,			vPhysical)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_LOGIC,				vLogic)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_PHYSICAL,		uID)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_LOGIC,			uID)
	
	MSG_SERIALIZE_IF(uType,TYPE_LOGIC_DEBUG,			vDebug)

	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_START_SERVER,	uServerID & eSrvType & uThread & uRunOnce & uPort & sExePath & sWorkingDir & uRecvSize & uSendSize & uBlockSize & uSaveTime & uPhysicalID & vPublicPort & uPublicRecv & uPublicSend & uPublicBlock & uPublicConnect & uHash & uHashCount & sServerTag & sCommand);
	MSG_SERIALIZE_IF(uType, TYPE_PHYSICAL_SET_TIME,		uMillTime)

	MSG_SERIALIZE_END
	MSG_CONSTRUCT(MsgCenterNtf,MSG_CENTER_NTF);
};

//���ķ�����Ӧ��
struct MsgCenterRep
	:public IMsgStream
{
	enum{
		OPT_INVAILD=0,
		OPT_MAX
	};
	uint8 uOpt;
	MSG_CONSTRUCT_SERIALIZE(MsgCenterRep,MSG_CENTER_REP, uOpt);
};

//���ƶ� ע��
//����-���
struct MsgControlRegist
	:public IMsgStream
{
	MSG_CONSTRUCT(MsgControlRegist,MSG_CONTROL_REGIST);
};

//����-�رշ�����
struct MsgControlShutDown
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlShutDown,MSG_CONTROL_LOGIC_SHUTDOWN,uServerID);
};

//����-ֹͣ����
struct MsgControlStopService
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlStopService,MSG_CONTROL_LOGIC_STOP_SERVICE,uServerID);
};

//����-���������
struct MsgControlSaveServer
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlSaveServer,MSG_CONTROL_LOGIC_SAVE,uServerID);
};

//����-���������
struct MsgControlCleanUpServer
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlCleanUpServer,MSG_CONTROL_LOGIC_CLEAN_UP,uServerID);
};

//����-���Է�����
struct MsgControlDebugServer
	:public IMsgStream
{
	uint32			uServerID;
	VectorString	vDebug;
	MSG_CONSTRUCT_SERIALIZE(MsgControlDebugServer, MSG_CONTROL_LOGIC_DEBUG, uServerID & vDebug);
};

//���÷���������
struct MsgControlSetServer
	:public IMsgStream
{
	String128			sServerGroupID;
	String128			sServerZoneID;
	String128			sServerName;
	CDate				xServerOpen;
	String64			sServerTag;
	MapConfigLogic		vConfigLogic;
	MapConfigLink		vConfigLink;
	MapConfigServer		vConfigServer;
	MSG_CONSTRUCT_SERIALIZE(MsgControlSetServer,MSG_CONTROL_SET_SERVER,sServerGroupID & sServerZoneID & sServerName & xServerOpen & sServerTag & vConfigLogic & vConfigLink & vConfigServer);
};

//��������������
struct MsgControlPhysicalStartServer
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalStartServer,MSG_CONTROL_PHYSICAL_START_SERVER, uServerID);
};

//�ڴ�����
struct MsgControlPhysicalMemoryClear
	:public IMsgStream
{
	uint32 uPhysicalID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalMemoryClear,MSG_CONTROL_PHYSICAL_MEMORY_CLEAR,uPhysicalID);
};

//����
struct MsgControlPhysicalReboot
	:public IMsgStream
{
	uint32 uPhysicalID;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalReboot,MSG_CONTROL_PHYSICAL_REBOOT,uPhysicalID);
};

//����ʱ��
struct MsgControlPhysicalSetTime
	:public IMsgStream
{
	uint32 uPhysicalID;
	uint64 uMillTime;
	MSG_CONSTRUCT_SERIALIZE(MsgControlPhysicalSetTime, MSG_CONTROL_PHYSICAL_SET_TIME, uPhysicalID & uMillTime);
};

//�߼�-ע��
struct MsgLogicRegist
	:public IMsgStream
{
	uint32			uServerID;	//������ID
	uint8			eSrvType;	//����������
	uint32			uProcessID;	//����ID
	XLogicUpdate	xUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgLogicRegist,MSG_LOGIC_REGIST,uServerID & eSrvType & uProcessID & xUpdate);
};

//�߼�-ע��
struct MsgLogicRegistRep
	:public IMsgStream
{
	uint32			uServerID;		//ID
	uint8			bSucceed;		//�ɹ�
	MSG_CONSTRUCT_SERIALIZE(MsgLogicRegistRep,MSG_LOGIC_REGIST_REP,uServerID & bSucceed);
};

//�߼�-״̬
struct MsgLogicUpdateReq
	:public IMsgStream
{
	uint32			uServerID;		//ID
	XLogicUpdate	xUpdate;

	MSG_CONSTRUCT_SERIALIZE(MsgLogicUpdateReq,MSG_LOGIC_UPDATE_REQ,uServerID & xUpdate);
};

//�߼�-״̬
struct MsgLogicUpdateNtf
	:public IMsgStream
{
	MapLogicUpdate vUpdate;
	MSG_CONSTRUCT_SERIALIZE(MsgLogicUpdateNtf,MSG_LOGIC_UPDATE_NTF,vUpdate);
};

//�߼�-����
struct MsgLogicDebug
	:public IMsgStream
{
	uint32			uServerID;		//ID
	StringLong		sString;

	MSG_CONSTRUCT_SERIALIZE(MsgLogicDebug, MSG_LOGIC_DEBUG, uServerID & sString);
};

//����-����
struct MsgLinkConnectReq
	:public IMsgStream
{
	uint32	uServerID;
	uint8	eSrvType;
	MSG_CONSTRUCT_SERIALIZE(MsgLinkConnectReq,MSG_LINK_CONNECT_REQ,uServerID & eSrvType);
};

//����-����
struct MsgLinkConnectRep
	:public IMsgStream
{
	uint32 uServerID;
	MSG_CONSTRUCT_SERIALIZE(MsgLinkConnectRep,MSG_LINK_CONNECT_REP,uServerID );
};

//����-����
struct MsgLinkTran
	:public IMsgStream
{
	XTopologyID		xSrcID;		//����ԴID
	StreamBinaryPtr	ptr;		//Э������
	uint32			uUserID;	//Ŀ��ID
	MSG_CONSTRUCT_SERIALIZE(MsgLinkTran,MSG_LINK_TRAN,xSrcID & ptr & uUserID);
};

//������Ȩ
struct MsgManagerAuthorization
	:public IMsgStream
{
	uint8		eClientType;//�ͻ�������
	String128	sPassword;	//��������

	MSG_CONSTRUCT_SERIALIZE(MsgManagerAuthorization,MSG_MANAGER_AUTHORIZATION,eClientType & sPassword);
};

//������Ȩ
struct MsgManagerAuthorizationRep
	:public IMsgStream
{
	uint8	bAuthorized;//�Ƿ���֤ͨ��
	uint32	uTimeStart;	//����������ʱ��
	MSG_CONSTRUCT_SERIALIZE(MsgManagerAuthorizationRep,MSG_MANAGER_AUTHORIZATION_REP,bAuthorized & uTimeStart);
};

//���������-�㲥���з�����
struct MsgManagerNtf
	:public IMsgStream
{
	enum {
		TYPE_INVAILD,
		TYPE_ALL_SERVER,
		TYPE_ADD_PHYSICAL,
		TYPE_REMOVE_PHYSICAL,

		TYPE_ADD_LOGIC,
		TYPE_REMOVE_LOGIC,
		TYPE_LOGIC_SAVE,			//�߼�������:���������
		TYPE_LOGIC_CLEAN_UP,		//�߼�������:���������
		TYPE_LOGIC_STOP_SERVICE,	//�߼�������:ֹͣ����
		TYPE_LOGIC_SHUT_DOWN,		//�߼�������:�رշ�����
		TYPE_PHYSICAL_START_SERVER,	//���������:��������
		TYPE_PHYSICAL_MEMORY_CLEAR,	//���������:�ڴ�����
		TYPE_PHYSICAL_REBOOT,		//���������:����
		TYPE_MAX,
	};
	uint8			uType;

	MapLogic		vLogic;		//�߼�������
	MapPhysical		vPhysical;	//���������

	uint32			uID;

	MapConfigLink	vConfigLink;	//�߼����������ӷ�ʽ
	MapConfigLogic	vConfigLogic;

	String128		sServerGroupID;	//��������ID
	String128		sServerZoneID;	//����������ID

	uint32			uServerID;		//������ID
	uint8			eSrvType;		//����������
	uint16			uPort;			//�˿�
	String1024		sExePath;		//Exe·��
	String1024		sWorkingDir;	//����Ŀ¼
	uint32			uRecvSize;		//���ջ���ش�С
	uint32			uSendSize;		//���ͻ���ش�С
	uint64			uSaveTime;		//����ʱ��
	uint32			uPhysicalID;	//����ID
	VectorUint16	vPublicPort;	//���Ŷ˿�
	uint32			uPublicRecv;	//���Ž��ջ����
	uint32			uPublicSend;	//���ŷ��ͻ����
	uint8			uHash;			//��ϣֵ
	uint8			uHashCount;		//��ϣ��
	String8192		sCommand;		//������
	String512		sCenterIP;		//���ķ�������ַ
	String128		sPassword;		//���ķ���������

	MSG_SERIALIZE_BEGIN
	MSG_SERIALIZE_ARG(uType)
	MSG_SERIALIZE_IF(uType,TYPE_ALL_SERVER,				vLogic & vPhysical & vConfigLink & vConfigLogic & sServerGroupID & sServerZoneID)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_PHYSICAL,			vPhysical)
	MSG_SERIALIZE_IF(uType,TYPE_ADD_LOGIC,				vLogic)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_PHYSICAL,		uID)
	MSG_SERIALIZE_IF(uType,TYPE_REMOVE_LOGIC,			uID)
	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_START_SERVER,	uServerID & eSrvType & uPort & sExePath & sWorkingDir & uRecvSize & uSendSize & uSaveTime & uPhysicalID & vPublicPort & uPublicRecv & uPublicSend & uHash & uHashCount & sCommand & sCenterIP & sPassword);
	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_MEMORY_CLEAR,	uPhysicalID)
	MSG_SERIALIZE_IF(uType,TYPE_PHYSICAL_REBOOT,		uPhysicalID)
	MSG_SERIALIZE_END
		
	MSG_CONSTRUCT(MsgManagerNtf,MSG_CENTER_NTF);
};

NS_TOOL_FRAME_END
