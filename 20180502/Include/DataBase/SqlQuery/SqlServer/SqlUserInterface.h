#pragma once

#include "MacroSqlSrv.h"

#ifdef MACRO_LIB_MY_SQL

#include "IUserClientResolver.h"
#include "IUserClient.h"

NS_TOOL_FRAME_BEGIN

class CSqlUserClient;
class ISqlUserAction
	:public IUserClientResolver
{
public:
	template<typename T>
	T*		CreateTopAction();
protected:
	virtual bool			Init(ISqlUserAction* pAc);
	virtual CSqlUserClient* GetUserClient()const;
	virtual bool			OnClientRecv(const IMsgStream& msgStream)override;
public:
	ISqlUserAction(void);
	virtual ~ISqlUserAction(void);
};

template<typename T>
T* ISqlUserAction::CreateTopAction()
{
	T* pAction = GetResolverMgr()->CreateTopResolver<T>(this);
	if (!pAction)return nullptr;
	
	pAction->Init(this);
	return pAction;
}

//////////////////////////////////////////////////////////////////////////
class CSqlUserClient
	:public IUserClient
{
protected:
	virtual bool	OnEncrypt(void* pBuffer, size_t uLength)override;	//º”√‹
	virtual bool	OnDecrypt(void* pBuffer, size_t uLength)override;	//Ω‚√‹
public:
	CSqlUserClient(void);
	virtual ~CSqlUserClient(void);
};

NS_TOOL_FRAME_END
//////////////////////////////////////////////////////////////////////////
#include "IUserClientManager.h"

NS_TOOL_FRAME_BEGIN

class CSqlUserManager
	:public IUserClientManager
{
protected:
	virtual ISyncProcesserPtr	OnCreateProcesser(int nUserInt, void* pUserData)override;
public:
	CSqlUserManager(void);
	virtual ~CSqlUserManager(void);
};

NS_TOOL_FRAME_END

#endif
