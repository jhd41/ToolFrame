#pragma once
#include "Macro.h"
#include "MacroDefineBoost.h"
#include "ToolStd.h"

//ID������ �̰߳�ȫ
//����һ����Ϊ0��ID,������ID����
NS_TOOL_FRAME_BEGIN

template<typename TIdType>
class TIDMaker
{
	//�̰߳�ȫ
public:
	bool SetIDRange(TIdType nMinID,TIdType nMaxID);	//����ID��Χ

	TIdType MakeID();
	template <typename TKey,typename TValue>
	TIdType MakeID(const std::map<TKey,TValue>& vIDs);

	template <typename TValue>
	TIdType MakeID(const std::set<TValue>& vIDs);

	template <typename TKey,typename TValue>
	bool IsFull(const std::map<TKey,TValue>& vIDs)const;

	template <typename TValue>
	bool IsFull(const std::set<TValue>& vIDs)const;

	TIdType SetNextID(TIdType nNextID);
	TIdType	GetNextID()const;

	//����
private:
	TIdType _MakeID();

	template <typename TKey,typename TValue>
	bool _IsFull(const std::map<TKey,TValue>& vIDs)const;

	template <typename TValue>
	bool _IsFull(const std::set<TValue>& vIDs)const;
public:
	TIDMaker(void);
	virtual ~TIDMaker(void);
private:
	TIdType _nNextID;//�¸�ID��
private:
	CFIELD_REF(TIdType,MinID,t);
	CFIELD_REF(TIdType,MaxID,t);
	
	mutable CMutexReadWrite _mutex;
};
template<typename TIdType>
TIdType TIDMaker<TIdType>::_MakeID()
{
	if (_nNextID > GetMaxID())_nNextID=GetMinID();
	return _nNextID++;
}

template<typename TIdType>
template <typename TValue>
bool TIDMaker<TIdType>::_IsFull( const std::set<TValue>& vIDs ) const
{
	return (TIdType)vIDs.size() >= GetMaxID() - GetMinID() + 1;
}

template<typename TIdType>
template <typename TKey,typename TValue>
bool TIDMaker<TIdType>::_IsFull( const std::map<TKey,TValue>& vIDs ) const
{
	return (TIdType)vIDs.size() >= GetMaxID() - GetMinID() + 1;
}

template<typename TIdType>
TIdType TIDMaker<TIdType>::SetNextID( TIdType nNextID )
{
	CLockWrite lock(_mutex);
	_nNextID = nNextID;
	return _nNextID;
}

template<typename TIdType>
TIdType TIDMaker<TIdType>::GetNextID() const
{
	CLockRead lock(_mutex);
	return _nNextID;
}

template<typename TIdType>
TIDMaker<TIdType>::TIDMaker( void )
{
	SetIDRange(1,ToolFrame::GetLimitMax(_nNextID));
	_nNextID = GetMinID();
}

template<typename TIdType>
TIDMaker<TIdType>::~TIDMaker( void )
{

}

template<typename TIdType>
bool TIDMaker<TIdType>::SetIDRange( TIdType nMinID,TIdType nMaxID )
{
	if (nMinID > nMaxID)return false;

	CLockWrite lock(_mutex);

	SetMinID(nMinID);
	SetMaxID(nMaxID);

	return true;
}

template<typename TIdType>
TIdType TIDMaker<TIdType>::MakeID()
{
	CLockWrite lock(_mutex);
	return _MakeID();
}

template <typename TIdType>
template <typename TKey,typename TValue>
bool TIDMaker<TIdType>::IsFull( const std::map<TKey,TValue>& vIDs )const
{
	CLockRead lock(_mutex);
	return _IsFull(vIDs);
}

template <typename TIdType>
template <typename TKey,typename TValue>
TIdType TIDMaker<TIdType>::MakeID( const std::map<TKey,TValue>& vIDs )
{
	CLockWrite lock(_mutex);
	
	if (_IsFull(vIDs))return INVALID_ID;

	TIdType nReturnID = _MakeID();
	while(ToolFrame::IsHasKey(vIDs,nReturnID))
		nReturnID = _MakeID();

	return nReturnID;
}

template <typename TIdType>
template <typename TValue>
bool TIDMaker<TIdType>::IsFull( const std::set<TValue>& vIDs )const
{
	CLockRead lock(_mutex);
	return _IsFull(vIDs);
}

template <typename TIdType>
template <typename TValue>
TIdType TIDMaker<TIdType>::MakeID( const std::set<TValue>& vIDs )
{
	CLockWrite lock(_mutex);
	if (_IsFull(vIDs))return INVALID_ID;

	TIdType nReturnID = _MakeID();
	while(ToolFrame::IsHasValue(vIDs,nReturnID))
		nReturnID = _MakeID();

	return nReturnID;
}

typedef TIDMaker<int>		CIDMakerInt;
typedef TIDMaker<uint>		CIDMakerUint;
typedef TIDMaker<uint32>	CIDMakerUint32;
typedef TIDMaker<size_t>	CIDMakerSize;

NS_TOOL_FRAME_END
