#pragma once
//服务器控制中心
//维护物理服务器表
//维护逻辑服务器表
//思路:
//服务器控制中心启动后开始监听
//当一台物理服务器启动后 会主动连接服务器控制中心
//这样，控制中心就知道有多少台物理机器了。
//之后通过UI界面配置控制中心每台物理机器添加多少逻辑类型服务器
//控制中心会发送消息给物理服务器 让其启动规定数量的逻辑服务器
//逻辑服务器会主动连接服务器控制中心。
//控制更新将所有的服务器列表,并发送给所有服务器
//服务器根据自己的业务需求进行相互连接。

#include "MacroTopology.h"
#include "IDataReceiverStream.h"
#include "HTopologyLogic.h"
#include "TopologyServerLogic.h"
#include "TopologyServerPhysical.h"
#include "TopologyServerController.h"
#include "HTimeOut.h"

NS_TOOL_FRAME_BEGIN

class HTopologyCenter{
public:
	virtual bool OnCenterStartServer(uint uSrvID, int eSrvType) { return false; }
	virtual bool OnCenterAuthorization(uint eClientType) { return false; }

	virtual bool OnPhysicalRegist(uint uPhysicalID) { return false; }

	virtual bool OnServerConnected(const XServerArg& xServerArg){return false;}
	virtual bool OnServerStateChanged(const XServerArg& xServerArg){return false;}
	virtual bool OnServerDisconnected(const XServerArg& xServerArg){return false;}
	virtual bool OnServerConfigChanged(uint uClientID){return false;}
	virtual bool OnServerCreateFaild(uint uPort){return false;}
	virtual bool OnServerCreateSucceed(uint uPort){return false;}
	virtual bool OnServerNotifyState(){return false;}

	virtual bool OnControlRegist() { return false; }
	virtual bool OnControlLogicSave(uint uSrvID) { return false; }
	virtual bool OnControlLogicCleanUp(uint uSrvID) { return false; }
	virtual bool OnControlLogicStopService(uint uSrvID) { return false; }
	virtual bool OnControlStartServer(uint uSrvID, int eSrvType) { return false; }
	virtual bool OnControlShutDown(uint uSrvID) { return false; }
	virtual bool OnControlDebug(uint uSrvID,const VectorString&	vDebug) { return false; }
	virtual bool OnControlPurgeMemory(uint uPhysicalID) { return false; }
	virtual bool OnControlReboot(uint uPhysicalID) { return false; }
	
	
public:
	HTopologyCenter(){}
	virtual ~HTopologyCenter(){}
};

class CTopologyCenter
	:public IDataReceiverStream
	,public HTimeOut
{
	struct XClientData 
	{
		uint uClientID;
		uint eClientType;	//EClientType
	};

	typedef std::map<uint,XClientData*> MapClientData;

public:
	bool SetPort(uint uPort);									//设置开放端口
	bool SetPassword(const std::string& sPassword);				//设置授权密码
	bool SetSendSize(uint uSize);
	bool SetRecvSize(uint uSize);
	bool SetBlockSize(uint uSize);
	bool SetTimeTryCreateServer(uint uTime);					//设置尝试创建服务器的时间间隔
	bool SetTimeNotifyState(uint uTime);						//设置服务器广播所有服务器状态时间间隔
	bool SetHandler(HTopologyCenter* hHandler);
	bool Init();
public:
	const std::string&			GetServerGroupID()const;
	const std::string&			GetServerZoneID()const;
private:
	bool Send(uint uClientID,IMsgStream& msgBase)const;
	bool Send(uint uClientID, StreamBinaryPtr ptrBuffer)const;

	bool SendAuthorizationRep(uint uClientID,bool bAuthorized)const;
	bool SendAllServer(uint uClientID);
	bool SendLogicUpdate(uint uServerID);
	bool SendLogicUpdateAll();
	bool SendLogicRegistRep(uint uClientID,uint uServerID,bool bSucceed);
	bool SendPhysicalUpdate(uint uPhysicalID);
	bool SendPhysicalRegistRep(uint uClientID,uint uPhysicalID,bool bSucceed);
private:
	bool AddClient(uint uClientID,uint eClientType);
	bool RemoveClient(uint uClientID);
	bool Broadcast(EClientType eClientType, IMsgStream& msgStream);
	bool Broadcast(EClientType eClientType, StreamBinaryPtr pBuffer);
private:
	bool CreateTimerCreateServer();
	bool RemoveTimerCreateServer();
private:
	virtual bool OnConnected(UINT uClientID);
	virtual bool OnConnectFailed(UINT uClientID);
	virtual bool OnDisconnected(UINT uClientID);
	virtual bool OnRecv( UINT uClientID,IMsgStream& msgStream);
private:
	virtual bool OnTimeOut(const CTimeNodePtr& pTimeNode);
public:
	CTopologyCenter(void);
	virtual ~CTopologyCenter(void);
private:
	uint			_uPort;

	std::string		_sPassword;					//授权密码

	MapClientData	_vClientData;				//<ClientID,Data*>

	CTopologyServerLogic		_vLogic;		//所有的服务器
	CTopologyServerPhysical		_vPhysical;
	CTopologyServerController	_vController;

	HTopologyCenter* _hHandler;

	time_t			_uTimeStart;				//启动时间

	uint			_uTimeTryCreateServer;		//监听端口时间间隔
	CTimeNodePtr	_pTimerCreateServer;		//计时器 监听端口

	uint			_uTimeNotifyState;			//广播所有服务器的状态
	CTimeNodePtr	_pTimerNotifyState;			//计时器 监听端口
};

NS_TOOL_FRAME_END
