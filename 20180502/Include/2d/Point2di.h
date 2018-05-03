#pragma once
#include "Macro.h"

//以CPoint2d为基础 改写成的 整型 版本 点

NS_TOOL_FRAME_BEGIN

class TOOLFRAME_DLL CPoint2di
{
public:
	bool		SetXY(int fX,	int fY);							//设置点
	bool		GetXY(int* fX,int* fY) const;						//获取点
	bool		Swap(CPoint2di& ptPoint);							//交换点
	CPoint2di	GetMidPoint(const CPoint2di& ptPoint)const;			//获取两点的中点		
	float		Distance(const CPoint2di& pt)const;					//距离
	int			DistanceSquared(const CPoint2di& pt)const;			//距离的平方(性能高于Distance)
	double		GetAngle()const;									//获取角度(于X轴的夹角)
	double		GetAngle(const CPoint2di& v)const;					//获取向量夹角
	double		GetRotation()const;									//获取旋转角度(与Y轴的夹角)
	int			Dot(const CPoint2di& v) const;						//点乘
	int			Cross(const CPoint2di& other) const;				//叉乘
	double		Length() const;										//模
	double		LengthSquared() const;								//模方
	bool		Negate();											//向量反向 
	bool		Normalize();										//标准化
	CPoint2di	GetNormalized() const;								//标准化
	bool		SetRotation(float fRotation);						//作为向量时根据角度设元向量值
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
