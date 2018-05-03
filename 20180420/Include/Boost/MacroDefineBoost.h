#pragma once

#include <boost/tuple/tuple.hpp>
#include <boost/bind.hpp>
#include <boost/pool/pool.hpp>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/weak_ptr.hpp>
#include <boost/smart_ptr/enable_shared_from_this.hpp>

// #include <boost/asio.hpp>//����boost/asio.hpp ����ƽ̨����� ���ṩ

#include "LockMutex.h"

//����ָ�뻻����
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

//���û�������
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

//�����ߺ�������ʹ��BOOST��ſ�������

//BOOST���� http://www.boost.org/ ���� ��ѹ���� boost�ļ���(Windows����.7z,Linux/Mac����.tar.gz)
//ע:.7z��.tar.gz���ѹ�������ļ� ������һ����,���ܹ�ֱ�ӵ����ܲ��ܹ�����BOOST

//Linux	����
//���� ./bootstrap.sh
//���� ./bjam stage --toolset=gcc --with-filesystem --with-thread --with-regex --with-date_time --stagedir="../Lib"

//Windows����
//���� bootstrap.bat
//���� bjam.exe toolset=msvc-14.0 --build-type=complete --with-atomic --with-date_time --with-filesystem --with-thread --with-regex --with-chrono --build-type=complete
//VS2015:msvc-15.0 VS2015:msvc-14.0 VS2012:msvc-11.0 VS2010:msvc-10.0 VS2008: msvc-9.0 VS2003:msvc-7.1
//����64λ��Ҫ
//���� bjam.exe toolset=msvc-14.0 --build-type=complete --with-atomic --with-date_time --with-filesystem --with-thread --with-regex --with-chrono --build-type=complete address - model = 64 architecture = x86 

//Mac -PC ����
//���� ./bootstrap.sh
//���� ./bjam stage --toolset=darwin --with-filesystem --with-thread --with-regex --with-date_time --stagedir="../Lib"

//Mac -Ipad(Ipad���� �� ��ͨ��һ������ΪIPad/IPhone��ArmCPU�ܹ��ġ�)
//Mac -IPad - ģ���� ����
//���� ./bootstrap.sh
//���� ./bjam stage --toolset=darwin --with-filesystem --with-thread --with-regex --with-date_time --stagedir="../Lib" architecture=x86 target-os=iphone define=_LITTLE_ENDIAN

//Mac -Ipad - ���
//�ο���ַhttp://www.a-coding.com/2011/01/building-boost-for-ios.html
//����XCode�Ľ��������Ȼ�� ���롣