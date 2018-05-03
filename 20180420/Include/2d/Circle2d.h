#pragma once

#include "Macro.h"
#include "Point2d.h"

//圆形2D:
//圆心和半径

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CCircle2d
{
public:
	bool			IsContain(const CPoint2d& pt)const;				//是否包含
	bool			IsContain(const CCircle2d& circle)const;		//是否包含
	bool			IsIntersect(const CCircle2d& circle)const;		//测试相交
	const CPoint2d& GetCenter()const;								//获取圆心
	float			GetRadius()const;								//获取半径
	float			CalCenterDistance(const CCircle2d& circle)const;//获取两圆圆心距离
	float			CalCenterDistanceSquared(const CCircle2d& circle)const;//获取两圆圆心距离的平方(性能高于GetCenterDistance)
public:
	bool	operator ==	(const CCircle2d& circle)const;
	bool	operator != (const CCircle2d& circle)const;
public:
	CCircle2d(void);
	virtual ~CCircle2d(void);
private:
	CPoint2d	_ptCenter;	//圆心
	float		_fRadius;	//半径
};

NS_TOOL_FRAME_END