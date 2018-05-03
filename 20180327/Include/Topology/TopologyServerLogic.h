#pragma once

#include "MacroTopology.h"

NS_TOOL_FRAME_BEGIN

class CTopologyServerLogic
{
public:
	bool						Init();
	
	//�̰߳�ȫ
public:
	bool						Clear();
	bool						AddServer(const XServerLogic& xServer);
	bool						AddServer(const VectorLogic& vLogic);
	bool						RemoveLogicByServerID(uint uServerID);
	bool						IsLogicEmpty()const;
	uint						FindServerIDHash(int eSrvType,uint uHash)const;
	bool						FindHashCount(uint* uHashCount,int eSrvType ) const;
	uint						FindServerIDBalance(int eSrvType)const;
	uint						FindServerIDSequence(int eSrvType)const;
	uint						FindServerRunType(int eSrvType)const;
	std::string					GetDebugString()const;

	//���� �ⲿ����ʱ���ע��ͬ����������
public:
	bool						UpdateLogicState(uint uServerID,const XLogicUpdate& xUpdate);
	bool						UpdateDebugString(uint uServerID,const std::string& sDebugString);
	bool						OptimizeSrvTypeInit();
	bool						OptimizeSrvType();
	const XServerLogic*			FindLogicByServerID( uint uServerID )const;
	const XServerLogic*			FindLogicByClientID( uint uClientID )const;
	CMutexReadWrite&			GetMutexLogic()const;
	CMutexReadWrite&			GetMutexConfig()const;
	bool						IsLogicOnline(uint uServerID)const;
	bool						FindOnlineServerList(VectorUint& vServerID)const;
public:
	bool						ClearConfig();
	bool						SetConfigLink(const MapConfigLink& vLinks);
	bool						SetConfigLogic(const MapConfigLogic& vConfigLogic);
	bool						SetConfigServer(const MapConfigServer& vConfigServer);

	const XConfigLink*			FindConfigLink(int nSrc,int nTar)const;
	const XConfigLogic*			FindConfigLogic( uint eSrvType ) const;
	const XConfigServer*		FindConfigServer(uint uServerID)const;
	const MapConfigLink&		GetConfigLinks()const;
	const MapConfigLogic&		GetConfigLogic()const;
	const MapConfigServer&		GetConfigServer()const;
public:
	bool						SetServerID(uint uServerID);
	bool						SetSrvType(int eSrvType);
	bool						SetPort(uint uPort);
	bool						SetHash(uint uHash);
	bool						SetHashCount(uint uHash);
	bool						SetSendSize(uint uSize);
	bool						SetRecvSize(uint uSize);
	bool						SetBlockSize(uint uSize);
	bool						SetThread(uint uCount);
	bool						SetServerGroupID(const std::string& sServerGroupID);
	bool						SetServerZoneID(const std::string& sServerZoneID);
	bool						SetServerName(const std::string& sServerName);
	bool						SetServerOpen(const CDate& xServerOpen);
	bool						SetServerTag(const std::string& sServerTag);
public:
	const MapLogic&				GetLogic()const;
	MapLogic&					GetLogic();
	const MapTypeLogic&			GetTypeLogic()const;
	uint						GetServerID()const;
	int							GetServerType()const;
	uint						GetHash()const;
	uint						GetHashCount()const;
	uint						GetPort()const;
	uint						GetSendSize()const;
	uint						GetRecvSize()const;
	uint						GetBlockSize()const;
	uint						GetThread()const;
	const std::string&			GetServerGroupID()const;
	const std::string&			GetServerZoneID()const;
	const std::string&			GetServerName()const;
	const CDate&				GetServerOpen()const;
	const std::string&			GetServerTag()const;
public:
	CTopologyServerLogic(void);
	virtual ~CTopologyServerLogic(void);
private:
	uint					_uServerID;
	int						_eSrvType;
	uint					_uHash;
	uint					_uHashCount;
	uint					_uPort;
	uint					_uSendSize;
	uint					_uRecvSize;
	uint					_uBlockSize;
	uint					_uThread;

	std::string				_sServerGroupID;//��������ID
	std::string				_sServerZoneID;	//����ID
	std::string				_sServerName;	//����������
	CDate					_xServerOpen;	//����ʱ��
	std::string				_sServerTag;	//���������

	mutable CMutexReadWrite	_xMutexLogic;
	MapLogic				_vLogic;		//�߼�������
	MapTypeLogic			_vTypeLogic;	//<SrvType,Servers>	

	mutable CMutexReadWrite	_xMutexConfig;
	MapConfigLink			_vConfigLink;	//�߼����������ӷ�ʽ
	MapConfigLogic			_vConfigLogic;
	MapConfigServer			_vConfigServer;

	MapLogicHash			_vLogicHash;	//����ϣ�йصķ������б�
	MapTypeRandom			_vLogicBalance;
	MapIntVectorInt			_vLogicSequence;
};

NS_TOOL_FRAME_END
