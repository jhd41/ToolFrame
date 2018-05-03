#pragma once
#include "Macro.h"
#include "ToolStd.h"

#include "MacroXml.h"
#include "ApiXml.h"

//����·����ʽ:"BOOK/AUTHOR[AUTHORID='99/09/01']"
//"BOOK/AUTHOR[AUTHORID='99/09/01' Other]"
//��'/'��Ϊ�ָ�,��[]��Ϊ���Խڵ������
//�� ���������Խڵ��� �� = �� ���� ֻ����/��ȡ������Ե�ֵ��ͬ�� Ԫ��/����
//����������غ��� �Լ� ����������ķ������� �����ж��Ƿ�ֻ����һ�� ��������ƥ���

namespace ToolFrame
{
	//����XML
	bool Parse(TiXmlDocument& xDoc, const char szBuffer[]);
	bool Parse(TiXmlDocument& xDoc, const std::string& sBuffer);
	
	//����XML
	void Clear(TiXmlDocument& xDoc);

	//�����ļ�
	bool LoadFile(TiXmlDocument& xDoc,const std::string& sFile);

	//�����ļ�
	bool SaveFile(const TiXmlDocument& xDoc,const std::string& sFileName);

	//��ȡXML����
	std::string				ToString(const TiXmlDocument& xDoc);
	bool					ToValue(const TiXmlDocument& xDoc,std::string& sDes);
	bool					ToValue(const std::string& sSrc,TiXmlDocument& xDoc);

	//��ȡԪ��
	TiXmlElement*			GetElement(TiXmlNode* xParent,const std::string& sNamePath);						//��ȡ����Ԫ��
	const TiXmlElement*		GetElement(const TiXmlNode* xParent,const std::string& sNamePath);
	bool					GetElement(VectorElement& vElement,TiXmlNode* xParent,const std::string& sNamePath);//��ȡԪ�ؼ���
	bool					GetElement(VectorElement& vElement,const TiXmlNode* xParent,const std::string& sNamePath);

	//ǿ�ƻ��ĳԪ�أ����û���򴴽�
	TiXmlElement*			GetElementForce(TiXmlNode* xParent,const std::string& sNamePath);

	//����ĳԪ��
	TiXmlElement*			InsertElement(TiXmlNode* xParent,const std::string& sNameElement);
	TiXmlElement*			InsertElement(TiXmlNode* xParent,const TiXmlElement* pXmlClone	,bool bCheckEqual=false);
	bool					InsertElement(TiXmlNode* xParent,const VectorElement& vXmlClone	,bool bCheckEqual=false);
	TiXmlNode*				InsertNode(TiXmlNode* xParent,const TiXmlNode* pXmlClone);

	//����
	bool					MergeElement(TiXmlNode* pNodeDes,const TiXmlNode* pNodeSrc,const std::string& sNamePath,bool bCheckEqual = false);

	//�ж��Ƿ�����ӽڵ�
	bool					IsHasChild(const TiXmlNode* pElement,const std::string& sName="");

	//��ȡ�ӽڵ�
	bool				GetSubNode(VectorXmlNode& vNode,const TiXmlNode* pNode,const std::string& sNamePath="");
	bool				GetSubNode(VectorElement& vElement,const TiXmlNode* pNode,const std::string& sNamePath="");


	//����ĳ���Ե�ֵ�ҵ�ĳԪ��
	template<typename TValue>
	const TiXmlElement*	GetElementByAttribute(const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute,const TValue& tValue);
	template<typename TValue1,typename TValue2>
	const TiXmlElement*	GetElementByAttribute(const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2);
	template<typename TValue1,typename TValue2,typename TValue3>
	const TiXmlElement*	GetElementByAttribute(const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2,const std::string& sAttribute3,const TValue1& tValue3);
	const TiXmlElement*	GetElementByAttribute(const TiXmlNode* pParent,const std::string& sName,const MapStringString& vValue);

	//����ĳ���Ե�ֵ�ҵ�ĳԪ�� ���ض��,�����ҵ��ĸ���,����-1Ϊ����
	template<typename TValue>
	int		GetElementByAttribute(VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute,const TValue& tValue);
	template<typename TValue1,typename TValue2>
	int		GetElementByAttribute(VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2);
	template<typename TValue1,typename TValue2,typename TValue3>
	int		GetElementByAttribute(VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2,const std::string& sAttribute3,const TValue1& tValue3);
	int		GetElementByAttribute(VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const MapStringString& vValue);

	//�ж�Ԫ������ֵ�Ƿ����
	bool	IsAttributEqual(const TiXmlElement* pNode,		const MapStringString& vValue);
	bool	IsAttributEqual(const TiXmlElement* pNodeSrc,	const TiXmlElement* pNodeDes);

	//�ж�Ԫ���Ƿ����
	bool	IsElementEqual(const TiXmlElement* pNodeSrc,	const TiXmlElement* pNodeDes);

	//�Ƿ������ͬ��Element
	bool	IsHasEqualElement(const TiXmlElement* pNodeArg,const VectorElement& vElement);
	bool	IsHasEqualElement(const TiXmlElement* pNodeArg,const TiXmlNode* pNodeParent);
	bool	IsHasEqualElement(const TiXmlElement* pNodeArg,const TiXmlNode* pNodeParent,const std::string& sNamePath);

	//��ȡ����
	template<typename T>
	bool	GetAttribute(const TiXmlNode* pNode,const std::string& sNamePath,T& tValue);
	template<typename T1,typename T2>
	bool	GetAttribute(const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2);	
	template<typename T1,typename T2,typename T3>
	bool	GetAttribute(const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2,T3& tValue3);	
	template<typename T1,typename T2,typename T3,typename T4>
	bool	GetAttribute(const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2,T3& tValue3,T4& tValue4);
	template<typename T1,typename T2,typename T3,typename T4,typename T5>
	bool	GetAttribute(const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2,T3& tValue3,T4& tValue4,T5& tValue5);	
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	bool	GetAttribute(const TiXmlNode* pNode, const std::string& sNamePath, T1& tValue1, T2& tValue2, T3& tValue3, T4& tValue4, T5& tValue5, T6& tValue6);
	
	bool	SafeGetAttribute(const TiXmlNode* pNode,const std::string& sNamePath,int& tValue,const int& tDefault);
	template<typename T,typename K>
	bool	SafeGetAttribute(const TiXmlNode* pNode,const std::string& sNamePath,T& tValue,const K& tDefault);

	template<typename T>
	bool	GetAttribute(T& tValue,const TiXmlNode* pNode,const VectorString& vPath);
	template<typename T>
	bool	GetAttribute(T& tValue,const TiXmlNode* pNode,const std::string& sPath);
	template<typename T>
	bool	GetAttribute(T& tValue,const TiXmlNode* pNode,const std::string& sPath1,const std::string& sPath2);
	template<typename T>
	bool	GetAttribute(T& tValue,const TiXmlNode* pNode,const std::string& sPath1,const std::string& sPath2,const std::string& sPath3,const std::string& sPath4);


	// VectorAttribute GetAttribute
	bool	GetAttribute(VectorAttribute& vAttribute,const TiXmlElement* pNode);

//��������ֵ
	template<typename T>
	bool	SetAttribute( TiXmlNode* pNode,const std::string& sNamePath,const T& tValue );
	template<typename T1,typename T2>
	bool	SetAttribute( TiXmlNode* pNode,const std::string& sNamePath,const T1& tValue1,const T2& tValue2 );
	template<typename T1,typename T2,typename T3>
	bool	SetAttribute( TiXmlNode* pNode,const std::string& sNamePath,const T1& tValue1,const T2& tValue2,const T3& tValue3 );
	
	//��ȡ�ı�
	template<typename T>
	bool		GetText(const TiXmlElement* pXml,T& tValue,const T& tDefault);
	bool		GetText(const TiXmlElement* pXml,std::string& sValue,const std::string& sDefault);
	TiXmlText*	GetText(TiXmlElement* pXml);

	//�����ı�
	template<typename T>
	bool		SetText(TiXmlElement* pXml,const T& tValue,bool bCData=false);

	//��ȡ�ӽڵ���ı�ֵ
	const char* GetSubText(const TiXmlElement* pXml,const std::string& sName);
	template<typename T>
	bool		GetSubText(const TiXmlElement* pXml,const std::string& sName,T& tValue,const T& tDefault);
	bool		GetSubText(const TiXmlElement* pXml,const std::string& sName,std::string& tValue,const std::string& tDefault);

	//�����ӽڵ���ı�ֵ
	template<typename T>
	bool		SetSubText(TiXmlElement* pXmlParent,const std::string& sName,const T& tValue,bool bCData=false);

	//�Ƿ���CDATA
	bool IsCData(const TiXmlText* pXml);

	//�Ƿ����ı�
	bool IsHasText(const TiXmlElement* pXml);

	//�ж��Ƿ����
	bool IsHasElement(const TiXmlNode* xParent,const std::string& sNameElement);

	//�ж��Ƿ��Ǹ��ڵ�
	bool IsRoot(const TiXmlNode* pXml);

	//����
	bool	CopyAttribute(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sName);
	bool	CopyAttribute(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sNameSrc,const std::string& sNameDes);
	void	CopyText(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sName);
	void	CopyText(const TiXmlElement* pSrc,TiXmlElement* pDes,const std::string& sNameSrc,const std::string& sNameDes);

	//��ȡ�ڵ�����
	std::string GetNodeName(const TiXmlNode* pXml);

	//�Ƴ��ı�
	void	RemoveText(TiXmlElement* pXml);

	//ת��
	TiXmlElement*		ToElement(TiXmlNode* xNode);
	const TiXmlElement*	ToElement(const TiXmlNode* xNode);

	//����˳��ȡ����ֵ���ȡ��������false
	template<typename T>
	bool	GetValueByAttribute(T& tValue,const TiXmlNode* pNode,const std::string& sNameAttribute1);
	template<typename T>
	bool	GetValueByAttribute(T& tValue,const TiXmlNode* pNode,const std::string& sNameAttribute1,const std::string& sNameAttribute2);
	template<typename T>
	bool	GetValueByAttribute(T& tValue,const TiXmlNode* pNode,const std::string& sNameAttribute1,const std::string& sNameAttribute2,const std::string& sNameAttribute3);
	template<typename T>
	bool	GetValueByAttribute(T& tValue,const TiXmlNode* pNode,const VectorString& vAttibuteName);

	//����Ѱ������Ľڵ�
	const TiXmlNode* GetParentNodeByNodeName( const TiXmlNode* pNode ,const std::string& sNodeName);

	//��¡
	TiXmlNode* Clone(const TiXmlNode* pNode);//�ڲ���New����
};

template<typename T>
bool ToolFrame::GetAttribute( T& tValue,const TiXmlNode* pNode,const VectorString& vPath )
{
	if (!pNode)return false;
	if (vPath.empty())return false;
	
	VectorString::const_iterator itr;
	foreach(itr,vPath){
		const std::string& sPath = *itr;
		if (sPath.empty())return false;

		if(GetAttribute(pNode,sPath,tValue))
			return true;
	}

	return false;
}

template<typename T>
bool ToolFrame::GetAttribute( T& tValue,const TiXmlNode* pNode,const std::string& sPath )
{
	if (!pNode)return false;

	VectorString vPath;
	vPath.push_back(sPath);
	return GetAttribute(tValue,pNode,vPath);
}

template<typename T>
bool ToolFrame::GetAttribute( T& tValue,const TiXmlNode* pNode,const std::string& sPath1,const std::string& sPath2 )
{
	if (!pNode)return false;

	VectorString vPath;
	vPath.push_back(sPath1);
	vPath.push_back(sPath2);
	return GetAttribute(tValue,pNode,vPath);
}

template<typename T>
bool ToolFrame::GetAttribute( T& tValue,const TiXmlNode* pNode,const std::string& sPath1,const std::string& sPath2,const std::string& sPath3,const std::string& sPath4 )
{
	if (!pNode)return false;

	VectorString vPath;
	vPath.push_back(sPath1);
	vPath.push_back(sPath2);
	vPath.push_back(sPath3);
	return GetAttribute(tValue,pNode,vPath);
}

template<typename T,typename K>
bool ToolFrame::SafeGetAttribute( const TiXmlNode* pNode,const std::string& sNamePath,T& tValue,const K& tDefault )
{
	if (!pNode)return false;

	if (!GetAttribute(pNode,sNamePath,tValue))
	{
		tValue = tDefault;
		return false;
	}
	return true;
}

template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
bool ToolFrame::GetAttribute(const TiXmlNode* pNode, const std::string& sNamePath, T1& tValue1, T2& tValue2, T3& tValue3, T4& tValue4, T5& tValue5, T6& tValue6)
{
	if (!pNode)return false;
	if (!ApiXml::IsPathName(sNamePath))return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName, vAttribute, vAttributeName, sNamePath))return false;

	//��鴫����������Ƿ�Ϸ�
	if (vAttributeName.size() < 6)return false;

	//�ҵ�Ŀ��ڵ�
	const TiXmlElement*  pElement = ApiXml::FindElement(pNode, vNodeName, vAttribute);
	if (!pElement)return false;
	return ToValue(pElement->Attribute(vAttributeName[0].c_str()), tValue1)
		&& ToValue(pElement->Attribute(vAttributeName[1].c_str()), tValue2)
		&& ToValue(pElement->Attribute(vAttributeName[2].c_str()), tValue3)
		&& ToValue(pElement->Attribute(vAttributeName[3].c_str()), tValue4)
		&& ToValue(pElement->Attribute(vAttributeName[4].c_str()), tValue5)
		&& ToValue(pElement->Attribute(vAttributeName[5].c_str()), tValue6);
}

template<typename T1,typename T2,typename T3,typename T4,typename T5>
bool ToolFrame::GetAttribute( const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2,T3& tValue3,T4& tValue4,T5& tValue5 )
{
	if (!pNode)return false;
	if (!ApiXml::IsPathName(sNamePath))return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//��鴫����������Ƿ�Ϸ�
	if(vAttributeName.size() < 5)return false;

	//�ҵ�Ŀ��ڵ�
	const TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
	if (!pElement)return false;
	return ToValue(pElement->Attribute(vAttributeName[0].c_str()),tValue1) 
		&& ToValue(pElement->Attribute(vAttributeName[1].c_str()),tValue2)
		&& ToValue(pElement->Attribute(vAttributeName[2].c_str()),tValue3)
		&& ToValue(pElement->Attribute(vAttributeName[3].c_str()),tValue4)
		&& ToValue(pElement->Attribute(vAttributeName[4].c_str()),tValue5);
}

template<typename T1,typename T2,typename T3,typename T4>
bool ToolFrame::GetAttribute( const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2,T3& tValue3,T4& tValue4 )
{
	if (!pNode)return false;
	if (!ApiXml::IsPathName(sNamePath))return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//��鴫����������Ƿ�Ϸ�
	if(vAttributeName.size() < 4)return false;

	//�ҵ�Ŀ��ڵ�
	const TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
	if (!pElement)return false;
	return ToValue(pElement->Attribute(vAttributeName[0].c_str()),tValue1) 
		&& ToValue(pElement->Attribute(vAttributeName[1].c_str()),tValue2)
		&& ToValue(pElement->Attribute(vAttributeName[2].c_str()),tValue3)
		&& ToValue(pElement->Attribute(vAttributeName[3].c_str()),tValue4);
}

template<typename T1,typename T2,typename T3>
bool ToolFrame::GetAttribute( const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2,T3& tValue3 )
{
	if (!pNode)return false;
	if (!ApiXml::IsPathName(sNamePath))return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//��鴫����������Ƿ�Ϸ�
	if(vAttributeName.size() < 3)return false;

	//�ҵ�Ŀ��ڵ�
	const TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
	if (!pElement)return false;
	return ToValue(pElement->Attribute(vAttributeName[0].c_str()),tValue1) 
		&& ToValue(pElement->Attribute(vAttributeName[1].c_str()),tValue2)
		&& ToValue(pElement->Attribute(vAttributeName[2].c_str()),tValue3);
}

template<typename T1,typename T2>
bool ToolFrame::GetAttribute( const TiXmlNode* pNode,const std::string& sNamePath,T1& tValue1,T2& tValue2 )
{
	if (!pNode)return false;
	if (!ApiXml::IsPathName(sNamePath))return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//��鴫����������Ƿ�Ϸ�
	if(vAttributeName.size() < 2)return false;

	//�ҵ�Ŀ��ڵ�
	const TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
	if (!pElement)return false;
	return ToValue(pElement->Attribute(vAttributeName[0].c_str()),tValue1) 
		&& ToValue(pElement->Attribute(vAttributeName[1].c_str()),tValue2);
}

template<typename T>
bool ToolFrame::GetAttribute( const TiXmlNode* pNode,const std::string& sNamePath,T& tValue )
{
	if (!pNode)return false;

	if (ApiXml::IsPathName(sNamePath))
	{
		VectorString vNodeName;
		MapStringString vAttribute;
		VectorString vAttributeName;
		if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

		//��鴫����������Ƿ�Ϸ�
		if(vAttributeName.size() < 1)return false;

		//�ҵ�Ŀ��ڵ�
		const TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
		if (!pElement)return false;
		return ToValue(pElement->Attribute(vAttributeName[0].c_str()),tValue);
	}else{
		const TiXmlElement*  pElement = pNode->ToElement();
		if (!pElement)return false;

		const char* sz = pElement->Attribute(sNamePath.c_str());
		if (!sz)return false;

		return ToValue(sz,tValue);
	}
	return false;
}

template<typename T1,typename T2>
bool ToolFrame::SetAttribute( TiXmlNode* pNode,const std::string& sNamePath,const T1& tValue1,const T2& tValue2 )
{
	if (!pNode)return false;
	if (!ApiXml::IsPathName(sNamePath))return false;
	
	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//��鴫����������Ƿ�Ϸ�
	if(vAttributeName.size() < 2)return false;

	//�ҵ�Ŀ��ڵ�
	TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
	if (!pElement)return false;

	ApiXml::SetAttribute(pElement,vAttributeName[0],ToolFrame::ToString(tValue1));
	ApiXml::SetAttribute(pElement,vAttributeName[1],ToolFrame::ToString(tValue2));

	return true;
}

template<typename T1,typename T2,typename T3>
bool ToolFrame::SetAttribute( TiXmlNode* pNode,const std::string& sNamePath,const T1& tValue1,const T2& tValue2,const T3& tValue3 )
{
	if (!pNode)return false;
	if (!ApiXml::IsPathName(sNamePath))return false;

	VectorString vNodeName;
	MapStringString vAttribute;
	VectorString vAttributeName;
	if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

	//��鴫����������Ƿ�Ϸ�
	if(vAttributeName.size() < 3)return false;

	//�ҵ�Ŀ��ڵ�
	TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
	if (!pElement)return false;

	ApiXml::SetAttribute(pElement,vAttributeName[0],ToolFrame::ToString(tValue1));
	ApiXml::SetAttribute(pElement,vAttributeName[1],ToolFrame::ToString(tValue2));
	ApiXml::SetAttribute(pElement,vAttributeName[2],ToolFrame::ToString(tValue3));

	return true;
}

template<typename T>
bool ToolFrame::SetAttribute(TiXmlNode* pNode,const std::string& sNamePath,const T& tValue )
{
	if (!pNode)return false;

	if (ApiXml::IsPathName(sNamePath)){
		VectorString vNodeName;
		MapStringString vAttribute;
		VectorString vAttributeName;
		if (!ApiXml::SplitName(vNodeName,vAttribute,vAttributeName,sNamePath))return false;

		//��鴫����������Ƿ�Ϸ�
		if(vAttributeName.size() < 1)return false;

		//�ҵ�Ŀ��ڵ�
		TiXmlElement*  pElement = ApiXml::FindElement(pNode,vNodeName,vAttribute);
		if (!pElement)return false;

		ApiXml::SetAttribute(pElement,vAttributeName[0],ToolFrame::ToString(tValue));
		
		return true;
	}else{
		TiXmlElement*  pElement = pNode->ToElement();
		if (!pElement)return false;

		ApiXml::SetAttribute(pElement,sNamePath,ToolFrame::ToString(tValue));
		return true;
	}

	return false;
}


template<typename T>
bool ToolFrame::GetValueByAttribute( T& tValue,const TiXmlNode* pNode,const std::string& sNameAttribute1,const std::string& sNameAttribute2,const std::string& sNameAttribute3 )
{
	VectorString vAttibuteName;
	vAttibuteName.push_back(sNameAttribute1);
	vAttibuteName.push_back(sNameAttribute2);
	vAttibuteName.push_back(sNameAttribute3);
	return GetValueByAttribute(tValue,pNode,vAttibuteName);
}

template<typename T>
bool ToolFrame::GetValueByAttribute( T& tValue,const TiXmlNode* pNode,const std::string& sNameAttribute1,const std::string& sNameAttribute2 )
{
	VectorString vAttibuteName;
	vAttibuteName.push_back(sNameAttribute1);
	vAttibuteName.push_back(sNameAttribute2);
	return GetValueByAttribute(tValue,pNode,vAttibuteName);
}

template<typename T>
bool ToolFrame::GetValueByAttribute( T& tValue,const TiXmlNode* pNode,const std::string& sNameAttribute1 )
{
	VectorString vAttibuteName;
	vAttibuteName.push_back(sNameAttribute1);
	return GetValueByAttribute(tValue,pNode,vAttibuteName);
}

template<typename T>
bool ToolFrame::GetValueByAttribute( T& tValue,const TiXmlNode* pNode,const VectorString& vAttibuteName )
{
	if (!pNode)return false;
	if (vAttibuteName.empty())return false;

	VectorString::const_iterator itr;
	foreach(itr,vAttibuteName){
		const std::string& sAttibuteName = *itr;
		if (GetAttribute(pNode,sAttibuteName,tValue))
			return true;
	}
	return false;
}

template<typename TValue1,typename TValue2,typename TValue3>
const TiXmlElement* ToolFrame::GetElementByAttribute( const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2,const std::string& sAttribute3,const TValue1& tValue3 )
{
	MapStringString vValue;
	if (!ToolFrame::Insert(vValue,sAttribute1,tValue1))return nullptr;
	if (!ToolFrame::Insert(vValue,sAttribute2,tValue2))return nullptr;
	if (!ToolFrame::Insert(vValue,sAttribute3,tValue3))return nullptr;
	return GetElementByAttribute(pParent,sName,vValue);
}

template<typename TValue1,typename TValue2>
const TiXmlElement* ToolFrame::GetElementByAttribute( const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2 )
{
	MapStringString vValue;
	if (!ToolFrame::Insert(vValue,sAttribute1,tValue1))return nullptr;
	if (!ToolFrame::Insert(vValue,sAttribute2,tValue2))return nullptr;
	return GetElementByAttribute(pParent,sName,vValue);
}

template<typename TValue>
const TiXmlElement* ToolFrame::GetElementByAttribute( const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute,const TValue& tValue )
{
	MapStringString vValue;
	if (!ToolFrame::Insert(vValue,sAttribute,tValue))return nullptr;
	return GetElementByAttribute(pParent,sName,vValue);
}

template<typename TValue1,typename TValue2,typename TValue3>
int ToolFrame::GetElementByAttribute( VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2,const std::string& sAttribute3,const TValue1& tValue3 )
{
	MapStringString vValue;
	if (!ToolFrame::Insert(vValue,sAttribute1,tValue1))return -1;
	if (!ToolFrame::Insert(vValue,sAttribute2,tValue2))return -1;
	if (!ToolFrame::Insert(vValue,sAttribute3,tValue3))return -1;
	return GetElementByAttribute(vElement,pParent,sName,vValue);
}

template<typename TValue1,typename TValue2>
int ToolFrame::GetElementByAttribute( VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute1,const TValue1& tValue1,const std::string& sAttribute2,const TValue1& tValue2 )
{
	MapStringString vValue;
	if (!ToolFrame::Insert(vValue,sAttribute1,tValue1))return -1;
	if (!ToolFrame::Insert(vValue,sAttribute2,tValue2))return -1;
	return GetElementByAttribute(vElement,pParent,sName,vValue);
}

template<typename TValue>
int ToolFrame::GetElementByAttribute( VectorElement& vElement,const TiXmlNode* pParent,const std::string& sName,const std::string& sAttribute,const TValue& tValue )
{
	MapStringString vValue;
	if (!ToolFrame::Insert(vValue,sAttribute,tValue))return -1;
	return GetElementByAttribute(vElement,pParent,sName,vValue);
}

template<typename T>
bool ToolFrame::GetSubText( const TiXmlElement* pXml,const std::string& sName,T& tValue,const T& tDefault )
{
	const std::string sText = ToolFrame::GetSubText(pXml,sName);
	if (sText.empty())
	{
		tValue = tDefault;
		return false;
	}

	return ToolFrame::ToValue(sText,tValue);
}

template<typename T>
bool ToolFrame::SetSubText(TiXmlElement* pXmlParent,const std::string& sName,const T& tValue,bool bCData/*=false*/ )
{
	TiXmlElement* pXml = ToolFrame::GetElementForce(pXmlParent,sName);
	if (!pXml)return false;
	return SetText(pXml,tValue,bCData);
}

template<typename T>
bool ToolFrame::GetText( const TiXmlElement* pXml,T& tValue,const T& tDefault )
{
	const char* szText = pXml->GetText();
	if (!szText)
	{
		tValue = tDefault;
		return false;
	}
	return ToolFrame::ToValue(szText,tValue);
}

template<typename T>
bool ToolFrame::SetText( TiXmlElement* pXml,const T& tValue,bool bCData/*=false*/ )
{
	if (IsHasText(pXml))
		RemoveText(pXml);
	
	TiXmlText xText(ToolFrame::ToString(tValue).c_str());
	xText.SetCDATA(bCData);

	pXml->InsertEndChild(xText);
	return true;
}
