#pragma once
#include "Macro.h"

//此处的线段为一维线段,仅由2个值表示起点和终点

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CSegment
{
public:
	bool		IsContain(float fPosition)const;		//是否包含该位置
	bool		IsContain(const CSegment& seg)const;	//是否包含线段
	bool		IsIntersect(const CSegment& seg)const;	//线段是否相交
	bool		CalIntersect(CSegment& segSub,const CSegment& seg)const;//计算相交区域
	float		GetLength() const;						//获取线段长度
	float		GetMidPosition()const;					//获取线段中点
	bool		SetSegment(float fPositionBegin,float fPositionEnd);
	bool		SetSegment(int nPositionBegin,int nPositionEnd);
	bool		SetSegment(const CSegment& seg);
public:
	bool		operator ==	(const CSegment& seg)const;
	bool		operator != (const CSegment& seg)const;
public:
	CSegment(void);
	CSegment(float fPositionBegin,float fPositionEnd);
	CSegment(int nPositionBegin,int nPositionEnd);
	CSegment(const CSegment& seg);
	virtual ~CSegment(void);
private:
	CFIELD_FLOAT(Begin);
	CFIELD_FLOAT(End);
};

NS_TOOL_FRAME_END