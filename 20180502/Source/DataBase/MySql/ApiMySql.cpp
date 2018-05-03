#include "ApiMySql.h"

#ifdef MACRO_LIB_MY_SQL

#include "ToolFrame.h"
#include "MySqlClass.h"

std::string ApiMySql::MakeSqlInsert( const std::string& sTable,const MapStringString& vValue )
{
	if (sTable.empty())return "";
	if (vValue.empty())return "";

	//INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....)
	std::stringstream sStream;
	sStream<<"INSERT INTO "<<sTable<<" (";

	//塞入Key
	{
		MapStringString::const_iterator itr = vValue.begin();
		sStream<<itr->first;
		++itr;
		foreachNext(itr,vValue){
			sStream<<","<<itr->first;
		}
	}

	sStream<<") VALUES (";

	//塞入Value
	{
		MapStringString::const_iterator itr = vValue.begin();
		sStream<<itr->second;
		++itr;
		foreachNext(itr,vValue){
			sStream<<","<<itr->second;
		}
	}
	sStream<<")";

	return sStream.str();
}

std::string ApiMySql::MakeSqlInsert( const std::string& sTable,const VectorString& vValue )
{
	//INSERT INTO 表名称 VALUES (值1, 值2,....)

	if (sTable.empty())return "";
	if (vValue.empty())return "";

	std::stringstream sStream;
	sStream<<"INSERT INTO "<<sTable<<" VALUES (";

	VectorString::const_iterator itr = vValue.begin();
	sStream<<*itr;
	++itr;
	foreachNext(itr,vValue){
		sStream<<","<<*itr;
	}

	sStream<<")";

	return sStream.str();
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,const std::string& sValue )
{
	return ToolFrame::InsertString(vValue,sKey,MAKE_STRING('\''<<EscapeString(sValue)<<'\''));
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,int nValue )
{
	return ToolFrame::InsertString(vValue,sKey,nValue);
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,double fValue )
{
	return ToolFrame::InsertString(vValue,sKey,fValue);
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,const ToolFrame::CDateTime& datetime )
{
	std::string sDataTime = datetime.IsTimeInvaild() ? "NULL" : MAKE_STRING('\''<<datetime.GetString()<<'\'');
	return ToolFrame::InsertString(vValue,sKey,sDataTime);
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,const ToolFrame::CDate& date )
{
	std::string sData = date.IsTimeInvaild() ? "NULL" : MAKE_STRING('\''<<date.GetString()<<'\'');
	return ToolFrame::InsertString(vValue,sKey,sData);
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,uint nValue )
{
	return ToolFrame::InsertString(vValue,sKey,nValue);
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,const void* pBuffer,uint nSize )
{
	return ToolFrame::InsertString(vValue,sKey,MAKE_STRING('\''<<EscapeString(pBuffer,nSize)<<'\''));
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,void* pBufferOut,const void* pBufferIn,uint nUsedSize,uint nBufferSize )
{
	return ToolFrame::InsertString(vValue,sKey,MAKE_STRING('\''<<EscapeString(pBufferOut,pBufferIn,nUsedSize,nBufferSize)<<'\''));
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,const ToolFrame::CStreamBuffer& buffer )
{
	if (buffer.GetLength()<=0){
		return ToolFrame::InsertString(vValue,sKey,"NULL");
	}

	return AddValue(vValue,sKey,buffer.GetBuffer(),buffer.GetLength());
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,const ToolFrame::StreamBufferPtr pBuffer )
{
	if (!pBuffer){
		return ToolFrame::InsertString(vValue,sKey,"NULL");
	}

	return AddValue(vValue,sKey,*pBuffer);
}

bool ApiMySql::AddNowTime( MapStringString& vValue,const std::string& sKey )
{
	return ToolFrame::InsertString(vValue,sKey,"NOW()");
}

std::string ApiMySql::MakeSqlQuery( const std::string& sTable,const std::string& sSel,const MapStringString& vWhere )
{
	return MakeSqlQuery(sTable,sSel,vWhere,ToolFrame::EmptyString());
}

std::string ApiMySql::MakeSqlQuery( const std::string& sTable,const std::string& sSel )
{
	return MakeSqlQuery(sTable,sSel,ToolFrame::EmptyString());
}

std::string ApiMySql::MakeSqlQuery( const std::string& sTable,const std::string& sSel,const std::string& sWhere )
{
	return MakeSqlQuery(sTable,sSel,sWhere,ToolFrame::EmptyString());
}

std::string ApiMySql::MakeSqlQuery( const std::string& sTable,const std::string& sSel,const std::string& sWhere, const std::string& sOrder )
{
	if (sTable.empty())return "";
	if (sSel.empty())return "";

	std::stringstream sStream;
	sStream<<"select "<<sSel<<" from "<<sTable;
	if (!sWhere.empty())
		sStream<<" where "<<ApiMySql::EscapeString(sWhere);
	if (!sOrder.empty())
		sStream<<" "<<ApiMySql::EscapeString(sOrder);

	return sStream.str();
}

std::string ApiMySql::MakeSqlQuery( const std::string& sTable,const std::string& sSel,const MapStringString& vWhere, const std::string& sOrder )
{
	if (sTable.empty())return "";
	if (sSel.empty())return "";

	//select * from Account where Account='1111' and RegistTime = '2011-09-03 14:44:11'
	std::stringstream sStream;
	sStream<<"SELECT "<<sSel<<" FROM "<<sTable;

	if (!MakeWhere(sStream,vWhere))
		return "";

	if (!sOrder.empty())
		sStream<<" "<<ApiMySql::EscapeString(sOrder);

	return sStream.str();
}

std::string ApiMySql::EscapeString( const void* pBuffer,uint uSize )
{
	if (uSize <=0)return "";
	if (!pBuffer)return "";

	if (uSize<1024)
	{
		ToolFrame::TArray<char,1024*2+1> szSql;
		uint uDes = mysql_escape_string(szSql,(const char*)pBuffer,uSize);
		szSql[uDes]='\0';

		return szSql.GetPtr();
	}
	if (uSize<4096)
	{
		ToolFrame::TArray<char,4096*2+1> szSql;
		uint uDes = mysql_escape_string(szSql,(const char*)pBuffer,uSize);
		szSql[uDes]='\0';
		return szSql.GetPtr();
	}

	ToolFrame::TArrayNew<char> szSql(2*uSize+1,true);

	uint uDes = mysql_escape_string(szSql,(const char*)pBuffer,uSize);
	szSql[uDes]='\0';
	return szSql.GetPtr();
}

std::string ApiMySql::EscapeString( const std::string& sString )
{
	if (sString.empty())
		return "";

	//为了提升性能 复制代码 EscapeString ( const void* pBuffer,uint uSize )

	const char* pBuffer = sString.c_str();
	uint uSize = sString.length();

	if (uSize<1024)
	{
		ToolFrame::TArray<char,1024*2+1> szSql;
		uint uDes = mysql_escape_string(szSql,pBuffer,uSize);
		szSql[uDes]='\0';

		return szSql.GetPtr();
	}
	if (uSize<4096)
	{
		ToolFrame::TArray<char,4096*2+1> szSql;
		uint uDes = mysql_escape_string(szSql,pBuffer,uSize);
		szSql[uDes]='\0';

		return szSql.GetPtr();
	}

	ToolFrame::TArrayNew<char> szSql(2*uSize+1,true);

	uint uDes = mysql_escape_string(szSql,pBuffer,uSize);
	szSql[uDes]='\0';

	return szSql.GetPtr();
}

std::string ApiMySql::EscapeString( void* pBufferOut,const void* pBufferIn,uint nUsedSize,uint nBufferSize )
{
	char* pBufferChar = (char*)pBufferOut;
	uint uDes = mysql_escape_string(pBufferChar,(const char*)pBufferIn,nUsedSize);//当溢出时 可能会崩溃
	pBufferChar[uDes]='\0';

	if (uDes > nBufferSize) return "";
	return pBufferChar;
}

std::string ApiMySql::MakeSqlUpdate( const std::string& sTable,const MapStringString& vValue,const MapStringString& vWhere )
{
	//sql="update 数据表 set 字段1=值1,字段2=值2 …… 字段n=值n where 条件表达式"
	std::stringstream sStream;
	sStream<<"update "<<sTable<<" set ";
	if (!MakeKeyValue(sStream,vValue,","))return "";
	if (!MakeWhere(sStream,vWhere))return "";

	return sStream.str();
}

std::string ApiMySql::MakeSqlUpdate( const std::string& sTable,const MapStringString& vValue )
{
	return MakeSqlUpdate(sTable,vValue,ToolFrame::EmptyString());
}

std::string ApiMySql::MakeSqlUpdate( const std::string& sTable,const MapStringString& vValue,const std::string& sWhere )
{
	//sql="update 数据表 set 字段1=值1,字段2=值2 …… 字段n=值n where 条件表达式"
	std::stringstream sStream;
	sStream<<"update "<<sTable<<" set ";
	if (!MakeKeyValue(sStream,vValue,","))return "";
	if (!sWhere.empty())
		sStream<<" where "<<ApiMySql::EscapeString(sWhere);

	return sStream.str();
}

bool ApiMySql::MakeKeyValue(std::stringstream& sStream, const MapStringString& vValue,const std::string& sSp)
{
	bool bFirst=true;
	MapStringString::const_iterator itr;
	foreach(itr,vValue){
		if (!bFirst)
			sStream<<" "<<sSp<<" ";

		sStream<<itr->first<<"="<<itr->second;
		bFirst = false;
	}

	return true;
}

bool ApiMySql::MakeWhere( std::stringstream& sStream, const MapStringString& vValue )
{
	if (vValue.empty())return true;
	sStream<<" where ";
	return MakeKeyValue(sStream,vValue,"and");
}

bool ApiMySql::AddValue( VectorString& vArgs,const std::string& sValue )
{
	return ToolFrame::InsertString(vArgs,MAKE_STRING('\''<<EscapeString(sValue)<<'\''));
}

bool ApiMySql::AddValue( VectorString& vArgs,int nValue )
{
	return ToolFrame::InsertString(vArgs,nValue);
}

bool ApiMySql::AddValue( VectorString& vArgs,const void* pBuffer,uint nSize )
{
	//return ToolFrame::Insert(vArgs,EscapeString(pBuffer,nSize));
	return ToolFrame::Insert(vArgs,MAKE_STRING('\''<<EscapeString(pBuffer,nSize)<<'\''));
}

bool ApiMySql::AddValue( VectorString& vArgs,uint nValue )
{
	return ToolFrame::InsertString(vArgs,nValue);
}

bool ApiMySql::AddValue( VectorString& vArgs,const ToolFrame::CDateTime& datetime )
{
	std::string sDataTime = datetime.IsTimeInvaild() ? "NULL" : MAKE_STRING('\''<<datetime.GetString()<<'\'');
	return ToolFrame::InsertString(vArgs,sDataTime);
}

bool ApiMySql::AddValue( VectorString& vArgs,const ToolFrame::CDate& date )
{
	std::string sData = date.IsTimeInvaild() ? "NULL" : MAKE_STRING('\''<<date.GetString()<<'\'');
	return ToolFrame::InsertString(vArgs,sData);
}

bool ApiMySql::AddValue( MapStringString& vValue,const std::string& sKey,const char* szValue )
{
	if (!szValue)
		return ToolFrame::InsertString(vValue,sKey,"NULL");
	return AddValue(vValue,sKey,std::string(szValue));
}

bool ApiMySql::AddValue( VectorString& vArgs,const char* szValue )
{
	if (!szValue)
		return ToolFrame::InsertString(vArgs,"NULL");
	return AddValue(vArgs,std::string(szValue));
}

bool ApiMySql::AddValue( VectorString& vArgs,const ToolFrame::CStreamBuffer& buffer )
{
	if (buffer.GetLength()<=0){
		return ToolFrame::InsertString(vArgs,"NULL");
	}

	return AddValue(vArgs,buffer.GetBuffer(),buffer.GetLength());
}

bool ApiMySql::AddValue( VectorString& vArgs,const ToolFrame::StreamBufferPtr pBuffer )
{
	if (!pBuffer)
		return ToolFrame::InsertString(vArgs,"NULL");

	return AddValue(vArgs,*pBuffer);
}

bool ApiMySql::AddNowTime( VectorString& vArgs )
{
	return ToolFrame::InsertString(vArgs,"NOW()");
}

bool ApiMySql::AddValue( VectorString& vArgs,double fValue )
{
	return ToolFrame::InsertString(vArgs,fValue);
}

std::string ApiMySql::MakeSqlCall( const std::string& sFunc,const VectorString& vArgs )
{
	std::stringstream sStream;

	//拼Call语句
	bool bFirst=true;
	sStream<<"call "<<sFunc<<"(";
	VectorString::const_iterator itr;
	foreach(itr,vArgs){
		const std::string& sFeild = *itr;
		if (!bFirst)
			sStream<<",";

		sStream<<sFeild;
		bFirst = false;
	}
	sStream<<")";
	return sStream.str();
}

bool ApiMySql::AddReturn( VectorString& vArgs,const std::string& sValue )
{
	if (sValue.empty())return false;

	if (ToolFrame::IsBeginWith(sValue,"@"))
		return ToolFrame::InsertString(vArgs,sValue);
	return ToolFrame::InsertString(vArgs,MAKE_STRING("@"<<sValue));
}

CMutexRecursive& ApiMySql::GetMutex()
{
	static CMutexRecursive g_mutex;
	return g_mutex;
}

std::string ApiMySql::MakeSqlInsertUpdate( const std::string& sTable,const MapStringString& vValue )
{
	if (sTable.empty())return "";
	if (vValue.empty())return "";

	//INSERT INTO Rank (BinData,ID) VALUES (NULL,42)ON DUPLICATE KEY update  BinData=NULL , ID=42
	std::stringstream sStream;
	sStream<<MakeSqlInsert(sTable,vValue);
	sStream<<" ON DUPLICATE KEY UPDATE ";
	if (!MakeKeyValue(sStream,vValue,","))return "";

	return sStream.str();
}

std::string ApiMySql::MakeSqlInsertUpdate( const std::string& sTable,const MapStringString& vValue,const std::string& sOnDuplicate )
{
	if (sTable.empty())return "";
	if (vValue.empty())return "";

	//INSERT INTO Rank (BinData,ID) VALUES (NULL,42)ON DUPLICATE KEY update  BinData=NULL , ID=42
	std::stringstream sStream;
	sStream<<MakeSqlInsert(sTable,vValue);

	if (!sOnDuplicate.empty())
		sStream<<" ON DUPLICATE KEY UPDATE "<<sOnDuplicate;

	return sStream.str();
}

std::string ApiMySql::MakeSqlReplace(const std::string& sTable, const MapStringString& vValue)
{
	if (sTable.empty())return "";
	if (vValue.empty())return "";

	//INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....)
	std::stringstream sStream;
	sStream << "REPLACE INTO " << sTable << " (";

	//塞入Key
	{
		MapStringString::const_iterator itr = vValue.begin();
		sStream << itr->first;
		++itr;
		foreachNext(itr, vValue) {
			sStream << "," << itr->first;
		}
	}

	sStream << ") VALUES (";

	//塞入Value
	{
		MapStringString::const_iterator itr = vValue.begin();
		sStream << itr->second;
		++itr;
		foreachNext(itr, vValue) {
			sStream << "," << itr->second;
		}
	}
	sStream << ")";

	return sStream.str();
}

const std::string& ApiMySql::MakeSqlSelectLastInsertID() 
{
	const static std::string sString = "SELECT LAST_INSERT_ID()";
	return sString;
}

const std::string& ApiMySql::MakeSqlSelectRowCount() 
{
	const static std::string sString = "SELECT ROW_COUNT()";
	return sString;
}

std::string ApiMySql::MakeSqlDelete( const std::string& sTable )
{
	if (sTable.empty())return "";

	std::stringstream sStream;
	sStream<<"DELETE * FROM "<<sTable;
	return sStream.str();
}

std::string ApiMySql::MakeSqlDelete( const std::string& sTable,const std::string& sWhere )
{
	if (sTable.empty())return "";

	//DELETE * FROM table_name where 
	std::stringstream sStream;
	sStream<<"DELETE FROM "<<sTable<<" "<<sWhere;

	return sStream.str();
}

std::string ApiMySql::MakeSqlDelete( const std::string& sTable,const MapStringString& vWhere )
{
	if (sTable.empty())return "";

	//DELETE * FROM table_name where 
	std::stringstream sStream;
	sStream<<"DELETE FROM "<<sTable;

	if (!MakeWhere(sStream,vWhere))
		return "";

	return sStream.str();
}

std::string ApiMySql::MakeSqlTruncateTable( const std::string& sTable )
{
	if (sTable.empty())return false;

	return MAKE_STRING("TRUNCATE TABLE "<<sTable);
}

std::string ApiMySql::MakeSqlDropTable( const std::string& sTable )
{
	if (sTable.empty())return false;

	return MAKE_STRING("DROP TABLE IF EXISTS \'"<<sTable<<"\'");
}

std::string ApiMySql::MakeSqlInsertIgnore( const std::string& sTable,const MapStringString& vValue )
{
	//复制粘贴自 MakeSqlInsert
	if (sTable.empty())return "";
	if (vValue.empty())return "";

	//INSERT INTO table_name (列1, 列2,...) VALUES (值1, 值2,....)
	std::stringstream sStream;
	sStream<<"INSERT IGNORE INTO "<<sTable<<" (";

	//塞入Key
	{
		MapStringString::const_iterator itr = vValue.begin();
		sStream<<itr->first;
		++itr;
		foreachNext(itr,vValue){
			sStream<<","<<itr->first;
		}
	}

	sStream<<") VALUES (";

	//塞入Value
	{
		MapStringString::const_iterator itr = vValue.begin();
		sStream<<itr->second;
		++itr;
		foreachNext(itr,vValue){
			sStream<<","<<itr->second;
		}
	}
	sStream<<")";

	return sStream.str();
}

std::string ApiMySql::MakeSqlInsertIgnore( const std::string& sTable,const VectorString& vValue )
{
	//复制粘贴自 MakeSqlInsert
	//INSERT INTO 表名称 VALUES (值1, 值2,....)

	if (sTable.empty())return "";
	if (vValue.empty())return "";

	std::stringstream sStream;
	sStream<<"INSERT IGNORE INTO "<<sTable<<" VALUES (";

	VectorString::const_iterator itr = vValue.begin();
	sStream<<*itr;
	++itr;
	foreachNext(itr,vValue){
		sStream<<","<<*itr;
	}

	sStream<<")";

	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( const std::string& sSelect1,const std::string& sSelect2/*=""*/,const std::string& sSelect3/*=""*/,const std::string& sSelect4/*=""*/,const std::string& sSelect5/*=""*/ )
{
	if (sSelect1.empty())return false;

	std::stringstream sStream;
	sStream<<"SELECT "<<sSelect1;
	
	if (!sSelect2.empty())
		sStream<<","<<sSelect2;
	if (!sSelect3.empty())
		sStream<<","<<sSelect3;
	if (!sSelect4.empty())
		sStream<<","<<sSelect4;
	if (!sSelect5.empty())
		sStream<<","<<sSelect5;

	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( int nArg )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<nArg;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( int nArg1,int nArg2 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<nArg1<<","<<nArg2;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( int nArg1,int nArg2,int nArg3 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<nArg1<<","<<nArg2<<","<<nArg3;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( int nArg1,int nArg2,int nArg3,int nArg4 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<nArg1<<","<<nArg2<<","<<nArg3<<","<<nArg4;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( int nArg1,int nArg2,int nArg3,int nArg4,int nArg5 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<nArg1<<","<<nArg2<<","<<nArg3<<","<<nArg4<<","<<nArg5;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( float fArg )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<fArg;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( float fArg1,float fArg2 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<fArg1<<","<<fArg2;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( float fArg1,float fArg2,float fArg3 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<fArg1<<","<<fArg2<<","<<fArg3;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( float fArg1,float fArg2,float fArg3,float fArg4 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<fArg1<<","<<fArg2<<","<<fArg3<<","<<fArg4;
	return sStream.str();
}

std::string ApiMySql::MakeSqlSelect( float fArg1,float fArg2,float fArg3,float fArg4,float fArg5 )
{
	std::stringstream sStream;
	sStream<<"SELECT "<<fArg1<<","<<fArg2<<","<<fArg3<<","<<fArg4<<","<<fArg5;
	return sStream.str();
}

const std::string& ApiMySql::FunLastInsertID()
{
	const static std::string sString = "LAST_INSERT_ID()";
	return sString;
}

const std::string& ApiMySql::FunRowCount()
{
	const static std::string sString = "ROW_COUNT()";
	return sString;
}

const std::string& ApiMySql::FunNow()
{
	const static std::string sString = "NOW()";
	return sString;
}

#endif
