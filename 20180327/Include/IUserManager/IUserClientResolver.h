#pragma once
#include "Macro.h"
#include "MacroTopology.h"
#include "IResolver.h"
#include "IMsgStream.h"

NS_TOOL_FRAME_BEGIN
class IUserClient;
class IUserClientResolver
	:public IResolver
{
public:
	virtual IUserClient*	GetIUserClient()const;
	virtual bool			SendClient(const IMsgStream& msgStream, bool bSecret = true);
	virtual bool			SendClient(StreamBinaryPtr ptr, bool bSecret = true);
	virtual bool			SendClient(const std::string& sMsg, bool bSecret = true);
	virtual bool			SendClient(const void* pBuffer, size_t uLen, bool bSecret = true);
public:
	virtual bool OnClientConnected() { return false; }
	virtual bool OnClientDisconnected() { return false; }
	virtual bool OnClientRecv(const IMsgStream& msgStream) { return false; }
	virtual bool OnClientRecv(IDataSession* pSession) { return false; }
	virtual bool OnClientRecvErr(const IMsgStream& msgStream);						//当客户端协议处理有误时
	virtual bool OnClientRecvErr(IDataSession* pSession);							//当客户端协议处理有误时

	virtual bool OnServerConnected(const XServerLogic* pServer) { return false; }
	virtual bool OnServerDisconnected(const XServerLogic* pServer) { return false; }
	virtual bool OnServerRecved(const XServerArg& xServerArg, const IMsgStream& msgBase) { return false; }
public:
	IUserClientResolver();
	virtual ~IUserClientResolver();
private:
	CFIELD_PTR(IUserClient*, User, p);
};

NS_TOOL_FRAME_END
