#pragma once

#include "Macro.h"

//����������ؼ���
#define foreachResult(record) for (bool bResult = true;bResult;bResult = record.NextResult())
#define foreachRecord(record) for (bool bRecord = !record.IsRecordEmpty();bRecord;bRecord = record.NextRecord())

//SQL���ִ�д������
enum ESqlErrCode {
	ERR_SQL_INVALID = 0,

	ERR_SQL_SUCCEED = 1,

	//׼���ڴ���
	ERR_SQL_DBNAME_EMPTY,		//���ݿ�����Ϊ��
	ERR_SQL_DBNAME_NOT_EXIST,	//���ݿⲻ����
	ERR_SQL_DBNAME_SQL_EMPTY,	//SQLΪ��
	ERR_SQL_PUSH_FAILD,			//ѹ��ʧ��

	//ִ���ڴ���
	ERR_SQL_TIMEOUT,			//��ʱ
	ERR_SQL_EXECUTE_FAILD,		//ִ��ʧ��	

	//�ص������
	ERR_SQL_RECODE_EMPTY,		//��¼Ϊ��
	ERR_SQL_RECODE_MORE,		//��¼����
	ERR_SQL_DATA_SIZE_MAX,		//����������(�޷��ش�)

	ERR_SQL_MAX,
};