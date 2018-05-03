#pragma once
#include "Macro.h"
#include "Point2d.h"

//�Ȼ���,360��ΪԲ�����ھ�Ϊ0Ϊ���Σ����߶���ΪԲ��

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CAnnularSector2d
{
public:
	bool	IsContain(const CPoint2d& ptPoint)const;		//�Ƿ�����õ�
	float	Distance(const CPoint2d& ptPoint) const;		//�㵽Բ�ĵľ���
	float	DistanceSquared(const CPoint2d& ptPoint) const;	//�㵽Բ�ĵľ����ƽ��
	bool	SetAnnularSector2d(float fInner,float fOuter,float fAngle,const CPoint2d& ptDirection);//����Բ��Ĭ��(0,0)
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
	CFIELD_FLOAT(InnerRadius);			//�ھ�
	CFIELD_FLOAT(OuterRadius);			//�⾶
	CFIELD_FLOAT(AngleRange);			//�Ƕȷ�Χ
	CFIELD_REF(CPoint2d,Direction,pt);	//��������
	CFIELD_REF(CPoint2d,Center,pt);		//Բ��
};

NS_TOOL_FRAME_END