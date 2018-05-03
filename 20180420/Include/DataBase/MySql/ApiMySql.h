#pragma once

#include "Macro.h"
#include "MacroDefineBoost.h"
#include "MacroDefineEx.h"
#include "DateTime.h"
#include "Date.h"

#ifdef MACRO_LIB_MY_SQL

class ApiMySql
{
public:
	static CMutexRecursive& GetMutex();//����init connectʱ ����ʹ�ô�������

	//���ɲ��� ��� INSERT INTO table_name (��1, ��2,...) VALUES (ֵ1, ֵ2,....)
	static std::string	MakeSqlInsert(const std::string& sTable,const MapStringString& vValue);//����SQL��� insert
	static std::string	MakeSqlInsert(const std::string& sTable,const VectorString& vValue);//����SQL��� insert

	//���ɲ��� ��� INSERT ignore INTO table_name (��1, ��2,...) VALUES (ֵ1, ֵ2,....)
	static std::string	MakeSqlInsertIgnore(const std::string& sTable,const MapStringString& vValue);//����SQL��� insert
	static std::string	MakeSqlInsertIgnore(const std::string& sTable,const VectorString& vValue);//����SQL��� insert

	//���ɲ�ѯ��� //select * from Account where Account='1111' and RegistTime = '2011-09-03 14:44:11'
	static std::string	MakeSqlQuery(const std::string& sTable,const std::string& sSel);
	static std::string	MakeSqlQuery(const std::string& sTable,const std::string& sSel,const std::string& sWhere);
	static std::string	MakeSqlQuery(const std::string& sTable,const std::string& sSel,const MapStringString& vWhere);
	static std::string	MakeSqlQuery(const std::string& sTable,const std::string& sSel,const std::string& sWhere,		const std::string& sOrder);
	static std::string	MakeSqlQuery(const std::string& sTable,const std::string& sSel,const MapStringString& vWhere,	const std::string& sOrder);

	//���ɸ������//sql="update ���ݱ� set �ֶ�1=ֵ1,�ֶ�2=ֵ2 ���� �ֶ�n=ֵn where �������ʽ"
	static std::string	MakeSqlUpdate(const std::string& sTable,const MapStringString& vValue);
	static std::string	MakeSqlUpdate(const std::string& sTable,const MapStringString& vValue,const std::string& sWhere);
	static std::string	MakeSqlUpdate(const std::string& sTable,const MapStringString& vValue,const MapStringString& vWhere );

	//����ɾ����� // DELETE * FROM table_name where 
	static std::string	MakeSqlDelete(const std::string& sTable);
	static std::string	MakeSqlDelete(const std::string& sTable,const std::string& sWhere);
	static std::string	MakeSqlDelete(const std::string& sTable,const MapStringString& vWhere);
	
	//���ɲ������ ���Ȳ��룬��� ���������Ѵ��ڣ������(MySql����)
	static std::string	MakeSqlInsertUpdate(const std::string& sTable,const MapStringString& vValue);
	static std::string	MakeSqlInsertUpdate(const std::string& sTable,const MapStringString& vValue,const std::string& sOnDuplicate);

	//�����滻��� ���Ȳ��룬��� ���������Ѵ��ڣ����滻(MySql����)
	static std::string	MakeSqlReplace(const std::string& sTable, const MapStringString& vValue);

	//����SQL��� ������ձ�
	static std::string MakeSqlTruncateTable(const std::string& sTable);

	//����SQL��� ������
	static std::string MakeSqlDropTable(const std::string& sTable);

	//���ɵ��ô洢�������
	static std::string	MakeSqlCall(const std::string& sFunc,const VectorString& vArgs);
	template<typename T>
	static std::string	MakeSqlCall(const std::string& sFunc,const T& tValue);
	template<typename TArg1,typename TArg2>
	static std::string	MakeSqlCall(const std::string& sFunc,const TArg1& tArg1,const TArg2& tArg2);
	template<typename TArg1,typename TArg2,typename TArg3>
	static std::string	MakeSqlCall(const std::string& sFunc,const TArg1& tArg1,const TArg2& tArg2,const TArg3& tArg3);

	//����SQL��� ѡ��
	static const std::string&	MakeSqlSelectLastInsertID();//ѡ��ող��������ID
	static const std::string&	MakeSqlSelectRowCount();	//ѡ��ո�Ӱ�쵽������
	static std::string			MakeSqlSelect(const std::string& sSelect1,const std::string& sSelect2="",const std::string& sSelect3="",const std::string& sSelect4="",const std::string& sSelect5="");
	static std::string			MakeSqlSelect(int nArg);
	static std::string			MakeSqlSelect(int nArg1,int nArg2);
	static std::string			MakeSqlSelect(int nArg1,int nArg2,int nArg3);
	static std::string			MakeSqlSelect(int nArg1,int nArg2,int nArg3,int nArg4);
	static std::string			MakeSqlSelect(int nArg1,int nArg2,int nArg3,int nArg4,int nArg5);
	static std::string			MakeSqlSelect(float fArg);
	static std::string			MakeSqlSelect(float fArg1,float fArg2);
	static std::string			MakeSqlSelect(float fArg1,float fArg2,float fArg3);
	static std::string			MakeSqlSelect(float fArg1,float fArg2,float fArg3,float fArg4);
	static std::string			MakeSqlSelect(float fArg1,float fArg2,float fArg3,float fArg4,float fArg5);
	
	//SQL����
	static const std::string&	FunLastInsertID();
	static const std::string&	FunRowCount();
	static const std::string&	FunNow();

	//���ü�ֵ - MapStringString
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,const char* szValue);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,const std::string& sValue);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,int nValue);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,uint nValue);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,double fValue);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,const ToolFrame::CDateTime& datetime);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,const ToolFrame::CDate& date);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,const void* pBuffer,uint nSize);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,void* pBufferOut,const void* pBufferIn,uint nUsedSize,uint nBufferSize);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,const ToolFrame::CStreamBuffer& buffer);
	static bool			AddValue(MapStringString& vValue,const std::string& sKey,const ToolFrame::StreamBufferPtr pBuffer);
	static bool			AddNowTime(MapStringString& vValue,const std::string& sKey);

	//���ü�ֵ - VectorString
	static bool			AddValue(VectorString& vArgs,const char* szValue);
	static bool			AddValue(VectorString& vArgs,const std::string& sValue);
	static bool			AddValue(VectorString& vArgs,int nValue);
	static bool			AddValue(VectorString& vArgs,uint nValue);
	static bool			AddValue(VectorString& vArgs,double fValue);
	static bool			AddValue(VectorString& vArgs,const ToolFrame::CDateTime& datetime);
	static bool			AddValue(VectorString& vArgs,const ToolFrame::CDate& date);
	static bool			AddValue(VectorString& vArgs,const void* pBuffer,uint nSize);
	static bool			AddValue(VectorString& vArgs,const ToolFrame::CStreamBuffer& buffer);
	static bool			AddValue(VectorString& vArgs,const ToolFrame::StreamBufferPtr pBuffer);
	static bool			AddNowTime(VectorString& vArgs);
	static bool			AddReturn(VectorString& vArgs,const std::string& sValue);

	//ȥ������Ҫ���ַ���
	static std::string	EscapeString(const std::string& sString);
	static std::string	EscapeString(const void* pBuffer,uint uSize);
	static std::string	EscapeString(void* pBufferOut,const void* pBufferIn,uint nUsedSize,uint nBufferSize);
	
	
private:
	static bool MakeWhere(std::stringstream& sStream, const MapStringString& vValue);
	static bool MakeKeyValue(std::stringstream& sStream, const MapStringString& vValue,const std::string& sSp);// Account='1111' and RegistTime = '2011-09-03 14:44:11'
};

template<typename TArg1,typename TArg2,typename TArg3>
std::string ApiMySql::MakeSqlCall( const std::string& sFunc,const TArg1& tArg1,const TArg2& tArg2,const TArg3& tArg3 )
{
	VectorString vArgs;
	AddValue(vArgs,tArg1);
	AddValue(vArgs,tArg2);
	AddValue(vArgs,tArg3);
	return MakeSqlCall(sFunc,vArgs);
}

template<typename TArg1,typename TArg2>
std::string ApiMySql::MakeSqlCall( const std::string& sFunc,const TArg1& tArg1,const TArg2& tArg2 )
{
	VectorString vArgs;
	AddValue(vArgs,tArg1);
	AddValue(vArgs,tArg2);
	return MakeSqlCall(sFunc,vArgs);
}

template<typename T>
std::string ApiMySql::MakeSqlCall( const std::string& sFunc,const T& tValue )
{
	VectorString vArgs;
	AddValue(vArgs,tValue);
	return MakeSqlCall(sFunc,vArgs);
}

#endif
