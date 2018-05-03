#pragma once

#include "Macro.h"

//2015-06-11
NS_TOOL_FRAME_BEGIN

class CDate
{
public:
	time_t		SetNowTime();
	std::string GetString()const;
	std::string GetString(const std::string& sFormat)const;//�Զ����ʽ���� YYYY-MM-DD
	std::string GetStringNumber()const;//���ظ�ʽ YYYYMMDD

	bool		SetTime(time_t uTime);
	bool		SetTime(const std::string& sTime);
	bool		SetTime(const char* szTimeString);
	bool		SetTime(const std::string& sTime,const std::string& sFormat);//��ʽ YYYMMDD
	bool		SetTime(const char* szTimeString,const std::string& sFormat);//��ʽ YYYMMDD
	time_t		GetTime()const;

	bool		IsTimeInvaild()const;	//�Ƿ�����Чʱ��
	bool		SetTimeInvaild();		//����Ϊ��Чʱ��
public:
	static time_t		Now();

	static CDate		Today();		//���������
	static std::string	TodayString();
	static std::string	TodayStringNumber();
	
	static CDate		Tomorrow();		//���������
	static std::string	TomorrowString();
	static std::string	TomorrowStringNumber();

	static CDate		Yesterday();		//���������
	static std::string	YesterdayString();
	static std::string	YesterdayStringNumber();

	static CDate		TodayOffset(int nOffSet=0);//���������ǰ �� ���� ������
	static std::string	TodayOffsetString(int nOffSet=0);
	static std::string	TodayOffsetStringNumber(int nOffSet=0);
public:
	int			operator - (const CDate& date)const;//��������
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
