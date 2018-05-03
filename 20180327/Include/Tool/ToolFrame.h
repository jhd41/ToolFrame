#pragma once
#include "Macro.h"

//基础工具
#include "ToolStd.h"
#include "ToolPlat.h"

#include "ToolCPlus11.h"

//因为cocos2d包含了windows.h因此不可以将其加入头文件
// #ifdef MACRO_LIB_COCOS2D
// #include "ToolCocos2d.h"
// #include "ToolCocos2dClass.h"
// #endif

#ifdef MACRO_LIB_BOOST
	#include "ToolBoost.h"
#endif

#ifdef MACRO_LIB_TINYXML
	#include "ToolXml.h"
#endif

//Ex
#include "ToolEx.h"

//Http
#include "ToolHttp.h"

//Intent
#include "ToolIntent.h"

#ifndef MACRO_CROSS_PLATFORM
#include "ToolWin.h"
#endif // MACRO_CROSS_PLATFORM

//Third
#include "ToolThird.h"

namespace ToolFrame{
	template<typename T>
	bool GetValueByAttributeFromXmlFile(const std::string& sPath,const std::string& sNamePath,T& tValue);

	//系统级别
	bool SystemInit();
	bool SystemRunOnce(int uTime);
	bool SystemRunOnce(uint64 uTime = 300);
};

template<typename T>
bool ToolFrame::GetValueByAttributeFromXmlFile( const std::string& sPath,const std::string& sNamePath,T& tValue )
{
	const std::string sFile = ToolFrame::LoadFile(sPath);

	TiXmlDocument xDoc;
	if (!ToolFrame::Parse(xDoc,sFile))return false;

	return ToolFrame::GetAttribute(&xDoc,sNamePath,tValue);
}

//动态类型转换并且声明变量(需要打开RTTI)
#define DECLARE_CAST_DYNAMIC(tT,tArgName,tArgSrc) tT tArgName;ToolFrame::DynamicCast(tArgName,tArgSrc);
//静态类型转换并且声明变量
#define DECLARE_CAST_STATIC(tT,tArgName,tArgSrc) tT tArgName;ToolFrame::StaticCast(tArgName,tArgSrc);
