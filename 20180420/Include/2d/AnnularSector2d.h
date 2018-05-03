#pragma once
#include "Macro.h"
#include "Point2d.h"

//扇环形,360度为圆环，内径为0为扇形，二者都有为圆形

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CAnnularSector2d
{
public:
	bool	IsContain(const CPoint2d& ptPoint)const;		//是否包含该点
	float	Distance(const CPoint2d& ptPoint) const;		//点到圆心的距离
	float	DistanceSquared(const CPoint2d& ptPoint) const;	//点到圆心的距离的平方
	bool	SetAnnularSector2d(float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection);//不填圆心默认(0,0)
	bool	SetAnnularSector2d(float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection,const CPoint2d& ptCenter);
	bool	SetAnnularSector2d(const CAnnularSector2d& sa);
	bool	SetDirection(float fRotation);
public:
	CAnnularSector2d(void);
	CAnnularSector2d(float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection);
	CAnnularSector2d(float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection,const CPoint2d& ptCenter);
	CAnnularSector2d(const CAnnularSector2d& sa);
	virtual ~CAnnularSector2d(void);
public:
	bool		operator ==	(const CAnnularSector2d& sa)const;
	bool		operator != (const CAnnularSector2d& sa)const;
private:
	CFIELD_FLOAT(InnerRadius);			//内径
	CFIELD_FLOAT(OuterRadius);			//外径
	CFIELD_FLOAT(AngleRange);			//角度范围
	CFIELD_REF(CPoint2d,Direction,pt);	//方向向量
	CFIELD_REF(CPoint2d,Center,pt);		//圆心
};

NS_TOOL_FRAME_END