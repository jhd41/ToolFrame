#pragma once
#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#include <jni.h>
#include "MacroDefineBoost.h"
#include "TThreadSaftyMap.h"
#include "TArray.h"


class ApiJni{
	typedef ToolFrame::TThreadSaftyMapValue<std::string,jclass> MapStringClass;
public:
	static void			CallJniReturnVoid(const std::string& sPacketName,const std::string& sFuncName);
	static void			CallJniReturnVoid(const std::string& sPacketName,const std::string& sFuncName,int nArg);
	static void			CallJniReturnVoid(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg);
	static void			CallJniReturnVoid(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,bool bArg);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3,const std::string& sArg4);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3,const std::string& sArg4,const std::string& sArg5);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2,const std::string& sArg3,const std::string& sArg4,const std::string& sArg5, const std::string& sArg6);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,int nArg1);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,int nArg1,int nArg2);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,int nArg1,int nArg2,int nArg3);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,int nArg1,int nArg2,int nArg3,int nArg4);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,int nArg1,int nArg2,int nArg3,int nArg4, int nArg5);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,long nArg1);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,long nArg1, long nArg2);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,long nArg1, long nArg2, long nArg3);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,long nArg1, long nArg2, long nArg3, long nArg4);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,long nArg1, long nArg2, long nArg3, long nArg4, long nArg5);
	static bool			CallJniReturnBool(const std::string& sPacketName,const std::string& sFuncName,const ToolFrame::CArrayRefByte& arrByte);
	static int			CallJniReturnInt(const std::string& sPacketName, const std::string& sFuncName);
	static long			CallJniReturnLong(const std::string& sPacketName,const std::string& sFuncName);
	static std::string	CallJniReturnString(const std::string& sPacketName,const std::string& sFuncName);
	static jobject		CallJniReturnJObject(const std::string& sPacketName, const std::string& sFuncName);

	static std::string	JString2String(jstring jstr);
	static std::string	JString2String(JNIEnv* pEnv,jstring jstr);
	static jclass		FindClass(JNIEnv * pEnv,const std::string& sClassName);
	static bool			DeleteLocalRef(JNIEnv * pEnv,jclass nClassID);
public:
	static void		SetJavaVM(JavaVM* psJavaVM);
	static JavaVM*	GetJavaVM();

	//外部不允许调用
public:
	static CMutexRecursive& GetMutex();
	static int		GetEnvCount();		//获取Env使用次数
	static int		AddEnvCount();		//增加Env使用次数
	static int		RemoveEnvCount();	//减少Env使用次数
	static JNIEnv*	SetEnv(JNIEnv* pEnv);//设置Env
	static JNIEnv*	GetEnv();			//获取Env
	static JNIEnv*	GetEnvByJavaVM();
	static bool		IsAttachThread();	//判断是否粘贴到了当前线程(需要释放)
	static JNIEnv*	JniEnvAttachThread();//粘贴当前线程
	static bool		JniEnvDetachThread();//分离当前线程
private:
	static JavaVM*			_pJavaVM;
	static MapStringClass	_vClass;
	static CMutexRecursive	_mutex;
	static int				_nEnvCount;
	static JNIEnv*			_pEnv;
	static bool				_bAttached;
};

#endif