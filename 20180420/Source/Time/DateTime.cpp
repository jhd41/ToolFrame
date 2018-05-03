#include "DateTime.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN
CDateTime::CDateTime(void)
{
	_uTime = 0;
}

CDateTime::CDateTime( time_t uTime )
{
	SetTime(uTime);
}

CDateTime::CDateTime( const char* szTimeStirng )
{
	SetTime(szTimeStirng);
}

CDateTime::CDateTime( const std::string& sTime )
{
	SetTime(sTime);
}

CDateTime::CDateTime( const CDateTime& datetime )
{
	_uTime = datetime._uTime;
}

CDateTime::~CDateTime(void)
{
}

std::string CDateTime::NowString()
{
	return ToolFrame::GetNowTimeString();
}

time_t CDateTime::Now()
{
	return ToolFrame::GetNowTime();
}

time_t CDateTime::SetNowTime()
{
	return _uTime = Now();
}

std::string CDateTime::GetString() const
{
	//2015-06-11 15:12:22
	if (IsTimeInvaild())return "";
	return ToolFrame::TimeToString(_uTime);
}

std::string CDateTime::GetString( const std::string& sFormat ) const
{
	if (IsTimeInvaild())return "";
	return ToolFrame::TimeToString(_uTime,sFormat);
}

time_t CDateTime::GetTime() const
{
	return _uTime;
}

bool CDateTime::SetTime( time_t uTime )
{
	_uTime = uTime;
	return true;
}

bool CDateTime::SetTime( const std::string& sTime )
{
	if (sTime.empty()){
		_uTime = 0;
		return true;
	}

	return ToolFrame::StringToTime(sTime,_uTime);
}

bool CDateTime::SetTime( const char* szTimeString )
{
	if (!szTimeString)return false;
	return SetTime(std::string(szTimeString));
}

bool CDateTime::SetTimeInvaild()
{
	_uTime = 0;
	return true;
}

bool CDateTime::IsTimeInvaild() const
{
	return !_uTime;
}

CDateTime CDateTime::operator-( int nSeconds ) const
{
	return CDateTime(_uTime - nSeconds);
}

CDateTime& CDateTime::operator-=( int nSeconds )
{
	_uTime -= nSeconds;
	return *this;
}

CDateTime CDateTime::operator+( int nSeconds ) const
{
	return CDateTime(_uTime + nSeconds);
}

CDateTime& CDateTime::operator+=( int nSeconds )
{
	_uTime += nSeconds;
	return *this;
}

time_t CDateTime::operator-( const CDateTime& datetime ) const
{
	return _uTime - datetime._uTime;
}

CDateTime CDateTime::NowDateTime()
{
	CDateTime dateTime;
	dateTime.SetNowTime();
	return dateTime;
}

std::string CDateTime::GetDateString() const
{
	return ToolFrame::DateToString(_uTime);
}

std::string CDateTime::GetDateStringNumber() const
{
	return ToolFrame::DateToStringNumber(_uTime);
}

CDate CDateTime::GetDate() const
{
	return CDate(_uTime);
}

NS_TOOL_FRAME_END
