#include "ToolXml.h"
#include "ToolStd.h"
#include "ApiXml.h"

TiXmlElement* ToolFrame::GetElement( TiXmlNode* xParent,const std::string& sNamePath)
{
	if (!xParent)return nullptr;
	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return nullptr;

	//找到目标节点
	return ApiXml::FindElement(xParent,vNodeName,vAttribute);
}

const TiXmlElement* ToolFrame::GetElement( const TiXmlNode* xParent,const std::string& sNamePath )
{
	return ToolFrame::GetElement((TiXmlNode*)xParent,sNamePath);
}

bool ToolFrame::GetElement(VectorElement& vElement, TiXmlNode* xParent,const std::string& sNamePath )
{
	if (!xParent)return false;
	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return nullptr;

	//找到目标节点
	TiXmlElement*  pElement = ApiXml::FindElement(xParent,vNodeName,vAttribute);
	if (!pElement)return false;
	
	while(pElement){
		vElement.push_back(pElement);
		pElement = ApiXml::FindElementSibling(pElement,vAttribute);
	}
	
	return true;
}

bool ToolFrame::GetElement(VectorElement& vElement, const TiXmlNode* xParent,const std::string& sNamePath )
{
	return GetElement(vElement,ConstCast(xParent),sNamePath);
}

TiXmlElement* ToolFrame::GetElementForce( TiXmlNode* xParent,const std::string& sNamePath )
{
	if (!xParent)return nullptr;
	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return nullptr;

	//如果没有给出节点路径 那么看自己是否符合条件
	if (vNodeName.empty())
	{
		if (ApiXml::IsAttributeEqual(xParent->ToElement(),vAttribute))
			return xParent->ToElement();
		
		return nullptr;
	}

	//找到目标节点的父节点
	std::string sLastNodeName = ToolFrame::GetBack(vNodeName);
	ToolFrame::EraseBack(vNodeName);
	VectorString::const_iterator itr;
	foreach(itr,vNodeName){
		if (!xParent)return nullptr;

		const std::string& sNodeName = *itr;

		if (sNodeName == "")
		{
			continue;
		}
		if (sNodeName == ".")
		{
			continue;
		}
		if (sNodeName == "..")
		{
			xParent = xParent->Parent();
			continue;
		}
		TiXmlNode* xNodeTemp = xParent->FirstChild(sNodeName.c_str());

		//如果找不到节点创建
		if (!xNodeTemp)
		{
			TiXmlElement xNew(sNodeName.c_str());
			xParent->InsertEndChild(xNew);
			xNodeTemp = xParent->LastChild(sNodeName.c_str());
		}

		xParent = xNodeTemp;
	}

	if (!xParent)return nullptr;//这几乎不可能 除非很极端的情况
	
	//找找此节点下面是否有符合条件的
	TiXmlElement*  pElement = ApiXml::FindChildElement(xParent,sLastNodeName,vAttribute);
	if (!pElement)
	{
		//如果没有 添加一个符合条件的
		TiXmlElement xNew(sLastNodeName.c_str());
		xParent->InsertEndChild(xNew);
		pElement = xParent->LastChild()->ToElement();

		//设置属性
		MapStringString::const_iterator itr;
		foreach(itr,vAttribute){
			const std::string& sKey = itr->first;
			const std::string& sValue = itr->second;
			pElement->SetAttribute(sKey.c_str(),sValue.c_str());
		}
	}

	return pElement;
}

TiXmlElement* ToolFrame::InsertElement( TiXmlNode* xParent,const std::string& sNameElement )
{
	if (!xParent)return nullptr;
	TiXmlElement xNew(sNameElement.c_str());
	xParent->InsertEndChild(xNew);
	TiXmlNode* pLastNode = xParent->LastChild(sNameElement.c_str());
	if (!pLastNode)return nullptr;
	return pLastNode->ToElement();
}

TiXmlElement* ToolFrame::InsertElement( TiXmlNode* xParent,const TiXmlElement* pXmlClone ,bool bCheckEqual/*=false*/ )
{
	if (!xParent || ! pXmlClone)return nullptr;

	if (!bCheckEqual || (bCheckEqual && !ToolFrame::IsHasEqualElement(pXmlClone,xParent))){
		TiXmlNode* pXml = InsertNode(xParent,pXmlClone);
		return pXml->ToElement();
	}
	return nullptr;
}

bool ToolFrame::InsertElement( TiXmlNode* xParent,const VectorElement& vXmlClone ,bool bCheckEqual/*=false*/ )
{
	VectorElement::const_iterator itr;
	foreach(itr,vXmlClone){
		ToolFrame::InsertElement(xParent,*itr,bCheckEqual);	
	}

	return true;
}

TiXmlNode* ToolFrame::InsertNode( TiXmlNode* xParent,const TiXmlNode* pXmlClone )
{
	if (!xParent || ! pXmlClone)return nullptr;

	return xParent->InsertEndChild(*pXmlClone);
}

bool ToolFrame::IsHasChild( const TiXmlNode* pElement,const std::string& sName)
{
	pElement = GetElement(pElement,sName);
	if (!pElement)return false;
	
	return nullptr != pElement->FirstChild();
}

bool ToolFrame::IsCData(const TiXmlText* pXml )
{
	return pXml->CDATA();
}

bool ToolFrame::GetText( const TiXmlElement* pXml,std::string& sValue,const std::string& sDefault )
{
	return GetText<std::string>(pXml,sValue,sDefault);
}

TiXmlText* ToolFrame::GetText( TiXmlElement* pXml )
{
	return pXml->ToText();
}

bool ToolFrame::IsHasText( const TiXmlElement* pXml )
{
	return nullptr != pXml->GetText();
}

bool ToolFrame::CopyAttribute(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sName )
{
	return CopyAttribute(pSrc,pDes,sName,sName);
}

bool ToolFrame::CopyAttribute(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sNameSrc,const std::string& sNameDes )
{
	std::string sValue;
	if (!ToolFrame::GetAttribute(pSrc,sNameSrc,sValue))return false;
	return ToolFrame::SetAttribute(pDes,sNameDes,sValue);
}

void ToolFrame::CopyText(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sName )
{
	return CopyText(pSrc,pDes,sName,sName);
}

void ToolFrame::CopyText(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sNameSrc,const std::string& sNameDes )
{
	std::string sValue;

	const TiXmlElement* pXmlSrc = pSrc->FirstChildElement(sNameSrc.c_str());
	while(pXmlSrc){
		TiXmlElement* pXmlDes = ToolFrame::InsertElement(pDes,sNameDes);
		ToolFrame::GetText(pXmlSrc,sValue,"");
		ToolFrame::SetText(pXmlDes,sValue);

		pXmlSrc = pXmlSrc->NextSiblingElement(sNameSrc.c_str());
	}
}

std::string ToolFrame::GetNodeName(const TiXmlNode* pXml )
{
	const char* szName = ApiXml::GetNodeName(pXml);
	return szName ? szName:"";
}

void ToolFrame::RemoveText( TiXmlElement* pXml )
{
	if (!IsHasText(pXml))return;
	
	TiXmlNode* pNode = pXml->FirstChild();
	while(pNode){
		TiXmlText* pText =  pNode->ToText();
		pXml->RemoveChild(pText);
		return ;

		pNode = pXml->NextSibling();
	}
}

const char* ToolFrame::GetSubText( const TiXmlElement* pXml,const std::string& sName )
{
	const TiXmlElement* pSub = pXml->FirstChildElement(sName.c_str());
	if (!pSub)return "";
	
	return pSub->GetText() ? pSub->GetText():"";
}

bool ToolFrame::GetSubText( const TiXmlElement* pXml,const std::string& sName,std::string& tValue,const std::string& tDefault )
{
	return GetSubText<std::string>(pXml,sName,tValue,tDefault);
}

bool ToolFrame::IsRoot( const TiXmlNode* pXml )
{
	if (!pXml->Parent())return true;
	if (!pXml->Parent()->Parent())return true;

	return false;
}

bool ToolFrame::Parse( TiXmlDocument& xDoc, const char szBuffer[] )
{
    if (!szBuffer) return false;
    xDoc.Parse(szBuffer);
    return !xDoc.Error();
}

bool ToolFrame::Parse( TiXmlDocument& xDoc, const std::string& sBuffer )
{
    xDoc.Parse(sBuffer.c_str());
    return !xDoc.Error();
}

TiXmlElement* ToolFrame::ToElement( TiXmlNode* xNode )
{
	return xNode->ToElement();
}

const TiXmlElement* ToolFrame::ToElement( const TiXmlNode* xNode )
{
	return xNode->ToElement();
}

bool ToolFrame::IsAttributEqual( const TiXmlElement* pNode,const MapStringString& vValue )
{
	return ApiXml::IsAttributeEqual(pNode,vValue);
}

bool ToolFrame::IsAttributEqual( const TiXmlElement* pNodeSrc, const TiXmlElement* pNodeDes )
{
	if (pNodeSrc == pNodeDes)return true;
	if (!pNodeSrc || !pNodeDes)return false;
	
	const TiXmlAttribute* pAttribute = pNodeSrc->FirstAttribute();
	while (pAttribute)
	{
		const char* pzDes = pNodeDes->Attribute(pAttribute->Name());
		if (!ToolFrame::IsEqual(pAttribute->Value(),pzDes))
			return false;

		pAttribute = pAttribute->Next();
	}

	return true;
}

bool ToolFrame::IsElementEqual( const TiXmlElement* pNodeSrc, const TiXmlElement* pNodeDes )
{
	if (pNodeSrc == pNodeDes)return true;
	if (!pNodeSrc || !pNodeDes)return false;

	if (GetNodeName(pNodeSrc) != GetNodeName(pNodeDes))return false;
	
	return IsAttributEqual(pNodeSrc,pNodeDes);
}

int ToolFrame::GetElementByAttribute( VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const MapStringString& vValue )
{
	VectorElement vNode;
	if (!GetElement(vNode,pParent,sName))return -1;

	VectorElement::iterator itr;
	foreach(itr,vNode){
		const TiXmlElement* pNode = *itr;
		if (IsAttributEqual(pNode,vValue))
			vElement.push_back(pNode);
	}

	return (int)vElement.size();
}

const TiXmlElement* ToolFrame::GetElementByAttribute( const TiXmlNode* pParent,const std::string& sName,const MapStringString& vValue )
{
	VectorElement vElement;
	if (!GetElementByAttribute(vElement,pParent,sName,vValue))return nullptr;
	if (vElement.empty())return nullptr;

	return ToolFrame::GetFront(vElement);
}

bool ToolFrame::SafeGetAttribute(const TiXmlNode* pNode,const std::string& sName,int& tValue,const int& tDefault){
    return SafeGetAttribute<int,int>(pNode,sName,tValue,tDefault);
}

std::string ToolFrame::ToString( const TiXmlDocument& xDoc )
{
	std::string sContent;
	if (!ToolFrame::ToValue(xDoc,sContent))return "";

	return sContent;
}

bool ToolFrame::ToValue( const TiXmlDocument& xDoc,std::string& sDes )
{
	TiXmlPrinter printer;  
	xDoc.Accept( &printer );

	sDes = 0 == printer.Size() ? "":printer.CStr();
	return true;
}

bool ToolFrame::ToValue( const std::string& sSrc,TiXmlDocument& xDoc )
{
	xDoc.Parse(sSrc.c_str());
	return !xDoc.Error();
}

const TiXmlNode* ToolFrame::GetParentNodeByNodeName( const TiXmlNode* pNode ,const std::string& sNodeName)
{
	while(pNode){
		if (sNodeName == GetNodeName(pNode))//到目前还没想出有什么节点是空名称的 因此不会崩溃
			return pNode;
		
		pNode = pNode->Parent();
	}

	return nullptr;
}

void ToolFrame::Clear( TiXmlDocument& xDoc )
{
	xDoc.Clear();
}

bool ToolFrame::GetSubNode( VectorXmlNode& vNode,const TiXmlNode* pNode,const std::string& sNamePath/*=""*/ )
{
	if (!pNode)return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//找到目标节点
	pNode = ApiXml::FindNode(pNode,vNodeName);
	if (!pNode)return false;

	pNode = pNode->FirstChild();
	while(pNode){
		vNode.push_back(pNode);
		pNode = pNode->NextSibling();
	}

	return true;
}

bool ToolFrame::GetSubNode( VectorElement& vElement,const TiXmlNode* pNode,const std::string& sNamePath/*=""*/ )
{
	if (!pNode)return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//找到目标节点
	pNode = ApiXml::FindNode(pNode,vNodeName);
	if (!pNode)return false;

	const TiXmlElement* pElement = pNode->FirstChildElement();
	while(pElement){
		vElement.push_back(pElement);
		pElement = pElement->NextSiblingElement();
	}

	return true;
}

bool ToolFrame::LoadFile( TiXmlDocument& xDoc,const std::string& sFile )
{
	return xDoc.LoadFile(sFile.c_str());
}

bool ToolFrame::GetAttribute( VectorAttribute& vAttribute,const TiXmlElement* pNode )
{
	if (!pNode)return false;

	const TiXmlAttribute* pAttribute = pNode->FirstAttribute();
	while(pAttribute){
		vAttribute.push_back(pAttribute);

		pAttribute = pAttribute->Next();
	}

	return true;
};

bool ToolFrame::IsHasElement( const TiXmlNode* xParent,const std::string& sNameElement )
{
	return !!GetElement(xParent,sNameElement);
}

bool ToolFrame::IsHasEqualElement( const TiXmlElement* pNodeArg,const VectorElement& vElement )
{
	if (!pNodeArg)return false;

	VectorElement::const_iterator itr;
	foreach(itr,vElement){
		if (IsElementEqual(pNodeArg,*itr))
			return true;
	}
	return false;
}

bool ToolFrame::IsHasEqualElement( const TiXmlElement* pNodeArg,const TiXmlNode* pNodeParent )
{
	if (!pNodeArg || !pNodeParent)return false;

	const TiXmlElement* pChildXml = pNodeParent->FirstChildElement();
	while (pChildXml)
	{
		if (IsElementEqual(pNodeArg,pChildXml))
			return true;

		pChildXml = pChildXml->NextSiblingElement();
	}

	return false;
}

bool ToolFrame::IsHasEqualElement( const TiXmlElement* pNodeArg,const TiXmlNode* pNodeParent,const std::string& sNamePath )
{
	return IsHasEqualElement(pNodeArg,GetElement(pNodeParent,sNamePath));
}

TiXmlNode* ToolFrame::Clone( const TiXmlNode* pNode )
{
	if (!pNode)return nullptr;
	return pNode->Clone();
}

bool ToolFrame::SaveFile( const TiXmlDocument& xDoc,const std::string& sFileName )
{
	return ApiXml::SaveFile(xDoc,sFileName);
}

bool ToolFrame::MergeElement( TiXmlNode* pNodeDes,const TiXmlNode* pNodeSrc,const std::string& sNamePath,bool bCheckEqual /*= false*/ )
{
	std::string sParent = ToolFrame::PickDir(sNamePath);
	TiXmlElement* pXmlDesParent = GetElement(pNodeDes,sParent);
	if (!pXmlDesParent)return false;

	VectorElement vXml;
	if (ToolFrame::GetElement(vXml,pNodeSrc,sNamePath))
		ToolFrame::InsertElement(pXmlDesParent,vXml,bCheckEqual);

	return true;
}
