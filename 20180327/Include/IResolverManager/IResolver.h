#pragma once

#include "MacroResolver.h"

NS_TOOL_FRAME_BEGIN
class IResolver;
class HResolver{
public:
	virtual bool OnResolverCreate(IResolver* pResolver){return true;}
	virtual bool OnResolverDestory(IResolver* pResolver){return true;}
	virtual bool OnResolverResetResolve(IResolver* pResolver){return true;}
public:
	HResolver(){}
	virtual ~HResolver(){}
};

class IResolver
{
	enum 
	{
		RESOLVER_BASE_INIT,
		RESOLVER_BASE_MAX,
	};
public:
	virtual bool IsResolveOver()const;
	virtual bool SetResolveRange(int nBegin,int nEnd);
	virtual bool ResetResolve();//重置结算阶段
	virtual bool SetResolveOver();//将阶段设置为结束
protected:
	virtual bool WaitSeconds(int nSeconds);	//等待N秒
	virtual bool WaitSeconds(float fSeconds);	//等待N秒 例如 4.5秒
	virtual bool WaitMillSec(uint64 uMillSec);//等待百万秒
	virtual bool WaitForever();		//永远等待
	virtual bool ClearWait();		//清除等待
	virtual bool MarkResolveOver();		//标记所有结算完成
	virtual bool IgnoreCheckResolve();//本次忽略检查(用于自身阶段循环)
	virtual bool PushAction(IResolver* pAc);
	virtual bool PushActionSelf();

	//内部调用
public:
	virtual bool SetHandler(HResolver* hHandler);
	virtual HResolver* GetHandler()const;

	//结算管理器回调
public:
	virtual bool OnResolve();
	virtual bool OnResolveOnce();
	virtual bool OnTimeOut();
	virtual bool OnResolveBegin();	//调用开始
	virtual bool OnResolveOver();	//调用完成
public:
	IResolver(void);
	virtual ~IResolver(void);
private:
	CFIELD_INT(Resolve);
	CFIELD_INT(ResolveBegin);
	CFIELD_INT(ResolveEnd);
	CFIELD_PTR(IResolver*,Parent,p);
	CFIELD_PTR(IResolverManager*,ResolverMgr,p);
	CFIELD_BOOL(Resolving);		//是否在结算中
	CFIELD_BOOL(ManagerCreate);	//管理器创建
	CFIELD_BOOL(Removed);		//标记是否被移除
private:
	HResolver* _hHandler;
};

NS_TOOL_FRAME_END
