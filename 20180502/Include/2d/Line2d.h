#pragma once
#include "Macro.h"
#include "Point2d.h"
//������ʾһ��˫�����������ֱ��,Ϊ�˱��־�ȷ�����ǲ�������ʽ�ı������洢ֱ�ߵı��ʽ
//����ʽ:(y-y0)/(y0-y1)=(x-x0)/(x0-x1) 
//����:(y-y0)*(x0-x1) = (y0-y1)*(x-x0)
//һ��ʽ(y1-y0)x+(x0-x1)y+(y0(x1-x0)-x0(y1-y0))=0
NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CLine2d
{
public:
	bool	IsInLine(const CPoint2d& pt)const;
	float	Distance(const CPoint2d& pt);			//�㵽ֱ�߾���
	float	DistanceSquared(const CPoint2d& pt);
	float	CalAngle(const CLine2d& line);			//����н�
	float	CalRadian(const CLine2d& line);			//����ֱ�߼нǻ���
private:
	bool	CalCoefficient(float& fA,float& fB,float& fC) const;		//����һ��ʽϵ��
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
