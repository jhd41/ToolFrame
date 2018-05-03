#pragma once

#include "MacroDefineEx.h"
#include "MacroDefineBoost.h"
#include "ToolStd.h"
#include "TArray.h"
#include "TThreadSaftyList.h"
#include "DateTime.h"
#include "Date.h"

//本类专门设计用于存放对自定义基本类的扩充
namespace ToolFrame
{
	//序列化:
	//外部可以单单重载一个函数Serialize,也可以通过重载两个函数Read/Write来执行。
	//符号重载:<< >> & 都只对两个参数模板有效

	//Serialize
	template<typename T>
	bool	Serialize(IStreamBase& iStream,T& tValue);
	//Serialize
	template<typename T>
	bool	Serialize(IStreamBase& iStream,const T& tValue);

	//Read/Write
	template<typename T>
	bool	Write(IStreamBase& iStream,const T& tValue);
	template<typename T>
	bool	Read(IStreamBase& iStream,T& tValue);

	//memcpy方式读取/写入内存
	template<typename T>
	bool	ReadCopy( ToolFrame::IStreamBase& iStream,T& tValue );
	template<typename T>
	bool	WriteCopy( ToolFrame::IStreamBase& iStream,const T& tValue );

	//常用变量的支持
	SERIALIZE_FUNCTION_COPY(bool);
	SERIALIZE_FUNCTION_COPY(char);
	SERIALIZE_FUNCTION_COPY(signed char);
	SERIALIZE_FUNCTION_COPY(short);
	SERIALIZE_FUNCTION_COPY(int);
	SERIALIZE_FUNCTION_COPY(long);
	SERIALIZE_FUNCTION_COPY(long long);

	SERIALIZE_FUNCTION_COPY(float);
	SERIALIZE_FUNCTION_COPY(double);

	SERIALIZE_FUNCTION_COPY(uchar);
	SERIALIZE_FUNCTION_COPY(ushort);
	SERIALIZE_FUNCTION_COPY(uint);
	SERIALIZE_FUNCTION_COPY(ulong);
	SERIALIZE_FUNCTION_COPY(ulonglong);

	//常用标准库 支持(写成模板特例化支持外部对标准库进行重载)
	template<>
	bool	Write(IStreamBase& iStream,const std::string& sString);
	template<>
	bool	Read(IStreamBase& iStream,std::string& sString);

	template<>
	bool	Write(IStreamBase& iStream,const CStreamBufferMalloc& buffer);
	template<>
	bool	Read(IStreamBase& iStream,CStreamBufferMalloc& buffer);

	template<>
	bool	Write(IStreamBase& iStream,const StreamBufferPtr& ptr);
	template<>
	bool	Read(IStreamBase& iStream,StreamBufferPtr& ptr);

	template<typename T,UINT uLenMax>
	bool	Write(IStreamBase& iStream,const TArray<T,uLenMax>& tArray);
	template<typename T,UINT uLenMax>
	bool	Read(IStreamBase& iStream,TArray<T,uLenMax>& tArray);

	//字符串支持
	template<typename TLenType, uint TLen,typename T>
	bool	WriteString(IStreamBase& iStream, const T& sString);
	template<typename TLenType, uint TLen, typename T>
	bool	ReadString(IStreamBase& iStream, T& sString);

	template<>
	bool	Write(IStreamBase& iStream, const String8& sString);
	template<>
	bool	Read(IStreamBase& iStream, String8& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String16& sString);
	template<>
	bool	Read(IStreamBase& iStream, String16& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String32& sString);
	template<>
	bool	Read(IStreamBase& iStream, String32& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String64& sString);
	template<>
	bool	Read(IStreamBase& iStream, String64& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String128& sString);
	template<>
	bool	Read(IStreamBase& iStream, String128& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String255& sString);
	template<>
	bool	Read(IStreamBase& iStream, String255& sString);

	template<>
	bool	Write(IStreamBase& iStream, const String512& sString);
	template<>
	bool	Read(IStreamBase& iStream, String512& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String1024& sString);
	template<>
	bool	Read(IStreamBase& iStream, String1024& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String2048& sString);
	template<>
	bool	Read(IStreamBase& iStream, String2048& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String4096& sString);
	template<>
	bool	Read(IStreamBase& iStream, String4096& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String8192& sString);
	template<>
	bool	Read(IStreamBase& iStream, String8192& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String16384& sString);
	template<>
	bool	Read(IStreamBase& iStream, String16384& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String32768& sString);
	template<>
	bool	Read(IStreamBase& iStream, String32768& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String65535& sString);
	template<>
	bool	Read(IStreamBase& iStream, String65535& sString);

	template<>
	bool	Write(IStreamBase& iStream, const String131072& sString);
	template<>
	bool	Read(IStreamBase& iStream, String131072& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String262144& sString);
	template<>
	bool	Read(IStreamBase& iStream, String262144& sString);
	template<>
	bool	Write(IStreamBase& iStream, const String524288& sString);
	template<>
	bool	Read(IStreamBase& iStream, String524288& sString);
	
	template<>
	bool	Write(IStreamBase& iStream, const StringByte& sString);
	template<>
	bool	Read(IStreamBase& iStream, StringByte& sString);
	template<>
	bool	Write(IStreamBase& iStream, const StringShort& sString);
	template<>
	bool	Read(IStreamBase& iStream, StringShort& sString);
	template<>
	bool	Write(IStreamBase& iStream, const StringLong& sString);
	template<>
	bool	Read(IStreamBase& iStream, StringLong& sString);

	//ToValue
	TO_VALUE(std::string, VectorString, String8,	VectorString8);
	TO_VALUE(std::string, VectorString, String16,	VectorString16);
	TO_VALUE(std::string, VectorString, String32,	VectorString32);
	TO_VALUE(std::string, VectorString, String64,	VectorString64);
	TO_VALUE(std::string, VectorString, String128,	VectorString128);
	TO_VALUE(std::string, VectorString, String255,	VectorString255);

	TO_VALUE(std::string, VectorString, String512,	VectorString512);
	TO_VALUE(std::string, VectorString, String1024, VectorString1024);
	TO_VALUE(std::string, VectorString, String2048, VectorString2048);
	TO_VALUE(std::string, VectorString, String4096, VectorString4096);
	TO_VALUE(std::string, VectorString, String8192, VectorString8192);
	TO_VALUE(std::string, VectorString, String16384,VectorString16384);
	TO_VALUE(std::string, VectorString, String32768,VectorString32768);
	TO_VALUE(std::string, VectorString, String65535,VectorString65535);

	TO_VALUE(std::string, VectorString, String131072, VectorString131072);
	TO_VALUE(std::string, VectorString, String262144, VectorString262144);
	TO_VALUE(std::string, VectorString, String524288, VectorString524288);

	TO_VALUE(std::string, VectorString, StringByte,	  VectorStringByte);
	TO_VALUE(std::string, VectorString, StringShort,  VectorStringShort);
	TO_VALUE(std::string, VectorString, StringLong,   VectorStringLong);

	//容器支持
	//容器支持 - vct
	template<typename T>
	bool	Write(IStreamBase& iStream,const std::vector<T>& vValue);
	template<typename T>
	bool	Read(IStreamBase& iStream,std::vector<T>& vValue);
	//容器支持 - lst
	template<typename T>
	bool	Write(IStreamBase& iStream,const std::list<T>& vValue);
	template<typename T>
	bool	Read(IStreamBase& iStream,std::list<T>& vValue);
	//容器支持 - set
	template<typename T>
	bool	Write(IStreamBase& iStream,const std::set<T>& vValue);
	template<typename T>
	bool	Read(IStreamBase& iStream,std::set<T>& vValue);
	//容器支持 - map
	template<typename T,typename K>
	bool	Write(IStreamBase& iStream,const std::map<T,K>& vValue);
	template<typename T,typename K>
	bool	Read(IStreamBase& iStream,std::map<T,K>& vValue);
	//容器支持 - multimap
	template<typename T,typename K>
	bool	Write(IStreamBase& iStream,const std::multimap<T,K>& vValue);
	template<typename T,typename K>
	bool	Read(IStreamBase& iStream,std::multimap<T,K>& vValue);
	//容器支持 - array
	template<typename T>
	bool	Write( IStreamBase& iStream,const T* tArray,int nLength );
	template<typename T>
	bool	Read( IStreamBase& iStream,T* tArray,int nLength );

	//操作符重载
	//重载<< 和 >> 号
	template<typename T>
	IStreamBase& operator <<(IStreamBase& iStream,const T& tValue);
	template<typename T>
	IStreamBase& operator >>(IStreamBase& iStream,T& tValue);

	//CStreamBuffer
	CStreamBuffer& operator <<(CStreamBuffer& iStream,std::fstream& fStream);
	CStreamBuffer& operator >>(CStreamBuffer& iStream,std::fstream& fStream);
	std::fstream& operator <<(std::fstream& fStream,CStreamBuffer& iStream);
	std::fstream& operator >>(std::fstream& fStream,CStreamBuffer& iStream);

	CStreamBuffer& operator <<(CStreamBuffer& iStream,std::ifstream& fStream);
	std::ifstream& operator >>(std::ifstream& fStream,CStreamBuffer& iStream);

	CStreamBuffer& operator >>(CStreamBuffer& iStream,std::ofstream& fStream);
	std::ofstream& operator <<(std::ofstream& fStream,CStreamBuffer& iStream);

	//CStreamBinary
	CStreamBinary& operator <<(CStreamBinary& iStream,std::fstream& fStream);
	CStreamBinary& operator >>(CStreamBinary& iStream,std::fstream& fStream);
	std::fstream& operator <<(std::fstream& fStream,CStreamBinary& iStream);
	std::fstream& operator >>(std::fstream& fStream,CStreamBinary& iStream);

	CStreamBinary& operator <<(CStreamBinary& iStream,std::ifstream& fStream);
	std::ifstream& operator >>(std::ifstream& fStream,CStreamBinary& iStream);

	CStreamBinary& operator >>(CStreamBinary& iStream,std::ofstream& fStream);
	std::ofstream& operator <<(std::ofstream& fStream,CStreamBinary& iStream);

	//TArray
	template<typename T>
	bool		operator <<(TArrayNew<T>& ar,IStreamBase& iStream);
	template<typename T>
	bool		operator >>(TArrayNew<T>& ar,IStreamBase& iStream);

	//重载&号
	template<typename T>
	IStreamBase& operator & (IStreamBase& iStream,T& tValue);
	template<typename T>
	IStreamBase& operator & (IStreamBase& iStream,const T& tValue);

	//设置2d传输最小单元变量大小(坐标存储类型)
	bool		SetPointValueType(EValueType eValueType);//默认为不受影响
	EValueType&	GetPointValueType();

	//CPoint2d
	bool ToValue(const std::string& tSrc,CPoint2d& tDes);
	bool ToValue(const CPoint2d& tSrc,std::string& tDes);

	bool ToValue(const std::string& tSrc,VectorPoint2d& tDes);
	bool ToValue(const VectorPoint2d& tSrc,std::string& tDes);

	template<>
	bool	Write(IStreamBase& iStream,const CPoint2d& pt);
	template<>
	bool	Read(IStreamBase& iStream,CPoint2d& pt);

	//CRect2d
	bool ToValue(const std::string& tSrc,CRect2d& tDes);
	bool ToValue(const CRect2d& tSrc,std::string& tDes);

	bool ToValue(const std::string& tSrc,VectorRect2d& tDes);
	bool ToValue(const VectorRect2d& tSrc,std::string& tDes);

	template<>
	bool	Write(IStreamBase& iStream,const CRect2d& pt);
	template<>
	bool	Read(IStreamBase& iStream,CRect2d& pt);

	//CPoint2di
	bool ToValue(const std::string& tSrc,CPoint2di& tDes);
	bool ToValue(const CPoint2di& tSrc,std::string& tDes);

	bool ToValue(const std::string& tSrc,VectorPoint2di& tDes);
	bool ToValue(const VectorPoint2di& tSrc,std::string& tDes);

	template<>
	bool	Write(IStreamBase& iStream,const CPoint2di& pt);
	template<>
	bool	Read(IStreamBase& iStream,CPoint2di& pt);

	//CDateTime
	bool ToValue(const char* szSrc,CDateTime& tDes);
	bool ToValue(const std::string& tSrc,CDateTime& tDes);
	bool ToValue(const CDateTime& tSrc,std::string& tDes);

	//CDate
	bool ToValue(const char* szSrc,CDate& tDes);
	bool ToValue(const std::string& tSrc,CDate& tDes);
	bool ToValue(const CDate& tSrc,std::string& tDes);

	template<>
	bool	Write(IStreamBase& iStream,const CDateTime& datetime);
	template<>
	bool	Read(IStreamBase& iStream,CDateTime& datetime);

	template<>
	bool	Write(IStreamBase& iStream,const CDate& date);
	template<>
	bool	Read(IStreamBase& iStream,CDate& date);
	
	template<typename T>
	bool	Delete(TThreadSaftyList<T>& vList);

	//2D
	bool		IsLessDistance(float fDistance,const CPoint2d& pt1,const CPoint2d& pt2);				//是否在两点范围内<
	float		CalDistance(const CPoint2d& pt1,const CPoint2d& pt2);									//计算两点间距离
	CPoint2d	CalReachTargetPoint(const CPoint2d& ptBegin,const CPoint2d& ptTarget,float fDistance);	//计算能够到达目标点 前的 最远点
	float		CalDistance(const ListPoint2d& vPoint);//计算点列 总长度
	CRect2d		MakeBoundingBox(const VectorPoint2d& vPoint);//制作绑定盒
	bool		MakeBoundingBox(CRect2d& rBoundingBox,const VectorPoint2d& vPoint);

	bool		Subtract(VectorPoint2d& vPoint,const CPoint2d& pt);//相减
	bool		Add(VectorPoint2d& vPoint,const CPoint2d& pt);//相加

	//2D坐标序列化辅助类函数
	template<typename TSrcType,typename TSrcDes,typename TPoint>
	bool		WritePointByValueTypeTarget(IStreamBase& iStream,const TPoint& pt);
	template<typename TSrcType,typename TPoint>
	bool		WritePointByValueType(IStreamBase& iStream,const TPoint& pt);
	template<typename TSrcType,typename TSrcDes,typename TPoint>
	bool		ReadPointByValueTypeTarget(IStreamBase& iStream, TPoint& pt);
	template<typename TSrcType,typename TPoint>
	bool		ReadPointByValueType(IStreamBase& iStream, TPoint& pt);
};

template<typename T>
bool ToolFrame::operator>>( TArrayNew<T>& ar,IStreamBase& iStream )
{
	iStream.SetDirection(IStreamBase::STREAM_INPUT);
	uint16 uSize = ar.GetLength();
	if (!ToolFrame::Write(iStream, uSize))return false;
	if (uSize <= 0)return true;

	const T* p = ar.GetPtr();
	if (!p)return false;

	for (size_t nIndex = 0; nIndex < uSize; ++nIndex)
	{
		if (!ToolFrame::Serialize(iStream, *p))return false;
		++p;
	}

	return true;
}

template<typename T>
bool ToolFrame::operator<<( TArrayNew<T>& ar,IStreamBase& iStream )
{
	iStream.SetDirection(IStreamBase::STREAM_OUTPUT);
	uint16 uSize = 0;
	if (!ToolFrame::Read(iStream, uSize))return false;
	if (uSize <= 0)return true;

	T* p = ar.GetPtr();
	if (!p)return false;
	
	for (size_t nIndex = 0; nIndex < uSize; ++nIndex)
	{
		if (!ToolFrame::Serialize(iStream,*p))return false;
		++p;
	}

	return ar.GetLength() == uSize;
}

template<typename T>
bool ToolFrame::Delete( TThreadSaftyList<T>& vList )
{
	if (vList.Empty())return true;

	CLockWrite lock(vList.GetMutex());
	ToolFrame::Delete(vList.GetList());

	return true;
}

//////////////////////////////////////////////////////////////////////////
//默认
template<typename T>
bool ToolFrame::Serialize( ToolFrame::IStreamBase& iStream,T& tValue )
{
	if (iStream.IsError())return false;

	switch(iStream.GetDirection())
	{
	case ToolFrame::IStreamBase::STREAM_INPUT:
		return ToolFrame::Write(iStream,(const T&)tValue);
		break;
	case ToolFrame::IStreamBase::STREAM_OUTPUT:
		return ToolFrame::Read(iStream,tValue);
		break;
	default:
		return false;
	}

	return false;
}

template<typename T>
bool ToolFrame::Serialize( IStreamBase& iStream,const T& tValue )
{
	return Serialize(iStream,(T&)tValue);
}

template<typename T>
bool ToolFrame::ReadCopy( IStreamBase& iStream,T& tValue )
{
	//不用考虑空间问题
	return iStream.Read(&tValue,sizeof(tValue));
}

template<typename T>
bool ToolFrame::WriteCopy( IStreamBase& iStream,const T& tValue )
{
	//不用考虑空间问题
	return iStream.Write(&tValue,sizeof(tValue));
}

//容器支持
template<typename T,typename K>
bool ToolFrame::Read( ToolFrame::IStreamBase& iStream,std::multimap<T,K>& vValue )
{
	uint16 uSize= 0;
	if (!ToolFrame::Read(iStream,uSize))return false;

	for (size_t nIndex =0;nIndex<uSize;++nIndex)
	{
		T tKey ;//没有初始化 外部使用时注意
		K tValue;//没有初始化 外部使用时注意
		if (!ToolFrame::Serialize(iStream,tKey))return false;
		if (!ToolFrame::Serialize(iStream,tValue))return false;

		if (!ToolFrame::Insert(vValue,tKey,tValue))return false;
	}

	return true;
}

template<typename T,typename K>
bool ToolFrame::Write( ToolFrame::IStreamBase& iStream,const std::multimap<T,K>& vValue )
{
	uint16 uLength = vValue.size();
	if (!ToolFrame::Write(iStream,uLength))return false;
	typename std::multimap<T,K>::const_iterator itr;
	foreach(itr,vValue){
		if (!ToolFrame::Serialize(iStream,itr->first))return false;
		if (!ToolFrame::Serialize(iStream,itr->second))return false;
	}

	return true;
}

//容器支持
template<typename T,typename K>
bool ToolFrame::Read( ToolFrame::IStreamBase& iStream,std::map<T,K>& vValue )
{
	uint16 uSize= 0;
	if (!ToolFrame::Read(iStream,uSize))return false;

	for (size_t nIndex =0;nIndex<uSize;++nIndex)
	{
		T tKey ;//没有初始化 外部使用时注意
		K tValue;//没有初始化 外部使用时注意
		if (!ToolFrame::Serialize(iStream,tKey))return false;
		if (!ToolFrame::Serialize(iStream,tValue))return false;

		if (!ToolFrame::Insert(vValue,tKey,tValue))return false;
	}

	return true;
}

template<typename T,typename K>
bool ToolFrame::Write( ToolFrame::IStreamBase& iStream,const std::map<T,K>& vValue )
{
	uint16 uLength = 0;
	if (!ToolFrame::ToValue(vValue.size(), uLength))return false;
	if (!ToolFrame::Write(iStream,uLength))return false;
	typename std::map<T,K>::const_iterator itr;
	foreach(itr,vValue){
		if (!ToolFrame::Serialize(iStream,itr->first))return false;
		if (!ToolFrame::Serialize(iStream,itr->second))return false;
	}

	return true;
}

template<typename T>
bool ToolFrame::Read( ToolFrame::IStreamBase& iStream,std::set<T>& vValue )
{
	uint16 uSize= 0;
	if (!ToolFrame::Read(iStream,uSize))return false;

	for (size_t nIndex =0;nIndex<uSize;++nIndex)
	{
		T nValue;//没有初始化 外部使用时注意
		if (!ToolFrame::Serialize(iStream,nValue))return false;
		if (!ToolFrame::Insert(vValue,nValue))return false;
	}

	return true;
}

template<typename T>
bool ToolFrame::Write( ToolFrame::IStreamBase& iStream,const std::set<T>& vValue )
{
	uint16 uLength = 0;
	if (!ToolFrame::ToValue(vValue.size(), uLength))return false;
	if (!ToolFrame::Write(iStream,uLength))return false;
	typename std::set<T>::const_iterator itr;
	foreach(itr,vValue){
		if (!ToolFrame::Serialize(iStream,*itr))return false;
	}

	return true;
}

template<typename T>
bool ToolFrame::Read( ToolFrame::IStreamBase& iStream,std::vector<T>& vValue )
{
	uint16 uSize= 0;
	if (!ToolFrame::Read(iStream,uSize))return false;
	for (size_t nIndex =0;nIndex<uSize;++nIndex)
	{
		T tValue;//没有初始化 外部使用时注意
		if (!ToolFrame::Serialize(iStream,tValue))return false;
		vValue.push_back(tValue);
	}

	return true;
}

template<typename T>
bool ToolFrame::Write( ToolFrame::IStreamBase& iStream,const std::vector<T>& vValue )
{
	uint16 uLength = 0;
	if (!ToolFrame::ToValue(vValue.size(), uLength))return false;
	if (!ToolFrame::Write(iStream,uLength))return false;
	typename std::vector<T>::const_iterator itr;
	foreach(itr,vValue){
		if (!ToolFrame::Serialize(iStream,*itr))return false;
	}

	return true;
}

template<typename T>
bool ToolFrame::Read( IStreamBase& iStream,std::list<T>& vValue )
{
	uint16 uSize= 0;
	if (!ToolFrame::Read(iStream,uSize))return false;
	for (size_t nIndex =0;nIndex<uSize;++nIndex)
	{
		T tValue;//没有初始化 外部使用时注意
		if (!ToolFrame::Serialize(iStream,tValue))return false;
		vValue.push_back(tValue);
	}

	return true;
}

template<typename T>
bool ToolFrame::Write( IStreamBase& iStream,const std::list<T>& vValue )
{
	uint16 uLength = 0;
	if (!ToolFrame::ToValue(vValue.size(), uLength))return false;
	if (!ToolFrame::Write(iStream,uLength))return false;
	typename std::list<T>::const_iterator itr;
	foreach(itr,vValue){
		if (!ToolFrame::Serialize(iStream,*itr))return false;
	}

	return true;
}

template<typename T>
bool ToolFrame::Write( ToolFrame::IStreamBase& iStream,const T* tArray,int nLength )
{
	if (!tArray)return false;

	for(int nIndex =0;nIndex<nLength;++nIndex){
		if (!ToolFrame::Serialize(iStream,tArray[nIndex]))return false;
	}
	return iStream.IsError();
}

template<typename T>
bool ToolFrame::Read( ToolFrame::IStreamBase& iStream,T* tArray,int nLength )
{
	if (!tArray)return false;

	for(int nIndex =0;nIndex<nLength;++nIndex){
		if (!ToolFrame::Serialize(iStream,tArray[nIndex]))return false;
	}
	return true;
}

template<typename T,UINT uLenMax>
bool ToolFrame::Write( IStreamBase& iStream,const TArray<T,uLenMax>& tArray )
{
	return iStream.Write(tArray.GetPtr(),tArray.GetLength() * sizeof(T));
}


template<typename T,UINT uLenMax>
bool ToolFrame::Read( IStreamBase& iStream,TArray<T,uLenMax>& tArray )
{
	if (iStream.GetLength() < uLenMax)return false;
	return iStream.Read(tArray.GetPtr(),tArray.GetLength() * sizeof(T));
}

//符号重载
//////////////////////////////////////////////////////////////////////////
template<typename T>
ToolFrame::IStreamBase& ToolFrame::operator&( ToolFrame::IStreamBase& iStream,T& tValue )
{
	if (iStream.IsError())
		return iStream;

	if (!Serialize(iStream,tValue))
		iStream.SetError();

	return iStream;
}

template<typename T>
ToolFrame::IStreamBase& ToolFrame::operator&( ToolFrame::IStreamBase& iStream,const T& tValue )
{
	return iStream & (T&)tValue;
}

template<typename T>
ToolFrame::IStreamBase& ToolFrame::operator>>( ToolFrame::IStreamBase& iStream,T& tValue )
{
	iStream.SetDirection(IStreamBase::STREAM_OUTPUT);
	if (!ToolFrame::Serialize(iStream,tValue))
		iStream.SetError();
	return iStream;
}

template<typename T>
ToolFrame::IStreamBase& ToolFrame::operator<<( ToolFrame::IStreamBase& iStream,const T& tValue )
{
	iStream.SetDirection(IStreamBase::STREAM_INPUT);
	if (!ToolFrame::Serialize(iStream,tValue))
		iStream.SetError();
	return iStream;
}

//其他函数
//////////////////////////////////////////////////////////////////////////



//坐标序列化辅助函数
//////////////////////////////////////////////////////////////////////////
template<typename TSrcType,typename TSrcDes,typename TPoint>
bool ToolFrame::WritePointByValueTypeTarget(IStreamBase& iStream,const TPoint& pt){
	TSrcDes x,y;
	if (!ToolFrame::ToValue(pt.GetX(),x))return false;
	if (!ToolFrame::ToValue(pt.GetY(),y))return false;

	if (!ToolFrame::Write(iStream,x))return false;
	if (!ToolFrame::Write(iStream,y))return false;
	return true;
}

template<typename TSrcType,typename TPoint>
bool ToolFrame::WritePointByValueType(IStreamBase& iStream,const TPoint& pt){
	switch (GetPointValueType())
	{
	case VALUE_TYPE_BOOL:
		return WritePointByValueTypeTarget<TSrcType,bool>(iStream,pt);
		break;
	case VALUE_TYPE_INT8:
		return WritePointByValueTypeTarget<TSrcType,int8>(iStream,pt);
		break;
	case VALUE_TYPE_UINT8:
		return WritePointByValueTypeTarget<TSrcType,uint8>(iStream,pt);
		break;
	case VALUE_TYPE_INT16:
		return WritePointByValueTypeTarget<TSrcType,int16>(iStream,pt);
		break;
	case VALUE_TYPE_UINT16:
		return WritePointByValueTypeTarget<TSrcType,uint16>(iStream,pt);
		break;
	case VALUE_TYPE_INT32:
		return WritePointByValueTypeTarget<TSrcType,int32>(iStream,pt);
		break;
	case VALUE_TYPE_UINT32:
		return WritePointByValueTypeTarget<TSrcType,uint32>(iStream,pt);
		break;
	case VALUE_TYPE_INT64:
		return WritePointByValueTypeTarget<TSrcType,int64>(iStream,pt);
		break;
	case VALUE_TYPE_UINT64:
		return WritePointByValueTypeTarget<TSrcType,uint64>(iStream,pt);
		break;
	default:
		return WritePointByValueTypeTarget<TSrcType,TSrcType>(iStream,pt);
	}

	return false;
}

template<typename TSrcType,typename TDesType,typename TPoint>
bool ToolFrame::ReadPointByValueTypeTarget(IStreamBase& iStream,TPoint& pt){
	TDesType xDes,yDes;
	if (!ToolFrame::Read(iStream,xDes))return false;
	if (!ToolFrame::Read(iStream,yDes))return false;

	TSrcType xSrc,ySrc;
	if (!ToolFrame::ToValue(xDes,xSrc))return false;
	if (!ToolFrame::ToValue(yDes,ySrc))return false;

	pt.SetXY(xSrc,ySrc);
	return true;
}

template<typename TSrcType,typename TPoint>
bool ToolFrame::ReadPointByValueType(IStreamBase& iStream,TPoint& pt){
	switch (GetPointValueType())
	{
	case VALUE_TYPE_BOOL:
		return ReadPointByValueTypeTarget<TSrcType,bool>(iStream,pt);
		break;
	case VALUE_TYPE_INT8:
		return ReadPointByValueTypeTarget<TSrcType,int8>(iStream,pt);
		break;
	case VALUE_TYPE_UINT8:
		return ReadPointByValueTypeTarget<TSrcType,uint8>(iStream,pt);
		break;
	case VALUE_TYPE_INT16:
		return ReadPointByValueTypeTarget<TSrcType,int16>(iStream,pt);
		break;
	case VALUE_TYPE_UINT16:
		return ReadPointByValueTypeTarget<TSrcType,uint16>(iStream,pt);
		break;
	case VALUE_TYPE_INT32:
		return ReadPointByValueTypeTarget<TSrcType,int32>(iStream,pt);
		break;
	case VALUE_TYPE_UINT32:
		return ReadPointByValueTypeTarget<TSrcType,uint32>(iStream,pt);
		break;
	case VALUE_TYPE_INT64:
		return ReadPointByValueTypeTarget<TSrcType,int64>(iStream,pt);
		break;
	case VALUE_TYPE_UINT64:
		return ReadPointByValueTypeTarget<TSrcType,uint64>(iStream,pt);
		break;
	default:	
		return ReadPointByValueTypeTarget<TSrcType,TSrcType>(iStream,pt);
	}

	return false;
}

