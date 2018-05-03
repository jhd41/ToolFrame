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
	virtual size_t GetProcesserSize()const;			//��ȡ������С
	virtual size_t GetSecondSize()const;			//��ȡ�μ���С
	virtual size_t GetQueueSize()const;				//��ȡ���г���
	virtual size_t GetVaildCount()const;			//��ȡ��Ч�û�����
	virtual size_t GetNormalCount()const;			//��ȡ�����û���

	//������
public:
	virtual bool DebugCheck();

public:
	//��������
	template<typename TClass, typename TFn>
	bool SyncCallProcesser(uint uProcesserID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncCallProcesser(uint uProcesserID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//���ôμ�
	template<typename TClass, typename TFn>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncCallProcesserSecondID(uint uSecondID, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//����
	template<typename TClass, typename TFn>
	bool SyncForEachCallProcesser(TFn fn);
	template<typename TClass, typename TFn, typename TArg1>
	bool SyncForEachCallProcesser(TFn fn, TArg1& tArg1);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2>
	bool SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncForEachCallProcesser(TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);
protected:
	//�ڲ�ʵ�ʵ���
	template<typename TClass,typename TMap, typename TKey, typename TFn>
	bool SyncCallProcesserMap(TMap& vMap,const TKey& tKey, TFn fn);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1>
	bool SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2>
	bool SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2);
	template<typename TClass, typename TMap, typename TKey, typename TFn, typename TArg1, typename TArg2, typename TArg3>
	bool SyncCallProcesserMap(TMap& vMap, const TKey& tKey, TFn fn, TArg1& tArg1, TArg2& tArg2, TArg3& tArg3);

	//�첽�������
public:
	virtual bool ReqOperate(ISyncProcesserPtr pProcesser);
	virtual bool ReqDelete(ISyncProcesserPtr pProcesser);
	virtual bool ReqInsertSecond(uint uSecondID, ISyncProcesserPtr pProcesser);
	virtual bool ReqRemoveSecond(uint uSecondID);

	//��������
protected:
	virtual CMutexReadWrite& GetMutex()const;
	virtual bool AutoInsertProcesser(ISyncProcesserPtr pProcesser);//��ӵ�ӳ�������дμ� Ҳһ������
	virtual bool AutoRemoveProcesser(ISyncProcesserPtr pProcesser);//�Ƴ�ӳ�������дμ� Ҳһ���Ƴ�
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

	//�ڲ����� ������Ҫ����
public:
	virtual bool SyncMarkNormal();
	virtual bool SyncClearNormal();
	virtual bool SyncMarkVaild();
	virtual bool SyncClearVaild();
	virtual bool SyncCalState(uint& uTotal, uint& uVaild, uint& uNormal, uint& uQueue, uint& uDelete, uint& uPerpairing,uint& uCache) const;//ͳ�ƻ����״̬(��������Ч���������� ������ ������)
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
	MapSyncProcesser		_vProcesser;//����ӳ���
	MapSyncProcesser		_vSecond;	//�μ�ӳ���

	CIDMakerUint			_xMaker;		//����ID������
	CIDMakerUint			_xMakerSecond;	//�μ�ID������

	CCalCounter				_uVaild;			//��Ч��
	CCalCounter				_uNormal;			//������

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

