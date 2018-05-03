#pragma once
#include "Macro.h"

#include "MMultiMap.h"
#include "ToolStd.h"

//创建器
//作用:方便迅速的构建指定类对象 
//注记:在连接时 将连接设置中“使用链接库输入” 选项打开
//代码理解:本创建器使用静态函数查找器来实现.

//模板参数:返回类型，主键类型，标记(仅仅识别不同的单件)
NS_TOOL_FRAME_BEGIN

#define CREATE_FUN_NAME CreateClass

//获取函数地址
#define	MMULTIMAP_FIRST_FUN(key,mgrName,FunType)			ToolFrame::GetValueByKey(mgrName::Singleton().GetMap(),key,(FunType)nullptr)

//定义创建函数
#define FUN_CREATE_REAL(clsName,reType,reRealType)	public:\
														static reType CREATE_FUN_NAME()\
														{\
															return reRealType(new clsName());\
														}
#define FUN_CREATE_REAL_ARG1(clsName,reType,argType1,reRealType)	public:\
														static reType CREATE_FUN_NAME(argType1 arg1)\
														{\
															return reRealType(new clsName(arg1));\
														}

#define FUN_CREATE(clsName,reType)						FUN_CREATE_REAL(clsName,reType,reType)
#define FUN_CREATE_ARG1(clsName,reType,argType1)		FUN_CREATE_REAL_ARG1(clsName,reType,argType1,reType)

template<typename TReturn,typename TKey,typename TFunType,typename TMgrName>
TReturn __CreateClass(TKey tKey){
	TFunType fn = ToolFrame::GetValueByKey(TMgrName::Singleton().GetMap(),tKey,(TFunType)nullptr);
	return fn ? fn() : TReturn();
}

template<typename TReturn,typename TKey,typename TFunType,typename TMgrName,typename TArg1>
TReturn __CreateClass(TKey tKey,TArg1 tArg1){
	TFunType fn = ToolFrame::GetValueByKey(TMgrName::Singleton().GetMap(),tKey,(TFunType)nullptr);
	return fn ? fn(tArg1) : TReturn();
}


//注册创建函数(key为传入键,keyMark 为 用于标识 不同的初始化变量名)
//创建类对象
#define MMULTIMAP_REGIST_CREATE_FUN(mgrName,key,className,keyMark)				bool __bMCreator##className##keyMark = ToolFrame::Insert(mgrName::Singleton().GetMap(),key,className::CREATE_FUN_NAME)
#define MMULTIMAP_FISRST_CREATE_FUN(mgrName,key,FunType)						ToolFrame::GetValueByKey(mgrName::Singleton().GetMap(),key,(FunType)nullptr)
#define MMULTIMAP_CREATE(key,reType,keyType,fnType,mgrName)						__CreateClass<reType,keyType,fnType,mgrName>(key)
#define MMULTIMAP_CREATE_ARG1(key,arg1,reType,keyType,fnType,mgrName,Arg1Type)	__CreateClass<reType,keyType,fnType,mgrName,Arg1Type>(key,arg1)

NS_TOOL_FRAME_END
