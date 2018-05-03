#include "ToolStd.h"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <locale>
#include <iomanip>

#define _USE_MATH_DEFINES
#include "math.h"

#include "ApiStd.h"

bool ToolFrame::ToValue( const std::string& sSrc,bool& tDes )
{
	if(sSrc.empty())return false;//若 为空 返回 ToValue失败
	
	//若为特殊字符串
	std::string sValue = sSrc;
	ToolFrame::ToLowerCase(sValue);
	if (sSrc == "true")
	{
		tDes = true;
		return true;
	}
	if (sSrc == "false")
	{
		tDes = false;
		return true;
	}

	//若为数值
	int nValue = 0;
	if (!ToolFrame::ToValue(sSrc,nValue))return false;
	tDes = 0 != nValue;//非0即真

	return true;
}

bool ToolFrame::ToValue(const std::string& sSrc,char* tDes){
	strcpy_s(tDes,sSrc.size()+1,sSrc.c_str());//只是屏蔽了警告 可能依然存在错误
	return true;
}

bool ToolFrame::ToValue( const char* szSrc,char* szDes,UINT uLength )
{
	strcpy_s(szDes,uLength,szSrc);
	return true;
}

bool ToolFrame::ToValue( const std::string& sSrc,char* szDes,UINT uLength )
{
	strcpy_s(szDes,uLength,sSrc.c_str());
	return true;
}

bool ToolFrame::ToValue( const std::string& sSrc,float& tDes )
{
	std::stringstream sStream;
	sStream<<sSrc;
	sStream>>tDes;

	return sStream.eof();
}

bool ToolFrame::ToValue( const std::string& sSrc,double& tDes )
{
	std::stringstream sStream;
	sStream<<sSrc;
	sStream>>tDes;
	return sStream.eof();
}

bool ToolFrame::ToValue( const std::string& sSrc, std::string& sDes )
{
	if (IsSelf(sSrc,sDes))return true;

	sDes = sSrc ;

	return true;
}

bool ToolFrame::ToValue( const char* szSrc, std::string& sDes )
{
	if (!szSrc)return false;

	sDes = szSrc;

	return true;
}

std::string ToolFrame::ToString( const char* szString )
{
	if (!szString)return "";

	return szString;
}

const std::string& ToolFrame::ToString( const std::string& sValue )
{
	return sValue;
}

bool ToolFrame::IsLetter(char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

bool ToolFrame::IsNumber(const char cSrc,int nNumberSystem )
{
	switch (nNumberSystem)
	{
	case NUMBER_SYSTEM_2:
		return cSrc >= '0' && cSrc <= '1';
		break;
	case NUMBER_SYSTEM_8:
		return cSrc >= '0' && cSrc <= '7';
		break;
	case NUMBER_SYSTEM_10:
		return cSrc >= '0' && cSrc <= '9';
		break;
	case NUMBER_SYSTEM_16:
		return (cSrc >= '0' && cSrc <= '9') || (cSrc >= 'A' && cSrc <= 'F');
		break;
	}

	assert(false);
	return false;
}

bool ToolFrame::IsNumber( const std::string& sSrc ,int nNumberSystem)
{
	if (sSrc.empty())return false;
	for (SSIZE_TYPE nIndex =0 ; nIndex < sSrc.length() ; ++nIndex)
	{
		if(!IsNumber(sSrc.at(nIndex),nNumberSystem))
			return false;
	}
	return true;
}

VectorString ToolFrame::SplitString( const std::string& sSrc,const std::string& sSP,bool bHold,bool bFront)
{
	VectorString vReturn;
	SplitString(vReturn,sSrc,sSP,bHold,bFront);
	return vReturn;
}

bool ToolFrame::SplitString( VectorString& vReturn,const std::string& sSrc,const std::string& sSP,bool bHold /*= false*/,bool bFront /*= false*/ )
{
	if (sSrc.empty())return true;
	if (sSP.empty())
	{
		vReturn.push_back(sSrc);
		return true;
	}

	SSIZE_TYPE nIndexCur = 0,nIndexBegin = 0,nIndexEnd = 0;

	while (true)
	{
		nIndexCur = sSrc.find(sSP,nIndexCur);
		if(std::string::npos == nIndexCur) break;

		//设置提取子串的终点位置
		if (bHold)
		{
			nIndexEnd = bFront ? nIndexCur + sSP.length() : nIndexCur;
		}else{
			nIndexEnd = nIndexCur;
		}

		vReturn.push_back(sSrc.substr(nIndexBegin,nIndexEnd - nIndexBegin));

		//设置下个提取子串的起点位置
		if (bHold)
		{
			nIndexBegin = bFront ? nIndexCur + sSP.length() : nIndexCur;
		}else{
			nIndexBegin = nIndexCur + sSP.length();
		}
		//设置下个搜索起点的位置
		nIndexCur += sSP.length();
	}
	vReturn.push_back(sSrc.substr(nIndexBegin,sSrc.length() - nIndexBegin));
	return true;
}

bool ToolFrame::GetMidString( std::string& sDes, const std::string& sSrc,const std::string& sBegin,const std::string& sEnd ,bool bFuzzy)
{
	//模糊查找,字符串 在中间即可,对两端不要求,遇到多个同样的字符串可能会返回错误。例如 "[aaa[bbb]ccc]",查找[]时 会 返回 aaa[bbb,
	//精确查找,对两端进行严格匹配。例如 对"[aaa[bbb]ccc]" 查询[]时 会返回 aaa[bbb]ccc
	if (bFuzzy)
	{
		SSIZE_TYPE uIndexStart = sSrc.find(sBegin);
		if (std::string::npos == uIndexStart)return false;
		uIndexStart += sBegin.length();

		SSIZE_TYPE uIndexEnd =  !sEnd.empty() ? sSrc.find(sEnd,uIndexStart):sSrc.length();
		if (std::string::npos == uIndexEnd)return false;

		sDes = sSrc.substr(uIndexStart,uIndexEnd - uIndexStart);
	}else
	{
		SSIZE_TYPE uIndexStart = sSrc.find(sBegin);
		if (0 != uIndexStart)return false;
		uIndexStart += sBegin.length();

		SSIZE_TYPE uIndexEnd = sSrc.rfind(sEnd);
		if (sSrc.length() -1 != uIndexEnd)return false;

		sDes = sSrc.substr(uIndexStart,uIndexEnd - uIndexStart);
	}
	return true;
}

bool ToolFrame::GetMidString( VectorString& vDes,const std::string& sSrc,const std::string& sBegin,const std::string& sEnd ,bool bFuzzy)
{
	//例子:"[aa][bb]d[cc]"查找[],使用模糊查找可以得到aa bb cc.使用精确查找则失败
	if (sSrc.empty())return true;

	if (bFuzzy)
	{
		SSIZE_TYPE nIndexStart = 0,nIndexEnd = 0;
		SSIZE_TYPE nIndexLast=0,nIndexCur=0;
		while(true){
			nIndexCur = sSrc.find(sBegin,nIndexLast);
			if (std::string::npos == nIndexCur)break;
			nIndexLast = nIndexCur + sBegin.length();
			nIndexStart = nIndexLast;

			nIndexCur = sSrc.find(sEnd,nIndexLast);
			if (std::string::npos == nIndexCur)break;
			nIndexEnd = nIndexCur;

			vDes.push_back(sSrc.substr(nIndexStart,nIndexEnd - nIndexStart));
		}

		return true;
	}else
	{
		SSIZE_TYPE nIndexStart = 0,nIndexEnd = 0;
		SSIZE_TYPE nIndexLast=0,nIndexCur=0;
		while(true){
			nIndexCur = sSrc.find(sBegin,nIndexLast);
			if (nIndexLast != nIndexCur)return false;
			nIndexStart = nIndexCur + sBegin.length();
			nIndexLast = nIndexStart;
			
			nIndexCur = sSrc.find(sEnd,nIndexLast);
			if (std::string::npos == nIndexCur)return false;
			nIndexEnd = nIndexCur;
			nIndexLast = nIndexEnd + sEnd.length();

			vDes.push_back(sSrc.substr(nIndexStart,nIndexEnd - nIndexStart));
		}

		return true;
	}

	return false;
}

std::string ToolFrame::GetMidString( const std::string& sSrc,const std::string& sBegin,const std::string& sEnd,bool bFuzzy /*= true */ )
{
	std::string sDes;
	return GetMidString(sDes,sSrc,sBegin,sEnd,bFuzzy) ? sDes : "";
}

VectorString ToolFrame::GetMidStringsHTML( const std::string& sSrc,const std::string& sBegin,const std::string& sEnd )
{
	//<li class="list-item" >
	//</li>
	VectorString vReturn;

	std::string sKey = sBegin.substr(0,3);

	SSIZE_TYPE nIndexStart = 0,nIndexEnd = 0;
	SSIZE_TYPE nIndexLast=0,nIndexCur=0;
	while(true){
		nIndexCur = sSrc.find(sBegin,nIndexLast);
		if (std::string::npos == nIndexCur)break;
		nIndexLast = nIndexCur + sBegin.length();
		nIndexStart = nIndexLast;//找到标签头

		//找与之对应的括号
		std::vector<SSIZE_TYPE> vTemp;//存放已经被匹配掉的key的位置

		do 
		{
			//挨着顺序往下找结束字符
			nIndexCur = sSrc.find(sEnd,nIndexLast);
			if (std::string::npos == nIndexCur)break;
			nIndexLast = nIndexCur + 1;

			//std::string sTemp = sSrc.substr(nIndexStart ,nIndexLast - nIndexStart);

			//每找到一个结束字符时 倒着往回找，找到与之匹配的关键字的位置
			SSIZE_TYPE nIndexLastTemp = nIndexLast;
			do 
			{
				nIndexCur = sSrc.rfind(sKey,nIndexLastTemp);
				if (std::string::npos == nIndexCur)
					return vReturn;
				nIndexLastTemp = nIndexCur - 1;

				//std::string sTemp1 = sSrc.substr(nIndexStart ,nIndexLastTemp - nIndexStart);
			} while (IsHasValue(vTemp,nIndexCur));

			//如果找到与之匹配的关键字的位置不是起点的位置，那么进行下一轮查找
			if (nIndexCur != nIndexStart - sBegin.length())
				vTemp.push_back(nIndexCur);
			else{
				nIndexEnd = nIndexLast - 1;
				break;
			}

		} while (true);

		//找到了关键字的终点位置之后
		std::string sFinded = sSrc.substr(nIndexStart,nIndexEnd - nIndexStart);
		vReturn.push_back(sFinded);
	}
	return vReturn;
}

const std::string& ToolFrame::ToLowerCase( std::string& sSrc )
{
	if (sSrc.empty())return sSrc;
	std::transform(sSrc.begin(), sSrc.end(), sSrc.begin(), tolower);
	return sSrc;
}

char ToolFrame::ToLowerCase(char ch)
{
	return tolower(ch);
}

bool ToolFrame::ToLowerCase(VectorString& vSrc)
{
	if (vSrc.empty())return true;
	VectorString::iterator itr;
	foreach(itr, vSrc) {
		ToLowerCase(*itr);
	}
	return true;
}

const std::string& ToolFrame::ToUpperCase(std::string& sSrc)
{
	if (sSrc.empty())return sSrc;
	std::transform(sSrc.begin(), sSrc.end(), sSrc.begin(), toupper);
	return sSrc;
}

char ToolFrame::ToUpperCase(char ch)
{
	return toupper(ch);
}

bool ToolFrame::ToUpperCase(VectorString& vSrc)
{
	if (vSrc.empty())return true;
	VectorString::iterator itr;
	foreach(itr, vSrc) {
		ToUpperCase(*itr);
	}
	return true;
}

std::string ToolFrame::EncodeURL(const std::string& sSrc)
{
	std::stringstream strResult;
	strResult<<"";
	unsigned char* pInTmp = (unsigned char*)sSrc.c_str();
	// do encoding
	while (*pInTmp)
	{
		if(isalnum(*pInTmp))
			strResult << *pInTmp;
		else
			if(isspace(*pInTmp))
				strResult << '+';
			else
			{
				strResult << '%';
				strResult << ToHex(*pInTmp>>4);
				strResult << ToHex(*pInTmp%16);
			}
			++pInTmp;
	}

	return strResult.str();
}
std::string ToolFrame::DecodeURL(const std::string& sString)
{
	std::string sResult = "";
	size_t uLen = sString.length();
	for(size_t nIndex=0;nIndex<uLen; ++nIndex)
	{
		if(sString.at(nIndex)=='%')
		{
			nIndex++;
			char ch = FromHex(sString.at(nIndex++));
			ch = ch << 4;
			ch += FromHex(sString.at(nIndex));
			sResult += ch;
		}
		else if(sString.at(nIndex)=='+')
			sResult += ' ';
		else
			sResult += sString.at(nIndex);
	}
	return sResult;
}

VectorString ToolFrame::GetValues( const std::string& sSrc,const VectorString& vFormat,const std::string& sValidFlag )
{
	if (vFormat.empty())
		return VectorString();

	VectorString vValue;

	SSIZE_TYPE nIndexBeigin = std::string::npos,nIndexEnd = std::string::npos;
	SSIZE_TYPE nIndexLast = 0,nIndexCur = 0;

	nIndexCur = sSrc.find(vFormat[0],nIndexLast);
	if(std::string::npos == nIndexCur)
		return VectorString();
	nIndexBeigin = nIndexLast = nIndexCur + vFormat[0].length();

	for(SSIZE_TYPE nIndex = 1 ;nIndex <=vFormat.size()-1;++nIndex){
		bool bVaild = false;
		std::string sFormat = vFormat[nIndex];
		if (IsBeginWith(sFormat,sValidFlag))
		{
			bVaild = true;
			sFormat = sFormat.substr(sValidFlag.length(),sFormat.length() - sValidFlag.length());
		}
		nIndexCur = sSrc.find(sFormat,nIndexLast);
		if(std::string::npos == nIndexCur)
			return VectorString();
		nIndexEnd = nIndexCur;

		if(bVaild)
			vValue.push_back(sSrc.substr(nIndexBeigin,nIndexEnd - nIndexBeigin));
		nIndexBeigin = nIndexLast = nIndexCur + sFormat.length();
	}
	return vValue;
}

std::vector<VectorString> ToolFrame::GetStringByFormat( const std::string& sSrc,const VectorString& vFormat )
{
	std::vector<VectorString> vResults;
	if (vFormat.empty())
		return vResults;

	VectorString vValue;

	SSIZE_TYPE nIndexBeigin = std::string::npos,nIndexEnd = std::string::npos;
	SSIZE_TYPE nIndexLast = 0,nIndexCur = 0;

	while(true){
		vValue.clear();
		nIndexCur = sSrc.find(vFormat[0],nIndexLast);
		if(std::string::npos == nIndexCur)
			return vResults;
		nIndexBeigin = nIndexLast = nIndexCur + vFormat[0].length();

		for(SSIZE_TYPE nIndex = 1 ;nIndex <=vFormat.size()-1;++nIndex){
			nIndexCur = sSrc.find(vFormat[nIndex],nIndexLast);
			if(std::string::npos == nIndexCur)
				return vResults;
			nIndexEnd = nIndexCur;

			vValue.push_back(sSrc.substr(nIndexBeigin,nIndexEnd - nIndexBeigin));
			nIndexBeigin = nIndexLast = nIndexCur + vFormat[nIndex].length();
		}
		vResults.push_back(vValue);
	}
}

std::vector<VectorString> ToolFrame::GetStringByFormat( const std::string& sSrc,const std::string& sTempalte,const std::string& sValueFlag,const std::string& sValidFlag )
{
	VectorString vFormat = SplitString(sTempalte,sValueFlag);
	return GetStringByFormat(sSrc,vFormat,sTempalte,sValueFlag);
}

std::vector<VectorString> ToolFrame::GetStringByFormat( const std::string& sSrc,const VectorString& vFormat,const std::string& sValueFlag,const std::string& sValidFlag )
{
	std::vector<VectorString> vResults;
	if (vFormat.empty())
		return vResults;

	VectorString vValue;

	SSIZE_TYPE nIndexBeigin = std::string::npos,nIndexEnd = std::string::npos;
	SSIZE_TYPE nIndexLast = 0,nIndexCur = 0;

	while(true){
		vValue.clear();

		nIndexCur = sSrc.find(vFormat[0],nIndexLast);
		if(std::string::npos == nIndexCur)
			return vResults;
		nIndexBeigin = nIndexLast = nIndexCur + vFormat[0].length();

		for(SSIZE_TYPE nIndex = 1 ;nIndex <=vFormat.size()-1;++nIndex){
			bool bVaild = false;
			std::string sFormat = vFormat[nIndex];
			if (IsBeginWith(sFormat,sValidFlag))
			{
				bVaild = true;
				sFormat = sFormat.substr(sValidFlag.length(),sFormat.length() - sValidFlag.length());
			}
			nIndexCur = sSrc.find(sFormat,nIndexLast);
			if(std::string::npos == nIndexCur)
				return vResults;
			nIndexEnd = nIndexCur;

			if(bVaild)
				vValue.push_back(sSrc.substr(nIndexBeigin,nIndexEnd - nIndexBeigin));
			nIndexBeigin = nIndexLast = nIndexCur + sFormat.length();
		}
		vResults.push_back(vValue);
	}
}

//sTempalte: {tpl-value}<{tpl-value}>
bool ToolFrame::GetStringByFormat( VectorString&vReturn, const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte )
{
	vReturn.clear();
	VectorString vFormat;

	//分离模板
	SplitString(vFormat,sTempalte,sValueFlag);

	//如果根本就不含模板变量
	if (vFormat.size() == 1){
		//判断输入是否和模板一致 一致返回true 否则返回false
		if (sSrc == sTempalte)
		{
			vReturn.push_back(sSrc);
			return true;
		}
		return false;
	}

	VectorSize vPos;
	//计算得到每个关键点的位置
	{
		SSIZE_TYPE nIndexLast = 0,nIndexCur = 0;//已解析到的位置以及当前位置的临时变量
		for(SSIZE_TYPE nIndex = 0 ;nIndex < vFormat.size();++nIndex){
			//找到模板解析字

			const std::string& sFormatMark = vFormat[nIndex];
			//末尾特殊处理
			if(nIndex == vFormat.size() -1 && sFormatMark == "")
			{
				vPos.push_back(sSrc.length());
			}else
			{
				nIndexCur = sSrc.find(sFormatMark,nIndexLast);

				if(std::string::npos == nIndexCur)return false;

				vPos.push_back(nIndexCur);
				nIndexLast = nIndexCur + sFormatMark.length();//计算偏移位置
			}
		}
	}

	//提取每个关键点之间的字符串
	for(SSIZE_TYPE nIndex = 0 ;nIndex < vPos.size()-1;++nIndex){//vPos.size() 一定 等于 vFormat.size() 并且大于1
		SSIZE_TYPE uIndexBegin	= vPos[nIndex]  + vFormat[nIndex].length();
		SSIZE_TYPE uIndexEnd	= vPos[nIndex+1];

		vReturn.push_back(sSrc.substr(uIndexBegin,uIndexEnd - uIndexBegin));
	}

	return true;//vReturn.size() == (vFormat.size() - 1) 这个检查没有意义,这是必然的

	//vReturn.clear();
	//
	//SVector vFormat;
	//SplitString(vFormat,sTempalte,sValueFlag);
	//if (vFormat.size() < 2)return true;
	//
	//SSIZE_TYPE nIndexLast = 0,nIndexCur = 0;	//已解析到的位置以及当前位置的临时变量
	//SSIZE_TYPE nIndexBeigin = -1,nIndexEnd = -1;//准备提取变量的起点 和 终点

	//for(SSIZE_TYPE nIndex = 0 ;nIndex < vFormat.size()-1;++nIndex){
	//	//找到两个模板之间的起点
	//	nIndexCur = sSrc.find(vFormat[nIndex],nIndexLast);
	//	if(std::string::npos == nIndexCur)return false;
	//	nIndexBeigin = nIndexCur+=vFormat[nIndex].length();

	//	//计算已解析的偏移位置
	//	nIndexLast += nIndexBeigin;

	//	//找到终点
	//	nIndexCur = sSrc.find(vFormat[nIndex + 1],nIndexLast);
	//	if(std::string::npos == nIndexCur)return false;
	//	nIndexEnd = nIndexCur;

	//	//提取值
	//	vReturn.push_back(sSrc.substr(nIndexBeigin,nIndexEnd-nIndexBeigin));

	//	//计算已解析的偏移位置
	//	nIndexLast += nIndexEnd-nIndexBeigin;
	//}
	//
	//return true;
}

bool ToolFrame::GetStringByFormat( VectorString&vReturn, const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte1,const std::string& sTempalte2 )
{
	if (GetStringByFormat(vReturn,sSrc,sValueFlag,sTempalte1))return true;
	return GetStringByFormat(vReturn,sSrc,sValueFlag,sTempalte2);
}

bool ToolFrame::GetStringByFormat( VectorString&vReturn, const std::string& sSrc,const std::string& sValueFlag,const VectorString& vTempalte )
{
	VectorString::const_iterator itr;
	foreach(itr,vTempalte){
		if (GetStringByFormat(vReturn,sSrc,sValueFlag,*itr))
			return true;
	}
	return false;
}

long ToolFrame::Replace( std::string& sString,const std::string& sSrc,const std::string& sDes )
{
	if (sString.empty())return 0;
	if (sSrc.empty())return 0;

	long nCount = 0;

	std::stringstream sStream;

	SSIZE_TYPE uPos=std::string::npos;
	SSIZE_TYPE uLast=0;
	while((uPos=sString.find(sSrc,uLast)) != std::string::npos){
		sStream<<sString.substr(uLast,uPos-uLast);
		sStream<<sDes;
		uLast = uPos + sSrc.length();
		
		++nCount;
	}
	sStream<<sString.substr(uLast,sString.length()-uLast);

	//返回
	sString = sStream.str();

	return nCount;
}

long ToolFrame::Replace(VectorString& vStrings,const std::string& sSrc,const std::string& sDes )
{
	if (vStrings.empty())return 0;

	long nCount = 0;
	VectorString::iterator itr;
	foreach(itr,vStrings){
		nCount += Replace(*itr,sSrc,sDes);
	}
	return nCount;
}

long ToolFrame::Replace( std::string& sSrc,const MapStringString& vMap )
{
	//算法特殊优化.
	if (sSrc.empty())return 0;
	if (vMap.empty())return 0;

	//初始化
	long nCount = 0;
	std::stringstream sStream;//返回流
	SSIZE_TYPE uLastIndex = 0;//目前替换到的源字符串位置
	
	MapStringSize vStringSize;//放置每个关键字在源字符串中出现的位置

	//初始化
	{
		MapStringString::const_iterator itr;
		foreach(itr,vMap){
			if (!ToolFrame::Insert(vStringSize,itr->first,std::string::npos))return -1;
		}
	}

	//找到每个关键字 在字符串中 最近出现的位置 若关键字没有出现 则 不再在容器中出现
	do 
	{
		{
			MapStringSize::iterator itr = vStringSize.begin();
			while(itr != vStringSize.end()){
				//当 当前的 Key的最近找到的值是无效的 或者 比当前的索引要小的话 更新下一个出现Key的位置
				if (std::string::npos == itr->second || uLastIndex > itr->second)
					itr->second = sSrc.find(itr->first,uLastIndex);

				if (std::string::npos == itr->second)
					itr = ToolFrame::EraseByItr(vStringSize,itr);
				else
					++itr;
			}

			//如果已经没有需要替换的 返回
			if (vStringSize.empty())
			{
				if (uLastIndex == 0)
					return 0;

				std::string  s = sSrc.substr(uLastIndex,sSrc.length()-uLastIndex);
				sStream<<s;
				sSrc = sStream.str();
				return nCount;
			}
		}

		//找到最早出现的Key
		MapStringSize::iterator itrMin = FindItrMinValue(vStringSize);
		if (itrMin == vStringSize.end())
		{
			//不可能
			assert(false);
			return nCount;
		}

		const std::string& sKeyMin = itrMin->first;
		std::string  s = sSrc.substr(uLastIndex,itrMin->second - uLastIndex);
		sStream<<s;
		sStream<<ToolFrame::GetValueByKey(vMap,sKeyMin);//vMap[sKeyMin]
		uLastIndex = itrMin->second + sKeyMin.length();
		++nCount;
	} while (true);

	return nCount;
}

bool ToolFrame::IsBeginWith( const std::string& sSrc,const std::string& sValue, SSIZE_TYPE uOffset /*= 0*/,bool bIgnoreCase/*=false*/ )
{
	if (sSrc.length() < sValue.length())
		return false;

	if (!bIgnoreCase)
		return sSrc.find(sValue,uOffset) == uOffset;

	return IsEqual(sSrc.substr(0,sValue.length()),sValue,true);
}

bool ToolFrame::IsBeginWith( const std::string& sSrc,const VectorString& vValue , SSIZE_TYPE uOffset)
{
	VectorString::const_iterator itr;
	foreach(itr,vValue){
		if (IsBeginWith(sSrc,*itr,uOffset))
			return true;
	}
	return false;
}

bool ToolFrame::IsEndWith( const std::string& sSrc,const std::string& sValue )
{
	return sSrc.rfind(sValue) == sSrc.length() - sValue.length();
}

std::string ToolFrame::StringCombine(const std::string& sSrc,const std::string& sValue )
{
	std::stringstream sStream;
	std::string sDoube = sValue;
	sDoube += sValue;

	SSIZE_TYPE nIndexStart = 0,nIndexEnd = 0;

	while(true){
		nIndexEnd = sSrc.find(sDoube,nIndexStart);
		if (std::string::npos == nIndexEnd){
			sStream << sSrc.substr(nIndexStart,sSrc.length() - nIndexStart).c_str();
			return sStream.str();
		}
		sStream << sSrc.substr(nIndexStart,nIndexEnd - nIndexStart).c_str();

		//剔除所有相同的字符串
		nIndexStart = nIndexEnd + sDoube.length();
		nIndexEnd = sSrc.find(sValue,nIndexStart);
		while(nIndexEnd == 0){
			nIndexStart = nIndexEnd + sValue.length();
			nIndexEnd = sSrc.find(sValue,nIndexStart);
		}
	}
	return sStream.str();
}

std::string ToolFrame::EncodeXML( const std::string& sSrc )
{
	//<![CDATA[level <= 10]]>
	std::string sReturn = "<![CDATA[";
	sReturn += sSrc;
	sReturn += "]]>";

	return sReturn;
}

void ToolFrame::EncodeXML(VectorString& vValues )
{
	VectorString::iterator itr;
	foreach(itr,vValues){
		*itr = EncodeXML(*itr);
	}
}
std::string ToolFrame::GetXMLString( const std::string& sLabel,const MapStringString* pvAttribute,const VectorString* pvValue,int nLayer /*= 0*/ )
{
	std::stringstream sStream;
	//head
	sStream << "<" << sLabel;
	if (pvAttribute)
	{
		sStream << " ";
		sStream << ToString(*pvAttribute);
	}
	sStream << ">" << std::endl;
	//body
	if (pvValue)
	{
		VectorString::const_iterator itrValue;
		foreach(itrValue,(*pvValue)){
			sStream << *itrValue << std::endl;
		}
	}
	//end
	sStream << "</" << sLabel << ">";

	return sStream.str();
}

std::string ToolFrame::GetXMLString( const std::string& sLabel,const MapStringString* pvAttribute,const std::string sValue,int nLayer /*= 0*/ )
{
	std::stringstream sStream;
	//head
	sStream << "<" << sLabel;
	if (pvAttribute)
	{
		sStream << " ";
		sStream << ToString(*pvAttribute);
	}
	sStream << ">" << sValue << "</" << sLabel << ">";

	return sStream.str();
}

void ToolFrame::Srand()
{
	srand((unsigned) time(nullptr));
}

std::string ToolFrame::PickDir(const std::string& sPath){
	std::string sSrcPath = sPath;
	Replace(sSrcPath,"\\","/");//linux

	SSIZE_TYPE nIndexCur = 0;
	nIndexCur = sSrcPath.rfind("/");
	if(std::string::npos == nIndexCur)
		return "";

	return sSrcPath.substr(0,nIndexCur + 1);
}
std::string ToolFrame::PickFileName(const std::string& sPath){
	std::string sSrcPath = sPath;
	Replace(sSrcPath,"\\","/");

	SSIZE_TYPE nIndexCur = sSrcPath.rfind("/");
	if(std::string::npos == nIndexCur)
		return sSrcPath;
	nIndexCur += sizeof('/');
	return sSrcPath.substr(nIndexCur,sSrcPath.length()-nIndexCur);
}

std::string ToolFrame::PickFileNameWithOutExt( const std::string& sPath )
{
	std::string sFileName = PickFileName(sPath);

	SSIZE_TYPE nIndex = sFileName.rfind('.');
	return sFileName.substr(0,nIndex);
}

std::string ToolFrame::TrimPath( const std::string& sPath )
{
	if (sPath.empty())return sPath;
	return ApiStd::TrimPath(sPath);
}

std::string ToolFrame::TrimDir( const std::string& sDir )
{
	if (sDir.empty())return sDir;

	std::string sDirTemp = ApiStd::TrimPath(sDir);

	if (!IsEndWith(sDirTemp,"/"))
		sDirTemp += "/";

	return sDirTemp;
}

int ToolFrame::Rand()
{
	//rand 上限 RAND_MAX
	return rand();
}

int ToolFrame::Rand( int nBegin,int nEnd )
{
	if (nEnd == nBegin)
		return nBegin;

	assert(nEnd > nBegin);
	uint uDiff = nEnd - nBegin + 1;
	uint nRand = uDiff < RAND_MAX ? Rand() : Rand32();
	return nRand % uDiff + nBegin;
}

uint16 ToolFrame::Rand8()
{
	return rand() % 0xFF;
}

uint16 ToolFrame::Rand16()
{
	return rand() + rand();
}

uint32 ToolFrame::Rand24()
{
	uint32 uRand = Rand16();
	uRand <<= 8;
	uRand |= Rand8();
	return uRand;
}

uint32 ToolFrame::Rand32()
{
	uint32 uRand = Rand16();
	uRand <<= 16;
	uRand |= Rand16();
	return uRand;
}

uint64 ToolFrame::Rand40()
{
	uint32 uRand = Rand32();
	uRand <<= 8;
	uRand |= Rand8();
	return uRand;
}

uint64 ToolFrame::Rand48(){
	uint64 uRand = Rand32();
	uRand <<= 16;
	uRand |= Rand16();
	return uRand;
}

uint64 ToolFrame::Rand56()
{
	uint64 uRand = Rand32();
	uRand <<= 24;
	uRand |= Rand24();
	return uRand;
}

uint64 ToolFrame::Rand64()
{
	uint64 uRand = Rand32();
	uRand <<= 32;
	uRand |= Rand32();
	return uRand;
}

void ToolFrame::EnumInsert( MapIntString& vct,int eEnum,const std::string& sValue )
{
	vct.insert(std::make_pair(eEnum,sValue));
}

const std::string& ToolFrame::EnumGetString( MapIntString& vct,int eFind,int eDefault )
{
	MapIntString::iterator itr = vct.find(eFind);
	if (itr == vct.end())
	{
		eFind = eDefault;
		itr  = vct.find(eFind);
		assert(itr != vct.end());
	}
	return itr->second;
}

int ToolFrame::EnumGetString( MapStringInt& vct,const std::string& sFind,int eDefault )
{
	MapStringInt::iterator itr;
	itr = vct.find(sFind);
	if (itr == vct.end())
	{
		return eDefault;
	}
	return itr->second;
}

int ToolFrame::GetLessCount( const std::set<int>& vVct,int nNumber )
{
	std::set<int>::const_iterator itrMax = vVct.upper_bound(nNumber);

	int nCount =0;
	for(std::set<int>::const_iterator itr = vVct.begin();itr != itrMax;++itr){
		++nCount;
	}

	return nCount;
}

bool ToolFrame::IsFloat( const std::string& sSrc )
{
	char* pReturn = nullptr;
	strtod(sSrc.c_str(),&pReturn);
	return pReturn != sSrc.c_str();
}

bool ToolFrame::IsBool( const std::string& sSrc )
{
	return IsInClosedInterval(sSrc,0,1);
}

bool ToolFrame::IsIP( const std::string& sValue )
{
	const std::string& sIP = sValue;
	VectorString vStrings;
	ToolFrame::SplitString(vStrings,sIP,".");
	if (vStrings.size() != 4)return false;

	VectorString::iterator itr;
	foreach(itr,vStrings){
		const std::string& s = *itr;
		if (!IsInClosedInterval(s,0,0xff))
			return false;
	}

	return true;
}

std::string ToolFrame::TrimString(const std::string& sString )
{
	return TrimString(sString,"\t ");
}

bool ToolFrame::TrimString(VectorString& vString)
{
	VectorString::iterator itr;
	foreach(itr, vString) {
		std::string& sString = *itr;
		sString = TrimString(sString);
	}

	return true;
}

std::string ToolFrame::TrimString(const std::string& sString, const char* const pCharSet)
{
	SSIZE_TYPE uBegin = sString.find_first_not_of(pCharSet);
	if (std::string::npos == uBegin)return "";

	SSIZE_TYPE uEnd = sString.find_last_not_of(pCharSet);
	if (std::string::npos == uEnd)return "";

	return sString.substr(uBegin,uEnd - uBegin+1);
}

bool ToolFrame::IsHas(const std::string& sSrc, const std::string& sDes, bool bIgnoreCase/*=false*/)
{
	if (sSrc.empty())return false;
	if (sDes.empty())return false;

	if (!bIgnoreCase)
		return	std::string::npos != sSrc.find(sDes);

	std::string t1 = sSrc;
	std::string t2 = sDes;
	ToolFrame::ToLowerCase(t1);
	ToolFrame::ToLowerCase(t2);
	
	return	std::string::npos != t1.find(t2);
}

bool ToolFrame::IsHas(const VectorString& vSrc, const std::string& sDes, bool bIgnoreCase /*= false*/)
{
	if (vSrc.empty())return false;
	if (sDes.empty())return false;
	
	VectorString::const_iterator itr;
	foreach(itr, vSrc){
		if (IsHas(*itr, sDes))return true;
	}

	return false;
}

void ToolFrame::LocaleChinese()
{
	setlocale(LC_ALL,"Chinese-simplified");//设置中文环境
}

void ToolFrame::LocaleC()
{
	setlocale(LC_ALL,"C");//还原
}

void ToolFrame::Locale()
{
	setlocale(LC_ALL,"");
}

void ToolFrame::Exit()
{
	exit(0);
}

std::string ToolFrame::ConvertBuff(const char* szBuff, uint uLength)
{
	std::stringstream sStream;
	sStream<<std::hex;

	for (uint nIndex =0;nIndex < uLength;++nIndex)
	{
		sStream.fill('0');
		sStream.width(2);

		sStream<<(unsigned int)szBuff[nIndex];
	}

	return sStream.str();
}

bool ToolFrame::ConvertValue( const std::string sSrc,char* sDes,size_t nDesLen )
{
	return ConvertValue(sSrc.c_str(),sSrc.length(),sDes,nDesLen);
}

bool ToolFrame::ConvertValue( const char* sSrc,size_t nSrcLen,char* sDes,size_t nDesLen )
{
	if (nSrcLen /2 != nDesLen )return false;

	std::stringstream sStream;

	int nBuff = 0;
	sStream>>std::hex;
	for (uint nIndex =0;nIndex < nSrcLen;nIndex += 2)
	{

		sStream.clear();
		sStream << sSrc[nIndex];
		sStream << sSrc[nIndex+1];

		sStream >> nBuff;
		sDes[nIndex/2] = nBuff;
	}

	return true;
}

bool ToolFrame::Clear( std::stringstream& sStream )
{
	sStream.str("");
	return true;
}

bool ToolFrame::Clear(std::string& sString)
{
	sString = ToolFrame::EmptyString();
	return true;
}

std::string ToolFrame::PeriodToString(uint uPeriod)
{
	uint uYear=0,uMonth=0,uDay=0,uHour=0,uMinute=0,uSecond=0;
	uYear	= uPeriod / GetSecondsEveryYear();
	uMonth	= uPeriod / GetSecondsEveryMonth()	% 12;
	uDay	= uPeriod / GetSecondsEveryDay()	% 30;
	uHour	= uPeriod / GetSecondsEveryHour()	% 24;
	uMinute = uPeriod / GetSecondsEveryMinute() % 60;
	uSecond = uPeriod / 1 % 60;

	std::stringstream sStream;
	if (uYear)sStream	<<uYear		<<"年";
	if (uMonth)sStream	<<uMonth	<<"个月";
	if (uDay)sStream	<<uDay		<<"天";
	if (uHour)sStream	<<uHour		<<"小时";
	if (uMinute)sStream	<<uMinute	<<"分钟";
	if (uSecond)sStream	<<uSecond	<<"秒";

	return sStream.str();
}

std::string ToolFrame::PeriodToString( uint uPeriod,const std::string& sFormat )
{
	if (sFormat.empty())return "";

	uint uYear=0,uMonth=0,uDay=0,uHour=0,uMinute=0,uSecond=0;
	uYear	= uPeriod / GetSecondsEveryYear();
	uMonth	= uPeriod / GetSecondsEveryMonth()	% 12;
	uDay	= uPeriod / GetSecondsEveryDay()	% 30;
	uHour	= uPeriod / GetSecondsEveryHour()	% 24;
	uMinute = uPeriod / GetSecondsEveryMinute() % 60;
	uSecond = uPeriod / 1 % 60;
	
	MapStringString vValue;
	if (!ToolFrame::InsertString(vValue,"YYYY",uYear,4))return "";
	if (!ToolFrame::InsertString(vValue,"yyyy",uYear,4))return "";
	if (!ToolFrame::InsertString(vValue,"MM",uMonth,2))return "";
	if (!ToolFrame::InsertString(vValue,"DD",uDay,2))return "";
	if (!ToolFrame::InsertString(vValue,"dd",uDay,2))return "";
	if (!ToolFrame::InsertString(vValue,"HH",uHour,2))return "";
	if (!ToolFrame::InsertString(vValue,"hh",uHour,2))return "";
	if (!ToolFrame::InsertString(vValue,"mm",uMinute,2))return "";
	if (!ToolFrame::InsertString(vValue,"SS",uSecond,2))return "";
	if (!ToolFrame::InsertString(vValue,"ss",uSecond,2))return "";

	std::string s = sFormat;
	if (-1 == ToolFrame::Replace(s,vValue))return "";

	return s;
}


time_t ToolFrame::StringToPeriod( const std::string& sPeriod )
{
	VectorString vValue;
	if (!ToolFrame::GetStringByFormat(vValue,sPeriod,"{tpl-value}","{tpl-value}年{tpl-value}个月{tpl-value}天{tpl-value}小时{tpl-value}分钟{tpl-value}秒"))return 0;
	std::vector<time_t> vTime;
	if (!ToolFrame::ToValue(vValue,vTime))return 0;

	return vTime[0]*GetSecondsEveryYear() + vTime[1]*GetSecondsEveryMonth() + vTime[2]*GetSecondsEveryDay() + vTime[3]*GetSecondsEveryHour() + vTime[4]*GetSecondsEveryMinute() + vTime[5];
}

int ToolFrame::GetSubNum( const std::string& sSrc,const std::string& sSub )
{
	int nCount=0;
	SSIZE_TYPE uTest = std::string::npos;

	uTest = sSrc.find(sSub,0);
	while (std::string::npos != uTest)
	{
		++nCount;
		uTest += sSub.length();
		uTest = sSrc.find(sSub,uTest);
	}

	return nCount;
}

int ToolFrame::GetBits( const bool&)
{
	return 1;
}

std::string ToolFrame::RemoveBeginString( const std::string& sSrc,const std::string& sRemove )
{
	if (!IsBeginWith(sSrc,sRemove))return sSrc;

	return sSrc.substr(sRemove.length(),sSrc.length() - sRemove.length());
}

std::string ToolFrame::RemoveEndString( const std::string& sSrc,const std::string& sRemove )
{
	if (!IsEndWith(sSrc,sRemove))return sSrc;

	return sSrc.substr(0,sSrc.length() - sRemove.length());
}

bool ToolFrame::Insert(SetInt& vSet, int tValue)
{
	size_t uSize = vSet.size();
	vSet.insert(tValue);
	return vSet.size() == uSize + 1;
}

bool ToolFrame::Insert( MapIntInt& vMap,int nKey,int nValue )
{
	size_t uSize = vMap.size();
	vMap[nKey] = nValue;
	return vMap.size() == uSize + 1;
}

bool ToolFrame::InsertString( MapIntString& vMap,int nKey,const std::string& sValue )
{
	size_t uSize = vMap.size();
	vMap[nKey] = sValue;
	return vMap.size() == uSize + 1;
}

bool ToolFrame::Insert( MultiSetInt& vSet,int tValue )
{
	size_t uSize = vSet.size();
	vSet.insert(tValue);
	return vSet.size() == uSize + 1;
}

bool ToolFrame::Insert( VectorInt& vVct,int tValue )
{
	vVct.push_back(tValue);
	return true;
}

bool ToolFrame::Insert( ListInt& vVct,int tValue )
{
	vVct.push_back(tValue);
	return true;
}

bool ToolFrame::InsertString( MapStringString& vMap,const std::string& sKey,int nValue,int nWidth/*=0*/,char chFill/*='0'*/ )
{
	std::stringstream sStream;
	if (nWidth > 0)
		sStream<<std::setw(nWidth)<<std::setfill(chFill);
	
	sStream<<nValue;
	
	return Insert(vMap,sKey,sStream.str());
}

int ToolFrame::RandValue(const VectorInt& vSrc,int tDefalut )
{
	if (vSrc.empty())return tDefalut;

	return RandValue(vSrc);
}

int ToolFrame::RandValue(const SetInt& vSrc,int tDefalut )
{
	if (vSrc.empty())return tDefalut;

	return RandValue(vSrc);
}

std::string ToolFrame::TimeToString( time_t tTime,const std::string& sFormat )
{
	//大写的MM代表月份,小写的mm代表分钟参考CString的写法
	//YYYY-MM-DD:hh-mm-ss
	if (0 == tTime)return "";
	if (sFormat.empty())return "";

	tm tmTm = {0};
	if (localtime_s(&tmTm,&tTime))return "";

	MapStringString vValue;
	if (!ToolFrame::InsertString(vValue,"YYYY",tmTm.tm_year+1900,4))return "";
	if (!ToolFrame::InsertString(vValue,"yyyy",tmTm.tm_year+1900,4))return "";
	if (!ToolFrame::InsertString(vValue,"MM",tmTm.tm_mon+1,2))return "";
	if (!ToolFrame::InsertString(vValue,"DD",tmTm.tm_mday,2))return "";
	if (!ToolFrame::InsertString(vValue,"dd",tmTm.tm_mday,2))return "";
	if (!ToolFrame::InsertString(vValue,"HH",tmTm.tm_hour,2))return "";
	if (!ToolFrame::InsertString(vValue,"hh",tmTm.tm_hour,2))return "";
	if (!ToolFrame::InsertString(vValue,"mm",tmTm.tm_min,2))return "";
	if (!ToolFrame::InsertString(vValue,"SS",tmTm.tm_sec,2))return "";
	if (!ToolFrame::InsertString(vValue,"ss",tmTm.tm_sec,2))return "";

	std::string s = sFormat;
	if (-1 == ToolFrame::Replace(s,vValue))return "";

	return s;
}

std::string ToolFrame::TimeToString( time_t tTime )
{
	char szData[64] = {0};

	tm tmTm = {0};
	if (localtime_s(&tmTm,&tTime))return "";

	_snprintf_s(szData,sizeof(szData), 60, "%4d-%02d-%02d %02d:%02d:%02d", tmTm.tm_year+1900, tmTm.tm_mon+1, tmTm.tm_mday, tmTm.tm_hour, tmTm.tm_min, tmTm.tm_sec);
	return szData;
}

bool ToolFrame::StringToTime( const std::string& sSrc,time_t& tDes )
{
	if (sSrc.empty())return false;

	struct tm p; 
	if (0 == sscanf_s(sSrc.c_str(),"%4d-%02d-%02d %02d:%02d:%02d",&p.tm_year,&p.tm_mon,&p.tm_mday,&p.tm_hour,&p.tm_min,&p.tm_sec))
		return false;
	p.tm_year -= 1900;
	p.tm_mon -= 1;

	tDes = mktime(&p);
	return true;
}

std::string ToolFrame::TimeToStringMill(uint64 tTime)
{
	return TimeToString(tTime / 1000);
}

std::string ToolFrame::TimeToStringMill(uint64 tTime, const std::string& sFormat)
{
	return TimeToString(tTime / 1000, sFormat);
}

std::string ToolFrame::DateToString( time_t tTime )
{
	char szData[64] = {0};

	tm tmTm = {0};
	if (localtime_s(&tmTm,&tTime))return "";

	_snprintf_s(szData,sizeof(szData), 60, "%4d-%02d-%02d", tmTm.tm_year+1900, tmTm.tm_mon+1, tmTm.tm_mday);
	return szData;
}

time_t ToolFrame::ToTime( int nYear,int nMonth,int nDay,int nHour,int nMin,int nSec )
{
	if (!ToolFrame::IsInClosedInterval(nMonth,	1,12))return 0;
	if (!ToolFrame::IsInClosedInterval(nDay,	1,31))return 0;
	if (!ToolFrame::IsInClosedInterval(nHour,	0,23))return 0;
	if (!ToolFrame::IsInClosedInterval(nMin,	0,59))return 0;
	if (!ToolFrame::IsInClosedInterval(nSec,	0,59))return 0;

	struct tm p; 
	ToolFrame::MemClear(p);

	p.tm_year	= nYear;
	p.tm_mon	= nMonth;
	p.tm_mday	= nDay;
	p.tm_hour	= nHour;
	p.tm_min	= nMin;
	p.tm_sec	= nSec;

	p.tm_year -= 1900;
	p.tm_mon -= 1;

	return mktime(&p);
}

bool ToolFrame::StringToDate(time_t& tDes,const std::string& sSrc,const std::string& sFormat)
{
	if (sSrc.empty())return false;
	if (sSrc.length() != sFormat.length())return false;

	int nYear=0, nMonth=0, nDay=0;

	std::stringstream sStreamYear;
	std::stringstream sStreamMonth;
	std::stringstream sStreamDay;

	for(uint uIndex = 0;uIndex<sFormat.length();++uIndex){
		char_t chFormat = sFormat[uIndex];
		if (chFormat == 'Y' || chFormat == 'y' )
		{
			sStreamYear<<sSrc[uIndex];
			continue;
		}
		if (chFormat == 'M' || chFormat == 'm' )
		{
			sStreamMonth<<sSrc[uIndex];
			continue;
		}
		if (chFormat == 'D' || chFormat == 'd' )
		{
			sStreamDay<<sSrc[uIndex];
			continue;
		}
	}
	if (!ToolFrame::ToValue(sStreamYear.str(),nYear))return false;
	if (!ToolFrame::ToValue(sStreamMonth.str(),nMonth))return false;
	if (!ToolFrame::ToValue(sStreamDay.str(),nDay))return false;
	tDes = ToTime(nYear,nMonth,nDay);
	return 0 != tDes;
}

bool ToolFrame::StringToDate( const std::string& sSrc,time_t& tDes )
{
	if (sSrc.empty())return false;

	if (StringToDate(tDes,sSrc,"YYYY-MM-DD"))return true;
	if (StringToDate(tDes,sSrc,"YYYYMMDD"))return true;
	if (StringToDate(tDes,sSrc,"YYYY/MM/DD"))return true;

	return false;
}

bool ToolFrame::OpenFile( std::fstream& fStream, const std::string& sFileName,const std::ios_base::openmode& nOpenMode )
{
	fStream.open(sFileName.c_str(),nOpenMode);
	return !!fStream;
}

bool ToolFrame::OpenFile( std::ifstream& fStream, const std::string& sFileName,const std::ios_base::openmode& nOpenMode /*= std::ios_base::in*/ )
{
	fStream.open(sFileName.c_str(),nOpenMode|std::ios_base::in);
	return !!fStream;
}

bool ToolFrame::OpenFile( std::ofstream& fStream, const std::string& sFileName,const std::ios_base::openmode& nOpenMode /*= std::ios_base::in*/ )
{
	fStream.open(sFileName.c_str(),nOpenMode|std::ios_base::out);
	return !!fStream;
}

bool ToolFrame::FileElement( std::ifstream& fStream,VectorInt& vValue )
{
	uint uSize= 0;
	ToolFrame::FileElement(fStream,uSize);
	for (uint nIndex =0;nIndex<uSize;++nIndex)
	{
		int nValue = 0;
		ToolFrame::FileElement(fStream,nValue);
		vValue.push_back(nValue);
	}

	return true;
}

bool ToolFrame::FileElement( std::ofstream& fStream,const VectorInt& vValue )
{
	ToolFrame::FileElement(fStream,vValue.size());
	for (uint nIndex =0;nIndex<vValue.size();++nIndex)
		ToolFrame::FileElement(fStream,vValue[nIndex]);

	return true;
}

bool ToolFrame::FileElement( std::ifstream& fStream,SetInt& vValue )
{
	uint uSize= 0;
	ToolFrame::FileElement(fStream,uSize);

	for (uint nIndex =0;nIndex<uSize;++nIndex)
	{
		int nValue = 0;
		ToolFrame::FileElement(fStream,nValue);
		vValue.insert(nValue);
	}

	return true;
}

bool ToolFrame::FileElement( std::ofstream& fStream,const SetInt& vValue )
{
	ToolFrame::FileElement(fStream,vValue.size());
	SetInt::const_iterator itr;
	foreach(itr,vValue){
		ToolFrame::FileElement(fStream,*itr);
	}

	return true;
}

bool ToolFrame::FileElement( std::ifstream& fStream,std::string& sString )
{
	std::stringstream sStream;
	char ch='\xff';
	while(!fStream.eof() && ch)
	{
		fStream.read(&ch,sizeof(ch));
		if (0 != ch)sStream<<ch;
	}
	sString = sStream.str();
	return true;
}

bool ToolFrame::FileElement( std::ofstream& fStream,const std::string& sString )
{
	fStream.write(sString.c_str(),sString.length()+1);
	return true;
}


bool ToolFrame::CopyFile( std::ofstream& fDes,std::ifstream& fRes )
{
	fDes<<fRes.rdbuf();//复制
	return true;
}

int ToolFrame::GetAvgCount( int nTotal,int nPart,int nIndex )
{
	int nAvg = nTotal / nPart;
	if (nTotal % nPart <= nIndex)
	{
		nAvg +=1;
	}
	return nAvg;
}

int ToolFrame::GetIntervalNum( int nDividend,int nDivisor )
{
	if(nDividend<=0 || nDivisor <= 0)return -1;
	return nDividend % nDivisor == 0 ? nDividend/nDivisor:nDividend/nDivisor + 1;
}

bool ToolFrame::IsInOpenInterval( int nVal,int nBegin,int nEnd )
{
	return IsInOpenInterval<int>(nVal,nBegin,nEnd);
}

bool ToolFrame::IsInClosedInterval( int nVal,int nBegin,int nEnd )
{
	return IsInClosedInterval<int>(nVal,nBegin,nEnd);
}

bool ToolFrame::IsInClosedInterval( const std::string& sSrc,int nBegin,int nEnd )
{
	int nValue = 0;
	if (!ToValue(sSrc,nValue))return false;
	return IsInClosedInterval(nValue,nBegin,nEnd);
}

int ToolFrame::CalChineseCharacterNum( const std::string& sString )
{
	int nCount = 0;

	std::string::const_iterator itr;
	foreach(itr,sString){
		char ch = *itr;
		if (0x80 != (0xC0 & ch))
			++nCount;
	}

	return nCount;
}

int ToolFrame::CalEnglishCharacterNum( const std::string& sString )
{
	int nCount =0 ;

	std::string::const_iterator itr;
	foreach(itr,sString){
		if (ToolFrame::IsLetter(*itr))
			++nCount;
	}

	return nCount;
}

int ToolFrame::CalCharacterNum( const std::string& sString )
{
	int nCount = 0;

	std::string::const_iterator itr;
	foreach(itr,sString){
		char ch = *itr;
		if (0x80 != (0xC0 & ch))
			++nCount;
	}

	return nCount;
}

size_t ToolFrame::GetNearPowerOf2(size_t uNum )
{
	size_t uSum=1;
	while(uSum<uNum)
		uSum <<= 1;

	return uSum;
}

size_t ToolFrame::SmartMemoryLength(size_t uSize)
{
	//小块内存申请尽可能向2的次方数对齐
	if (uSize > 0x10000)return uSize;
	if (uSize < 4)return 4;

	return ToolFrame::GetNearPowerOf2(uSize);
}

size_t ToolFrame::SmartMemoryLengthNextLevel(size_t uSize)
{
	//小块内存申请尽可能向2的次方数对齐
	if (uSize > 0x10000)return uSize;
	if (uSize < 4)return 8;

	size_t uMalloc = ToolFrame::GetNearPowerOf2(uSize);
	if (uMalloc > 0x10000)return uSize;
	uMalloc <<= 1;//下一阶
	if (uMalloc > 0x10000)return uSize;
	return uMalloc;
}

uint ToolFrame::GetFileLength(const std::ifstream& fStreamIn)
{
	std::ifstream& fStream = ToolFrame::ConstCast(fStreamIn);

	//获取文件长度
	fStream.seekg(0, std::ios::end);
	std::streamoff uFileLen = fStream.tellg();
	fStream.seekg(0, std::ios::beg);

	return (uint)uFileLen;
}

UINT ToolFrame::GetFileLength( const std::fstream& fStreamIn )
{
	std::fstream& fStream = ToolFrame::ConstCast(fStreamIn);

	//获取文件长度
	fStream.seekg(0, std::ios::end);
	std::streamoff  uFileLen = fStream.tellg();
	fStream.seekg(0, std::ios::beg);

	return (UINT)uFileLen;
}

UINT ToolFrame::GetStreamLength( const std::ifstream& fStreamIn )
{
	std::ifstream& fStream = ToolFrame::ConstCast(fStreamIn);

	std::streamoff uPos = fStream.tellg();//当前所在位置
	fStream.seekg(0, std::ios::end);
	std::streamoff  uFileLen = fStream.tellg();
	fStream.seekg(uPos, std::ios::beg);
	return (UINT)(uFileLen - uPos);
}

UINT ToolFrame::GetStreamLength( const std::fstream& fStreamIn )
{
	std::fstream& fStream = ToolFrame::ConstCast(fStreamIn);

	std::streamoff uPos = fStream.tellg();//当前所在位置
	fStream.seekg(0, std::ios::end);
	std::streamoff  uFileLen = fStream.tellg();
	fStream.seekg(uPos, std::ios::beg);
	return (UINT)(uFileLen - uPos);
}

bool ToolFrame::IsOpen( const std::fstream& fStream )
{
	return !!fStream;
}

bool ToolFrame::IsOpen( const std::ifstream& fStream )
{
	return !!fStream;
}

bool ToolFrame::IsOpen( const std::ofstream& fStream )
{
	return !!fStream;
}

bool ToolFrame::MemClear( void* p, size_t uLen )
{
	if (!p)return false;
	memset(p,0,uLen);
	return true;
}

bool ToolFrame::ToValue( const bool& bSrc, bool& bDes )
{
	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const char& bSrc, bool& bDes )
{
	if (bSrc < MACRO_BOOL_MIN || bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const signed short& bSrc, bool& bDes )
{
	if (bSrc < MACRO_BOOL_MIN || bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const signed long& bSrc, bool& bDes )
{
	if (bSrc < MACRO_BOOL_MIN || bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const signed char& bSrc, bool& bDes )
{
	if (bSrc < MACRO_BOOL_MIN || bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const unsigned char& bSrc, bool& bDes )
{
	if ( bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const unsigned short& bSrc, bool& bDes )
{
	if ( bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const unsigned long& bSrc, bool& bDes )
{
	if ( bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, char& nDes )
{
	if (nSrc < MACRO_INT8_MIN || nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, char& nDes )
{
	if (nSrc < MACRO_INT8_MIN || nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, char& nDes )
{
	if ( nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc, char& nDes )
{
	if ( nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, char& nDes )
{
	if ( nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, short& nDes )
{
	if (nSrc < MACRO_INT16_MIN || nSrc > MACRO_INT16_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc, short& nDes )
{
	if ( nSrc > MACRO_INT16_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, short& nDes )
{
	if ( nSrc > MACRO_INT16_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, long& nDes )
{
	if ( nSrc > MACRO_INT32_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, unsigned char& nDes )
{
	if (nSrc < MACRO_UINT8_MIN)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, unsigned char& nDes )
{
	if (nSrc < MACRO_UINT8_MIN || nSrc > MACRO_UINT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, unsigned char& nDes )
{
	if (nSrc < MACRO_UINT8_MIN || nSrc > MACRO_UINT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, unsigned char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc, unsigned char& nDes )
{
	if (nSrc > MACRO_UINT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, unsigned char& nDes )
{
	if (nSrc > MACRO_UINT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::StaticCast( bool& bDes,const bool& tSrc )
{
	bDes = tSrc;
	return true;
}

bool ToolFrame::ToValue( const signed int& bSrc, bool& bDes )
{
	if (bSrc < MACRO_BOOL_MIN || bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const unsigned int& bSrc, bool& bDes )
{
	if ( bSrc > MACRO_BOOL_MAX)return false;

	return StaticCast(bDes,bSrc);
}

bool ToolFrame::ToValue( const char& nSrc, signed char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, signed char& nDes )
{
	if (nSrc < MACRO_INT8_MIN || nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, signed char& nDes )
{
	if (nSrc < MACRO_INT8_MIN || nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, signed char& nDes )
{
	if ( nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc, signed char& nDes )
{
	if ( nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, signed char& nDes )
{
	if ( nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, signed char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, signed char& nDes )
{
	if (nSrc < MACRO_INT8_MIN || nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, signed char& nDes )
{
	if (nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, char& nDes )
{
	if ( nSrc < MACRO_INT8_MIN || nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, char& nDes )
{
	if ( nSrc > MACRO_INT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, signed char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, short& nDes )
{
	if (nSrc < MACRO_UINT16_MIN || nSrc > MACRO_INT16_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, short& nDes )
{
	if ( nSrc > MACRO_INT16_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, long& nDes )
{
	if (nSrc > MACRO_INT32_MAX )return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc,long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, long& nDes )
{
	if (nSrc < MACRO_INT32_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, int& nDes )
{
	if (nSrc > MACRO_INT_MAX)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc,int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, int& nDes )
{
	if (nSrc > MACRO_INT32_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, int& nDes )
{
	if (nSrc > MACRO_INT32_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, unsigned char& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, unsigned char& nDes )
{
	if (nSrc < MACRO_UINT8_MIN)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, unsigned char& nDes )
{
	if (nSrc < MACRO_UINT8_MIN || nSrc > MACRO_UINT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, unsigned char& nDes )
{
	if (nSrc > MACRO_UINT8_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, unsigned short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, unsigned short& nDes )
{
	if (nSrc < MACRO_UINT16_MIN)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, unsigned short& nDes )
{
	if (nSrc < MACRO_UINT16_MIN)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, unsigned short& nDes )
{
	if (nSrc < MACRO_UINT16_MIN)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, unsigned short& nDes )
{
	if (nSrc < MACRO_UINT16_MIN || nSrc > MACRO_UINT16_MAX )return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, unsigned short& nDes )
{
	if (nSrc < MACRO_UINT16_MIN || nSrc > MACRO_UINT16_MAX )return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, unsigned short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc,unsigned short& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, unsigned short& nDes )
{
	if (nSrc > MACRO_UINT16_MAX )return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, unsigned short& nDes )
{
	if (nSrc > MACRO_UINT16_MAX )return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, unsigned long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, unsigned long& nDes )
{
	if (nSrc < MACRO_UINT32_MIN)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, unsigned long& nDes )
{
	if (nSrc < MACRO_UINT32_MIN)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, unsigned long& nDes )
{
	if (nSrc < MACRO_UINT32_MIN)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, unsigned long& nDes )
{
	if (nSrc < MACRO_UINT32_MIN)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, unsigned long& nDes )
{
	if (nSrc < MACRO_UINT32_MIN || nSrc > MACRO_UINT32_MAX)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, unsigned long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc,unsigned long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, unsigned long& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, unsigned long& nDes )
{
	if (nSrc > MACRO_UINT32_MAX)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const bool& nSrc, unsigned int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const char& nSrc, unsigned int& nDes )
{
	if (nSrc < MACRO_UINT_MIN)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed char& nSrc, unsigned int& nDes )
{
	if (nSrc < MACRO_UINT_MIN)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed short& nSrc, unsigned int& nDes )
{
	if (nSrc < MACRO_UINT_MIN)return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed long& nSrc, unsigned int& nDes )
{
	if (nSrc < MACRO_UINT_MIN )return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const signed int& nSrc, unsigned int& nDes )
{
	if (nSrc < MACRO_UINT_MIN )return false;
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned char& nSrc, unsigned int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned short& nSrc,unsigned int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned long& nSrc, unsigned int& nDes )
{
	if (nSrc > MACRO_UINT_MAX)return false;

	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const unsigned int& nSrc, unsigned int& nDes )
{
	return StaticCast(nDes,nSrc);
}

bool ToolFrame::ToValue( const float& nSrc, int& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT_MIN,MACRO_INT_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, int& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT_MIN,MACRO_INT_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, char& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT8_MIN,MACRO_INT8_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, char& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT8_MIN,MACRO_INT8_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, bool& nDes )
{
	if (ToolFrame::IsEqual(nSrc,1.0f)){
		nDes = true;
		return true;
	}
	if (ToolFrame::IsEqual(nSrc,0.0f)){
		nDes = true;
		return true;
	}
	return false;
}

bool ToolFrame::ToValue( const double& nSrc, bool& nDes )
{
	if (ToolFrame::IsEqual(nSrc,1.0f)){
		nDes = true;
		return true;
	}
	if (ToolFrame::IsEqual(nSrc,0.0f)){
		nDes = true;
		return true;
	}
	return false;
}

bool ToolFrame::ToValue( const float& nSrc, signed char& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT8_MIN,MACRO_INT8_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, signed char& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT8_MIN,MACRO_INT8_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, short& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT16_MIN,MACRO_INT16_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, short& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT16_MIN,MACRO_INT16_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, long& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT32_MIN,MACRO_INT32_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, long& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_INT32_MIN,MACRO_INT32_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, unsigned char& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT8_MIN,MACRO_UINT8_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, unsigned char& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT8_MIN,MACRO_UINT8_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, unsigned short& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT16_MIN,MACRO_UINT16_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, unsigned short& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT16_MIN,MACRO_UINT16_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, unsigned long& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT32_MIN,MACRO_UINT32_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, unsigned long& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT32_MIN,MACRO_UINT32_MAX);
}

bool ToolFrame::ToValue( const float& nSrc, unsigned int& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT_MIN,MACRO_UINT_MAX);
}

bool ToolFrame::ToValue( const double& nSrc, unsigned int& nDes )
{
	return ToValueRange(nSrc,nDes,MACRO_UINT_MIN,MACRO_UINT_MAX);
}

bool ToolFrame::ToValue( const std::string* sSrc, std::string& sDes )
{
	if (!sSrc)return false;

	sDes = *sSrc;
	return true;
}

bool ToolFrame::ToValue( const std::string& sSrc, char& tDes )
{
	if (sSrc.size()>1)return false;
	tDes = sSrc[0];
	return true;
}

bool ToolFrame::ToValue( const MapStringString& vValues,std::string& sDes,const std::string& sSpKeyValue/*="="*/,const std::string& sSpLine/*=" "*/ )
{
	if (vValues.empty())return true;

	std::stringstream sStream;

	MapStringString::const_iterator itr;
	bool bAttch= false;
	foreach(itr,vValues){
		if (bAttch)sStream << sSpLine;
		bAttch = true;

		sStream << itr->first;
		sStream << sSpKeyValue;
		sStream << itr->second;
	}

	sDes = sStream.str();

	return true;
}

bool ToolFrame::ToValue( const VectorString& vValues,std::string& sDes,const std::string& sSpLine/*=" "*/ )
{
	if (vValues.empty())return true;

	std::stringstream sStream;
	bool bAttch= false;
	VectorString::const_iterator itr;
	foreach(itr,vValues){
		if (bAttch)sStream << sSpLine;
		bAttch = true;

		sStream << *itr;
	}

	sDes = sStream.str();

	return true;
}

bool ToolFrame::ToValue( const std::string& sSrc, MapStringString& vDes,const std::string& sSpKeyValue/*="="*/,const std::string& sSpLine/*=" "*/ )
{
	if (sSrc.empty())return true;
	
	VectorString vLine;
	if (!ToolFrame::SplitString(vLine,sSrc,sSpLine))return false;
	
	VectorString::const_iterator itr;
	foreach(itr,vLine){
		const std::string& sLine = *itr;

		SSIZE_TYPE uOffSet = sLine.find(sSpKeyValue);
		if (std::string::npos == uOffSet)return false;

		std::string s1 = sLine.substr(0,uOffSet);
		std::string s2 = sLine.substr(uOffSet+sSpKeyValue.length(),sLine.length() - uOffSet);

		if (!ToolFrame::Insert(vDes,s1,s2))return false;
	}

	return true;
}

bool ToolFrame::ToValue( const std::string& sSrc, VectorString& vDes,const std::string& sSpLine/*=" "*/ )
{
	return ToolFrame::SplitString(vDes,sSrc,sSpLine);
}

bool ToolFrame::IsBeginEndWith( const std::string& sSrc,const std::string& sBegin,const std::string& sEnd )
{
	if (sSrc.find(sBegin) != 0)return false;

	return sSrc.rfind(sEnd) ==  sSrc.length() - 1;
}

bool ToolFrame::IsEqual( const double t1,const double t2 ,const double relError )
{
	if (t1 == t2)return true;

	double fAvg =  GetLimitMax(t1) / 2.0;

	if (t1 < fAvg && t2 >= fAvg)return false;
	if (t2 < fAvg && t1 >= fAvg)return false;

	return ToolFrame::Abs(t1-t2) < relError;
}

bool ToolFrame::IsEqual( const float t1,const float t2 )
{
	return IsEqual((double)t1,(double)t2,0.001f);
}

bool ToolFrame::IsEqual( const float t1,const double t2 )
{
	return IsEqual((double)t1,(double)t2,0.00001f);
}

bool ToolFrame::IsEqual( const double t1,const float t2 )
{
	return IsEqual((double)t1,(double)t2,0.00001f);
}

bool ToolFrame::IsFileGood( const std::fstream& fStream )
{
	if (!fStream)return false;
	return fStream.good();
}

bool ToolFrame::ResetFile( std::fstream& fStream )
{
	if (!fStream)return false;

	fStream.seekg(0, std::ios::beg);
	return true;
}

std::string ToolFrame::MakeAddress( const std::string& sIP,const std::string& sPort )
{
	std::stringstream sStream;
	sStream<<sIP<<":"<<sPort;
	return sStream.str();
}

std::string ToolFrame::MakeAddress( const std::string& sIP,const int& nPort )
{
	return ToolFrame::MakeAddress(sIP,ToString(nPort));
}

std::string ToolFrame::MakeAddress( const std::string& sIP,const unsigned int& uPort )
{
	return ToolFrame::MakeAddress(sIP,ToString(uPort));
}

bool ToolFrame::ResolveAddress( std::string& sIP,std::string& sPort,const std::string& sAddress )
{
	UINT uPort = 0;
	VectorString vString;
	if (ToolFrame::SplitStringFirst(vString,sAddress,":",false))
	{
		if (vString.size() < 2 )return false;
		if (ToValue(vString[0],sIP) && ToValue(vString[1],uPort)){
			sPort = vString[1];
			return true;
		}	
	}

	if (!ToolFrame::ToValue(sAddress,uPort))
	{
		sIP = sAddress;
		sPort = "80";//默认连接80端口
	}else{
		sIP="127.0.0.1";
		sPort=sAddress;
	}
	
	return true;
}

VectorString ToolFrame::SplitAddress(const std::string& sIP)
{
	VectorString vReturn;
	if (sIP == ToolFrame::EmptyString())return vReturn;

	VectorString vIP;
	if (!ToolFrame::SplitString(vIP, sIP, ";"))return vReturn;
	if (vIP.empty())return vReturn;

	VectorString::const_iterator itr;
	foreach(itr, vIP){
		const std::string& sIPAddress = *itr;

		VectorString vIPAddress;
		if (!ToolFrame::SplitStringFirst(vIPAddress, sIPAddress, ":"))
		{
			ToolFrame::Merge(vReturn, sIPAddress);
			continue;
		}

		const std::string& sAddress = vIPAddress[0];
		const std::string& sPort	= vIPAddress[1];

		VectorString vPort;
		ToolFrame::SplitString(vPort, sPort, ",");
		VectorString::const_iterator itrPort;
		foreach(itrPort, vPort) {
			ToolFrame::Merge(vReturn,ToolFrame::MakeAddress(sAddress, *itrPort));
		}
	}

	return vReturn;
}

VectorString ToolFrame::TrimAddress(const VectorString& vAddress)
{
	VectorString vReturn;
	if (vAddress.empty())return vReturn;

	VectorString::const_iterator itr;
	foreach(itr, vAddress) {
		ToolFrame::Merge(vReturn, SplitAddress(*itr));
	}

	return vReturn;
}

SSIZE_TYPE ToolFrame::FindFristNotOf(const std::string& sSrc, const char sz[], SSIZE_TYPE uOffset)
{
	return sSrc.find_first_not_of(sz,uOffset);
}

SSIZE_TYPE ToolFrame::SkipInvisibleChar( const std::string& sSrc, SSIZE_TYPE nOffset ,bool bNot)
{
	return SkipChar(sSrc,nOffset,IsVisibleChar,!bNot);
}

SSIZE_TYPE ToolFrame::SkipChar( const std::string& sSrc, SSIZE_TYPE nOffset,bool(*fn)(char),bool bNot /*= false*/ )
{
	if (std::string::npos == nOffset)return std::string::npos;

	for (size_t uIndex = nOffset ; uIndex < sSrc.length();++uIndex)
	{
		if ( bNot ? fn(sSrc.at(uIndex)) : !fn(sSrc.at(uIndex)))
			return uIndex;
	}
	return std::string::npos;
}

std::string ToolFrame::PickChar( const std::string& sSrc, SSIZE_TYPE nOffset,bool(*fn)(char) )
{
	SSIZE_TYPE uPos = ToolFrame::SkipChar(sSrc,nOffset,fn);
	if (std::string::npos == uPos)return "";

	return sSrc.substr(nOffset,uPos - nOffset);
}

bool ToolFrame::IsVisibleChar( char ch )
{
	//return (ch >='0' && ch <="9") || (ch >='A' && ch <="Z") || (ch >='a' && ch <="z");
	return ch >= 33 && ch <= 126;//查询ASCII码表
}

bool ToolFrame::IsVisibleString(const std::string& sSrc)
{
	if (sSrc.empty())return false;
	for (SSIZE_TYPE nIndex = 0; nIndex < sSrc.length(); ++nIndex)
	{
		if (!IsVisibleChar(sSrc.at(nIndex)))
			return false;
	}
	return true;
}

const MapStringString& ToolFrame::GetVarCodeSignMap()
{
	static MapStringString	vCodeSign;
	if (vCodeSign.empty())
	{
		assert(ToolFrame::InsertString(vCodeSign,"void",			"X"));
		assert(ToolFrame::InsertString(vCodeSign,"bool",			"_N"));
		assert(ToolFrame::InsertString(vCodeSign,"char",			"D"));
		assert(ToolFrame::InsertString(vCodeSign,"unsigned char",	"E"));
		assert(ToolFrame::InsertString(vCodeSign,"short",			"F"));
		assert(ToolFrame::InsertString(vCodeSign,"unsigned short",	"G"));
		assert(ToolFrame::InsertString(vCodeSign,"int",				"H"));
		assert(ToolFrame::InsertString(vCodeSign,"unsigned int",	"I"));
		assert(ToolFrame::InsertString(vCodeSign,"long",			"J"));
		assert(ToolFrame::InsertString(vCodeSign,"unsigned long",	"K"));
		assert(ToolFrame::InsertString(vCodeSign,"float",			"M"));
		assert(ToolFrame::InsertString(vCodeSign,"double",			"N"));
	}

	return vCodeSign;
}

const std::string ToolFrame::GetVarCodeSign( const std::string& sType )
{
	return ToolFrame::GetValueByKey(GetVarCodeSignMap(),sType,"");
}

const VectorInt& ToolFrame::ZeroVectorInt()
{
	static const VectorInt v;
	return v;
}

int ToolFrame::CalIndexFromRight( int nIndexLeft,int nBegin,int nEnd )
{
	assert(nIndexLeft >= nBegin && nIndexLeft <= nEnd);
	
	//return (nEnd - nBegin + 1) -  (nIndexLeft - nBegin + 1) + 1;//总个数 - 从左数过来个数 + 1
	return nEnd  + 1 - nIndexLeft;//变形
}

int ToolFrame::CalIndexFromLeft( int nIndexRight,int nBegin,int nEnd )
{
	assert(nIndexRight >= nBegin && nIndexRight <= nEnd);

	//return (nEnd - nBegin + 1) -  (nEnd - nIndexRight + 1) + 1;//总个数 - 从右数过来个数 + 1
	return nIndexRight - nBegin + 1;//变形
}

unsigned int ToolFrame::CalIndexFromRight( unsigned int nIndexLeft,unsigned int nBegin,unsigned int nEnd )
{
	assert(nIndexLeft >= nBegin && nIndexLeft <= nEnd);

	//return (nEnd - nBegin + 1) -  (nIndexLeft - nBegin + 1) + 1;//总个数 - 从左数过来个数 + 1
	return nEnd  + 1 - nIndexLeft;//变形
}

unsigned int ToolFrame::CalIndexFromLeft( unsigned int nIndexRight,unsigned int nBegin,unsigned int nEnd )
{
	assert(nIndexRight >= nBegin && nIndexRight <= nEnd);

	//return (nEnd - nBegin + 1) -  (nEnd - nIndexRight + 1) + 1;//总个数 - 从右数过来个数 + 1
	return nIndexRight - nBegin + 1;//变形
}

bool ToolFrame::MemCopyPtr( void* tDes,const void* tSrc, size_t nLen )
{
	if (!tDes || !tSrc)return false;
	if (nLen <= 0)return true;
	if (tDes == tSrc)return true;

	char* pDes = (char*)tDes;
	char* pSrc = (char*)tSrc;

	//内存拷贝 需要处理当内存地址非常接近的时候 内存拷贝 也要能够正确处理
	if (abs(pDes - pSrc) >= (int)nLen)
	{
		memcpy_s(tDes,nLen,tSrc,nLen);
		return true;
	}

	if (pSrc < pDes)
	{
		//从后往前拷贝
		for (size_t nIndex =0;nIndex<nLen;++nIndex)
			pDes[nLen - 1 - nIndex] = pSrc[nLen -1 - nIndex];
	}else{
		//从前往后拷贝
		for (size_t nIndex =0;nIndex<nLen;++nIndex)
			pDes[nIndex] = pSrc[nIndex];
	}

	return true;
}

void* ToolFrame::MemCheck(void* pSrc, size_t uMax)
{
	if (!pSrc)return nullptr;
	if (uMax <= 0)return pSrc;

	char* pCopy = new char[uMax];
	MemCopyPtr(pCopy, pSrc, uMax);
	delete[] pSrc;
	return pCopy;
}

bool ToolFrame::MemCmp(const void* p1, const void* p2, size_t uLen)
{
	if (uLen <= 0)return true;
	if (!p1)return false;
	if (!p2)return false;

	return !memcmp(p1, p2, uLen);
}

std::string ToolFrame::MemString(const void* p, size_t uLen)
{
	if (!p)return "";

	unsigned char* pData = (unsigned char*)p;
	std::stringstream sStream;
	sStream.str("");
	sStream << std::hex << std::setfill('0') << std::setw(2);
	for (size_t uIndex = 0; uIndex < uLen; ++uIndex)
	{
		sStream << ((uint)pData[uIndex]) << " ";
	}

	return sStream.str();
}

bool ToolFrame::MemPrint(const void* p, size_t uLen)
{
	if (!p) {
		printf("Memory Data is Null!");
		return false;
	}
	
	std::string sMemString = MemString(p, uLen);
	if (sMemString.empty())
	{
		printf("Memory Data is Null!");
		return false;
	}
	printf("Memory Data:%s", sMemString.c_str());
	return true;
}

bool ToolFrame::MemCmp(const void* p1, size_t uLen1, const void* p2, size_t uLen2)
{
	if (uLen1 != uLen2)return false;

	return MemCmp(p1, p2, uLen1);
}

SSIZE_TYPE ToolFrame::FindFrist(const std::string& sSrc, const std::string& sDes, SSIZE_TYPE nOffset /*= 0*/)
{
	return sSrc.find(sDes,nOffset);
}

SSIZE_TYPE ToolFrame::FindFrist( const std::string& sSrc,const VectorString& vDes, SSIZE_TYPE nOffset /*= 0*/ )
{
	return FindFrist(nullptr,sSrc,vDes,nOffset);
}

SSIZE_TYPE ToolFrame::FindFrist( std::string& sDes,const std::string& sSrc,const VectorString& vDes, SSIZE_TYPE nOffset /*= 0*/ )
{
	return FindFrist(&sDes,sSrc,vDes,nOffset);
}

SSIZE_TYPE ToolFrame::FindFrist( std::string* pDes,const std::string& sSrc,const VectorString& vDes, SSIZE_TYPE nOffset /*= 0*/ )
{
	if(vDes.empty())return std::string::npos;

	SSIZE_TYPE uPos = std::string::npos;int nIndex = -1;
	for (uint nIndexCur =0;nIndexCur < vDes.size();++nIndexCur)
	{
		const std::string& sKey = vDes[nIndexCur];
		SSIZE_TYPE uPosCur = FindFrist(sSrc,sKey,nOffset);
		//如果没有,那么当前就是最大的
		if (std::string::npos == uPosCur)
		{
			uPos = uPosCur;
			nIndex = nIndexCur;
			continue;
		}

		if (uPosCur > uPos)
		{
			uPos = uPosCur;
			nIndex = nIndexCur;
			continue;
		}
	}

	//返回字符串
	if (std::string::npos != uPos && pDes)
	{
		assert(IsVaildIndex(vDes,nIndex));
		*pDes = vDes[nIndex];
	}

	return uPos;
}

bool ToolFrame::IsBeforeCharactor( const std::string& sString,const std::string& sJudge, SSIZE_TYPE uOffSet )
{
	assert(!sJudge.empty());
	assert(uOffSet <= sString.length() );
	if (sJudge.empty())return false;
	if (sString.empty())return false;

	if (uOffSet < sJudge.length())return false;
	
	const std::string sCmp = sString.substr(uOffSet,sJudge.length());
	return sCmp == sJudge;
}

SSIZE_TYPE ToolFrame::IsVisibleCharBeginWith( const std::string& sSrc,const std::string& sCmp, SSIZE_TYPE nOffset /*= 0*/,bool bSkip /*= false*/ )
{
	SSIZE_TYPE uPos = ToolFrame::SkipInvisibleChar(sSrc,nOffset);
	if (std::string::npos == uPos)return std::string::npos;

	if (!IsBeginWith(sSrc,sCmp,uPos))return std::string::npos;

	return bSkip ? uPos + sCmp.length() : uPos;
}

//查找下一个可见字符
SSIZE_TYPE ToolFrame::PickVisibleString(std::string& sDes, const std::string& sSrc, SSIZE_TYPE nOffset) {
	SSIZE_TYPE uBegin = ToolFrame::SkipInvisibleChar(sSrc, nOffset);
	if (std::string::npos == uBegin)
		return std::string::npos;

	SSIZE_TYPE uEnd = ToolFrame::SkipInvisibleChar(sSrc, uBegin, true);
	if (std::string::npos == uEnd)
		return std::string::npos;

	sDes = sSrc.substr(uBegin, uEnd - uBegin);
	return uEnd;
}

const std::string& ToolFrame::EmptyString()
{
	const static std::string& s = "";
	return s;
}

UINT ToolFrame::RemoveString( VectorString& vReturn,const std::string& sString /*= ""*/ )
{
	UINT uCount = 0;
	for (int uIndex = (int)vReturn.size()-1;uIndex>=0;--uIndex)
	{
		if (sString == vReturn[uIndex])
		{
			vReturn.erase(vReturn.begin()+uIndex);
			++uCount;
		}
	}
	return uCount;
}

std::string ToolFrame::RemoveReturn(const std::string& sSrc)
{
	if (sSrc.empty())return sSrc;

	std::stringstream sStream;

	std::string::const_iterator itr;
	foreach(itr,sSrc){
		char ch = *itr;
		if ('\n' != ch && '\r' != ch)
			sStream<<ch;
	}

	return sStream.str();
}

std::string ToolFrame::GetFilePath( const std::string& sDir ,const std::string& sFileName )
{
	return TrimDir(sDir) + sFileName;
}
bool ToolFrame::IsSpecialDir(const std::string& sPath)
{
	return sPath == "."  || sPath == ".." ;
}

std::string ToolFrame::GenerateID(uint uCount /*= 40*/)
{
	std::stringstream sStream;
	for (uint uIndex = 0; uIndex < uCount; ++uIndex)
	{
		int nRand = ToolFrame::Rand(0, 35);
		char ch = nRand < 10 ? '0' + nRand : 'a' + nRand - 10;
		sStream << ch;
	}

	return sStream.str();
}

uint ToolFrame::RandProbability( uint uProbability,uint uMax/*=100*/ )
{
	if (uMax <=0)return 0;
	
	uint uNum = uProbability / uMax;
	uProbability %= uMax;

	if (ToolFrame::Rand(1,uMax) <= (int)uProbability)
		uNum +=1;
	return uNum;
}

int ToolFrame::GetValueInOpenInterval( int nVal,int nBegin,int nEnd )
{
	return GetValueInOpenInterval<int>(nVal,nBegin,nEnd);
}

int ToolFrame::GetValueInClosedInterval( int nVal,int nBegin,int nEnd )
{
	return GetValueInClosedInterval<int>(nVal,nBegin,nEnd);
}

std::string ToolFrame::AbsPathToRelativePath( const std::string& sPath,const std::string& sCmpPath )
{
	return ApiStd::AbsPathToRelativePath(sPath,sCmpPath);
}

bool ToolFrame::AbsPathToRelativePath( VectorString& vDes,const VectorString& vAbsPath,const std::string& sCmpPath )
{
	return ApiStd::AbsPathToRelativePath(vDes,vAbsPath,sCmpPath);
}

bool ToolFrame::IsLengthInOpenInterval( const std::string& sString,uint uBegin,uint uEnd )
{
	return IsInOpenInterval((int)sString.size(),uBegin,uEnd);
}

bool ToolFrame::IsLengthInClosedInterval( const std::string& sString,uint uBegin,uint uEnd )
{
	return IsInClosedInterval((int)sString.size(),uBegin,uEnd);
}

uint ToolFrame::Hash( const std::string& sString,uint nMax )
{
	uint uLength = (uint)sString.length();
	uint nHash = uLength;
	for (uint nIndex =0;nIndex<uLength;++nIndex)
		nHash += (uint)sString.at(nIndex);
	
	return nHash % nMax;
}

uint ToolFrame::Hash( uint uValue,uint nMax )
{
	return uValue % nMax;
}

bool ToolFrame::IsInValue( int nValue,int nArg1 )
{
	return nValue == nArg1;
}

bool ToolFrame::IsInValue( int nValue,int nArg1,int nArg2 )
{
	return nValue == nArg1 || nValue == nArg2;
}

bool ToolFrame::IsInValue( int nValue,int nArg1,int nArg2,int nArg3 )
{
	return nValue == nArg1 || nValue == nArg2 || nValue == nArg3;
}

bool ToolFrame::IsInValue( int nValue,int nArg1,int nArg2,int nArg3,int nArg4 )
{
	return nValue == nArg1 || nValue == nArg2 || nValue == nArg3 || nValue == nArg4;
}

bool ToolFrame::IsInValue( int nValue,int nArg1,int nArg2,int nArg3,int nArg4,int nArg5 )
{
	return nValue == nArg1 || nValue == nArg2 || nValue == nArg3 || nValue == nArg4 || nValue == nArg5;
}

int ToolFrame::GetSecondsEveryMinute()
{
	return 60;
}

int ToolFrame::GetSecondsEveryHour()
{
	return 60*60;
}

int ToolFrame::GetSecondsEveryDay( int nHours /*= 24*/ )
{
	return 60*60*nHours;
}

int ToolFrame::GetSecondsEveryWeek(int nDays /*= 7*/ )
{
	return 60*60*24*nDays;
}

int ToolFrame::GetSecondsEveryMonth( int nDays /*= 30*/ )
{
	return 60*60*24*nDays;
}

int ToolFrame::GetSecondsEveryYear( int nDays /*= 365*/ )
{
	return 60*60*24*nDays;
}

std::string ToolFrame::PickFileExt( const std::string& sPath )
{
	SSIZE_TYPE nIndexCur = sPath.rfind(".");
	if(std::string::npos == nIndexCur)
		return "";

	return sPath.substr(nIndexCur,sPath.length()-nIndexCur);
}

bool ToolFrame::IsEqual(const char ch1, const char ch2, bool bIgnoreCase /*= false*/)
{
	if (ch1 == ch2)
		return true;

	if (!bIgnoreCase)
		return false;

	//忽略大小写
	if (!ToolFrame::IsLetter(ch1))return false;
	if (!ToolFrame::IsLetter(ch2))return false;
	return ch1 + 32 == ch2 || ch1 == ch2 + 32;
}

bool ToolFrame::IsEqual( const std::string& s1,const std::string& s2,bool bIgnoreCase/*=false*/ )
{
	if (IsSelf(s1,s2))return true;

	if (s1.empty() && s2.empty())return true;
	if (s1.length() != s2.length())return false;

	size_t uLength = s1.length();
	for (size_t uIndex = 0; uIndex < uLength;++uIndex) {
		if (!IsEqual(s1[uIndex], s2[uIndex], bIgnoreCase))
			return false;
	}

	return true;
}

bool ToolFrame::IsEqual( const char* pSrc,const char* pDes,bool bIgnoreCase/*=false*/ )
{
	if (pSrc == pDes)return true;

	if (!pSrc)return false;
	if (!pDes)return false;

	std::string s1 = pSrc;
	std::string s2 = pDes;
	return IsEqual(s1,s2,bIgnoreCase);
}

std::string ToolFrame::DateToStringNumber( time_t tTime )
{
	char szData[64] = {0};

	tm tmTm = {0};
	if (localtime_s(&tmTm,&tTime))return "";

	_snprintf_s(szData,sizeof(szData), 60, "%4d%02d%02d", tmTm.tm_year+1900, tmTm.tm_mon+1, tmTm.tm_mday);
	return szData;
}

float ToolFrame::Sqrt( float fValue )
{
	return ::sqrt(fValue);
	
}

float ToolFrame::Power( float fValue,int nPower )
{
	if (0 == nPower)return 1.;//任何数的0次方 等于 1
	
	if (nPower>0)
	{
		float fSum=fValue;
		while (--nPower)
			fSum *= fValue;

		return fSum;
	}
	
	nPower = -nPower;
	float fSum=fValue;
	while (--nPower)
		fSum *= fValue;

	return 1.f/fSum;
}

const VectorString& ToolFrame::EmptyVectorString()
{
	const static VectorString g_vEmptyString;
	return g_vEmptyString;
}

const VectorInt& ToolFrame::EmptyVectorInt()
{
	const static VectorInt g_vEmptyVectorInt;
	return g_vEmptyVectorInt;
}

double ToolFrame::ATan( double fY,double fX )
{
	return atan2(fY, fX);
}

double ToolFrame::RadianToAngel( double fRadian )
{
	return 180.0f * fRadian / M_PI;
}

double ToolFrame::AngelToRadian( double fAngel )
{
	return fAngel * M_PI / 180.f;
}

bool ToolFrame::Offset(size_t& uDes,size_t uSrc, int nOffset, size_t uLimitBegin, size_t uLimitEnd, bool bFix /*= true*/)
{
	//计算指针
	if (nOffset >= 0)
	{
		size_t uResult = uSrc + nOffset;
		if (uResult > uLimitEnd) {
			if (!bFix)return false;

			uDes = uLimitEnd;
			return true;
		}

		uDes = uResult;
		return true;
	}

	//小于
	if (uSrc < (size_t)ToolFrame::Abs(nOffset)) {
		if (!bFix)return false;

		uDes = uLimitBegin;
		return true;
	}

	uDes = uSrc + nOffset;
	return true;
}

time_t ToolFrame::CalLocalHour( int tTime,time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	tmValue.tm_hour = tTime;
	tmValue.tm_min = 0;
	tmValue.tm_sec = 0;

	return mktime(&tmValue);
}

time_t ToolFrame::CalLocalNextHour( int tTime,time_t tTimeNow )
{
	time_t tHour = CalLocalHour(tTime,tTimeNow);
	if (tHour > tTimeNow)
		return tHour;

	return CalLocalHour(tTime,tTimeNow + ToolFrame::GetSecondsEveryDay());
}

time_t ToolFrame::CalLocalToNextHour( int tTime,time_t tTimeNow )
{
	return CalLocalNextHour(tTime,tTimeNow) - tTimeNow;
}

int ToolFrame::GetLocalSec( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return tmValue.tm_sec;
}

int ToolFrame::GetLocalMin( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return tmValue.tm_min;
}

int ToolFrame::GetLocalHour( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return tmValue.tm_hour;
}

int ToolFrame::GetLocalMonth( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return tmValue.tm_mon + 1;
}

int ToolFrame::GetLocalYear( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return 1900 + tmValue.tm_year;
}

int ToolFrame::GetLocalMonthDay( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return tmValue.tm_mday;
}

int ToolFrame::GetLocalWeekDay( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return tmValue.tm_wday;
}

int ToolFrame::GetLocalYearDay( time_t tTimeNow )
{
	tm tmValue;
	localtime_s(&tmValue,&tTimeNow);
	return tmValue.tm_yday;
}

uint64 ToolFrame::GetBytesEveryKB()
{
	return 1024;
}

uint64 ToolFrame::GetBytesEveryMB()
{
	return 1024 * GetBytesEveryKB();
}

uint64 ToolFrame::GetBytesEveryGB()
{
	return 1024 * GetBytesEveryMB();
}

uint64 ToolFrame::GetBytesEveryTB()
{
	return 1024 * GetBytesEveryGB();
}

uint64 ToolFrame::GetBytesEveryPB()
{
	return 1024 * GetBytesEveryTB();
}

std::string ToolFrame::ValueToRead( uint64 uValue,uint uUint/*=3*/ )
{
	std::string sValue;
	if (!ToValue(uValue,sValue))return "";

	for(int uIndex = (int)sValue.length()-uUint;uIndex > 0;uIndex -= uUint){
		sValue.insert(uIndex,",");
	}

	return sValue;
}

uint64 ToolFrame::ReadToValue( const std::string& sRead,uint uUint/*=3*/ )
{
	std::string s = sRead;
	Replace(s,",","");
	uint64 uValue=0;
	if(!ToValue(s,uValue))return 0;

	return uValue;
}

std::string ToolFrame::TimeToRead(uint64 uValue)
{
	char szData[64] = { 0 };

	int uHour = 0,uMiniute = 0,uSecond = 0,uMill=0;

	uMill = uValue % 1000;
	uValue /= 1000;
	uSecond = uValue % 60;
	uValue /= 60;
	uMiniute = uValue % 60;
	uValue /= 60;
	uHour = uValue % 60;

	_snprintf_s(szData, sizeof(szData), 60, "%d:%02d:%02d.%03d", uHour, uMiniute, uSecond,uMill);
	return szData;
}

uint64 ToolFrame::ReadToTime(const std::string& sRead)
{
	if (sRead.empty())return 0;

	int uHour = 0, uMiniute = 0, uSecond = 0, uMill = 0;
	
	if (0 == sscanf_s(sRead.c_str(), "%d:%02d:%02d.%03d", &uHour,&uMiniute,&uSecond,&uMill))
		return 0;

	uint64 uValue = 0;

	uValue = uHour;
	uValue *= 60;
	uValue += uMiniute;
	uValue *= 60;
	uValue += uSecond;
	uValue *= 1000;
	uValue += uMill;
	return uValue;
}

std::string ToolFrame::MoneyToString( uint32 uMoney )
{
	uint32 uMoneyBefore = uMoney / 100;
	uint32 uMoneyBehand = uMoney % 100;

	return MAKE_STRING(uMoneyBefore<<"."<<std::setw(2)<<std::setfill('0')<<uMoneyBehand);
}

bool ToolFrame::IsMoneyCharacter( char ch )
{
	if (ToolFrame::IsNumber(ch))return true;

	return ch == '.';
}

std::string ToolFrame::TrimMoneyString( const std::string& sMoney )
{
	std::stringstream sStream;
	std::string::const_iterator itr;
	foreach(itr,sMoney){
		char ch = *itr;
		if (IsMoneyCharacter(ch))
			sStream<<ch;
	}
	return sStream.str();
}

uint32 ToolFrame::StringToMoney( const std::string& sMoney )
{
	const std::string sValue = TrimMoneyString(sMoney);

	std::string sSpKeyValue = ".";
	SSIZE_TYPE uOffSet = sValue.find(sSpKeyValue);
	if (std::string::npos == uOffSet){
		uint32 uInteger=0;
		if (!ToolFrame::ToValue(sValue,uInteger))return 0;

		return uInteger*100;
	}

	uint32 uInteger=0;uint32 uDecimal=0;

	std::string sInteger	= sValue.substr(0,uOffSet);
	std::string sDecimal	= sValue.substr(uOffSet+sSpKeyValue.length(),2);

	if (!sInteger.empty())
		if (!ToolFrame::ToValue(sInteger,uInteger))return 0;
	if (!sDecimal.empty())
		if (!ToolFrame::ToValue(sDecimal,uDecimal))return 0;

	return uInteger*100 + uDecimal;
}

double ToolFrame::ACos( double fValue )
{
	return acos(fValue);
}

double ToolFrame::Sin( double fAngel )
{
	return sin(fAngel);
}

double ToolFrame::Cos( double fAngel )
{
	return cos(fAngel);
}

int ToolFrame::ToInteger( float fValue )
{
	int nValue = 0;
	if(ToValue(fValue,nValue))return 0 ;
	return nValue;
}

int ToolFrame::ToInteger( double fValue )
{
	int nValue = 0;
	if(ToValue(fValue,nValue))return 0 ;
	return nValue;
}

bool ToolFrame::SplitStringFirst( VectorString& vReturn,const std::string& sSrc,const std::string& sSP,bool bFront /*= true*/ )
{
	if (sSrc.empty())return false;

	SSIZE_TYPE uOffSet = bFront ? sSrc.find(sSP):sSrc.rfind(sSP);
	if (std::string::npos == uOffSet)return false;

	vReturn.push_back(sSrc.substr(0,uOffSet));
	vReturn.push_back(sSrc.substr(uOffSet+sSP.length(),sSrc.length() - uOffSet));
	return true;
}

int ToolFrame::CalStringCount( const std::string& sString,const std::string& sCount )
{
	int nCount = 0;

	SSIZE_TYPE uFind = 0;

	while (std::string::npos != (uFind = sString.find(sCount,uFind))){
		++nCount;
		uFind += sCount.length();
	}

	return nCount;
}

