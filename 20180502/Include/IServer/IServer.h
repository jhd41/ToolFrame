#pragma once
#include "Macro.h"
#include "ElasticThreadManager.h"
#include "MSystem.h"

//服务器基类,弹性线程(默认不开启)

NS_TOOL_FRAME_BEGIN
class IServer
	:public ISystemInit
	,public HElasticThread
{
public:
	virtual bool	SetRunOnceSleep(uint uRunOnceSleep);//单次循环睡觉时间
public:
	virtual bool	Init();						//初始化
	virtual	bool	RunOnce();					//运行单次
public:
	virtual	bool	Run();						//循环运行
	virtual bool	ShutDown();					//关闭
	//子类实现
public:
	virtual bool	OnInitSucceed();			//初始化成功
	virtual bool	OnInitFaild();				//初始化失败
protected:
	virtual bool	OnRunElasticThread();		//执行弹性线程，返回是否超时
public:
	IServer(void);
	virtual ~IServer(void);
protected:
	CTimeElapse				_xTimeServerStart;	//服务器运行时间
	CElasticThreadManager	_mgrElasticThread;
	uint					_uRunOnceSleep;		//单次循环睡觉时间
};
NS_TOOL_FRAME_END
