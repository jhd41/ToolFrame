#pragma once

#include "Macro.h"
#include "MacroDefineEx.h"
#include "MacroDefineBoost.h"

#include "IPool.h"

NS_TOOL_FRAME_BEGIN

DECLARE_SHARE_PTR(CTimeNode);

class HTimeOut;
class CTimeNode
	:public IPoolZero
{
public:
	void				SetObj(void* pObj);
	void*				GetObj()const;
	void				SetUserDataInt(int nArg);
	int					GetUserDataInt()const;
	void				SetUserDataString(const std::string& sArg);
	const std::string&	GetUserDataString()const;

	//外部不要调用
public:
	bool				Init(bool bLoop,uint64 uTimeDelay,HTimeOut* pCallBack);
	bool				SetInvaild();//使其无效
	void				SetTimeOut(uint64 uTimeOut);
	
	bool				IsEnable()const;
	bool				IsLoop()const;
	HTimeOut*			GetProcesser()const;
	uint64				GetTimeOut()const;
	uint64				GetTimeDelay()const;
	
	CMutexRecursive&	GetMutex()const;
public:
	CTimeNode();
	virtual ~CTimeNode();
private:
	mutable CMutexRecursive	_mutex;//由于超时时为了保证正确性要上锁，但上锁后 又可能发生析构 移除时间节点 因此不可避免的 要重复访问 本类，因此 只能使用 递归锁。

	bool		_bEnable;	//是否有效
	uint64		_uTimeOut;	//超时时间
	bool		_bLoop;		//是否循环
	uint64		_uTimeDelay;//延迟时间
	HTimeOut*	_pProcesser;//超时处理器
	
	void*		_pObj;		//绑定的附带参数
	int			_nArg;		
	std::string _sArg;		
};

NS_TOOL_FRAME_END
