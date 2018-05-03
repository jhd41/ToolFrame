#pragma once
#include "Macro.h"

//�˴����߶�Ϊһά�߶�,����2��ֵ��ʾ�����յ�

NS_TOOL_FRAME_BEGIN
class TOOLFRAME_DLL CSegment
{
public:
	bool		IsContain(float fPosition)const;		//�Ƿ������λ��
	bool		IsContain(const CSegment& seg)const;	//�Ƿ�����߶�
	bool		IsIntersect(const CSegment& seg)const;	//�߶��Ƿ��ཻ
	bool		CalIntersect(CSegment& segSub,const CSegment& seg)const;//�����ཻ����
	float		GetLength() const;						//��ȡ�߶γ���
	float		GetMidPosition()const;					//��ȡ�߶��е�
	bool		SetSegment(float fPositionBegin,float fPositionEnd);
	bool		SetSegment(int nPositionBegin,int nPositionEnd);
	bool		SetSegment(const CSegment& seg);
public:
	bool		operator ==	(const CSegment& seg)const;
	bool		operator != (const CSegment& seg)const;
public:
	CSegment(void);
	CSegment(float fPositionBegin,float fPositionEnd);
	CSegment(int nPositionBegin,int nPositionEnd);
	CSegment(const CSegment& seg);
	virtual ~CSegment(void);
private:
	CFIELD_FLOAT(Begin);
	CFIELD_FLOAT(End);
};

NS_TOOL_FRAME_END