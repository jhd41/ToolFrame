#include "ToolExtra.h"

#include "ToolXml.h"
#include "ToolPlat.h"
#include "ToolStd.h"
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
#include "ApiWin.h"
#endif
#ifdef MACRO_LIB_MFC
#include "ApiMFC.h"
#endif

#ifdef MACRO_LIB_MFC
void ToolFrame::Insert( MapFieldPropery& vDes,int nCol,const std::string& sTitle,int eSortRule,const std::string& sField,const std::string& sDefault ,IEditing* pEdit)
{
	SFieldMfcXmlProperty& property = ToolFrame::GetValueByKeyForce(vDes,nCol);
	property.nCol		= nCol;
	property.sTitle		= sTitle;
	property.eSortRule	= eSortRule;
	property.sField		= sField;
	property.sDefault	= sDefault;
	property.pEdit		= pEdit;
}

bool ToolFrame::Insert( TiXmlElement* pParent,const std::string& sSubName,CListCtrlEdit& cBox, MapFieldPropery& vField,const SetInt& vFliter )
{
	int nRows = ApiMFC::GetRowCount(cBox);
	for (int nRow =0;nRow<nRows;++nRow)
	{
		TiXmlElement* pElement = ToolFrame::InsertElement(pParent,sSubName);
		if (!pElement)return false;

		SetInt::const_iterator itr;
		foreach(itr,vFliter){
			int nCol = *itr;

			const SFieldMfcXmlProperty* pPropery = ToolFrame::GetValuePtrByKey(vField,nCol);
			if (!pPropery)return false;

			std::string sValue;
			ApiMFC::GetItemText(cBox,nRow,pPropery->nCol,sValue);
			ToolFrame::SetAttribute(pElement,pPropery->sField,sValue);
		}
	}
	return true;
}

bool ToolFrame::Check(  MapFieldPropery& vField )
{
	size_t uTotal = vField.size();
	for (size_t uIndex = 0;uIndex<uTotal;++uIndex)
	{
		if (!ToolFrame::IsHasKey(vField,(int)uIndex))return false;
	}

	return true;
}

bool ToolFrame::Init( CListCtrlEdit& cBox, MapFieldPropery& vSrc )
{
	for (size_t uIndex = 0;uIndex<vSrc.size();++uIndex)
	{
		const SFieldMfcXmlProperty* pPropery = ToolFrame::GetValuePtrByKey(vSrc,(int)uIndex);
		if (!pPropery)return false;

		cBox.SetTitle(pPropery->nCol,pPropery->sTitle,pPropery->eSortRule,pPropery->pEdit);
	}
	cBox.Init();
	return true;
}

bool ToolFrame::AddLine( CListCtrlEdit& cBox,TiXmlElement* pElement, MapFieldPropery& vPropery )
{
	int nRow = cBox.InsertItem(cBox.GetItemCount(),_T(""));

	for (size_t uIndex = 0;uIndex<vPropery.size();++uIndex)
	{
		const SFieldMfcXmlProperty* pPropery = ToolFrame::GetValuePtrByKey(vPropery,(int)uIndex);
		if (!pPropery)return false;

		std::string sValue;
		ToolFrame::SafeGetAttribute(pElement,pPropery->sField,	sValue,	pPropery->sDefault);
		cBox.SetItemText(nRow,pPropery->nCol,ApiWin::ToStringT(sValue).c_str());
	}

	return true;
}

bool ToolFrame::UTF8toGBK( TiXmlNode* pNode )
{
	if (!pNode)return false;

	//先翻译自己
	VectorAttribute vAttribute;
	if (ToolFrame::GetAttribute(vAttribute,pNode->ToElement()))
	{
		VectorAttribute::const_iterator itr;
		foreach(itr,vAttribute){
			TiXmlAttribute* pAttribute = (TiXmlAttribute*)*itr;
			if (!pAttribute)return false;

			if (pAttribute->Value())
			{
				pAttribute->SetValue(ApiWin::Utf8ToGbk(pAttribute->Value()).c_str());
			}
		}		
	}

	
	//翻译儿子
	if (ToolFrame::IsHasChild(pNode))
	{
		VectorElement vNode;
		if (!ToolFrame::GetSubNode(vNode,pNode))return false;

		VectorElement::iterator itr;
		foreach(itr,vNode){
			TiXmlElement* pElement = (TiXmlElement*)*itr;
			if (!UTF8toGBK(pElement))return false;

		}
	}
	return true;
}

bool ToolFrame::ModfiyLine( CListCtrlEdit& cBox,int nColKey,TiXmlElement* pParent,const std::string& sNodeName,MapFieldPropery& vPropery,const SetInt& vFliter )
{
	const SFieldMfcXmlProperty* pFieldKey = ToolFrame::GetValuePtrByKey(vPropery,nColKey);
	if (!pFieldKey)return false;

	std::string sValueKey;

	int nRows = ApiMFC::GetRowCount(cBox);
	for (int nRow = 0;nRow<nRows;++nRow)
	{
		ApiMFC::GetItemText(cBox,nRow,nColKey,sValueKey);
		const TiXmlElement* pElement = ToolFrame::GetElementByAttribute(pParent,sNodeName,pFieldKey->sField,sValueKey);
		if (pElement)
		{
			SetInt::const_iterator itr;
			foreach(itr,vFliter){
				int nColCur = *itr;

				const SFieldMfcXmlProperty* pFieldCur = ToolFrame::GetValuePtrByKey(vPropery,nColCur);
				if (pFieldCur)
				{
					std::string sValue;
					ToolFrame::GetAttribute(pElement,pFieldCur->sField,sValue);
					ApiMFC::SetItemText(cBox,nRow,pFieldCur->nCol,sValue);
				}
			}
		}
	}
	return true;
}

bool ToolFrame::SetWindowTex( CEdit& cBox,int nColKey,TiXmlElement* pElement,MapFieldPropery& vPropery )
{
	const SFieldMfcXmlProperty* pFieldKey = ToolFrame::GetValuePtrByKey(vPropery,nColKey);
	if (!pFieldKey)return false;

	std::string sValue;
	ToolFrame::GetAttribute(pElement,pFieldKey->sField,sValue);
	ApiMFC::SetWindowText(cBox,sValue);
	return true;
}

bool ToolFrame::SetWindowTex( CEdit& cBox,TiXmlElement* pElement,const std::string& sAttubiteName )
{
	std::string sValue;
	ToolFrame::GetAttribute(pElement,sAttubiteName,sValue);
	ApiMFC::SetWindowText(cBox,sValue);
	return true;
}

#endif//MACRO_LIB_MFC

#ifdef MACRO_LIB_BOOST
bool ToolFrame::IsLockedByOtherThread( const boost::recursive_mutex& mutex )
{
#if MACRO_TARGET_OS == MACRO_OS_WINDOWS
	if (!mutex.locking_thread_id)return false;
	if (mutex.locking_thread_id == ToolFrame::GetThreadId())
		return false;

	return true;
#endif

	return false;
}
#endif //MACRO_LIB_BOOST
