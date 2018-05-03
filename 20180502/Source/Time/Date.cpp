#include "Date.h"

#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN
CDate::CDate(void)
{
	_uTime = 0;
}

CDate::CDate( time_t uTime )
{
	SetTime(uTime);
}

CDate::CDate( const char* szTimeStirng )
{
	SetTime(szTimeStirng);
}

CDate::CDate( const std::string& sTime )
{
	SetTime(sTime);
}

CDate::CDate( const CDate& datetime )
{
	_uTime = datetime._uTime;
}

CDate::~CDate(void)
{
}

std::string CDate::TodayString()
{
	return Today().GetString();
}

std::string CDate::TodayStringNumber()
{
	return Today().GetStringNumber();
}

time_t CDate::Now()
{
	return ToolFrame::CalLocalHour(0,ToolFrame::GetNowTime());
}

time_t CDate::SetNowTime()
{
	return _uTime = Now();
}

std::string CDate::GetString() const
{
	//2015-06-11
	if (IsTimeInvaild())return "";
	return ToolFrame::DateToString(_uTime);
}

std::string CDate::GetString( const std::string& sFormat ) const
{
	if (IsTimeInvaild())return "";
	return ToolFrame::TimeToString(_uTime,sFormat);
}

time_t CDate::GetTime() const
{
	return _uTime;
}

bool CDate::SetTime( time_t uTime )
{
	_uTime = ToolFrame::CalLocalHour(0,uTime);
	return true;
}

bool CDate::SetTime( const std::string& sTime )
{
	if (sTime.empty()){
		_uTime = 0;
		return true;
	}

	return ToolFrame::StringToDate(sTime,_uTime);
}

bool CDate::SetTime( const char* szTimeString )
{
	if (!szTimeString)return false;
	return SetTime(std::string(szTimeString));
}

bool CDate::SetTime( const std::string& sTime,const std::string& sFormat )
{
	if (sTime.empty()){
		_uTime = 0;
		return true;
	}

	return ToolFrame::StringToDate(_uTime,sTime,sFormat);
}

bool CDate::SetTime( const char* szTimeString,const std::string& sFormat )
{
	if (!szTimeString)return false;
	return SetTime(std::string(szTimeString),sFormat);
}

bool CDate::SetTimeInvaild()
{
	_uTime = 0;
	return true;
}

bool CDate::IsTimeInvaild() const
{
	return !_uTime;
}

int CDate::operator-( const CDate& date ) const
{
	return ToolFrame::Difference(_uTime,date._uTime) / ToolFrame::GetSecondsEveryDay();
}

CDate CDate::operator-( int nDays ) const
{
	return CDate(_uTime - ToolFrame::GetSecondsEveryDay() * nDays);
}

CDate CDate::operator+( int nDays ) const
{
	return CDate(_uTime + ToolFrame::GetSecondsEveryDay() * nDays);
}

CDate& CDate::operator+=( int nDays )
{
	_uTime += ToolFrame::GetSecondsEveryDay() * nDays;
	return *this;
}

CDate& CDate::operator-=( int nDays )
{
	_uTime -= ToolFrame::GetSecondsEveryDay() * nDays;
	return *this;
}

CDate CDate::Today()
{
	CDate date;
	date.SetNowTime();
	return date;
}

ToolFrame::CDate CDate::Tomorrow()
{
	CDate date;
	date.SetNowTime();
	++date;
	return date;
}

std::string CDate::GetStringNumber() const
{
	return ToolFrame::DateToStringNumber(_uTime);
}

CDate& CDate::operator++()
{
	_uTime += ToolFrame::GetSecondsEveryDay();
	return *this;
}

CDate& CDate::operator++( int nDays )
{
	_uTime += ToolFrame::GetSecondsEveryDay();
	return *this;
}

std::string CDate::TomorrowString()
{
	return CDate::Tomorrow().GetString();
}

std::string CDate::TomorrowStringNumber()
{
	return CDate::Tomorrow().GetStringNumber();
}

ToolFrame::CDate CDate::Yesterday()
{
	CDate date;
	date.SetNowTime();
	--date;
	return date;
}

std::string CDate::YesterdayString()
{
	return CDate::Yesterday().GetString();
}

std::string CDate::YesterdayStringNumber()
{
	return CDate::Yesterday().GetStringNumber();
}

CDate& CDate::operator--()
{
	_uTime -= ToolFrame::GetSecondsEveryDay();
	return *this;
}

CDate& CDate::operator--( int nDays )
{
	_uTime -= ToolFrame::GetSecondsEveryDay();
	return *this;
}

ToolFrame::CDate CDate::TodayOffset( int nOffSet/*=0*/ )
{
	CDate date;
	date.SetNowTime();
	date += nOffSet;
	return date;
}

std::string CDate::TodayOffsetString( int nOffSet/*=0*/ )
{
	return CDate::TodayOffset(nOffSet).GetString();
}

std::string CDate::TodayOffsetStringNumber( int nOffSet/*=0*/ )
{
	return CDate::TodayOffset(nOffSet).GetStringNumber();
}

NS_TOOL_FRAME_END
