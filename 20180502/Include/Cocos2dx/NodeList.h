#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_COCOS2D

#include "MacroCocos2dx.h"

NS_TOOL_FRAME_BEGIN

//ע��:������ɶ��CCSprite���֡���ê��(0.5,0.5 ����)��д
//ĿǰΪ�˷������ֻ֧��ÿ����Ԫ��ͬ����С �� ÿ����ԪС�ڵ�����ʾ����
//�Լ�����̳�CCNode��Ϊһ���ڵ� Ҳͬ���ܵ� ��Ч �Լ��Լ� Ӱ��
//ͨ���Լ��ĺ��ӽڵ�����������
class CNodeList
	:public	CCNodeRGBA
{
	COCOS2DX_CREATE(CNodeList);
public:
	enum{
		ALIGN_INVAID=0,

		ALIGN_HORIZONTAL_CENTER,	//ˮƽ���ж���
		ALIGN_HORIZONTAL_AVG,		//ˮƽ����
		ALIGN_HORIZONTAL_FULL,		//ˮƽ����
		
		ALIGN_VERTICAL_CENTER,		//��ֱ����
		ALIGN_VERTICAL_AVG,			//��ֱ����
		ALIGN_VERTICAL_FULL,		//��ֱ����
	};

public:
	bool	SetSize(const CCSize& rSize);
	bool	SetWithRect(const CCRect& rect);
	
	void	SetMoveArg(float fMoveTime,float fMoveRate);
public:
	virtual void addChild(CCNode * child);
	virtual void addChild(CCNode * child, int zOrder);
	virtual void addChild(CCNode * child, int zOrder, int tag);
	virtual void removeChild(CCNode* child, bool cleanup);
	virtual void reorderChild(CCNode * child, int zOrder);

private:
	void	Update(float dt);
public:
	//���Բ�����
	bool	Adjust();		//ƥ����Ļ ������������
	bool	Cut();			//�ü���Ļ
private:

	bool	AdjustLeft();				//�����
	bool	AdjustRight();				//�Ҷ���

	bool	AdjustCenterHorizontal();	//ˮƽ����
	bool	AdjustAvgHorizonta();		//ˮƽ����

	bool	AdjustCenterVertical();		//��ֱ����
	bool	AdjustAvgVertical();		//��ֱ����

	bool	AdjustFullHorizontal();		//ˮƽ���
	bool	AdjustFullVertical();		//��ֱ���

	//��������
public:
	void	SetAdjustScreenCenter();
	void	SetSizeWhithScreenSize();

private:
	CCSize	CalTotalSize();//��ȡ�����ܳߴ�
	bool	MoveTo(const VectorPoint& vPoint);//�������ƶ���ָ���ص�

	bool	CalPosTileHorizontal(VectorPoint& vPoint,const CCPoint& ptOffset =CCPoint(0,0) );	//����ˮƽƽ�̵�����
	bool	CalPosAvgHorizontal(VectorPoint& vPoint);											//����ˮƽ���ֵ�����

	bool	CalPosTileVertical(VectorPoint& vPoint,const CCPoint& ptOffset =CCPoint(0,0) );		//������ֱƽ�̵�����
	bool	CalPosAvgVertical(VectorPoint& vPoint);												//������ֱ���ֵ�����

	bool	CalPosFullHorizontal(VectorPoint& vPoint);											//����ˮƽ������ĸ�������
	bool	CalPosFullVertical(VectorPoint& vPoint);											//������ֱ������ĸ�������

	//������ݴ�С
	CCSize	GetNeedSize(int eAlign);

	CCSize	GetNeedSizeHorizontalTile();//���ˮƽƽ�̷�ʽ�����С
	CCSize	GetNeedSizeHorizontalAvg();	//���ˮƽ���ַ�ʽ�����С
	CCSize	GetNeedSizeHorizontalFull();//���ˮƽ��䷽ʽ�����С
	CCSize	GetNeedSizeVerticalTile();	//�����ֱƽ�̷�ʽ�����С
	CCSize	GetNeedSizeVerticalAvg();	//�����ֱ���ַ�ʽ�����С
	CCSize	GetNeedSizeVerticalFull();	//�����ֱ��䷽ʽ�����С

	//����Ӧ��С
	void	SetAdaptive(const CCSize& rNeed);
	float	GetAdaptiveRate(const CCSize& rContent,const CCSize& rNeed);
	CCSize	GetAdaptiveSize(const CCSize& rContent,const CCSize& rNeed);

	//�ж��Ƿ��㹻�ռ�
	bool	IsEnoughSpace(const CCSize& rNeed);
	bool	IsEnoughSpace(const CCSize& rContent,const CCSize& rNeed);

	bool	AdjustEnoughSpace(CCSize& rNeed,int eAlign);

	//��ȡ�ӽڵ�
	bool	IsChildEmpty();					//�ӽڵ��Ƿ��
	UINT	GetChildCount();				//��ȡ�ӽڵ�����
	CCNode*	FindChildAtIndex(UINT nIndex);	//��ȡ�ӽڵ� ͨ������
	CCNode*	FindChildLast();					//��ȡ���һ���ӽڵ�
	CCNode* FindChildByBoundingBoxMostHigh();//��ȡ�󶨺���ߵ��ӽڵ�
	CCNode* FindChildByBoundingBoxMostWide();//��ȡ�󶨺������ӽڵ�
	
	//�������ݴ�С
	bool	Cut(CCSize rNeed);
private:
	CNodeList(void);
	virtual ~CNodeList(void);
private:
	CFIELD_INT(Align);		//���뷽ʽ
	CFIELD_BOOL(Adaptive);	//����Ӧ
	CFIELD_BOOL(AutoCut);	//�Զ��ü�
private:
	float			_fMoveTime;		//�ƶ���ʱ��
	float			_fMoveRate;		//�ƶ��ļ��ٶ�
	bool			_bDirtyAdjust;	//������ ���ڼ�������
	CCSize	_rStandard;		//�ü����� ��׼��С
};


NS_TOOL_FRAME_END

#endif //MACRO_LIB_COCOS2D
