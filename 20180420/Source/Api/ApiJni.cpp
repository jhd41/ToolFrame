#include "ApiJni.h"

#if MACRO_TARGET_OS == MACRO_OS_ANDROID

#include "JniCaller.h"

/*
注意事项：
1. getMethodInfo中最后一个参数的签名
boolean -----Z
byte    -----B
char    -----C
short   -----S
int     -----I
long    -----J
float   -----F
double  -----D
void    -----V
Object  -----Ljava/lang/String; L用/分割类的完整路径
Array   -----[Ljava/lang/String; [签名 [I
如果有多个请求参数，直接并列。这里注意Object对象结尾处的分号，示例：
IIII                   //四个整形参数
ILjava/lang/String;I   //整形，string类型，整形组合  (int x, String a, int y)

2. 参数与返回值的类型
boolean    -----jboolean       ---C/C++8位整型
byte       -----jbyte          ---C/C++8位带符号整型   
char       -----jchar          ---
short      -----jshort         ---
int        -----jint           ---
long       -----jlong          ---
float      -----jfloat         ---
double     -----jdouble        ---
Object     -----jobject        ---
Class      -----jclass         ---
String     -----jstring        ---
Object[]   -----jobjectArray   ---
boolean[]  -----jbooleanArray  ---
byte[]     -----jbyteArray     ---
char[]     -----jcharArray     ---
short[]    -----jshortArray    ---
int[]      -----jintArray      ---
long[]     -----jlongArray     ---
float[]    -----jfloatArray    ---  
double[]   -----jdoubleArray   ---

//jstring jmsg = minfo.env->NewStringUTF("http://www.baidu.com");
*/

USING_NS_TOOL_FRAME;

JavaVM*					ApiJni::_pJavaVM	= nullptr;
ApiJni::MapStringClass	ApiJni::_vClass;
CMutexRecursive			ApiJni::_mutex;
int						ApiJni::_nEnvCount	= 0;
JNIEnv*					ApiJni::_pEnv		= nullptr;
bool					ApiJni::_bAttached	= false;

void ApiJni::SetJavaVM( JavaVM* pJavaVM )
{
	_pJavaVM = pJavaVM;
}

JavaVM* ApiJni::GetJavaVM()
{
	return _pJavaVM;
}

CMutexRecursive& ApiJni::GetMutex()
{
	return _mutex;
}

JNIEnv*	ApiJni::GetEnvByJavaVM()
{
	JNIEnv* pEnv = nullptr;
	jint ret = ApiJni:: GetJavaVM()->GetEnv((void**)&pEnv,JNI_VERSION_1_4);
	switch (ret)
	{
	case JNI_OK :
		return pEnv;
	case JNI_EDETACHED:
		// Thread not attached

		return ApiJni::JniEnvAttachThread();
	case JNI_EVERSION :
		//LOGE("JNI interface version 1.4 not supported");
	default :
		//LOGE("Failed to get the environment using GetEnv()");
		return nullptr;
	}
}


bool ApiJni::IsAttachThread()
{
	return _bAttached;
}

JNIEnv* ApiJni::JniEnvAttachThread()
{
	// TODO : If calling AttachCurrentThread() on a native thread
	// must call DetachCurrentThread() in future.
	// see: http://developer.android.com/guide/practices/design/jni.html

	JNIEnv* pEnv = nullptr;
	if(ApiJni::GetJavaVM()->AttachCurrentThread(&pEnv,0)<0)
		return nullptr;

	_bAttached = true;
	return pEnv;
}

bool ApiJni::JniEnvDetachThread()
{
	if (!_bAttached)return false;
	
	if (JNI_OK != ApiJni::GetJavaVM()->DetachCurrentThread())return false;

	_bAttached = false;
	return true;
}

std::string	ApiJni::JString2String(jstring jstr)
{
	if (!jstr)return "";

	CJniEnvLock lock;
	CJniString xString(lock.GetEnv(),jstr);
	return xString.GetString();
}

std::string ApiJni::JString2String( JNIEnv* pEnv,jstring jstr )
{
	if (!jstr)return "";
	
	CJniString xString(pEnv,jstr);
	return xString.GetString();
}

bool ApiJni::CallJniReturnBool( const std::string& sPacketName,const std::string& sFuncName )
{
	CJniEnvLock lock;
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"()Z");
	return jniCaller.CallStaticBooleanMethod();
}

bool ApiJni::CallJniReturnBool( const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg )
{
	CJniEnvLock lock;
	CJniJString jniJString(lock.GetEnv(),sArg);
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"(Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString.GetString());
}

bool ApiJni::CallJniReturnBool( const std::string& sPacketName,const std::string& sFuncName,bool bArg )
{
	CJniEnvLock lock;
	jboolean jBool = bArg;
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"(Z)Z");
	return jniCaller.CallStaticBooleanMethod(jBool);
}

bool ApiJni::CallJniReturnBool( const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2 )
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(),sArg1);
	CJniJString jniJString2(lock.GetEnv(),sArg2);

	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"(Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(),jniJString2.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const std::string& sArg1, const std::string& sArg2, const std::string& sArg3)
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(), sArg1);
	CJniJString jniJString2(lock.GetEnv(), sArg2);
	CJniJString jniJString3(lock.GetEnv(), sArg3);

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(), jniJString2.GetString(), jniJString3.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const std::string& sArg1, const std::string& sArg2, const std::string& sArg3, const std::string& sArg4)
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(), sArg1);
	CJniJString jniJString2(lock.GetEnv(), sArg2);
	CJniJString jniJString3(lock.GetEnv(), sArg3);
	CJniJString jniJString4(lock.GetEnv(), sArg4);

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(), jniJString2.GetString(), jniJString3.GetString(), jniJString4.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const std::string& sArg1, const std::string& sArg2, const std::string& sArg3, const std::string& sArg4, const std::string& sArg5)
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(), sArg1);
	CJniJString jniJString2(lock.GetEnv(), sArg2);
	CJniJString jniJString3(lock.GetEnv(), sArg3);
	CJniJString jniJString4(lock.GetEnv(), sArg4);
	CJniJString jniJString5(lock.GetEnv(), sArg5);

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(), jniJString2.GetString(), jniJString3.GetString(), jniJString4.GetString(), jniJString5.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const std::string& sArg1, const std::string& sArg2, const std::string& sArg3, const std::string& sArg4, const std::string& sArg5, const std::string& sArg6)
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(), sArg1);
	CJniJString jniJString2(lock.GetEnv(), sArg2);
	CJniJString jniJString3(lock.GetEnv(), sArg3);
	CJniJString jniJString4(lock.GetEnv(), sArg4);
	CJniJString jniJString5(lock.GetEnv(), sArg5);
	CJniJString jniJString6(lock.GetEnv(), sArg6);

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(), jniJString2.GetString(), jniJString3.GetString(), jniJString4.GetString(), jniJString5.GetString(), jniJString6.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const std::string& sArg1, const std::string& sArg2, const std::string& sArg3, const std::string& sArg4, const std::string& sArg5, const std::string& sArg6, const std::string& sArg7)
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(), sArg1);
	CJniJString jniJString2(lock.GetEnv(), sArg2);
	CJniJString jniJString3(lock.GetEnv(), sArg3);
	CJniJString jniJString4(lock.GetEnv(), sArg4);
	CJniJString jniJString5(lock.GetEnv(), sArg5);
	CJniJString jniJString6(lock.GetEnv(), sArg6);
	CJniJString jniJString7(lock.GetEnv(), sArg7);

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(), jniJString2.GetString(), jniJString3.GetString(), jniJString4.GetString(), jniJString5.GetString(), jniJString6.GetString(), jniJString7.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const std::string& sArg1, const std::string& sArg2, const std::string& sArg3, const std::string& sArg4, const std::string& sArg5, const std::string& sArg6, const std::string& sArg7, const std::string& sArg8)
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(), sArg1);
	CJniJString jniJString2(lock.GetEnv(), sArg2);
	CJniJString jniJString3(lock.GetEnv(), sArg3);
	CJniJString jniJString4(lock.GetEnv(), sArg4);
	CJniJString jniJString5(lock.GetEnv(), sArg5);
	CJniJString jniJString6(lock.GetEnv(), sArg6);
	CJniJString jniJString7(lock.GetEnv(), sArg7);
	CJniJString jniJString8(lock.GetEnv(), sArg8);

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(), jniJString2.GetString(), jniJString3.GetString(), jniJString4.GetString(), jniJString5.GetString(), jniJString6.GetString(), jniJString7.GetString(), jniJString8.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const std::string& sArg1, const std::string& sArg2, const std::string& sArg3, const std::string& sArg4, const std::string& sArg5, const std::string& sArg6, const std::string& sArg7, const std::string& sArg8, const std::string& sArg9)
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(), sArg1);
	CJniJString jniJString2(lock.GetEnv(), sArg2);
	CJniJString jniJString3(lock.GetEnv(), sArg3);
	CJniJString jniJString4(lock.GetEnv(), sArg4);
	CJniJString jniJString5(lock.GetEnv(), sArg5);
	CJniJString jniJString6(lock.GetEnv(), sArg6);
	CJniJString jniJString7(lock.GetEnv(), sArg7);
	CJniJString jniJString8(lock.GetEnv(), sArg8);
	CJniJString jniJString9(lock.GetEnv(), sArg9);

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Z");
	return jniCaller.CallStaticBooleanMethod(jniJString1.GetString(), jniJString2.GetString(), jniJString3.GetString(), jniJString4.GetString(), jniJString5.GetString(), jniJString6.GetString(), jniJString7.GetString(), jniJString8.GetString(), jniJString9.GetString());
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, int nArg1)
{
	CJniEnvLock lock;
	jint arg1 = (jint)nArg1;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(I)Z");
	return jniCaller.CallStaticBooleanMethod(arg1);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, int nArg1, int nArg2)
{
	CJniEnvLock lock;
	jint arg1 = (jint)nArg1;
	jint arg2 = (jint)nArg2;

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(II)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, int nArg1, int nArg2, int nArg3)
{
	CJniEnvLock lock;
	jint arg1 = (jint)nArg1;
	jint arg2 = (jint)nArg2;
	jint arg3 = (jint)nArg3;

	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(III)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2, arg3);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, int nArg1, int nArg2, int nArg3, int nArg4)
{
	CJniEnvLock lock;
	jint arg1 = (jint)nArg1;
	jint arg2 = (jint)nArg2;
	jint arg3 = (jint)nArg3;
	jint arg4 = (jint)nArg4;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(IIII)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2, arg3, arg4);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, int nArg1, int nArg2, int nArg3, int nArg4, int nArg5)
{
	CJniEnvLock lock;
	jint arg1 = (jint)nArg1;
	jint arg2 = (jint)nArg2;
	jint arg3 = (jint)nArg3;
	jint arg4 = (jint)nArg4;
	jint arg5 = (jint)nArg5;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(IIIII)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2, arg3, arg4, arg5);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, long nArg1)
{
	CJniEnvLock lock;
	jlong arg1 = (jlong)nArg1;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(J)Z");
	return jniCaller.CallStaticBooleanMethod(arg1);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, long nArg1, long nArg2)
{
	CJniEnvLock lock;
	jlong arg1 = (jlong)nArg1;
	jlong arg2 = (jlong)nArg2;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(JJ)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, long nArg1, long nArg2, long nArg3)
{
	CJniEnvLock lock;
	jlong arg1 = (jlong)nArg1;
	jlong arg2 = (jlong)nArg2;
	jlong arg3 = (jlong)nArg3;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(JJJ)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2, arg3);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, long nArg1, long nArg2, long nArg3, long nArg4)
{
	CJniEnvLock lock;
	jlong arg1 = (jlong)nArg1;
	jlong arg2 = (jlong)nArg2;
	jlong arg3 = (jlong)nArg3;
	jlong arg4 = (jlong)nArg4;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(JJJJ)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2, arg3, arg4);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, long nArg1, long nArg2, long nArg3, long nArg4, long nArg5)
{
	CJniEnvLock lock;
	jlong arg1 = (jlong)nArg1;
	jlong arg2 = (jlong)nArg2;
	jlong arg3 = (jlong)nArg3;
	jlong arg4 = (jlong)nArg4;
	jlong arg5 = (jlong)nArg5;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "(JJJJJ)Z");
	return jniCaller.CallStaticBooleanMethod(arg1, arg2, arg3, arg4, arg5);
}

bool ApiJni::CallJniReturnBool(const std::string& sPacketName, const std::string& sFuncName, const ToolFrame::CArrayRefByte& arrByte)
{
	CJniEnvLock lock;

	CJniJByteArray jniJByteArray(lock.GetEnv(), arrByte.GetPtr(), arrByte.GetLength());
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "([B)z");

	return jniCaller.CallStaticBooleanMethod(jniJByteArray.GetArray());
}

int ApiJni::CallJniReturnInt(const std::string& sPacketName, const std::string& sFuncName)
{
	CJniEnvLock lock;
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"()I");
	return (int)jniCaller.CallStaticIntMethod();
}

long ApiJni::CallJniReturnLong( const std::string& sPacketName,const std::string& sFuncName )
{
	CJniEnvLock lock;
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"()J");
	return (long)jniCaller.CallStaticLongMethod();
}

std::string ApiJni::CallJniReturnString( const std::string& sPacketName,const std::string& sFuncName )
{
	CJniEnvLock lock;
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"()Ljava/lang/String;");
	jstring str = (jstring)jniCaller.CallStaticObjectMethod();
	if (!str)return "";
	return JString2String(lock.GetEnv(),str);
}

jobject ApiJni::CallJniReturnJObject(const std::string& sPacketName, const std::string& sFuncName)
{
	CJniEnvLock lock;
	CJniCaller jniCaller(lock.GetEnv(), sPacketName, sFuncName, "()Ljava/lang/Object;");
	return jniCaller.CallStaticObjectMethod();
}

void ApiJni::CallJniReturnVoid( const std::string& sPacketName,const std::string& sFuncName )
{
	CJniEnvLock lock;
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"()V");
	return jniCaller.CallStaticVoidMethod();
}

void ApiJni::CallJniReturnVoid( const std::string& sPacketName,const std::string& sFuncName,int nArg )
{
	CJniEnvLock lock;
	jint arg = (jint) nArg;
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"(I)V");
	return jniCaller.CallStaticVoidMethod(arg);
}

void ApiJni::CallJniReturnVoid( const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg )
{
	CJniEnvLock lock;
	CJniJString jniJString(lock.GetEnv(),sArg);
	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"(Ljava/lang/String;)V");
	return jniCaller.CallStaticVoidMethod(jniJString.GetString());
}

void ApiJni::CallJniReturnVoid( const std::string& sPacketName,const std::string& sFuncName,const std::string& sArg1,const std::string& sArg2 )
{
	CJniEnvLock lock;
	CJniJString jniJString1(lock.GetEnv(),sArg1);
	CJniJString jniJString2(lock.GetEnv(),sArg2);

	CJniCaller jniCaller(lock.GetEnv(),sPacketName,sFuncName,"(Ljava/lang/String;Ljava/lang/String;)V");
	return jniCaller.CallStaticVoidMethod(jniJString1.GetString(),jniJString2.GetString());
}

jclass ApiJni::FindClass( JNIEnv * pEnv,const std::string& sClassName )
{
	jclass jClassID = _vClass.GetPtrValueByKey(sClassName);
	if (nullptr != jClassID)return jClassID;

	jclass nClassID = pEnv->FindClass(sClassName.c_str());
	if (nullptr == nClassID)return nullptr;

	nClassID = pEnv->NewGlobalRef(nClassID);

	_vClass.Insert(sClassName,nClassID);
	return nClassID;
}

bool ApiJni::DeleteLocalRef( JNIEnv * pEnv,jclass nClassID )
{
	pEnv->DeleteLocalRef(nClassID);
	return true;
}

int ApiJni::GetEnvCount()
{
	return _nEnvCount;
}

int ApiJni::AddEnvCount()
{
	return ++_nEnvCount;
}

int ApiJni::RemoveEnvCount()
{
	return --_nEnvCount;
}

JNIEnv* ApiJni::SetEnv( JNIEnv* pEnv )
{
	_pEnv = pEnv;
	return _pEnv;
}

JNIEnv* ApiJni::GetEnv()
{
	return _pEnv;
}

#endif
