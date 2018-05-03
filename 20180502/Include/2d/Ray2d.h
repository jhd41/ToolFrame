#pragma once
#include "Macro.h"
#include "Point2d.h"

NS_TOOL_FRAME_BEGIN

//射线
//用两个点来来表示射线，其中第一个点认为是起点
//设起点x0,方向点为x1,目标点为x2
//(x2-x0) / (x1-x0) = (y2-y0) / (y1-y0); 比值不能为负数
//变形:(x2-x0) * (y1-y0) = (x1-x0) * (y2-y0)
class TOOLFRAME_DLL CRay2d
{
public:
	bool		IsInRay(const CPoint2d& pt)const;		//判断是否在射线上
	CPoint2d	CalDistancePoint(float fDistance)const;	//计算距离起点 fDistance 距离处的坐标
public:
	bool operator == (const CRay2d& ray)const;
public:
	CRay2d(void);
	CRay2d(const CPoint2d& ptStart,const CPoint2d& ptPointDirect);
	CRay2d(const CRay2d& ray);
	virtual ~CRay2d(void);
public:
	CFIELD_REF(CPoint2d,PointStart,pt);
	CFIELD_REF(CPoint2d,PointDirect,pt);
};

NS_TOOL_FRAME_END
