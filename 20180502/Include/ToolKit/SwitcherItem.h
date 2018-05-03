#pragma once

#include "Macro.h"

NS_TOOL_FRAME_BEGIN

//������С����
//ѭ��ģʽ,��ǰֵ��������ֵ ��ô ����
//��ѭ��ģʽ,��ǰֵ��������ֵ����Ϊ����ֵ
class TOOLFRAME_DLL CSwitcherItem
{
public:
	bool	SetLoop(bool bLoop);	//����Ƿ�Ϊѭ��ģʽ
	int		AddItem(int nItemID);	//�����Ʒ ���ظ���Ʒ����������
	bool	RemoveItem(int nItemID);//�Ƴ���Ʒ ���ظ���Ʒ����������
	bool	ClearItem();			//�����Ʒ
	bool	AddItemRange(int nItemBegin,int nItemEnd);		//��ӷ�Χ��Ʒ
	bool	AddItemRangeOpen(int nItemBegin,int nItemEnd);	//��ӷ�Χ��Ʒ(������)
	
	int		GetSelIndex()const;		//��õ�ǰѡ�е� ����
	int		GetSelItem()const;		//��õ�ǰѡ�е� ��Ʒ
	bool	IsItemEmpty()const;		//�Ƿ���ƷΪ��
	bool	IsItemVaild(int nItemID)const;//���ظ���Ʒ�Ƿ���Ч
	uint	GetItemSize()const;		//��ȡ��Ʒ����
	bool	IsLoop()const;			//�����Ƿ���ѭ��ģʽ

	int		SelIndex(int nIndex);	//ѡ��ָ����������Ʒ ����ʵ��ָ����Ч��Ʒ����
	int		SelItem(int nItemID);	//ѡ�е�һ����Ʒ ����ʵ��ָ����Ч��Ʒ����
	int		SelFirstItem();			//ѡ�е�һ����Ʒ ����ʵ��ָ����Ч��Ʒ����
	int		SelLastItem();			//ѡ�����һ����Ʒ ����ʵ��ָ����Ч��Ʒ����

	int		NextSel(int nStep=1);	//ѡ����һ�� ����ʵ��ָ����Ч��Ʒ����
	int		PrevSel(int nStep=1);	//ѡ����һ�� ����ʵ��ָ����Ч��Ʒ����
public:
	CSwitcherItem(void);
	virtual ~CSwitcherItem(void);
private:
	VectorInt	_vItem;
	int			_nIndexCur;
	bool		_bLoop;
};

NS_TOOL_FRAME_END
