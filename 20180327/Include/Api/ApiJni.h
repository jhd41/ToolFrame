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

	//�ⲿ���������
public:
	static CMutexRecursive& GetMutex();
	static int		GetEnvCount();		//��ȡEnvʹ�ô���
	static int		AddEnvCount();		//����Envʹ�ô���
	static int		RemoveEnvCount();	//����Envʹ�ô���
	static JNIEnv*	SetEnv(JNIEnv* pEnv);//����Env
	static JNIEnv*	GetEnv();			//��ȡEnv
	static JNIEnv*	GetEnvByJavaVM();
	static bool		IsAttachThread();	//�ж��Ƿ�ճ�����˵�ǰ�߳�(��Ҫ�ͷ�)
	static JNIEnv*	JniEnvAttachThread();//ճ����ǰ�߳�
	static bool		JniEnvDetachThread();//���뵱ǰ�߳�
private:
	static JavaVM*			_pJavaVM;
	static MapStringClass	_vClass;
	static CMutexRecursive	_mutex;
	static int				_nEnvCount;
	static JNIEnv*			_pEnv;
	static bool				_bAttached;
};

#endif