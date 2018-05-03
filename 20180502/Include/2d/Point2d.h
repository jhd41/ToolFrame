#pragma once
#include "Macro.h"

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CPoint2d
{
public:
	bool		SetXY(float fX,	float fY);							//设置点
	bool		GetXY(float* fX,float* fY) const;					//获取点
	bool		Swap(CPoint2d& ptPoint);							//交换点
	CPoint2d	GetMidPoint(const CPoint2d& ptPoint)const;			//获取两点的中点		
	float		Distance(const CPoint2d& pt)const;					//距离
	float		DistanceSquared(const CPoint2d& pt)const;			//距离的平方(性能高于Distance)
	double		GetAngle()const;									//获取角度(于X轴的夹角)
	double		GetAngle(const CPoint2d& v)const;					//获取向量夹角
	double		GetRotation()const;									//获取旋转角度(与Y轴的夹角)
	float		Dot(const CPoint2d& v) const;						//点乘
	float		Cross(const CPoint2d& other) const;					//叉乘
	double		Length() const;										//模
	double		LengthSquared() const;								//模方
	bool		Negate();											//向量反向 
	bool		Normalize();										//标准化
	CPoint2d	GetNormalized() const;								//标准化
	bool		SetRotation(float fRotation);						//作为向量时根据角度设元向量值
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
