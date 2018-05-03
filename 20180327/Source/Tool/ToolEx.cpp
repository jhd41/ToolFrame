#include "ToolEx.h"

#include "MLoger.h"
#include "ToolFrame.h"
#include "Ray2d.h"

using namespace ToolFrame;

//符号重载
//////////////////////////////////////////////////////////////////////////
class ToolExHelper
	:public CStreamBinary
{
public:
	template <typename T>
	static bool OutputFileStreamBinary(T& fStream,const CStreamBinary& iStream){
		DECLARE_CAST_STATIC(const ToolExHelper*,pStream,&iStream);
		if (pStream->IsEmpty())return true;

		ListStreamBufferPtr::const_iterator itr;
		foreach(itr,pStream->_vBuffer){
			StreamBufferPtr ptr = *itr;
			ASSERT_LOG_ERROR(ptr);

			fStream.write((const char*)ptr->GetBuffer(),ptr->GetLength());
		}
		return true;	
	}
	template <typename T>
	static bool InputFileStreamBinary(T& fStream,CStreamBinary& iStream){
		DECLARE_CAST_STATIC(ToolExHelper* ,pStream,&iStream);
		if(!ToolFrame::IsOpen(fStream))return false;

		UINT uFileLength = ToolFrame::GetStreamLength(fStream);
		StreamBufferPtr ptr(new CStreamBufferMalloc(uFileLength));
		fStream.read(ptr->GetMallocBuffer(), ptr->GetMaxSize());
		ptr->SetSize(uFileLength);
		ptr->SetWriteCursor(uFileLength);
		pStream->_vBuffer.push_back(ptr);

		//更新长度
		pStream->_uSize += uFileLength;
		return true;
	}

	template <typename T>
	static bool OutputFileStreamBuffer(T& fStream,const CStreamBuffer& iStream){
		if (iStream.IsEmpty())return true;

		fStream.write(iStream.GetBuffer(),iStream.GetLength());
		return true;
	}
	template <typename T>
	static bool InputFileStreamBuffer(T& fStream,CStreamBuffer& iStream){
		if(!ToolFrame::IsOpen(fStream))return false;

		size_t uFileLength = ToolFrame::GetStreamLength(fStream);
		size_t uUsedSize  = iStream.GetSize() +  uFileLength;
		if (uUsedSize > iStream.GetMaxSize())return false;
		
		fStream.read((char*)iStream.GetUnusedBuffer(),uFileLength);
		iStream.SetSize(uUsedSize);
		return true;
	}
};
//////////////////////////////////////////////////////////////////////////
CStreamBinary& ToolFrame::operator<<( CStreamBinary& iStream,std::fstream& fStream )
{
	if (!ToolExHelper::InputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return iStream;
}

CStreamBinary& ToolFrame::operator>>( CStreamBinary& iStream,std::fstream& fStream )
{
	if (!ToolExHelper::OutputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return iStream;
}

std::fstream& ToolFrame::operator>>( std::fstream& fStream,CStreamBinary& iStream )
{
	if (!ToolExHelper::InputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return fStream;
}

std::ifstream& ToolFrame::operator>>( std::ifstream& fStream,CStreamBinary& iStream )
{
	if (!ToolExHelper::InputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return fStream;
}

CStreamBinary& ToolFrame::operator>>( CStreamBinary& iStream,std::ofstream& fStream )
{
	if (!ToolExHelper::OutputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return iStream;
}

std::fstream& ToolFrame::operator<<( std::fstream& fStream,CStreamBinary& iStream )
{
	if (!ToolExHelper::OutputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return fStream;
}

CStreamBinary& ToolFrame::operator<<( CStreamBinary& iStream,std::ifstream& fStream )
{
	if (!ToolExHelper::InputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return iStream;
}

std::ofstream& ToolFrame::operator<<( std::ofstream& fStream,CStreamBinary& iStream )
{
	if (!ToolExHelper::OutputFileStreamBinary(fStream,iStream))
		iStream.SetError();
	return fStream;
}

//////////////////////////////////////////////////////////////////////////
CStreamBuffer& ToolFrame::operator<<( CStreamBuffer& iStream,std::fstream& fStream )
{
	if (!ToolExHelper::InputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return iStream;
}

CStreamBuffer& ToolFrame::operator>>( CStreamBuffer& iStream,std::fstream& fStream )
{
	if (!ToolExHelper::OutputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return iStream;
}

std::fstream& ToolFrame::operator<<( std::fstream& fStream,CStreamBuffer& iStream )
{
	if (!ToolExHelper::OutputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return fStream;
}

std::fstream& ToolFrame::operator>>( std::fstream& fStream,CStreamBuffer& iStream )
{
	if (!ToolExHelper::InputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return fStream;
}

CStreamBuffer& ToolFrame::operator<<( CStreamBuffer& iStream,std::ifstream& fStream )
{
	if (!ToolExHelper::InputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return iStream;
}

std::ifstream& ToolFrame::operator>>( std::ifstream& fStream,CStreamBuffer& iStream )
{
	if (!ToolExHelper::InputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return fStream;
}

CStreamBuffer& ToolFrame::operator>>( CStreamBuffer& iStream,std::ofstream& fStream )
{
	if (!ToolExHelper::OutputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return iStream;
}

std::ofstream& ToolFrame::operator<<( std::ofstream& fStream,CStreamBuffer& iStream )
{
	if (!ToolExHelper::OutputFileStreamBuffer(fStream,iStream))
		iStream.SetError();
	return fStream;
}

//////////////////////////////////////////////////////////////////////////
template<typename TLenType, uint TLen, typename T>
bool ToolFrame::WriteString(IStreamBase& iStream, const T& sString)
{
	if (sString.length() > TLen)return false;

	TLenType uLength = 0;
	if (!ToolFrame::ToValue(sString.length(), uLength))return false;
	if (!ToolFrame::Write(iStream, uLength))return false;
	return iStream.Write(sString.c_str(), sString.length());
}

template<typename TLenType, uint TLen, typename T>
bool ToolFrame::ReadString(IStreamBase& iStream, T& sString)
{
	TLenType uLength = 0;
	if (!ToolFrame::Read(iStream, uLength))return false;
	if (0 == uLength)
	{
		sString = "";
		return true;
	}

	if (uLength > TLen)return false;//硬性规定不能超过规定长度,可能内存申请不到从而挂掉。
	if (iStream.GetLength() < uLength)return false;
	
	TArrayNew<char> array(uLength + 1, false);
	if (!array)return false;
	if (!iStream.Read(array.GetPtr(), uLength))return false;
	array[array.GetLength() - 1] = 0;//末尾置零
	sString = array.GetPtr();

	return sString.length() == uLength;
}


template<>
bool ToolFrame::Write( IStreamBase& iStream,const std::string& sString )
{
	return WriteString<uint16,0xFFFF>(iStream, sString);
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,std::string& sString )
{
	return ReadString<uint16, 0xFFFF>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String8& sString)
{
	return WriteString<uint8, 8>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String8& sString)
{
	return ReadString<uint8, 8>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String16& sString)
{
	return WriteString<uint8, 16>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String16& sString)
{
	return ReadString<uint8, 16>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String32& sString)
{
	return WriteString<uint8, 32>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String32& sString)
{
	return ReadString<uint8, 32>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String64& sString)
{
	return WriteString<uint8, 64>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String64& sString)
{
	return ReadString<uint8, 64>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String128& sString)
{
	return WriteString<uint8, 128>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String128& sString)
{
	return ReadString<uint8, 128>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String255& sString)
{
	return WriteString<uint8, 255>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String255& sString)
{
	return ReadString<uint8, 255>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String512& sString)
{
	return WriteString<uint16, 512>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String512& sString)
{
	return ReadString<uint16, 512>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String1024& sString)
{
	return WriteString<uint16, 1024>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String1024& sString)
{
	return ReadString<uint16, 1024>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String2048& sString)
{
	return WriteString<uint16, 2048>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String2048& sString)
{
	return ReadString<uint16, 2048>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String4096& sString)
{
	return WriteString<uint16, 4096>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String4096& sString)
{
	return ReadString<uint16, 4096>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String8192& sString)
{
	return WriteString<uint16, 8192>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String8192& sString)
{
	return ReadString<uint16, 8192>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String16384& sString)
{
	return WriteString<uint16, 16384>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String16384& sString)
{
	return ReadString<uint16, 16384>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String32768& sString)
{
	return WriteString<uint16, 32768>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String32768& sString)
{
	return ReadString<uint16, 32768>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String65535& sString)
{
	return WriteString<uint16, 65535>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String65535& sString)
{
	return ReadString<uint16, 65535>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String131072& sString)
{
	return WriteString<uint32, 131072>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String131072& sString)
{
	return ReadString<uint32, 131072>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String262144& sString)
{
	return WriteString<uint32, 262144>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String262144& sString)
{
	return ReadString<uint32, 262144>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const String524288& sString)
{
	return WriteString<uint32, 524288>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, String524288& sString)
{
	return ReadString<uint32, 524288>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const StringByte& sString)
{
	return WriteString<uint8, 255>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, StringByte& sString)
{
	return ReadString<uint8, 255>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const StringShort& sString)
{
	return WriteString<uint16, 65535>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, StringShort& sString)
{
	return ReadString<uint16, 65535>(iStream, sString);
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const StringLong& sString)
{
	return WriteString<uint32, 524288>(iStream, sString);
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, StringLong& sString)
{
	return ReadString<uint32, 524288>(iStream, sString);
}

template<>
bool ToolFrame::Write( IStreamBase& iStream,const CStreamBufferMalloc& buffer )
{
	uint16 uLength = 0;
	if (!ToolFrame::ToValue(buffer.GetLength(), uLength))return false;
	if (!Write(iStream,uLength))return false;
	return iStream.Write(buffer.GetBuffer(),buffer.GetLength());
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,CStreamBufferMalloc& buffer )
{
	uint16 uLength=0;
	if (!Read(iStream,uLength))return false;
	if (iStream.GetLength() < uLength)return false;

	buffer.Resize(uLength);
	if (!iStream.Read(buffer.GetWriteBuffer(),uLength))return false;
	buffer.SetSize(uLength);
	buffer.SetWriteCursor(uLength);
	return true;
}

template<>
bool ToolFrame::Write( IStreamBase& iStream,const StreamBufferPtr& ptr )
{
	if (!ptr)return false;

	uint16 uLength = 0;
	if (!ToolFrame::ToValue(ptr->GetLength(), uLength))return false;
	if (!Write(iStream,uLength))return false;
	if (uLength <= 0)return true;
	return iStream.Write(ptr->GetBuffer(), ptr->GetLength());
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,StreamBufferPtr& ptr )
{
	uint16 uLength=0;
	if (!Read(iStream,uLength))return false;
	if (iStream.GetLength() < uLength)return false;

	ptr = StreamBufferMallocPtr(new CStreamBufferMalloc(uLength));
	if (!ptr->Write(iStream, uLength))return false;
	return true;
}

template<>
bool ToolFrame::Write(IStreamBase& iStream, const StreamBinaryPtr& ptr)
{
	if (!ptr)return false;

	uint16 uLength = 0;
	if (!ToolFrame::ToValue(ptr->GetLength(), uLength))return false;
	if (!Write(iStream, uLength))return false;
	if (uLength <= 0)return true;

	//写入数据 然后还原
	size_t uReadCursor = ptr->GetReadCursor();
	if (!iStream.Write(*ptr))
	{
		ptr->SetReadCursor(uReadCursor);
		return false;
	}

	ptr->SetReadCursor(uReadCursor);
	return true;
}

template<>
bool ToolFrame::Read(IStreamBase& iStream, StreamBinaryPtr& ptr)
{
	uint16 uLength = 0;
	if (!Read(iStream, uLength))return false;
	if (iStream.GetLength() < uLength)return false;

	ptr = StreamBinaryPtr(new CStreamBinary());

	StreamBufferPtr pBuffer(new CStreamBufferMalloc(uLength));
	if (!pBuffer->Write(iStream, uLength))return false;

	return ptr->Splice(pBuffer);
}

//////////////////////////////////////////////////////////////////////////
bool ToolFrame::ToValue( const std::string& tSrc,CPoint2d& tDes )
{
	VectorString vPointString;
	if (!ToolFrame::GetStringByFormat(vPointString,tSrc,"{Value}","({Value},{Value})","{Value},{Value}"))return false;
	if (vPointString.size() != 2)return false;

	float x=0,y=0;
	if (!ToValue(vPointString[0],x))return false;
	if (!ToValue(vPointString[1],y))return false;
	
	tDes.SetXY(x,y);
	return true;
}

bool ToolFrame::ToValue( const CPoint2d& tSrc,std::string& tDes )
{
	tDes = MAKE_STRING("("<<tSrc.GetX()<<","<<tSrc.GetY()<<")");
	return true;
}

bool ToolFrame::ToValue( const std::string& tSrc,VectorPoint2d& tDes )
{
	if (ToValue(tSrc,tDes,";"))return true;
	if (ToValue(tSrc,tDes," "))return true;
	
	return false;
}

bool ToolFrame::ToValue( const VectorPoint2d& tSrc,std::string& tDes )
{
	return ToValue(tSrc,tDes,";");
}

bool ToolFrame::ToValue( const VectorPoint2di& tSrc,std::string& tDes )
{
	return ToValue(tSrc,tDes,";");
}

template<>
bool ToolFrame::Write( IStreamBase& iStream,const CPoint2d& pt )
{
	return WritePointByValueType<float>(iStream,pt);
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,CPoint2d& pt )
{
	return ReadPointByValueType<float>(iStream,pt);
}

//////////////////////////////////////////////////////////////////////////
bool ToolFrame::ToValue( const std::string& tSrc,CRect2d& tDes )
{
	VectorString vPointString;
	if (!ToolFrame::GetStringByFormat(vPointString,tSrc,"{Value}","({Value},{Value},{Value},{Value})","{Value},{Value},{Value},{Value}"))return false;
	if (vPointString.size() != 4)return false;

	float x1=0,y1=0,x2=0,y2=0;
	if (!ToValue(vPointString[0],x1))return false;
	if (!ToValue(vPointString[1],y1))return false;
	if (!ToValue(vPointString[2],x2))return false;
	if (!ToValue(vPointString[3],y2))return false;

	tDes.SetLeftBottom(x1,y1);
	tDes.SetRightTop(x2,y2);
	return true;
}

bool ToolFrame::ToValue( const CRect2d& tSrc,std::string& tDes )
{
	tDes = MAKE_STRING("("<<tSrc.GetLeftBottom().GetX()<<","<<tSrc.GetLeftBottom().GetY()<<"," <<tSrc.GetRightTop().GetX()<<","<<tSrc.GetRightTop().GetY()<<")");
	return true;
}

bool ToolFrame::ToValue( const std::string& tSrc,VectorRect2d& tDes )
{
	return ToValue(tSrc,tDes,";");
}

bool ToolFrame::ToValue( const VectorRect2d& tSrc,std::string& tDes )
{
	return ToValue(tSrc,tDes,";");
}

template<>
bool ToolFrame::Write( IStreamBase& iStream,const CRect2d& pt )
{
	if (!ToolFrame::Write(iStream,pt.GetLeftBottom()))return false;
	if (!ToolFrame::Write(iStream,pt.GetRightTop()))return false;
	return true;
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,CRect2d& pt )
{
	CPoint2d ptLeftBottom,ptRightTop;
	if (!ToolFrame::Read(iStream,ptLeftBottom))return false;
	if (!ToolFrame::Read(iStream,ptRightTop))return false;

	pt.SetLeftBottom(ptLeftBottom);
	pt.SetRightTop(ptRightTop);
	return true;
}

bool ToolFrame::ToValue( const std::string& tSrc,CPoint2di& tDes )
{
	VectorString vPointString;
	if (!ToolFrame::GetStringByFormat(vPointString,tSrc,"{Value}","({Value},{Value})","{Value},{Value}"))return false;
	if (vPointString.size() != 2)return false;

	int x=0,y=0;
	if (!ToValue(vPointString[0],x))return false;
	if (!ToValue(vPointString[1],y))return false;

	tDes.SetXY(x,y);
	return true;
}

bool ToolFrame::ToValue( const CPoint2di& tSrc,std::string& tDes )
{
	tDes = MAKE_STRING("("<<tSrc.GetX()<<","<<tSrc.GetY()<<")");
	return true;
}

bool ToolFrame::ToValue( const std::string& tSrc,VectorPoint2di& tDes )
{
	if (ToValue(tSrc,tDes,";"))return true;
	if (ToValue(tSrc,tDes," "))return true;

	return false;
}

template<>
bool ToolFrame::Write( IStreamBase& iStream,const CPoint2di& pt )
{
	return WritePointByValueType<int>(iStream,pt);
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,CPoint2di& pt )
{
	return ReadPointByValueType<int>(iStream,pt);
}

bool ToolFrame::ToValue( const std::string& tSrc,CDateTime& tDes )
{
	return tDes.SetTime(tSrc);
}

bool ToolFrame::ToValue( const CDateTime& tSrc,std::string& tDes )
{
	tDes = tSrc.GetString();
	return true;
}

bool ToolFrame::ToValue( const char* szSrc,CDateTime& tDes )
{
	if (!szSrc)
		return tDes.SetTimeInvaild();

	return tDes.SetTime(szSrc);
}

bool ToolFrame::ToValue( const char* szSrc,CDate& tDes )
{
	if (!szSrc)
		return tDes.SetTimeInvaild();

	return tDes.SetTime(szSrc);
}

bool ToolFrame::ToValue( const std::string& tSrc,CDate& tDes )
{
	return tDes.SetTime(tSrc);
}

bool ToolFrame::ToValue( const CDate& tSrc,std::string& tDes )
{
	tDes = tSrc.GetString();
	return true;
}

template<>
bool ToolFrame::Write( IStreamBase& iStream,const CDateTime& datetime )
{
	uint32 uTime = (uint32)datetime.GetTime();
	return ToolFrame::Write(iStream,uTime);
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,CDateTime& datetime )
{
	uint32 uTime = 0;
	if (!ToolFrame::Read(iStream,uTime))return false;
	return datetime.SetTime(uTime);
}

template<>
bool ToolFrame::Write( IStreamBase& iStream,const CDate& date )
{
	uint32 uTime = (uint32)date.GetTime();
	return ToolFrame::Write(iStream,uTime);
}

template<>
bool ToolFrame::Read( IStreamBase& iStream,CDate& date )
{
	uint32 uTime = 0;
	if (!ToolFrame::Read(iStream,uTime))return false;
	return date.SetTime(uTime);
}

bool ToolFrame::IsLessDistance( float fDistance,const CPoint2d& pt1,const CPoint2d& pt2 )
{
	return fDistance < CalDistance(pt1,pt2);
}

float ToolFrame::CalDistance( const CPoint2d& pt1,const CPoint2d& pt2 )
{
	return pt1.Distance(pt2);
}

float ToolFrame::CalDistance( const ListPoint2d& vPoint )
{
	if (vPoint.size()<=1)return 0.f;
	
	float fDistance = 0.f;
	ListPoint2d::const_iterator itr = vPoint.begin();
	while (itr != vPoint.end())
	{
		const CPoint2d& pt1 = *itr;
		++itr;
		if (itr == vPoint.end())return fDistance;
		const CPoint2d& pt2 = *itr;
		fDistance += pt1.Distance(pt2);
	}
	return fDistance;
}

CPoint2d ToolFrame::CalReachTargetPoint( const CPoint2d& ptBegin,const CPoint2d& ptTarget,float fDistance )
{
	if (ptBegin == ptTarget)return ptBegin;

	float fDistanceTotal = ptBegin.Distance(ptTarget);
	if (fDistance > fDistanceTotal)return ptTarget;

	CRay2d ray(ptBegin,ptTarget);
	return ray.CalDistancePoint(fDistance);
}

CRect2d ToolFrame::MakeBoundingBox( const VectorPoint2d& vPoint )
{
	CRect2d rBoundingBox(vPoint.front());
	MakeBoundingBox(rBoundingBox,vPoint);
	return rBoundingBox;
}

bool ToolFrame::MakeBoundingBox( CRect2d& rBoundingBox,const VectorPoint2d& vPoint )
{
	if (vPoint.empty())return false;

	VectorPoint2d::const_iterator itr;
	foreach(itr,vPoint){
		rBoundingBox.Contain(*itr);
	}
	return true;
}

bool ToolFrame::Subtract( VectorPoint2d& vPoint,const CPoint2d& pt )
{
	VectorPoint2d::iterator itr;
	foreach(itr,vPoint){
		CPoint2d& ptPoint = *itr;
		ptPoint -= pt;
	}
	return true;
}

bool ToolFrame::Add( VectorPoint2d& vPoint,const CPoint2d& pt )
{
	VectorPoint2d::iterator itr;
	foreach(itr,vPoint){
		CPoint2d& ptPoint = *itr;
		ptPoint += pt;
	}
	return true;
}

bool ToolFrame::SetPointValueType( EValueType eValueType )
{
	if (GetPointValueType() == eValueType)return false;

	GetPointValueType() = eValueType;
	return true;
}

EValueType& ToolFrame::GetPointValueType()
{
	static EValueType g_eValueType = VALUE_TYPE_INVAILD;
	return g_eValueType;
}

