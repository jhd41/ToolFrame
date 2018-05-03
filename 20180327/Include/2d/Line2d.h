#pragma once
#include "Macro.h"
#include "Point2d.h"
//本来表示一条双向无限延伸的直线,为了保持精确，我们采用两点式的变形来存储直线的表达式
//两点式:(y-y0)/(y0-y1)=(x-x0)/(x0-x1) 
//变形:(y-y0)*(x0-x1) = (y0-y1)*(x-x0)
//一般式(y1-y0)x+(x0-x1)y+(y0(x1-x0)-x0(y1-y0))=0
NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CLine2d
{
public:
	bool	IsInLine(const CPoint2d& pt)const;
	float	Distance(const CPoint2d& pt);			//点到直线距离
	float	DistanceSquared(const CPoint2d& pt);
	float	CalAngle(const CLine2d& line);			//计算夹角
	float	CalRadian(const CLine2d& line);			//计算直线夹角弧度
private:
	bool	CalCoefficient(float& fA,float& fB,float& fC) const;		//计算一般式系数
public:
	bool operator == (const CLine2d& line)const;
public:
	CLine2d(void);
	CLine2d(const CPoint2d& pt1,const CPoint2d& pt2);
	CLine2d(const CLine2d& line);
	virtual ~CLine2d(void);
public:
	CFIELD_REF(CPoint2d,Point1,pt);
	CFIELD_REF(CPoint2d,Point2,pt);
};

NS_TOOL_FRAME_END
