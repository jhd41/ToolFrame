#pragma once
//�����Ƕ�Jni������һ����װ��ʹ�������ʹ�á�

#include "Macro.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#include <jni.h>
#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

//////////////////////////////////////////////////////////////////////////
//��ȡJni����
class CJniEnvLock
{
public:
	JNIEnv* GetEnv()const;
public:
	CJniEnvLock();
	~CJniEnvLock();
private:
	CLockScoped _lock;
};

//////////////////////////////////////////////////////////////////////////
//�ֽ����麯��(Java -> C++)
class CJniByteArray
{
public:
	char*	GetPtr();
	char*	GetPtr()const;
	UINT	GetLength()const;
public:
	CJniByteArray(JNIEnv* pEnv, jbyteArray jByteArray);
	~CJniByteArray();
private:
	JNIEnv*		_pEnv;
	jbyteArray	_jByteArray;
	jboolean	_isCopy;

	jbyte*		_arrayBody;
	jsize		_theArrayLengthJ;
};

//////////////////////////////////////////////////////////////////////////
//�ֽ����麯��(C++ -> Java)
class CJniJByteArray
{
public:
	const jbyteArray&	GetArray()const;
	jbyteArray&			GetArray();
public:
	CJniJByteArray(JNIEnv* pEnv, const char* pBuff,uint uLength);
	~CJniJByteArray();
private:
	JNIEnv*		_pEnv;
	
	jbyteArray	_jByteArray;
};

//////////////////////////////////////////////////////////////////////////
//�ַ���(Java -> C++)
class CJniString
{
public:
	const std::string& GetString()const;
public:
	CJniString(JNIEnv* pEnv, jstring jstr);
	~CJniString();
private:
	JNIEnv*		_pEnv;
	jstring		_jstr;
	jboolean	_isCopy;
	const char*	_szString;

	std::string _sString;
};

//////////////////////////////////////////////////////////////////////////
//�ַ���(C++ -> Java)
class CJniJString
{
public:
	const jstring&	GetString()const;
	jstring&		GetString();
public:
	CJniJString(JNIEnv* pEnv, const std::string& sString);
	~CJniJString();
private:
	JNIEnv*		_pEnv;
	jstring		_jstr;
};

//////////////////////////////////////////////////////////////////////////
//Jni���ù���
class CJniCaller
{
public:
	CJniCaller(JNIEnv* pEnv,const std::string& sClassName,const std::string& sMethodName,const std::string& sParmCode);
	virtual ~CJniCaller(void);
public:
	//���÷���ֵΪobject�ĺ���
	jobject		CallStaticObjectMethod();
	template<typename TArg1>
	jobject		CallStaticObjectMethod(const TArg1 tArg);
	
	//���÷���ֵΪbool�ĺ���
	jboolean	CallStaticBooleanMethod();
	template<typename TArg1>
	jboolean	CallStaticBooleanMethod(const TArg1& tArg);
	template<typename TArg1,typename TArg2>
	jboolean	CallStaticBooleanMethod(const TArg1& tArg1,const TArg2& tArg2);
	template<typename TArg1,typename TArg2,typename TArg3>
	jboolean	CallStaticBooleanMethod(const TArg1& tArg1,const TArg2& tArg2,const TArg3& tArg3);
	template<typename TArg1,typename TArg2,typename TArg3,typename TArg4>
	jboolean	CallStaticBooleanMethod(const TArg1& tArg1,const TArg2& tArg2,const TArg3& tArg3,const TArg4& tArg4);
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
	jboolean	CallStaticBooleanMethod(const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5);
	template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
	jboolean	CallStaticBooleanMethod(const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5, const TArg6& tArg6);

	//���÷���ֵΪlong�ĺ���
	jlong		CallStaticLongMethod();
	//���÷���ֵΪint�ĺ���
	jint		CallStaticIntMethod();

	//���÷���ֵΪvoid�ĺ���
	void		CallStaticVoidMethod();
	template<typename TArg1>
	void		CallStaticVoidMethod(const TArg1& tArg);
	template<typename TArg1,typename TArg2>
	void		CallStaticVoidMethod(const TArg1& tArg1,const TArg2& tArg2);
	void		CallStaticVoidMethod(const std::string& s);
	void		CallStaticVoidMethod(const std::string& s1,const std::string& s2);
public:
	JNIEnv*				GetEnv();
private:
	//��ȡJni��ID
	static jclass		GetJniClassID(JNIEnv * pEnv,const std::string& sClassName);
	//��ȡJni��̬����ID
	static jmethodID	GetJniStaticMethodID(JNIEnv *pEnv,jclass _nClassID, const std::string& sMethodName, const std::string& sParmCode); 
private:
	std::string	_sClassName;
	std::string	_sMethodName;
	std::string	_sParmCode;

	JNIEnv*		_pEnv;
	jclass		_nClassID;
	jmethodID	_nMethodID;
};

template<typename TArg1>
jobject CJniCaller::CallStaticObjectMethod(const TArg1 tArg )
{
	return _pEnv->CallStaticObjectMethod(_nClassID, _nMethodID,tArg);
}

template<typename TArg1,typename TArg2>
void CJniCaller::CallStaticVoidMethod(const TArg1& tArg1,const TArg2& tArg2 )
{
	_pEnv->CallStaticVoidMethod(_nClassID, _nMethodID,tArg1,tArg2);
}

template<typename TArg1>
void CJniCaller::CallStaticVoidMethod(const TArg1& tArg )
{
	_pEnv->CallStaticVoidMethod(_nClassID, _nMethodID,tArg);
}

template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5, typename TArg6>
jboolean CJniCaller::CallStaticBooleanMethod(const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5, const TArg6& tArg6)
{
	return _pEnv->CallStaticBooleanMethod(_nClassID, _nMethodID, tArg1, tArg2, tArg3, tArg4, tArg5 , tArg6);
}

template<typename TArg1, typename TArg2, typename TArg3, typename TArg4, typename TArg5>
jboolean CJniCaller::CallStaticBooleanMethod(const TArg1& tArg1, const TArg2& tArg2, const TArg3& tArg3, const TArg4& tArg4, const TArg5& tArg5)
{
	return _pEnv->CallStaticBooleanMethod(_nClassID, _nMethodID, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename TArg1,typename TArg2,typename TArg3,typename TArg4>
jboolean ToolFrame::CJniCaller::CallStaticBooleanMethod(const TArg1& tArg1,const TArg2& tArg2,const TArg3& tArg3,const TArg4& tArg4 )
{
	return _pEnv->CallStaticBooleanMethod(_nClassID, _nMethodID,tArg1,tArg2,tArg3,tArg4);
}

template<typename TArg1,typename TArg2,typename TArg3>
jboolean ToolFrame::CJniCaller::CallStaticBooleanMethod(const TArg1& tArg1,const TArg2& tArg2,const TArg3& tArg3 )
{
	return _pEnv->CallStaticBooleanMethod(_nClassID, _nMethodID,tArg1,tArg2,tArg3);
}

template<typename TArg1,typename TArg2>
jboolean ToolFrame::CJniCaller::CallStaticBooleanMethod(const TArg1& tArg1,const TArg2& tArg2 )
{
	return _pEnv->CallStaticBooleanMethod(_nClassID, _nMethodID,tArg1,tArg2);
}

template<typename TArg1>
jboolean CJniCaller::CallStaticBooleanMethod(const TArg1& tArg )
{
	return _pEnv->CallStaticBooleanMethod(_nClassID, _nMethodID,tArg);
}

NS_TOOL_FRAME_END

#endif
