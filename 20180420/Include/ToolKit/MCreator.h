#pragma once
#include "Macro.h"

#include "MMultiMap.h"
#include "ToolStd.h"

//������
//����:����Ѹ�ٵĹ���ָ������� 
//ע��:������ʱ �����������С�ʹ�����ӿ����롱 ѡ���
//�������:��������ʹ�þ�̬������������ʵ��.

//ģ�����:�������ͣ��������ͣ����(����ʶ��ͬ�ĵ���)
NS_TOOL_FRAME_BEGIN

#define CREATE_FUN_NAME CreateClass

//��ȡ������ַ
#define	MMULTIMAP_FIRST_FUN(key,mgrName,FunType)			ToolFrame::GetValueByKey(mgrName::Singleton().GetMap(),key,(FunType)nullptr)

//���崴������
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


//ע�ᴴ������(keyΪ�����,keyMark Ϊ ���ڱ�ʶ ��ͬ�ĳ�ʼ��������)
//���������
#define MMULTIMAP_REGIST_CREATE_FUN(mgrName,key,className,keyMark)				bool __bMCreator##className##keyMark = ToolFrame::Insert(mgrName::Singleton().GetMap(),key,className::CREATE_FUN_NAME)
#define MMULTIMAP_FISRST_CREATE_FUN(mgrName,key,FunType)						ToolFrame::GetValueByKey(mgrName::Singleton().GetMap(),key,(FunType)nullptr)
#define MMULTIMAP_CREATE(key,reType,keyType,fnType,mgrName)						__CreateClass<reType,keyType,fnType,mgrName>(key)
#define MMULTIMAP_CREATE_ARG1(key,arg1,reType,keyType,fnType,mgrName,Arg1Type)	__CreateClass<reType,keyType,fnType,mgrName,Arg1Type>(key,arg1)

NS_TOOL_FRAME_END
