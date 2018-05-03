#pragma once
#include "Macro.h"

class HIntent
{
public:
	virtual bool CallBackSelImg(const std::string& sUrl){return false;}
public:
	HIntent(){}
	virtual ~HIntent(){}
};

class MIntentHelper
{
	ST_INTANCE(MIntentHelper);
public:
	bool		SetIntentHander(HIntent* hIntent);
	HIntent*	GetIntentHander();
public:
	MIntentHelper(void);
	virtual ~MIntentHelper(void);
private:
	HIntent*	_hIntent;
};

