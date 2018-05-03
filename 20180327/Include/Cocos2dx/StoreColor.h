#pragma once
#include "MacroCocos2dx.h"

//�ڵ���ɫ�洢
#ifdef MACRO_LIB_COCOS2D

class CStoreColor
{
	typedef std::vector<Color3B> VectorColor3B;
public:
	bool	SetNode(Node* pNode,const Color3B& clr);
	bool	SetNode(VectorNode& vNode,const Color3B& clr);
	bool	Store(Node* pNode);
	bool	Store(VectorNode& vNode);
	bool	Restore();//��ԭ
	bool	Clear();
public:
	CStoreColor(void);
	virtual ~CStoreColor(void);
private:
	VectorNode		_vNode;
	VectorColor3B	_vColor;//��ʼ����ɫ
};

#endif //MACRO_LIB_COCOS2D