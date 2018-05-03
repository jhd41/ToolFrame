#pragma once

//ע��:�����ṩ�� ���߿�� ��һ���ۺ��塣���и�ǿ�ľ������������֡�ƽ̨���汾
//�ڱ������������ ͨ�ù��� ��ʹ�õ����ࡣ(������־,��ƽ̨,Boost,TinyXML)
//������Ҫ��Ϊ�˱���֮ǰ�����߿��໥��Ⱦ���ر������ġ����� ��׼����ļ� ��Ҫ���ÿ�ƽ̨���� ��ȡ��ǰ����·���ȵ�

#include "Macro.h"
#include "tinyxml.h"
#include "ToolPlat.h"
#include "MLoger.h"

#ifdef MACRO_LIB_MFC
#include "ListCtrlEdit.h"

//���Խṹ for xml�е��ֶ�����ͼLC�ؼ�һһ��Ӧ
struct SFieldMfcXmlProperty 
{
	int						nCol;			//��ͼ��
	std::string				sTitle;			//������
	int						eSortRule;		//������� CListCtrlEdit::ESoreRule
	std::string				sField;			//xml�е��ֶ�
	std::string				sDefault;		//Ĭ��ֵ
	ToolFrame::IEditing*	pEdit;			//�༭����
};

typedef std::vector<SFieldMfcXmlProperty>	VectorFieldPropery;
typedef std::map<int,SFieldMfcXmlProperty>	MapFieldPropery;
#endif
#ifdef MACRO_LIB_BOOST
#include <boost/thread/recursive_mutex.hpp>
#endif

namespace ToolFrame
{
	//MFC
#ifdef MACRO_LIB_MFC
	void Insert(MapFieldPropery& vDes,int nCol,const std::string& sTitle,int eSortRule,const std::string& sField,const std::string& sDefault,IEditing* pEdit = nullptr);
	bool Check( MapFieldPropery& vField);
	bool Init(CListCtrlEdit& cBox, MapFieldPropery& vSrc);
	//��ȡ�ڵ���ֶ���ӵ��б�ؼ�
	bool AddLine(CListCtrlEdit& cBox,TiXmlElement* pElement,MapFieldPropery& vPropery);
	//����ĳ�ֶ�ƥ���޸��б�ؼ�
	bool ModfiyLine( CListCtrlEdit& cBox,int nColKey,TiXmlElement* pParent,const std::string& sNodeName,MapFieldPropery& vPropery,const SetInt& vFliter );
	//����ĳ�ֶθ����ı�����
	bool SetWindowTex(CEdit& cBox,int nColKey,TiXmlElement* pElement,MapFieldPropery& vPropery);
	bool SetWindowTex(CEdit& cBox,TiXmlElement* pElement,const std::string& sAttubiteName);
	//����
	bool UTF8toGBK(TiXmlNode* pNode);

	//��ֵ����pParent��Ϊ�ӽڵ�
	bool Insert( TiXmlElement* pParent,const std::string& sSubName,CListCtrlEdit& cBox, MapFieldPropery& vField,const SetInt& vFliter );
#endif //MACRO_LIB_MFC

#ifdef MACRO_LIB_BOOST
	bool IsLockedByOtherThread(const boost::recursive_mutex& mutex);
#endif

	//ͨ��
	template<typename TPtr>
	void DropRef(std::vector<TPtr*>& vSrc);
};
template<typename TPtr>
void ToolFrame::DropRef( std::vector<TPtr*>& vSrc )
{
	typename std::vector<TPtr*>::iterator itr;
	foreach(itr,vSrc){
		(*itr)->DropRef();
	}
	vSrc.clear();
}

#ifdef MACRO_LIB_BOOST
//#define LOCK_RECURSIVE_MUTEX(mutex)		ASSERT_DEBUG_MSG(!ToolExtra::IsLockedByOtherThread(mutex),"LockedByOther! ThreadId:"<<ToolFrame::GetThreadId());\
//										LOG_DEBUG("EnterMutex ThreadId:"<<ToolFrame::GetThreadId());\
//										boost::recursive_mutex::scoped_lock lock##mutex(mutex);\
//										LOG_DEBUG("LeaveMutex ThreadId:"<<ToolFrame::GetThreadId());
// 		#define LOCK_RECURSIVE_MUTEX(mutex)		ASSERT_DEBUG_MSG(!ToolExtra::IsLockedByOtherThread(mutex),"LockedByOther! ThreadId:"<<ToolFrame::GetThreadId());\
// 												boost::recursive_mutex::scoped_lock lock##mutex(mutex);
#endif // MACRO_LIB_BOOST