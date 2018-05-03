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
	virtual bool			SetQueryMax(size_t uMax);					//设置查询最大值(超过也没关系)
	virtual bool			Init();
public:
	virtual IQueryPtr		Query(IQueryPtr ptr, size_t uKey = INVALID_ID);
	virtual size_t			GetQueryCount()const;
	virtual size_t			ClearProcessCount();		//清除本次处理量
	virtual bool			IsQueryEmpty()const;
	virtual const MapVectorExecuter& GetExecuter()const;
	virtual VectorExecuter*	 FindExecuter(int eType = 0)const;

	//创建执行器
	template<typename T>
	T*						CreateExecuter(int eType=0);
	virtual bool			DestoryExecuter();

	//内部调用 外部不要访问
public:
	virtual IQueryPtr		OnQueryExecuted(IQueryExecuter* pExecuter, uint uQueryID);	//查找出结果 返回 完成的查询
	virtual bool			OnQueryOver(IQueryExecuter* pExecuter, uint uQueryID);		//执行下一次查询
private:
	virtual bool			InsertExecuter(IQueryExecuter* pExecuter, int eType = 0);
public:
	IQueryClient();
	virtual ~IQueryClient();
protected:
	MapVectorExecuter	_vExecuter;	//执行器
	VectorMapQuery		_vVectorMap;//正在查询的数量
	VectorQuery			_vWait;		//待查询数量
	CCalCounterSize		_uProcessCount;	//本次完成的数量
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
