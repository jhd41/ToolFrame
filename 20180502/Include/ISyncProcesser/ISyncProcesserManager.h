#pragma once
#include "Macro.h"
#include "ISyncProcesser.h"
#include "IDMaker.h"
#include "CalCounter.h"
#include "MulitOperateQueue.h"
#include "ToolCPlus11.h"

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
	virtual size_t ClearQueueProcess();				//清除处理量
	virtual CMutexReadWrite& GetMutex()const;

	//调试用
public:
	virtual bool CheckDebug();
	virtual bool DebugCheck();

	//异步(上锁失败 会 进入队列)
public:
	//调用主键
	template<typename TClass, typename TFn>
	bool AsyncCallProcesser(uint uProcesserID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool AsyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool AsyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool AsyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//调用次键
	template<typename TClass, typename TFn>
	bool AsyncCallProcesserSecondID(uint uSecondID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool AsyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool AsyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool AsyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//遍历
	template<typename TClass, typename TFn>
	bool AsyncForEachCallProcesser(TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool AsyncForEachCallProcesser(TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool AsyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool AsyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//同步(上锁失败 会一直等待 直到上锁成功)
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

	//尝试(上锁失败 返回false)
public:
	//调用主键
	template<typename TClass, typename TFn>
	bool SyncTryCallProcesser(uint uProcesserID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncTryCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncTryCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncTryCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//调用次键
	template<typename TClass, typename TFn>
	bool SyncTryCallProcesserSecondID(uint uSecondID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncTryCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncTryCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncTryCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

protected:
	//内部实际调用
	template<typename TClass,typename TMap, typename TKey, typename TFn>
	bool AsyncCallProcesserMap(TMap* vMap,const TKey& tKey, TFn fn);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
	bool AsyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
	bool AsyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool AsyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	template<typename TClass, typename TMap, typename TKey, typename TFn>
	bool SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
	bool SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
	bool SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	template<typename TClass, typename TMap, typename TKey, typename TFn>
	bool SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
	bool SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
	bool SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	
	//异步处理调用
public:
	virtual bool ReqOperate(ISyncProcesserPtr pProcesser);
	virtual bool ReqDelete(ISyncProcesserPtr pProcesser);
	virtual bool ReqInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser);
	virtual bool ReqRemoveSecond(uint uSecondID);

	//以下无锁
protected:
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
	virtual bool SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing, uint& uCache, uint& uOperateQueue, uint& uDelayOperateQueue) const;//统计缓存的状态(总数，有效数，正常数 低性能 调试用)
private:
	virtual bool OnProcesserOperate(ISyncProcesserPtr pProcesser);
	virtual bool OnProcesserDelete(ISyncProcesserPtr pProcesser);
	virtual bool OnInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser);
	virtual bool OnRemoveSecond(uint uSecondID);
private:
	//遍历
	template<typename TClass, typename TFn>
	bool ForEachCallProcesser(TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool ForEachCallProcesser(TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool ForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool ForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//单独调用
	template<typename TClass, typename TMap, typename TKey, typename TFn>
	bool CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
	bool CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
	bool CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
public:
	ISyncProcesserManager();
	virtual ~ISyncProcesserManager();
protected:
	MapSyncProcesser		_vProcesser;	//主键映射表
	MapSyncProcesser		_vSecond;		//次键映射表

	CIDMakerUint			_xMaker;		//主键ID生成器
	CIDMakerUint			_xMakerSecond;	//次键ID生成器

	CCalCounter				_uVaild;		//有效数
	CCalCounter				_uNormal;		//正常数

	CTimeOut				_xDebugCheck;

	CMulitOperateQueue		_vQueue;

	HSyncProcesserManager*	_hHandler;
};

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::AsyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return AsyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID,fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::AsyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return AsyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::AsyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1)
{
	return AsyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::AsyncCallProcesser(uint uProcesserID, TFn fn)
{
	return AsyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::AsyncCallProcesserSecondID(uint uSecondID, TFn fn)
{
	return AsyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::AsyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1)
{
	return AsyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::AsyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return AsyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::AsyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return AsyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::ForEachCallProcesser(TFn fn) {
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

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::ForEachCallProcesser(TFn fn, TArg1& tArg1) {
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
template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::ForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2) {
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
template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::ForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3) {
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

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::AsyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{	
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::ForEachCallProcesser<TClass, TFn, TArg1, TArg2, TArg3>,this), fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::AsyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::ForEachCallProcesser<TClass, TFn, TArg1, TArg2>, this), fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::AsyncForEachCallProcesser(TFn fn, TArg1& tArg1)
{
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::ForEachCallProcesser<TClass, TFn, TArg1>, this), fn, tArg1);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::AsyncForEachCallProcesser(TFn fn)
{
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::ForEachCallProcesser<TClass, TFn>, this), fn);
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::AsyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::CallProcesserMap<TClass,TMap, TKey, TFn, TArg1, TArg2, TArg3>, this), vMap, tKey, fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::AsyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::CallProcesserMap<TClass, TMap, TKey, TFn, TArg1, TArg2>, this), vMap, tKey, fn, tArg1, tArg2);
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
bool ISyncProcesserManager::AsyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1)
{
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::CallProcesserMap<TClass, TMap, TKey, TFn, TArg1>, this), vMap, tKey, fn, tArg1);
}

template<typename TClass, typename TMap, typename TKey, typename TFn>
bool ISyncProcesserManager::AsyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn)
{
	return _vQueue.ReadOperate(ToolFrame::Bind(&ISyncProcesserManager::CallProcesserMap<TClass, TMap, TKey, TFn>,this), vMap, tKey, fn);
}

template<typename TClass, typename TMap, typename TKey, typename TFn>
bool ISyncProcesserManager::CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn) {
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(*vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)();
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
bool ISyncProcesserManager::CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1) {
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(*vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)(tArg1);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2) {
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(*vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)(tArg1, tArg2);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::CallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3) {
	ISyncProcesserPtr pProcesser = ToolFrame::GetPtrValueByKey(*vMap, tKey);
	if (!pProcesser)return false;

	TClass* pProcesserSub = pProcesser->ToProcesser<TClass>();
	if (!pProcesserSub)return false;

	(pProcesserSub->*fn)(tArg1, tArg2, tArg3);
	return true;
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return SyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return SyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1)
{
	return SyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncCallProcesser(uint uProcesserID, TFn fn)
{
	return SyncCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn)
{
	return SyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1)
{
	return SyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return SyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return SyncCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	CLockRead lock(_vQueue.GetMutex());
	return CallProcesserMap<TClass>(vMap, tKey,fn,tArg1, tArg2, tArg3);
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	CLockRead lock(_vQueue.GetMutex());
	return CallProcesserMap<TClass>(vMap, tKey, fn, tArg1, tArg2);
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1)
{
	CLockRead lock(_vQueue.GetMutex());
	return CallProcesserMap<TClass>(vMap, tKey, fn, tArg1);
}

template<typename TClass, typename TMap, typename TKey, typename TFn>
bool ISyncProcesserManager::SyncCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn)
{
	CLockRead lock(_vQueue.GetMutex());
	return CallProcesserMap<TClass>(vMap, tKey, fn);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	CLockRead lock(_vQueue.GetMutex());
	return ForEachCallProcesser<TClass>(fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	CLockRead lock(_vQueue.GetMutex());
	return ForEachCallProcesser<TClass>(fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn, TArg1& tArg1)
{
	CLockRead lock(_vQueue.GetMutex());
	return ForEachCallProcesser<TClass>(fn, tArg1);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncForEachCallProcesser(TFn fn)
{
	CLockRead lock(_vQueue.GetMutex());
	return ForEachCallProcesser<TClass>(fn);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncTryCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return SyncTryCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncTryCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return SyncTryCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncTryCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1)
{
	return SyncTryCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn, tArg1);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncTryCallProcesser(uint uProcesserID, TFn fn)
{
	return SyncTryCallProcesserMap<TClass>(&_vProcesser, uProcesserID, fn);
}

template<typename TClass, typename TFn>
bool ISyncProcesserManager::SyncTryCallProcesserSecondID(uint uSecondID, TFn fn)
{
	return SyncTryCallProcesserMap<TClass>(&_vSecond, uSecondID, fn);
}

template<typename TClass, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncTryCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1)
{
	return SyncTryCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncTryCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	return SyncTryCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1, tArg2);
}

template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncTryCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	return SyncTryCallProcesserMap<TClass>(&_vSecond, uSecondID, fn, tArg1, tArg2, tArg3);
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
bool ISyncProcesserManager::SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3)
{
	CLockRead lock(_vQueue.GetMutex(),true);
	if (!lock.IsLocked())return false;

	CallProcesserMap<TClass>(vMap, tKey, fn, tArg1, tArg2, tArg3);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
bool ISyncProcesserManager::SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2)
{
	CLockRead lock(_vQueue.GetMutex(), true);
	if (!lock.IsLocked())return false;

	CallProcesserMap<TClass>(vMap, tKey, fn, tArg1, tArg2);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
bool ISyncProcesserManager::SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn, TArg1& tArg1)
{
	CLockRead lock(_vQueue.GetMutex(), true);
	if (!lock.IsLocked())return false;

	CallProcesserMap<TClass>(vMap, tKey, fn, tArg1);
	return true;
}

template<typename TClass, typename TMap, typename TKey, typename TFn>
bool ISyncProcesserManager::SyncTryCallProcesserMap(TMap* vMap, const TKey& tKey, TFn fn)
{
	CLockRead lock(_vQueue.GetMutex(), true);
	if (!lock.IsLocked())return false;

	CallProcesserMap<TClass>(vMap, tKey, fn);
	return true;
}
NS_TOOL_FRAME_END
