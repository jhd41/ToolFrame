#pragma once

#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <boost/pool/pool.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>

// #include <boost/asio.hpp>//由于boost/asio.hpp 具有平台相关性 不提供

#include "LockMutex.h"

//共享指针换名字
#define CSharePtr		boost::shared_ptr
#define CWeakPtr		boost::weak_ptr		
#define CShareFromThis	boost::enable_shared_from_this

//shared_from_this()

#define MUTEX_BOOL_RW(ArgName) \
private:\
	volatile	bool			_b##ArgName;\
	mutable		CMutexReadWrite	_bMutex##ArgName;\
public:\
	bool				Is##ArgName()const{CLockRead lock(_bMutex##ArgName);return _b##ArgName;}\
	bool				Set##ArgName(bool bArg){CLockWrite lock(_bMutex##ArgName);if (_b##ArgName == bArg)return false; _b##ArgName = bArg; return true;}

#define MUTEX_INT_RW(ArgName) \
private:\
	volatile	int				_n##ArgName;\
	mutable		CMutexReadWrite	_nMutex##ArgName;\
public:\
	int					Get##ArgName()const{CLockRead lock(_nMutex##ArgName);return _n##ArgName;}\
	bool				Set##ArgName(int nArg){CLockWrite lock(_nMutex##ArgName);if (_n##ArgName == nArg)return false; _n##ArgName = nArg; return true;}\
	bool				Add##ArgName(int nArg){CLockWrite lock(_nMutex##ArgName);_n##ArgName += nArg; return true;}\
	bool				Remove##ArgName(int nArg){CLockWrite lock(_nMutex##ArgName);_n##ArgName -= nArg; return true;}\

//内置基本函数
NS_TOOL_FRAME_BEGIN
template<typename T>
bool SetPtr(boost::shared_ptr<T>& pDes,boost::shared_ptr<T> pSrc){
	if (pDes == pSrc)return false;
	pDes = pSrc;
	return true;
}

template<typename T>
bool SetPtr(boost::weak_ptr<T>& pDes,boost::weak_ptr<T> pSrc){
	if (pDes.lock() == pSrc.lock())return false;
	pDes = pSrc;
	return true;
}

template<typename T>
bool SetPtrNull(boost::shared_ptr<T>& ptr){
	if (!ptr)return false;
	ptr = boost::shared_ptr<T>();
	return true;
}

template<typename T>
bool SetPtrNull(boost::weak_ptr<T>& ptr){
	if (!ptr.lock())return false;
	ptr = boost::weak_ptr<T>();
	return true;
}

NS_TOOL_FRAME_END

//本工具函数必须使用BOOST库才可以运行

//BOOST官网 http://www.boost.org/ 下载 解压并打开 boost文件夹(Windows下载.7z,Linux/Mac下载.tar.gz)
//注:.7z和.tar.gz里解压出来的文件 并不是一样的,这能够直接导致能不能够编译BOOST

//Linux	编译
//运行 ./bootstrap.sh
//运行 ./bjam stage --toolset=gcc --with-filesystem --with-thread --with-regex --with-date_time --stagedir="../Lib"

//Windows编译
//运行 bootstrap.bat
//运行 bjam.exe toolset=msvc-14.0 --build-type=complete --with-atomic --with-date_time --with-filesystem --with-thread --with-regex --with-chrono --build-type=complete
//VS2015:msvc-15.0 VS2015:msvc-14.0 VS2012:msvc-11.0 VS2010:msvc-10.0 VS2008: msvc-9.0 VS2003:msvc-7.1
//编译64位需要
//运行 bjam.exe toolset=msvc-14.0 --build-type=complete --with-atomic --with-date_time --with-filesystem --with-thread --with-regex --with-chrono --build-type=complete address - model = 64 architecture = x86 

//Mac -PC 编译
//运行 ./bootstrap.sh
//运行 ./bjam stage --toolset=darwin --with-filesystem --with-thread --with-regex --with-date_time --stagedir="../Lib"

//Mac -Ipad(Ipad编译 和 普通不一样，因为IPad/IPhone是ArmCPU架构的。)
//Mac -IPad - 模拟器 编译
//运行 ./bootstrap.sh
//运行 ./bjam stage --toolset=darwin --with-filesystem --with-thread --with-regex --with-date_time --stagedir="../Lib" architecture=x86 target-os=iphone define=_LITTLE_ENDIAN

//Mac -Ipad - 真机
//参考网址http://www.a-coding.com/2011/01/building-boost-for-ios.html
//下载XCode的解决方案。然后 编译。