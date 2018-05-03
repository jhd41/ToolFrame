#pragma once
#include "Macro.h"
#include "Segment.h"
#include "TObjCreator.h"

//���������ö���������ʽ�洢һά�߶�
NS_TOOL_FRAME_BEGIN

//�ڵ�
struct IBinaryNode;
typedef std::map<int,IBinaryNode*>				MapIntBinaryNode;
typedef std::vector<IBinaryNode*>				VectorBinaryNode;
typedef std::list<std::pair<CSegment,void*> >	ListObj;

struct IBinaryNode
{
	CSegment			seg;
	VectorBinaryNode	vNode;
	ListObj				vObj;
	IBinaryNode*		pParent;
	int					nIndex;
	IBinaryNode(){
		pParent = nullptr;
		nIndex = 0;
	}
};
class TOOLFRAME_DLL CBinaryTree
{
public:
	bool Init(const CSegment& rRoot,const float fCell);		//���ø��ڵ������С ��Ԫ���С
	bool AddObj(const CSegment& segObj,const void* pObj);	//��ӽڵ�
	bool Find(ListVoidPtr& vObj,const CSegment& seg)const;	//���Ҹ������ڵ�Ԫ��
	bool Erase(const CSegment& segObj,void* pObj);			//ɾ��
	uint Erase(void* pObj,int nCount = 1);					//ɾ��(��Ч�� ���ز�������)
	size_t GetSize()const;									//��ȡԪ�صĸ���
	size_t GetNodeSize()const;								//��ȡ�ڵ�ĸ���
	bool ClearEmptyNode();									//�����Ч�ڵ�
private:
	bool			IsLeaf(const IBinaryNode* pNode)const;	//�߶γ���С�ڵ���Ԫ�߶Σ���ô����Ҷ�ӽڵ�
	IBinaryNode*	AddObj(IBinaryNode* pNode, const CSegment& segObj,void* pObj);			//��ӽڵ�
	IBinaryNode*	FindChildCanContainSegment(IBinaryNode* pParent,const CSegment& segObj)const;//Ѱ�ҿ������ɵ��ӽڵ�
	IBinaryNode*	FindNode(IBinaryNode* pNode,const CSegment& seg)const;	
	bool			Find(ListVoidPtr& vObj,IBinaryNode* pParent,const CSegment& seg)const;	//���Ҹ������ڵ�Ԫ��//����ָ���������ڽڵ�
	bool			ClearOneEmptyNode();
	uint			Erase(IBinaryNode* pParent,void* pObj,int nCount);
public:
	CBinaryTree(void);
	virtual ~CBinaryTree(void);
private:
	IBinaryNode*				_pNodeRoot;	//���ڵ�
	float						_fCell;		//��Ԫ�߶δ�С
	TObjCreator<IBinaryNode>	_vCreator;	//�ڵ㴴����(�����ڴ����)
	size_t						_uCount;	//Ԫ�ظ���
};

NS_TOOL_FRAME_END