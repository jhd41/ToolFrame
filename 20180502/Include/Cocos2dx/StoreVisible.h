#pragma once
#include "MacroCocos2dx.h"

//�ڵ���ɫ�洢
#ifdef MACRO_LIB_COCOS2D

class CStoreVisible
{
public:
	bool	SetNode(Node* pNode,bool bVisible);
	bool	SetNode(VectorNode& vNode,bool bVisible);

	bool	Store(Node* pNode);
	bool	Store(VectorNode& vNode);

	bool	Restore();//��ԭ
	bool	Clear();
public:
	CStoreVisible(void);
	virtual ~CStoreVisible(void);
private:
	VectorNode	_vNode;
	VectorBool	_vVisible;//��ʼ����ɫ
};

#endif //MACRO_LIB_COCOS2D