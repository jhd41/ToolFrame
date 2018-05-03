#pragma once

#include "Macro.h"
#include "Point2d.h"

//����2D:
//�����½� �� ���Ͻ� ���� ����� Ϊ ���ζ�λ�㡣
//����ϵ������Ϊ����ԭ�㣬������ΪX��������������λY��������

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CRect2d
{
public:
	bool	IsContain(const CPoint2d& pt)const;			//���԰���
	bool	IsContain(const CRect2d& rect)const;		//���԰���
	bool	IsIntersect(const CRect2d& rect)const;		//�����ཻ
	bool	CalIntersect(CRect2d& rResult,const CRect2d& rect)const;	//��ȡ�ཻ����
	float	GetWidth()const;
	float	GetHeight()const;
	bool	IsValid()const;					//�Ƿ�Ϊ��Ч�ľ���
	void	SetLeftBottom(float nX,float nY);
	void	SetRightTop(float nX,float nY);
	void	SetRect(float x1,float y1,float x2,float y2);
	void	SetRect(const CPoint2d& ptLeftBottom,const CPoint2d& ptRightTop);
	void	SetRectMid(const CPoint2d& ptMidPoint,const CPoint2d& ptSize);
	CPoint2d GetMidPoint()const;			//��ȡ�����е�
	CPoint2d GetSize()const;				//��ȡ��С(����)
	bool	Contain(const CPoint2d& pt);	//����ĳ��(�����󶨺�)
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
