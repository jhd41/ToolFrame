#pragma once

#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "MacroDataBase.h"
#include "SqlStruct.h"
#include "SqlConst.h"

NS_TOOL_FRAME_BEGIN

class CSqlResults
{
	NO_COPY(CSqlResults);
public:
	virtual bool			SetResults(const SqlResults* pResults);
	virtual bool			SetError(int nError);
	virtual bool			IsError()const;
	virtual int				GetError()const;			//获取错误代号

	virtual const SqlResult* FindResult(uint uResult)const;
	virtual const SqlRecord* FindRecord(uint uResult,uint uRecord)const;
	virtual const SqlField*	FindField(uint uResult, uint uRecord, uint uField)const;

	virtual const SqlResult* FindResultCur()const;			//得到当前的结果集
	virtual const SqlRecord* FindRecordCur()const;			//得到当前的记录
	virtual const SqlField*	FindFieldCur(uint uField)const;	//得到当前的字段

	virtual const char*		GetFieldValue(uint uField)const;
	virtual size_t			GetFieldLength(uint uField)const;

	virtual bool			ResetResults();			//重置
	virtual bool			FirstResult();			//获取第一个记录
	virtual bool			NextResult();			//下一个结果集
	virtual bool			FirstRecord();			//获取第一个记录
	virtual bool			NextRecord();			//获取下一个记录

	virtual bool			IsHasResult()const;		//是否包含结果集
	virtual bool			IsHasRecord()const;		//是否包含记录

	virtual bool			IsResultEmpty()const;	//是否为空结果
	virtual bool			IsRecordEmpty()const;	//是否为空记录
		
	virtual size_t			GetResultCount()const;	//获取结果个数
	virtual size_t			GetRecordCount()const;	//获取记录个数
	virtual size_t			GetFieldCount()const;	//获取字段个数
public:
	CSqlResults();
	virtual ~CSqlResults();
private:
	const SqlResults*	_pResults;
	int					_nError;	 //错误码

	uint				_uResultIndex;//当前结果集
	uint				_uRecordIndex;//当前记录
};

NS_TOOL_FRAME_END

#endif

