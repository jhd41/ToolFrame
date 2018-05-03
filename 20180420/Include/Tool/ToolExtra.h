#pragma once

//注记:本类提供在 工具框架 下一个综合体。具有更强的纠错性例如语种、平台、版本
//在本类会引入所有 通用工具 所使用到的类。(例如日志,跨平台,Boost,TinyXML)
//本类主要是为了避免之前各工具库相互污染所特别设立的。例如 标准库打开文件 需要调用跨平台函数 获取当前绝对路径等等

#include "Macro.h"
#include "tinyxml.h"
#include "ToolPlat.h"
#include "MLoger.h"

#ifdef MACRO_LIB_MFC
#include "ListCtrlEdit.h"

//属性结构 for xml中的字段与视图LC控件一一对应
struct SFieldMfcXmlProperty 
{
	int						nCol;			//视图列
	std::string				sTitle;			//标题栏
	int						eSortRule;		//排序规则 CListCtrlEdit::ESoreRule
	std::string				sField;			//xml中的字段
	std::string				sDefault;		//默认值
	ToolFrame::IEditing*	pEdit;			//编辑窗口
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
	//读取节点的字段添加到列表控件
	bool AddLine(CListCtrlEdit& cBox,TiXmlElement* pElement,MapFieldPropery& vPropery);
	//根据某字段匹配修改列表控件
	bool ModfiyLine( CListCtrlEdit& cBox,int nColKey,TiXmlElement* pParent,const std::string& sNodeName,MapFieldPropery& vPropery,const SetInt& vFliter );
	//根据某字段更新文本内容
	bool SetWindowTex(CEdit& cBox,int nColKey,TiXmlElement* pElement,MapFieldPropery& vPropery);
	bool SetWindowTex(CEdit& cBox,TiXmlElement* pElement,const std::string& sAttubiteName);
	//翻译
	bool UTF8toGBK(TiXmlNode* pNode);

	//将值插入pParent作为子节点
	bool Insert( TiXmlElement* pParent,const std::string& sSubName,CListCtrlEdit& cBox, MapFieldPropery& vField,const SetInt& vFliter );
#endif //MACRO_LIB_MFC

#ifdef MACRO_LIB_BOOST
	bool IsLockedByOtherThread(const boost::recursive_mutex& mutex);
#endif

	//通用
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