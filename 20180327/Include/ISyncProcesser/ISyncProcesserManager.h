#pragma once
#include "Macro.h"
#include "ISyncProcesser.h"
#include "TThreadSaftyList.h"
#include "IDMaker.h"
#include "CalCounter.h"

NS_TOOL_FRAME_BEGIN

class HSyncProcesserManager {
public:
	virtual ISyncProcesserPtr OnCreateProcesser(int nUserInt = 0, void* pUserData = nullptr) {
		return ISyncProcesserPtr(new ISyncProcesser());
	}
	virtual bool OnDestoryProcesser(ISyncProcesserPtr pProcesser) {
		return true;
	}
public:
	HSyncProcesserManager() {}
	virtual ~HSyncProcesserManager() {}
};

class ISyncProcesserManager
	:public HSyncProcesserManager
{
public:
	typedef std::map<uint,	ISyncProcesserPtr>			MapSyncProcesser;
	typedef TThreadSaftyListValue<ISyncProcesserPtr>	QueueSyncProcesser;
	typedef std::vector<ISyncProcesserPtr>				VectorSyncProcesser;
public:
	virtual bool SetHandler(HSyncProcesserManager* hHandler);
	virtual bool SyncCreate(uint uProcesserID,uint uSecondID = INVALID_ID, int nUserInt = 0, void* pUserData = nullptr);
	virtual bool SyncInsert(ISyncProcesserPtr pProcesser);
	virtual bool SyncInsertMakeProcesserID(ISyncProcesserPtr pProcesser);
	virtual bool SyncInsertMakeSecondID(ISyncProcesserPtr pProcesser);
	virtual bool SyncIsExist(uint uProcesserID)const;
	virtual bool SyncIsExistSecondID(uint uSecondID)const;
	virtual bool ProcessRetry(uint64 uMillTime);

	virtual bool SyncInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser);
	virtual bool SyncRemoveSecond(uint uSecondID);
public:
	virtual size_t GetProcesserSize()const;			//获取主键大小
	virtual size_t GetSecondSize()const;			//获取次键大小
	virtual size_t GetQueueSize()const;				//获取队列长度
	virtual size_t GetVaildCount()const;			//获取有效用户个数
	virtual size_t GetNormalCount()const;			//获取正常用户数

	//调试用
public:
	virtual bool DebugCheck();

public:
	//调用主键
	template<typename TClass, typename TFn>
	bool SyncCallProcesser(uint uProcesserID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//调用次键
	template<typename TClass, typename TFn>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//遍历
	template<typename TClass, typename TFn>
	bool SyncForEachCallProcesser(TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncForEachCallProcesser(TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
protected:
	//内部实际调用
	template<typename TClass,typename TMap, typename TKey, typename TFn>
	bool SyncCallProcesserMap(TMap& vMap,const TKey& tKey, TFn fn);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
	bool SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
	bool SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//异步处理调用
public:
	virtual bool ReqOperate(ISyncProcesserPtr pProcesser);
	virtual bool ReqDelete(ISyncProcesserPtr pProcesser);
	virtual bool ReqInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser);
	virtual bool ReqRemoveSecond(uint uSecondID);

	//以下无锁
protected:
	virtual CMutexReadWrite& GetMutex()const;
	virtual bool AutoInsertProcesser(ISyncProcesserPtr pProcesser);//添加到映射表，如果有次键 也一并加入
	virtual bool AutoRemoveProcesser(ISyncProcesserPtr pProcesser);//移除映射表，如果有次键 也一并移除
	virtual uint MakeProcesserID();
	virtual uint MakeSecondID();
	virtual bool InsertProcesser(ISyncProcesserPtr pProcesser);
	virtual bool RemoveProcesser(uint uProcesserID);
	virtual ISyncProcesserPtr FindProcesser(uint uProcesserID);
	virtual ISyncProcesserPtr FindProcesserSecond(uint uSecondID);
	virtual bool InsertSecond(uint uSecondID,ISyncProcesserPtr pProcesser);
	virtual bool RemoveSecond(uint uSecondID);
	virtual const MapSyncProcesser& GetProcesser()const;
	virtual const MapSyncProcesser& GetProcesserSecond()const;

	//内部函数 尽量不要访问
public:
	virtual bool SyncMarkNormal();
	virtual bool SyncClearNormal();
	virtual bool SyncMarkVaild();
	virtual bool SyncClearVaild();
	virtual bool SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing,uint& uCache) const;//统计缓存的状态(总数，有效数，正常数 低性能 调试用)
private:
	virtual bool OnProcesserOperate(ISyncProcesserPtr pProcesser);
	virtual bool OnProcesserDelete(ISyncProcesserPtr pProcesser);
	virtual bool OnInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser);
	virtual bool OnRemoveSecond(uint uSecondID);
public:
	ISyncProcesserManager();
	virtual ~ISyncProcesserManager();
protected:
	mutable CMutexReadWrite _mutex;
	MapSyncProcesser		_vProcesser;//主键映射表
	MapSyncProcesser		_vSecond;	//次键映射表

	CIDMakerUint			_xMaker;		//主键ID生成器
	CIDMakerUint			_xMakerSecond;	//次键ID生成器

	CCalCounter				_uVaild;			//有效数
	CCalCounter				_uNormal;			//正常数

	CFunctionQueue				_vQueue;

	HSyncProcesserManager*	_hHandler;
};

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return SyncCallProcesserMap<TClass>(_vProcesser, uProcesserID,fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return SyncCallProcesserMap<TClass>(_vProcesser, uProcesserID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1)
{
	return SyncCallProcesserMap<TClass>(_vProcesser, uProcesserID, fn, tArg1);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn)
{
	return SyncCallProcesserMap<TClass>(_vProcesser, uProcesserID, fn);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn)
{
	return SyncCallProcesserMap<TClass>(_vSecond, uSecondID, fn);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1)
{
	return SyncCallProcesserMap<TClass>(_vSecond, uSecondID, fn, tArg1);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return SyncCallProcesserMap<TClass>(_vSecond, uSecondID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return SyncCallProcesserMap<TClass>(_vSecond, uSecondID, fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	CLockRead lock(_mutex);
	MapSyncProcesser::const_iterator itr;
	foreach(itr, _vProcesser) {
		ISyncProcesserPtr pProcesser = itr->second;
		if (!pProcesser)
			continue;

		TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
		if (!pProcesserSub)return false;

		(pProcesserSub->*fn)(tArg1, tArg2, tArg3);
	}
	return true;
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	CLockRead lock(_mutex);
	MapSyncProcesser::const_iterator itr;
	foreach(itr, _vProcesser) {
		ISyncProcesserPtr pProcesser = itr->second;
		if (!pProcesser)
			continue;

		TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
		if (!pProcesserSub)return false;

		(pProcesserSub->*fn)(tArg1, tArg2);
	}
	return true;
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn, TArg1& tArg1)
{
	CLockRead lock(_mutex);
	MapSyncProcesser::const_iterator itr;
	foreach(itr, _vProcesser) {
		ISyncProcesserPtr pProcesser = itr->second;
		if (!pProcesser)
			continue;

		TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
		if (!pProcesserSub)return false;

		(pProcesserSub->*fn)(tArg1);
	}
	return true;
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn)
{
	CLockRead lock(_mutex);
	MapSyncProcesser::const_iterator itr;
	foreach(itr, _vProcesser) {
		ISyncProcesserPtr pProcesser = itr->second;
		if (!pProcesser)
			continue;

		TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
		if (!pProcesserSub)return false;

		(pProcesserSub->*fn)();
	}
	return true;
}


template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	CLockRead lock(_mutex);
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)(tArg1, tArg2, tArg3);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	CLockRead lock(_mutex);
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)(tArg1, tArg2);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1)
{
	CLockRead lock(_mutex);
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)(tArg1);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn)
{
	CLockRead lock(_mutex);
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)();
	return true;
}

NS_TOOL_FRAME_END

