#pragma once
#include "Macro.h"
#include "Point2d.h"
//���������һ���߶�(����Ϊ�˵�)
//����ʽ:(y-y0)/(y0-y1)=(x-x0)/(x0-x1) 
//����:(y-y0)*(x0-x1)=(y0-y1)*(x-x0)
//�߶ΰ����������Ϊ���ڸ��߶�����ֱ�����ҵ��ڸ��߶�Ϊ�Խ��ߵľ�����
//�߶ΰ�����һ���߶ε�����Ϊ��һ���߶ε������˵㶼�������߶ΰ���

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CSegment2d
{
public:
	bool		IsContain(const CPoint2d& pt)const;		//�Ƿ�����õ�
	bool		IsContain(const CSegment2d& seg)const;	//�Ƿ�����߶�
	bool		IsIntersect(const CSegment2d& seg)const;//�߶��Ƿ��ཻ
	float		GetLength() const;						//��ȡ�߶γ���
	float		GetLengthSquared() const;				//��ȡ�߶γ��ȵ�ƽ��(���ܸ���)
	CPoint2d	GetMidPoint()const;						//��ȡ�߶��е�
private:
	float		CalDelta(float f1,float f2,float f3, float f4)const;								//�����ֵ
public:
	bool		operator ==	(const CSegment2d& seg)const;
	bool		operator != (const CSegment2d& seg)const;
public:
	CSegment2d(void);
	CSegment2d(const CPoint2d& pt1,const CPoint2d& pt2);
	CSegment2d(const CSegment2d& seg);
	virtual ~CSegment2d(void);
public:
	CFIELD_REF(CPoint2d,PointBegin,pt);			//���
	CFIELD_REF(CPoint2d,PointEnd,pt);			//�յ�
};

NS_TOOL_FRAME_END