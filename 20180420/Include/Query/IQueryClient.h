#pragma once

#include "Macro.h"

#include "IQuery.h"
#include "IQueryExecuter.h"

#include "TThreadSaftyVectorMap.h"
#include "TThreadSaftyList.h"

NS_TOOL_FRAME_BEGIN

class IQueryClient
{
public:
	typedef TThreadSaftyVectorMap<IQueryPtr>			VectorMapQuery;
	typedef TThreadSaftyListValue<IQueryPtr>			VectorQuery;
	typedef std::vector<IQueryExecuter*>				VectorExecuter;
	typedef std::map<int, VectorExecuter>				MapVectorExecuter;
public:
	virtual bool			SetQueryMax(size_t uMax);					//���ò�ѯ���ֵ(����Ҳû��ϵ)
	virtual bool			Init();
public:
	virtual IQueryPtr		Query(IQueryPtr ptr, size_t uKey = INVALID_ID);
	virtual size_t			GetQueryCount()const;
	virtual size_t			ClearProcessCount();		//������δ�����
	virtual bool			IsQueryEmpty()const;
	virtual const MapVectorExecuter& GetExecuter()const;
	virtual VectorExecuter*	 FindExecuter(int eType = 0)const;

	//����ִ����
	template<typename T>
	T*						CreateExecuter(int eType=0);
	virtual bool			DestoryExecuter();

	//�ڲ����� �ⲿ��Ҫ����
public:
	virtual IQueryPtr		OnQueryExecuted(IQueryExecuter* pExecuter, uint uQueryID);	//���ҳ���� ���� ��ɵĲ�ѯ
	virtual bool			OnQueryOver(IQueryExecuter* pExecuter, uint uQueryID);		//ִ����һ�β�ѯ
private:
	virtual bool			InsertExecuter(IQueryExecuter* pExecuter, int eType = 0);
public:
	IQueryClient();
	virtual ~IQueryClient();
protected:
	MapVectorExecuter	_vExecuter;	//ִ����
	VectorMapQuery		_vVectorMap;//���ڲ�ѯ������
	VectorQuery			_vWait;		//����ѯ����
	CCalCounterSize		_uProcessCount;	//������ɵ�����
};

template<typename T>
T* IQueryClient::CreateExecuter(int eType)
{
	T* pExecuter = new T();
	if (!pExecuter)return nullptr;

	if (!InsertExecuter(pExecuter, eType))
	{
		delete pExecuter;
		return nullptr;
	}

	return pExecuter;
}

NS_TOOL_FRAME_END
