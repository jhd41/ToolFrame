#pragma once
#include "Macro.h"
#include "Point2d.h"

NS_TOOL_FRAME_BEGIN

//����
//��������������ʾ���ߣ����е�һ������Ϊ�����
//�����x0,�����Ϊx1,Ŀ���Ϊx2
//(x2-x0) / (x1-x0) = (y2-y0) / (y1-y0); ��ֵ����Ϊ����
//����:(x2-x0) * (y1-y0) = (x1-x0) * (y2-y0)
class TOOLFRAME_DLL CRay2d
{
public:
	bool		IsInRay(const CPoint2d& pt)const;		//�ж��Ƿ���������
	CPoint2d	CalDistancePoint(float fDistance)const;	//���������� fDistance ���봦������
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
