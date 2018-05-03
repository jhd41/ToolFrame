#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL
#include "mysql.h"

//��ע:
//��¼	Record
//����� Result	һ������ɶ�����¼��ɵ�

//MySql��ѯ��������ɽ����(Result)��һ��SQL�������һ���������������������ɶ����
//�л������ʹ�� NextResult ����
//�ڵ���������� �ж�����¼ �л� ��¼ ʹ�� NextRecord();

NS_TOOL_FRAME_BEGIN

class CMySqlResults
{
public:
	bool		IsRecordEmpty()const;	//�Ƿ�Ϊ�ռ�¼
	uint		GetRecordCount()const;	//��ȡ��¼����
	uint		GetFieldCount()const;	//��ȡ�ֶθ���

	uint		GetAffectedRows()const;	//����Ӱ������

	bool		FirstRecord();				//��ȡ��һ����¼��
	bool		NextRecord();				//��ȡ��һ����¼��
	const char* GetFieldValue(uint nIndex)const;//��ȡ��ǰ��¼����ĳһ���ֶε�ֵ(Index��0��ʼ)
	std::string	GetFieldString(uint nIndex)const;//ͬGetFieldValue ֻ����ֵ��Ч ���ؿ�string,���ܽ�GetFieldValue�Ե�
	int			GetFieldLength(uint nIndex)const;//��ȡ���м�¼����

	//�����������
// 	bool		ResetRecord();//���ü�¼
// 	bool		FetchRecord();//����һ����¼

// 	bool		ResetResult();//���ý����
// 	bool		FetchResult();//����һ�����
public:
	bool		SetMySql(MYSQL* pMySql);//����ָ��
	void		SetError();				//���ô�����
	bool		Clear();				//�������
	bool		IsHasResult()const;		//�Ƿ��н����
	bool		IsMoreResult();			//�Ƿ��ж�������
	bool		NextResult();			//��һ�������
	bool		ClearResult();			//��������

	bool		IsError()const;			//�Ƿ��д���
	const char* GetLastError()const;	//��ȡ������Ϣ
	uint		GetLastErrCode()const;	//��ȡ�����
public:
	CMySqlResults(void);
	virtual ~CMySqlResults(void);
private:
	MYSQL*		_pMySql;	//SQL������
	MYSQL_RES*  _pSqlRes;	//SQL�����
	MYSQL_ROW   _sqlRow;	//SQL�������
	bool		_bError;	//�Ƿ��д�
};

NS_TOOL_FRAME_END


#endif

