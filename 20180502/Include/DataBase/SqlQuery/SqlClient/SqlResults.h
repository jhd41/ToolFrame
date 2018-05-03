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
	virtual int				GetError()const;			//��ȡ�������

	virtual const SqlResult* FindResult(uint uResult)const;
	virtual const SqlRecord* FindRecord(uint uResult,uint uRecord)const;
	virtual const SqlField*	FindField(uint uResult, uint uRecord, uint uField)const;

	virtual const SqlResult* FindResultCur()const;			//�õ���ǰ�Ľ����
	virtual const SqlRecord* FindRecordCur()const;			//�õ���ǰ�ļ�¼
	virtual const SqlField*	FindFieldCur(uint uField)const;	//�õ���ǰ���ֶ�

	virtual const char*		GetFieldValue(uint uField)const;
	virtual size_t			GetFieldLength(uint uField)const;

	virtual bool			ResetResults();			//����
	virtual bool			FirstResult();			//��ȡ��һ����¼
	virtual bool			NextResult();			//��һ�������
	virtual bool			FirstRecord();			//��ȡ��һ����¼
	virtual bool			NextRecord();			//��ȡ��һ����¼

	virtual bool			IsHasResult()const;		//�Ƿ���������
	virtual bool			IsHasRecord()const;		//�Ƿ������¼

	virtual bool			IsResultEmpty()const;	//�Ƿ�Ϊ�ս��
	virtual bool			IsRecordEmpty()const;	//�Ƿ�Ϊ�ռ�¼
		
	virtual size_t			GetResultCount()const;	//��ȡ�������
	virtual size_t			GetRecordCount()const;	//��ȡ��¼����
	virtual size_t			GetFieldCount()const;	//��ȡ�ֶθ���
public:
	CSqlResults();
	virtual ~CSqlResults();
private:
	const SqlResults*	_pResults;
	int					_nError;	 //������

	uint				_uResultIndex;//��ǰ�����
	uint				_uRecordIndex;//��ǰ��¼
};

NS_TOOL_FRAME_END

#endif

