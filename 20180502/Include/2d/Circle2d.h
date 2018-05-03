#pragma once

#include "Macro.h"
#include "Point2d.h"

//Բ��2D:
//Բ�ĺͰ뾶

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CCircle2d
{
public:
	bool			IsContain(const CPoint2d& pt)const;				//�Ƿ����
	bool			IsContain(const CCircle2d& circle)const;		//�Ƿ����
	bool			IsIntersect(const CCircle2d& circle)const;		//�����ཻ
	const CPoint2d& GetCenter()const;								//��ȡԲ��
	float			GetRadius()const;								//��ȡ�뾶
	float			CalCenterDistance(const CCircle2d& circle)const;//��ȡ��ԲԲ�ľ���
	float			CalCenterDistanceSquared(const CCircle2d& circle)const;//��ȡ��ԲԲ�ľ����ƽ��(���ܸ���GetCenterDistance)
public:
	bool	operator ==	(const CCircle2d& circle)const;
	bool	operator != (const CCircle2d& circle)const;
public:
	CCircle2d(void);
	virtual ~CCircle2d(void);
private:
	CPoint2d	_ptCenter;	//Բ��
	float		_fRadius;	//�뾶
};

NS_TOOL_FRAME_END