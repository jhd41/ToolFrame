#pragma once

//�����ߺ�����ҪΧ��HttpЭ�����
#include "Macro.h"

namespace ToolFrame
{
	//HTTP
	std::string HttpRequestGet(const std::string& sUrl);								//��ҳ����(Get)
	std::string HttpRequestGet(const std::string& sUrl, const MapStringString& vArg);	//��ҳ����(Get)						//��ҳ����(Get)
	std::string HttpRequestPost(const std::string& sUrl);								//��ҳ����(Post)
	std::string HttpRequestPost(const std::string& sUrl, const MapStringString& vArg);	//��ҳ����(Post)
	std::string HttpResponce(const std::string& sContent);								//��ҳӦ��
	std::string GetHttpContent(const std::string& sSrc, bool bCheckLength = false);		//��ȡHttp����
	bool		GetHttpArg(MapStringString& vArg, const std::string& sSrc);				//��ȡHttp����
	std::string HttpParamsToString(const MapStringString& vValue);						//ƴ��Get��ʽ��Http����
	bool		StringToHttpParams(MapStringString& vValue,const std::string& sSrc);	//�ַ�����������ת��
	bool		IsUrlNetAddress(const std::string& sUrl);								//��ַ�Ƿ��������ַ
	bool		IsUrlFileAddress(const std::string& sUrl);								//��ַ�Ƿ��������ַ
	bool		IsFullUrl(const std::string& sUrl);										//�ж��Ƿ�Ϊ����URL
	std::string GetFullUrl(const std::string& sUrl);									//��ȡ����URL
	std::string TrimUrl(const std::string& sUrl);										//������URL
	
	std::string UrlEncode(const std::string& str);										//�ַ�����URL��ʽת��
	std::string UrlDecode(const std::string& str);										//URL���ַ�����ʽת��

	bool		UrlEncode(MapStringString& vValue);										//�ַ�����URL��ʽת��
	bool		UrlDecode(MapStringString& vValue);										//URL���ַ�����ʽת��

	bool		UrlEncode(MapStringString& vValue,const MapStringString& vSrc);			//�ַ�����URL��ʽת��
	bool		UrlDecode(MapStringString& vValue, const MapStringString& vSrc);		//URL���ַ�����ʽת��

	char		UrlChar2Int(char cChar);//�ڲ����� ��Ҫ����
	char		UrlStr2Bin(char *czStr);//�ڲ����� ��Ҫ����
};

