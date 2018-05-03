#pragma once
#include "Macro.h"
#include "Date.h"

//2015-06-11 15:12:22
NS_TOOL_FRAME_BEGIN

class CDateTime
{
public:
	time_t		SetNowTime();
	std::string GetString()const;
	std::string GetString(const std::string& sFormat)const;//自定义格式返回 YYYY-MM-DD hh:mm:ss

	std::string GetDateString()const;			//仅获得日期字符串 2015-06-11
	std::string GetDateStringNumber()const;		//仅获得日期字符串 20150611

	CDate		GetDate()const;//获得日期

	bool		SetTime(time_t uTime);
	bool		SetTime(const std::string& sTime);
	bool		SetTime(const char* szTimeString);
	time_t		GetTime()const;

	bool		IsTimeInvaild()const;	//是否是无效时间
	bool		SetTimeInvaild();		//设置为无效时间
public:
	static std::string	NowString();
	static time_t		Now();
	static CDateTime	NowDateTime();
public:
	time_t			operator - (const CDateTime& datetime)const;		
	CDateTime		operator - (int nSeconds)const;		
	CDateTime&		operator -= (int nSeconds);
	CDateTime		operator + (int nSeconds)const;
	CDateTime&		operator +=(int nSeconds);
public:
	operator time_t(void)const{return _uTime;}
public:
	CDateTime(void);
	CDateTime(time_t uTime);
	CDateTime(const char* szTimeStirng);
	CDateTime(const std::string& sTime);
	CDateTime(const CDateTime& datetime);
	virtual ~CDateTime(void);
private:
	time_t _uTime;
};

NS_TOOL_FRAME_END
