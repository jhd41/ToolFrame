#include "ApiXml.h"
#include "ToolStd.h"

bool ApiXml::IsPathName( const std::string& sName )
{
	return ToolFrame::IsEndWith(sName,"]"); 
}

bool ApiXml::SplitName( std::string& sNodeName,std::string& sAttribute,const std::string& sPath )
{
	if (sPath.empty())return true;

	if (!ToolFrame::IsEndWith(sPath,"]"))
	{
		sNodeName = sPath;
		return true;
	}

	SSIZE_TYPE nIndex =	ToolFrame::FindFrist(sPath,"[");
	if (std::string::npos == nIndex)return false;

	sNodeName =	sPath.substr(0,nIndex-0);
	sAttribute=	sPath.substr(nIndex+1,sPath.length() - 1 - (nIndex+1));
	return true;
}

bool ApiXml::SplitName(  VectorString& vNodeName,MapStringString& vAttribute,VectorString& vAttributeName,const std::string& sPath )
{
	//"BOOK/AUTHOR[AUTHORID='99/09/01' Other]"

	std::string sNodeString,sAttributeString;
	if (!SplitName(sNodeString,sAttributeString,sPath))return false;

	//因为解析属性比较复杂,因此放在解析节点名称前面
	//解析属性
	if (!SplitAttributeString(vAttribute,vAttributeName,sAttributeString))return false;

	//解析NodeName
	if (!SplitNodeString(vNodeName,sNodeString))return false;

	return true;
}

bool ApiXml::SplitNodeString( VectorString& vNodeName,const std::string& sNodeString )
{
	if (sNodeString.empty())return true;

	ToolFrame::SplitString(vNodeName,sNodeString,"/");
	ToolFrame::TrimString(vNodeName);
	return true;
}

bool ApiXml::SplitAttributeString( MapStringString& vAttribute,VectorString& vAttributeName,const std::string& sAttributeString )
{
	if (sAttributeString.empty())return true;

	//继续拆解属性表达式
	VectorString vAttributeExp;
	ToolFrame::SplitString(vAttributeExp,sAttributeString," ");
	ToolFrame::RemoveString(vAttributeExp,"");

	VectorString::const_iterator itr;
	foreach(itr,vAttributeExp){
		const std::string& sExp = *itr;
		if (sExp.empty())continue;

		VectorString vValue;
		ToolFrame::SplitString(vValue,sExp,"=");

		switch (vValue.size())
		{
		case 1:
			{
				const std::string& sAttribute = vValue[0];
				if (sAttribute.empty())return false;

				vAttributeName.push_back(sAttribute);
			}
			break;
		case 2:
			{
				const std::string& sName = vValue[0];

				if (sName.empty())return false;

				//属性必须用引号引起来
				std::string sValue;
				if (!ToolFrame::GetMidString(sValue,vValue[1],"\"","\"",false))
					if (!ToolFrame::GetMidString(sValue,vValue[1],"'","'",false))
						return false;

				if (!ToolFrame::Insert(vAttribute,sName,sValue))return false;
			}
			break;
		default:
			return false;
		}
	}

	return true;
}

TiXmlNode* ApiXml::FindNode( TiXmlNode* pNode,const VectorString& vNodeName )
{
	if (!pNode)return nullptr;
	if (vNodeName.empty())return pNode;

	VectorString::const_iterator itr;
	foreach(itr,vNodeName){
		if (!pNode)return nullptr;

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
			pNode = pNode->Parent();
			continue;
		}

		pNode = pNode->FirstChild(sNodeName.c_str());
	}
	return pNode;
}

const TiXmlNode* ApiXml::FindNode( const TiXmlNode* pNode,const VectorString& vNodeName )
{
	return FindNode(ToolFrame::ConstCast(pNode),vNodeName);
}

TiXmlElement* ApiXml::FindElement(  TiXmlNode* pNode,const VectorString& vNodeName,const MapStringString& vAttribute )
{
	TiXmlElement* pElement = FindElement(pNode,vNodeName);
	if (!pElement)return nullptr;

	//如果当前属性相等
	if (IsAttributeEqual(pElement,vAttribute))
		return pElement;

	//如果是查找合适的子节点
	if (!vNodeName.empty())
		return FindElementSibling(pElement, vAttribute);
	
	return nullptr;
}

const TiXmlElement* ApiXml::FindElement( const TiXmlNode* pNode,const VectorString& vNodeName,const MapStringString& vAttribute )
{
	return FindElement((TiXmlNode*)pNode,vNodeName,vAttribute);
}

TiXmlElement* ApiXml::FindElement( TiXmlNode* pNode,const VectorString& vNodeName )
{
	if (!pNode)return nullptr;
	if (vNodeName.empty())return pNode->ToElement();

	VectorString::const_iterator itr;
	foreach(itr,vNodeName){
		if (!pNode)return nullptr;

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
			pNode = pNode->Parent();
			continue;
		}

		pNode = pNode->FirstChildElement(sNodeName.c_str());
	}
	if (!pNode)return nullptr;
	return pNode->ToElement();
}

const TiXmlElement* ApiXml::FindElementSibling( const TiXmlElement* pElement,const MapStringString& vAttribute )
{
	return FindElementSibling((TiXmlElement*)pElement,vAttribute);
}

TiXmlElement* ApiXml::FindElementSibling( TiXmlElement* pElement,const MapStringString& vAttribute )
{
	if (!pElement)return nullptr;

	//查找与属性值相匹配的节点
	const char * szNodeName = GetNodeName(pElement);

	pElement = pElement->NextSiblingElement(szNodeName);
	while(pElement){
		if (ApiXml::IsAttributeEqual(pElement,vAttribute))
			return pElement;

		pElement = pElement->NextSiblingElement(szNodeName);
	}
	return nullptr;
}

TiXmlElement* ApiXml::FindChildElement( TiXmlNode* pNode,const std::string& sName,const MapStringString& vAttribute )
{
	if (!pNode)return nullptr;

	TiXmlElement* pElement  = pNode->FirstChildElement(sName.c_str());
	while(pElement){
		if (IsAttributeEqual(pElement,vAttribute))
			return pElement;

		pElement = pElement->NextSiblingElement(sName.c_str());
	}

	return nullptr;
}

bool ApiXml::IsAttributeEqual( const TiXmlElement* pSrc,const std::string& sAttributeName,const std::string& sAttributeValue )
{
	const char* sz = pSrc->Attribute(sAttributeName.c_str());
	if (!sz)return false;

	return sAttributeValue == sz;
}

bool ApiXml::IsAttributeEqual( const TiXmlElement* pSrc,const MapStringString& vAttribute )
{
	if (!pSrc)return false;
	if (vAttribute.empty())return true;

	MapStringString::const_iterator itr;
	foreach(itr,vAttribute){
		if (!IsAttributeEqual(pSrc,itr->first,itr->second))
			return false;
	}

	return true;
}

bool ApiXml::LoadFile( TiXmlDocument& xDoc, const std::string& sFileName )
{
	return xDoc.LoadFile(sFileName.c_str());
}

bool ApiXml::LoadFile( TiXmlDocument& xDoc, const char szFileName[] )
{
	return xDoc.LoadFile(szFileName);
}

bool ApiXml::SaveFile(const TiXmlDocument& xDoc, const std::string& sFileName )
{
	return xDoc.SaveFile(sFileName.c_str());
}

bool ApiXml::SaveFile(const TiXmlDocument& xDoc,const char szFileName[] )
{
	return xDoc.SaveFile(szFileName);
}

const char* ApiXml::GetNodeName(const TiXmlNode* pXml )
{
	return pXml->Value();
}

void ApiXml::SetAttribute( TiXmlElement* pElement,const std::string& sKey,const std::string& sValue )
{
	pElement->SetAttribute(sKey.c_str(),sValue.c_str());
}
