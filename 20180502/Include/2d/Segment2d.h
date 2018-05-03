#pragma once
#include "Macro.h"
#include "Point2d.h"
//用两点代表一条线段(两点为端点)
//两点式:(y-y0)/(y0-y1)=(x-x0)/(x0-x1) 
//变形:(y-y0)*(x0-x1)=(y0-y1)*(x-x0)
//线段包含点的条件为点在该线段所在直线上且点在该线段为对角线的矩形中
//线段包含另一条线段的条件为另一条线段的两个端点都被这条线段包含

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CSegment2d
{
public:
	bool		IsContain(const CPoint2d& pt)const;		//是否包含该点
	bool		IsContain(const CSegment2d& seg)const;	//是否包含线段
	bool		IsIntersect(const CSegment2d& seg)const;//线段是否相交
	float		GetLength() const;						//获取线段长度
	float		GetLengthSquared() const;				//获取线段长度的平方(性能更高)
	CPoint2d	GetMidPoint()const;						//获取线段中点
private:
	float		CalDelta(float f1,float f2,float f3, float f4)const;								//计算差值
public:
	bool		operator ==	(const CSegment2d& seg)const;
	bool		operator != (const CSegment2d& seg)const;
public:
	CSegment2d(void);
	CSegment2d(const CPoint2d& pt1,const CPoint2d& pt2);
	CSegment2d(const CSegment2d& seg);
	virtual ~CSegment2d(void);
public:
	CFIELD_REF(CPoint2d,PointBegin,pt);			//起点
	CFIELD_REF(CPoint2d,PointEnd,pt);			//终点
};

NS_TOOL_FRAME_END