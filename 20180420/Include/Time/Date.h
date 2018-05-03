#pragma once

#include "Macro.h"

//2015-06-11
NS_TOOL_FRAME_BEGIN

class CDate
{
public:
	time_t		SetNowTime();
	std::string GetString()const;
	std::string GetString(const std::string& sFormat)const;//自定义格式返回 YYYY-MM-DD
	std::string GetStringNumber()const;//返回格式 YYYYMMDD

	bool		SetTime(time_t uTime);
	bool		SetTime(const std::string& sTime);
	bool		SetTime(const char* szTimeString);
	bool		SetTime(const std::string& sTime,const std::string& sFormat);//格式 YYYMMDD
	bool		SetTime(const char* szTimeString,const std::string& sFormat);//格式 YYYMMDD
	time_t		GetTime()const;

	bool		IsTimeInvaild()const;	//是否是无效时间
	bool		SetTimeInvaild();		//设置为无效时间
public:
	static time_t		Now();

	static CDate		Today();		//今天的日期
	static std::string	TodayString();
	static std::string	TodayStringNumber();
	
	static CDate		Tomorrow();		//明天的日期
	static std::string	TomorrowString();
	static std::string	TomorrowStringNumber();

	static CDate		Yesterday();		//昨天的日期
	static std::string	YesterdayString();
	static std::string	YesterdayStringNumber();

	static CDate		TodayOffset(int nOffSet=0);//距离今天往前 或 往后 多少天
	static std::string	TodayOffsetString(int nOffSet=0);
	static std::string	TodayOffsetStringNumber(int nOffSet=0);
public:
	int			operator - (const CDate& date)const;//相差多少天
	CDate		operator - (int nDays)const;		
	CDate&		operator -= (int nDays);
	CDate		operator + (int nDays)const;
	CDate&		operator +=(int nDays);
	CDate&		operator ++();
	CDate&		operator ++(int nDays);
	CDate&		operator --();
	CDate&		operator --(int nDays);
public:
	operator time_t(void)const{return _uTime;}
public:
	CDate(void);
	CDate(time_t uTime);
	CDate(const char* szTimeStirng);
	CDate(const std::string& sDate);
	CDate(const CDate& date);
	virtual ~CDate(void);
private:
	time_t _uTime;
};

NS_TOOL_FRAME_END
