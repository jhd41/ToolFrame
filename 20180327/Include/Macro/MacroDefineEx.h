#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"

#include "Point2d.h"
#include "Rect2d.h"
#include "Point2di.h"

#include "MMemory.h"
#include "IPool.h"

#include "IThread.h"

#include "IStreamBase.h"
#include "StreamBuffer.h"
#include "StreamBufferMalloc.h"
#include "StreamBinary.h"

#include "TRenameClass.h"

NS_TOOL_FRAME_BEGIN

//�����Զ�����ĳ�������
class IStreamBase;
class CStreamBuffer;
class CStreamBufferMalloc;
class CStreamBinary;

typedef CSharePtr<IStreamBase>				IStreamPtr;
typedef CSharePtr<CStreamBuffer>			StreamBufferPtr;
typedef CSharePtr<CStreamBufferMalloc>		StreamBufferMallocPtr;
typedef CSharePtr<CStreamBinary>			StreamBinaryPtr;

typedef std::list<IStreamPtr>				ListStreamPtr;

typedef std::list<StreamBufferPtr>			ListStreamBuffer;
typedef std::list<StreamBufferPtr>			QueueStreamBuffer;

typedef std::list<StreamBinaryPtr>			ListStreamBinary;

typedef CSharePtr<IThread>					IThreadPtr;

typedef std::vector<CPoint2d>				VectorPoint2d;
typedef std::list<CPoint2d>					ListPoint2d;
typedef std::vector<CRect2d>				VectorRect2d;
typedef std::list<CRect2d>					ListRect2d;

typedef std::vector<CPoint2di>				VectorPoint2di;

//�ַ�������ܹ�����ĳ���
typedef TRenameClass<std::string, 1>		String8;
typedef TRenameClass<std::string, 2>		String16;
typedef TRenameClass<std::string, 3>		String32;
typedef TRenameClass<std::string, 4>		String64;
typedef TRenameClass<std::string, 5>		String128;
typedef TRenameClass<std::string, 6>		String255;

typedef TRenameClass<std::string, 7>		String512;
typedef TRenameClass<std::string, 8>		String1024;
typedef TRenameClass<std::string, 9>		String2048;
typedef TRenameClass<std::string, 10>		String4096;
typedef TRenameClass<std::string, 11>		String8192;
typedef TRenameClass<std::string, 12>		String16384;
typedef TRenameClass<std::string, 13>		String32768;
typedef TRenameClass<std::string, 14>		String65535;

typedef TRenameClass<std::string, 15>		String131072;
typedef TRenameClass<std::string, 16>		String262144;
typedef TRenameClass<std::string, 17>		String524288;

typedef TRenameClass<std::string, 100>		StringByte;
typedef TRenameClass<std::string, 101>		StringShort;
typedef TRenameClass<std::string, 102>		StringLong;

typedef std::vector<String8>				VectorString8;
typedef std::vector<String16>				VectorString16;
typedef std::vector<String32>				VectorString32;
typedef std::vector<String64>				VectorString64;
typedef std::vector<String128>				VectorString128;
typedef std::vector<String255>				VectorString255;
typedef std::vector<String512>				VectorString512;
typedef std::vector<String1024>				VectorString1024;
typedef std::vector<String2048>				VectorString2048;
typedef std::vector<String4096>				VectorString4096;
typedef std::vector<String8192>				VectorString8192;
typedef std::vector<String16384>			VectorString16384;
typedef std::vector<String32768>			VectorString32768;
typedef std::vector<String65535>			VectorString65535;
typedef std::vector<String131072>			VectorString131072;
typedef std::vector<String262144>			VectorString262144;
typedef std::vector<String524288>			VectorString524288;

typedef std::vector<StringByte>				VectorStringByte;
typedef std::vector<StringShort>			VectorStringShort;
typedef std::vector<StringLong>				VectorStringLong;

//���������干��ָ��
#define DEFINE_SHARE_PTR(TClassName,TPtrName)	class TClassName;\
												typedef CSharePtr<TClassName> TPtrName;\

#define DECLARE_SHARE_PTR(TClassName)			DEFINE_SHARE_PTR(TClassName,TClassName##Ptr);

//����ָ�봴������
#define MCREATER_FUN_CREATE_PTR(TClassName,TReturn,TPtr)	public:\
	static TReturn CreateClass()\
{\
	return TPtr(new TClassName());\
}

//����Ĭ�ϴ�������(ʹ�ø�������ͨ��Create���,�����Ѿ���ʼ��Ϊ0,���ȫ)
#define ZERO_CLASS_FUN(TClassName,TPtr)		protected:\
												TClassName(){}\
											public:\
												virtual ~TClassName(){}\
											public:\
												static TPtr Create(){ TPtr ptr(new TClassName()); return  ptr;}\
											public:\
												static void* operator new(uint uSize){return Malloc(uSize,false,false,true);}\
												static void	 operator delete(void* pMem){return Free(pMem,false);}\
												static void* operator new[](uint uSize){return Malloc(uSize,true,true,true);}\
												static void  operator delete[](void* pMem){return Free(pMem,true);}

//�������л�����
#define SERIALIZE_DECLARE(className)			template<typename T> bool Serialize(IStreamBase& iStream,T& t);template<> bool Serialize(IStreamBase& iStream,className& t);

#define SERIALIZE_FUNCTION(className,msg)		template<> inline bool Serialize(IStreamBase& iStream,className& t){iStream & msg;return !iStream.IsError();}
#define SERIALIZE_CLASS(className,msg)			namespace ToolFrame{SERIALIZE_FUNCTION(className,msg)};

#define SERIALIZE_FUNCTION_COPY(className)		template<> inline bool Read( ToolFrame::IStreamBase& iStream,className& tValue ){return ReadCopy(iStream,tValue);}\
												template<> inline bool Write( ToolFrame::IStreamBase& iStream,const className& tValue ){return WriteCopy(iStream,tValue);}
#define SERIALIZE_CLASS_COPY(className)			namespace ToolFrame{SERIALIZE_FUNCTION_COPY(className)};

//��ע:ʹ��ģ��ƫ�ػ�ʵ��,ԭ�����������������ȼ�����ģ�������,������ios ʹ�� gcc����ʱ,���Ӳ���ȷ��

//ToValue�������ٱ�д
#define TO_VALUE_ASS(tTypeSrc,tTypeDes) 				inline bool ToValue(const tTypeSrc& tSrc, tTypeDes& tDes) {\
																	tDes = tSrc;\
																	return true;\
																}

#define TO_VALUE_VECTOR(tVectorSrc,tVectorDes)			inline bool ToValue(const tVectorSrc& vSrc, tVectorDes& vDes) {\
																	if (vSrc.empty())return true;\
																	typename tVectorSrc::const_iterator itr;\
																	foreach(itr, vSrc) {\
																		vDes.push_back(*itr);\
																	}\
																	\
																	return true;\
																}

//ͬʱ����ת������ �Լ� ������ ת������
#define TO_VALUE(tTypeSrc,tVectorSrc,tTypeDes,tVectorDes) TO_VALUE_ASS(tTypeSrc,tTypeDes);TO_VALUE_ASS(tTypeDes,tTypeSrc);TO_VALUE_VECTOR(tVectorSrc,tVectorDes);TO_VALUE_VECTOR(tVectorDes,tVectorSrc);

NS_TOOL_FRAME_END

