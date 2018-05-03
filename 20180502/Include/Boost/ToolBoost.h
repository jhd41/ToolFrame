#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_BOOST
#include "MacroDefineBoost.h"
#include "ApiBoost.h"

namespace ToolFrame{
	template<typename TSrc,typename TDes>
	bool		DynamicCast(boost::shared_ptr<TDes>& ptrDes,const boost::shared_ptr<TSrc>& ptrSrc);
	template<typename TDes, typename TSrc>
	TDes		DynamicCast(const boost::shared_ptr<TSrc>& ptrSrc);

	bool		IsEmail(const std::string& sAddress);

	template<typename T>
	bool		Delete(CSharePtr<T>& p);

	std::string	GetLocalIp();
	std::string	GetHostName();
};

template<typename T>
bool ToolFrame::Delete( CSharePtr<T>& p )
{
	if (!p)return false;

	p = CSharePtr<T>();
	return true;
}

template<typename TSrc,typename TDes>
bool ToolFrame::DynamicCast( boost::shared_ptr<TDes>& ptrDes,const boost::shared_ptr<TSrc>& ptrSrc )
{
	return ApiBoost::DynamicCast(ptrDes, ptrSrc);
}

template<typename TDes, typename TSrc>
TDes ToolFrame::DynamicCast(const boost::shared_ptr<TSrc>& ptrSrc)
{
	TDes pDes;
	if (!ApiBoost::DynamicCast(pDes, ptrSrc))return TDes();

	return pDes;
}

#endif
