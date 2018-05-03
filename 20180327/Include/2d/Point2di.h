#pragma once
#include "Macro.h"

//��CPoint2dΪ���� ��д�ɵ� ���� �汾 ��

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CPoint2di
{
public:
	bool		SetXY(int fX,	int fY);							//���õ�
	bool		GetXY(int* fX,int* fY) const;						//��ȡ��
	bool		Swap(CPoint2di& ptPoint);							//������
	CPoint2di	GetMidPoint(const CPoint2di& ptPoint)const;			//��ȡ������е�		
	float		Distance(const CPoint2di& pt)const;					//����
	int			DistanceSquared(const CPoint2di& pt)const;			//�����ƽ��(���ܸ���Distance)
	double		GetAngle()const;									//��ȡ�Ƕ�(��X��ļн�)
	double		GetAngle(const CPoint2di& v)const;					//��ȡ�����н�
	double		GetRotation()const;									//��ȡ��ת�Ƕ�(��Y��ļн�)
	int			Dot(const CPoint2di& v) const;						//���
	int			Cross(const CPoint2di& other) const;				//���
	double		Length() const;										//ģ
	double		LengthSquared() const;								//ģ��
	bool		Negate();											//�������� 
	bool		Normalize();										//��׼��
	CPoint2di	GetNormalized() const;								//��׼��
	bool		SetRotation(float fRotation);						//��Ϊ����ʱ���ݽǶ���Ԫ����ֵ
public:
	bool		operator <	(const CPoint2di &ptPoint)const;
	bool		operator <=	(const CPoint2di &ptPoint)const;
	bool		operator ==	(const CPoint2di &ptPoint)const;
	bool		operator !=	(const CPoint2di &ptPoint)const;

	CPoint2di	operator +	(const CPoint2di &ptPoint)const;
	CPoint2di	operator -	(const CPoint2di &ptPoint)const;
	CPoint2di	operator *	(int fValue)const;
	CPoint2di	operator /	(int fValue)const;

	CPoint2di&	operator +=	(const CPoint2di &ptPoint);
	CPoint2di&	operator -=	(const CPoint2di &ptPoint);
	CPoint2di&	operator *=	(int fValue);
	CPoint2di&	operator /=	(int fValue);
public:
	CPoint2di(void);
	CPoint2di(int fX,int fY);
	CPoint2di(const CPoint2di& pt);
	virtual ~CPoint2di(void);
private:
	CFIELD_INT(X);
	CFIELD_INT(Y);
};

NS_TOOL_FRAME_END
