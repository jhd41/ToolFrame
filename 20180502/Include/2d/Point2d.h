#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CPoint2d
{
public:
	bool		SetXY(float fX,	float fY);							//���õ�
	bool		GetXY(float* fX,float* fY) const;					//��ȡ��
	bool		Swap(CPoint2d& ptPoint);							//������
	CPoint2d	GetMidPoint(const CPoint2d& ptPoint)const;			//��ȡ������е�		
	float		Distance(const CPoint2d& pt)const;					//����
	float		DistanceSquared(const CPoint2d& pt)const;			//�����ƽ��(���ܸ���Distance)
	double		GetAngle()const;									//��ȡ�Ƕ�(��X��ļн�)
	double		GetAngle(const CPoint2d& v)const;					//��ȡ�����н�
	double		GetRotation()const;									//��ȡ��ת�Ƕ�(��Y��ļн�)
	float		Dot(const CPoint2d& v) const;						//���
	float		Cross(const CPoint2d& other) const;					//���
	double		Length() const;										//ģ
	double		LengthSquared() const;								//ģ��
	bool		Negate();											//�������� 
	bool		Normalize();										//��׼��
	CPoint2d	GetNormalized() const;								//��׼��
	bool		SetRotation(float fRotation);						//��Ϊ����ʱ���ݽǶ���Ԫ����ֵ
public:
	bool		operator <	(const CPoint2d &ptPoint)const;
	bool		operator <=	(const CPoint2d &ptPoint)const;
	bool		operator ==	(const CPoint2d &ptPoint)const;
	bool		operator !=	(const CPoint2d &ptPoint)const;

	CPoint2d	operator +	(const CPoint2d &ptPoint)const;
	CPoint2d	operator -	(const CPoint2d &ptPoint)const;
	CPoint2d	operator *	(float fValue)const;
	CPoint2d	operator /	(float fValue)const;

	CPoint2d&	operator +=	(const CPoint2d &ptPoint);
	CPoint2d&	operator -=	(const CPoint2d &ptPoint);
	CPoint2d&	operator *=	(float fValue);
	CPoint2d&	operator /=	(float fValue);
public:
	CPoint2d(void);
	CPoint2d(float fX,float fY);
	CPoint2d(const CPoint2d& pt);
	virtual ~CPoint2d(void);
private:
	CFIELD_FLOAT(X);
	CFIELD_FLOAT(Y);
};

NS_TOOL_FRAME_END
