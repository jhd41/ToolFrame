#include "JniCaller.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#include "ApiAndroid.h"
#include "ApiJni.h"

NS_TOOL_FRAME_BEGIN
//////////////////////////////////////////////////////////////////////////
//获取Jni环境
CJniEnvLock::CJniEnvLock() :_lock(ApiJni::GetMutex())
{
	if (1 == ApiJni::AddEnvCount())
	{
		JNIEnv*	pEnv = ApiJni::GetEnvByJavaVM();
		ApiJni::SetEnv(pEnv);
	}
}

CJniEnvLock::~CJniEnvLock()
{
	if (0 == ApiJni::RemoveEnvCount())
	{
		ApiJni::JniEnvDetachThread();
		ApiJni::SetEnv(nullptr);
	}
}

JNIEnv* CJniEnvLock::GetEnv() const
{
	return ApiJni::GetEnv();
}
//////////////////////////////////////////////////////////////////////////
//字节数组函数
CJniJByteArray::CJniJByteArray(JNIEnv* pEnv, const char* pBuff, uint uLength)
{
	_pEnv = pEnv;

	_jByteArray = _pEnv->NewByteArray(uLength);//建立jbarray数组

	jbyte* jBuff= (jbyte*)pBuff;  //BYTE强制转换成Jbyte；
	pEnv->SetByteArrayRegion(_jByteArray, 0, uLength, jBuff);            //将Jbyte 转换为jbarray数组
}

CJniJByteArray::~CJniJByteArray()
{

}

const jbyteArray& CJniJByteArray::GetArray() const
{
	return _jByteArray;
}

jbyteArray& CJniJByteArray::GetArray()
{
	return _jByteArray;
}

//////////////////////////////////////////////////////////////////////////
//字节数组函数
CJniByteArray::CJniByteArray( JNIEnv* pEnv, jbyteArray jByteArray )
{
	_pEnv = pEnv;
	_jByteArray = jByteArray;
	_isCopy = false;

	//取到数组的头和长度
	_arrayBody = pEnv->GetByteArrayElements(_jByteArray,&_isCopy);
	_theArrayLengthJ = pEnv->GetArrayLength(_jByteArray);
}

CJniByteArray::~CJniByteArray()
{
	if (_isCopy){
		_pEnv->ReleaseByteArrayElements(_jByteArray, _arrayBody,_theArrayLengthJ);
	}
}

char* CJniByteArray::GetPtr()
{
	return (char*)_arrayBody;
}

char* CJniByteArray::GetPtr() const
{
	return (char*)_arrayBody;
}

UINT CJniByteArray::GetLength() const
{
	return _theArrayLengthJ;
}

//////////////////////////////////////////////////////////////////////////
//字符串
CJniString::CJniString( JNIEnv* pEnv, jstring jstr )
{
	_pEnv = pEnv;
	_jstr = jstr;
	_isCopy = false;
	_szString = nullptr;
	
	if (jstr)
	{
		_szString = pEnv->GetStringUTFChars(jstr, &_isCopy);
		_sString = nullptr == _szString ? "" : _szString;
	}
}

CJniString::~CJniString()
{
	if (_isCopy){
		_pEnv->ReleaseStringUTFChars(_jstr,_szString);
	}
}

const std::string& CJniString::GetString() const
{
	return _sString;
}

//////////////////////////////////////////////////////////////////////////
//字符串
CJniJString::CJniJString( JNIEnv* pEnv, const std::string& sString )
{
	_pEnv = pEnv;
	_jstr = pEnv->NewStringUTF(sString.c_str());
}

CJniJString::~CJniJString()
{
	_pEnv->DeleteLocalRef(_jstr);
}

const jstring& CJniJString::GetString() const
{
	return _jstr;
}

jstring& CJniJString::GetString()
{
	return _jstr;
}
//////////////////////////////////////////////////////////////////////////
//Jni调用工具
CJniCaller::CJniCaller( JNIEnv* pEnv,const std::string& sClassName,const std::string& sMethodName,const std::string& sParmCode )
{
	_sClassName = sClassName;
	_sMethodName = sMethodName;
	_sParmCode = sParmCode;

	_pEnv = pEnv;
	_nClassID = GetJniClassID(_pEnv,sClassName);
	_nMethodID = GetJniStaticMethodID(_pEnv,_nClassID,sMethodName,sParmCode);
}

CJniCaller::~CJniCaller(void)
{
	//_pEnv->DeleteLocalRef(_nClassID);
}

JNIEnv* CJniCaller::GetEnv()
{
	return _pEnv;
}

jclass CJniCaller::GetJniClassID( JNIEnv * pEnv,const std::string& sClassName )
{
	jclass nClassID = ApiJni::FindClass(pEnv,sClassName);
	if (nullptr == nClassID) { 
		std::stringstream sStream;
		sStream<<sClassName<<FUN_FILE_LINE;
		ApiAndroid::LogDebug(sStream.str());
	} 

	return nClassID;
}

jmethodID CJniCaller::GetJniStaticMethodID( JNIEnv *pEnv,jclass _nClassID, const std::string& sMethodName, const std::string& sParmCode )
{
	jmethodID nMethodID = pEnv->GetStaticMethodID(_nClassID, sMethodName.c_str(), sParmCode.c_str());
	if (nullptr == nMethodID)
	{
		std::stringstream sStream;
		sStream<<"MethodName:"<<sMethodName<<" Code Sign:"<<sParmCode <<FUN_FILE_LINE;
		ApiAndroid::LogDebug(sStream.str());
	}
	return nMethodID;
}

jobject CJniCaller::CallStaticObjectMethod()
{
	return _pEnv->CallStaticObjectMethod(_nClassID, _nMethodID);
}

jboolean CJniCaller::CallStaticBooleanMethod()
{
	return _pEnv->CallStaticBooleanMethod(_nClassID, _nMethodID);
}

jlong CJniCaller::CallStaticLongMethod()
{
	return _pEnv->CallStaticLongMethod(_nClassID, _nMethodID);
}

jint CJniCaller::CallStaticIntMethod()
{
	return _pEnv->CallStaticIntMethod(_nClassID, _nMethodID);
}

void CJniCaller::CallStaticVoidMethod()
{
	return _pEnv->CallStaticVoidMethod(_nClassID, _nMethodID);
}

void CJniCaller::CallStaticVoidMethod( const std::string& s1,const std::string& s2 )
{
	CJniJString jniJStringS1(_pEnv,s1);
	CJniJString jniJStringS2(_pEnv,s2);
	return _pEnv->CallStaticVoidMethod(_nClassID, _nMethodID,jniJStringS1.GetString(),jniJStringS2.GetString());
}

void CJniCaller::CallStaticVoidMethod( const std::string& s )
{
	CJniJString jniJString(_pEnv,s);
	return _pEnv->CallStaticVoidMethod(_nClassID, _nMethodID,jniJString.GetString());
}

NS_TOOL_FRAME_END

#endif
