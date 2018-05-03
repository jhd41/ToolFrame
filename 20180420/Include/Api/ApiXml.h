#pragma once

#include "MacroXml.h"

class TOOLFRAME_DLL ApiXml
{
public:
	static bool	IsPathName(const std::string& sName);

	static bool SplitName(std::string& sNodeName,std::string& sAttribute,const std::string& sPath);
	static bool SplitName( VectorString& vNodeName,MapStringString& vAttribute,VectorString& vAttributeName,const std::string& sPath );
	static bool SplitNodeString(VectorString& vNodeName,const std::string& sNodeString);
	static bool SplitAttributeString( MapStringString& vAttribute,VectorString& vAttributeName,const std::string& sAttributeString );

	static TiXmlNode*	 FindNode(TiXmlNode* pNode,const VectorString& vNodeName); 
	static TiXmlElement* FindElement(TiXmlNode* pNode,const VectorString& vNodeName); 
	static TiXmlElement* FindElement(TiXmlNode* pNode,const VectorString& vNodeName,const MapStringString& vAttribute);
	static TiXmlElement* FindElementSibling(TiXmlElement* pElement,const MapStringString& vAttribute); 
	static TiXmlElement* FindChildElement( TiXmlNode* pNode,const std::string& sName,const MapStringString& vAttribute );

	static const TiXmlNode*		FindNode(const TiXmlNode* pNode,const VectorString& vNodeName);
	static const TiXmlElement*	FindElement(const TiXmlNode* pNode,const VectorString& vNodeName,const MapStringString& vAttribute);
	static const TiXmlElement*	FindElementSibling(const TiXmlElement* pElement,const MapStringString& vAttribute); 

	//�жϵ�ǰ�Ľڵ������ֵ�Ƿ����Ҫ��
	static bool	IsAttributeEqual(const TiXmlElement* pSrc,const std::string& sAttributeName,const std::string& sAttributeValue);
	static bool	IsAttributeEqual(const TiXmlElement* pSrc,const MapStringString& vAttribute);

	//����XML�ļ�
	static bool LoadFile(TiXmlDocument& xDoc, const std::string& sFileName);
	static bool LoadFile(TiXmlDocument& xDoc, const char szFileName[]);

	//д��XML�ļ�
	static bool SaveFile(const TiXmlDocument& xDoc, const std::string& sFileName);
	static bool SaveFile(const TiXmlDocument& xDoc, const char szFileName[]);
	
	static const char* GetNodeName(const TiXmlNode* pXml );

	static void SetAttribute(TiXmlElement* pElement,const std::string& sKey,const std::string& sValue);
};

