#pragma once

#include "Macro.h"
#include "Point2d.h"

//矩形2D:
//以左下角 和 右上角 两个 坐标点 为 矩形定位点。
//坐标系以左下为坐标原点，横向右为X轴正方向，纵向上位Y轴正方向

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CRect2d
{
public:
	bool	IsContain(const CPoint2d& pt)const;			//测试包含
	bool	IsContain(const CRect2d& rect)const;		//测试包含
	bool	IsIntersect(const CRect2d& rect)const;		//测试相交
	bool	CalIntersect(CRect2d& rResult,const CRect2d& rect)const;	//获取相交矩形
	float	GetWidth()const;
	float	GetHeight()const;
	bool	IsValid()const;					//是否为有效的矩形
	void	SetLeftBottom(float nX,float nY);
	void	SetRightTop(float nX,float nY);
	void	SetRect(float x1,float y1,float x2,float y2);
	void	SetRect(const CPoint2d& ptLeftBottom,const CPoint2d& ptRightTop);
	void	SetRectMid(const CPoint2d& ptMidPoint,const CPoint2d& ptSize);
	CPoint2d GetMidPoint()const;			//获取矩形中点
	CPoint2d GetSize()const;				//获取大小(长宽)
	bool	Contain(const CPoint2d& pt);	//包含某点(制作绑定盒)
public:
	bool	operator ==	(const CRect2d &rect)const;
	bool	operator != (const CRect2d &rect)const;
public:
	CRect2d(void);
	CRect2d(const CPoint2d& ptWhole);
	CRect2d(const CPoint2d& ptLeftBottom,const CPoint2d& ptRightTop);
	CRect2d(float x1,float y1,float x2,float y2);
	virtual ~CRect2d(void);
private:
	CFIELD_REF(CPoint2d,LeftBottom,pt);
	CFIELD_REF(CPoint2d,RightTop,pt);
};

NS_TOOL_FRAME_END
