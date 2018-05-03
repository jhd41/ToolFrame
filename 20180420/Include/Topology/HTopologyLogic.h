#pragma once

#include "MacroTopology.h"
#include "IMsgStream.h"

NS_TOOL_FRAME_BEGIN

class HTopologyLogic
{
public:
	virtual bool OnCenterConnected(uint uClientID){return false;}
	virtual bool OnCenterDisconnected(uint uClientID){return false;}
	virtual bool OnCenterAuthorized(uint uClientID,bool bAuthorized){return false;}
	
	virtual bool OnServerConnected(const XServerArg& xServerArg){return false;}
	virtual bool OnServerDisconnected(const XServerArg& xServerArg){return false;}
	virtual bool OnServerRecved(const XServerArg& xServerArg,IMsgStream& msgBase){return false;}
	virtual bool OnServerStateChanged(const MapLogicUpdate& vUpdate,uint uClientID){return false;}
	virtual bool OnServerCreateFaild(uint uPort){return false;}
	virtual bool OnServerCreateSucceed(uint uPort){return false;}
	virtual bool OnServerAllConnected(){return false;}

	virtual bool OnServerRecvErr(const XServerArg& xServerArg,IMsgStream& msgBase){return false;}

	virtual bool OnServerCreatePublicFaild(uint uPort){return false;}
	virtual bool OnServerCreatePublicSucceed(uint uPort){return false;}

	virtual bool OnServerReport(){return false;}		//汇报状态
	virtual bool OnServerSave(){return false;}			//保存数据
	virtual bool OnServerCleanUp(){return false;}		//清理缓存
	virtual bool OnServerStopService(){return false;}	//停止服务
	virtual bool OnServerShutDown(){return false;}		//退出进程
	virtual std::string OnServerDebug(const VectorString& vDebug) { return ""; }	//调试进程

	virtual bool OnPublicConnected(uint uClientID){return false;}
	virtual bool OnPublicDisconnected(uint uClientID){return false;}
	virtual uint OnPublicRecv(uint uClientID, IDataSession*	pSession) { return 0; }//返回非0值 则不再调用 OnPublicRecv（IMsgStream）
	virtual bool OnPublicRecv(uint uClientID, IDataSession*	pSession,StreamBinaryPtr pMsgStream) { return false; }
	virtual bool OnPublicRecv(uint uClientID, IDataSession*	pSession,IMsgStream&	 msgStream){return false;}
public:
	HTopologyLogic(void){}
	virtual ~HTopologyLogic(void){}
};

NS_TOOL_FRAME_END

