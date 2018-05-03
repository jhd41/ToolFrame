#pragma once

//�����ߺ�����������ƽ̨��ִ��
#include "Macro.h"

#include <algorithm>
#include <assert.h>
#include <complex>
#include <limits>
#include <typeinfo>

//Ϊ�˼���cocos2d�Ƚ���ѧ��include��ͷ��
#undef max
#undef min

//˼·����: key:�� value:ֵ index:���� ʾ��: vector<value> set<value> map<key,value>

namespace ToolFrame
{
	//ת�� - ��������Ԫ֮��ת��(Ϊ��ת����ȫ,ͨ������������ʵ��,����ʹ��ģ���ԭ���� ��ģ��̫ͨ��)
	template<typename T,typename K>
	bool ToValue(const T& tSrc,				K& tDes);

	bool ToValue(const bool& bSrc,			bool& bDes);
	bool ToValue(const char& bSrc,			bool& bDes);
	bool ToValue(const signed char& bSrc,	bool& bDes);
	bool ToValue(const signed short& bSrc,	bool& bDes);
	bool ToValue(const signed long& bSrc,	bool& bDes);
	bool ToValue(const signed int& bSrc,	bool& bDes);
	bool ToValue(const unsigned char& bSrc,	bool& bDes);
	bool ToValue(const unsigned short& bSrc,bool& bDes);
	bool ToValue(const unsigned long& bSrc,	bool& bDes);
	bool ToValue(const unsigned int& bSrc,	bool& bDes);
	bool ToValue(const float& nSrc,			bool& nDes);
	bool ToValue(const double& nSrc,		bool& nDes);

	bool ToValue(const bool& nSrc,			signed char& nDes);
	bool ToValue(const char& nSrc,			signed char& nDes);
	bool ToValue(const signed char& nSrc,	signed char& nDes);
	bool ToValue(const signed short& nSrc,	signed char& nDes);
	bool ToValue(const signed long& nSrc,	signed char& nDes);
	bool ToValue(const signed int& nSrc,	signed char& nDes);
	bool ToValue(const unsigned char& nSrc,	signed char& nDes);
	bool ToValue(const unsigned short& nSrc,signed char& nDes);
	bool ToValue(const unsigned long& nSrc,	signed char& nDes);
	bool ToValue(const unsigned int& nSrc,	signed char& nDes);
	bool ToValue(const float& nSrc,			signed char& nDes);
	bool ToValue(const double& nSrc,		signed char& nDes);

	bool ToValue(const bool& nSrc,			char& nDes);
	bool ToValue(const char& nSrc,			char& nDes);
	bool ToValue(const signed char& nSrc,	char& nDes);
	bool ToValue(const signed short& nSrc,	char& nDes);
	bool ToValue(const signed long& nSrc,	char& nDes);
	bool ToValue(const signed int& nSrc,	char& nDes);
	bool ToValue(const unsigned char& nSrc,	char& nDes);
	bool ToValue(const unsigned short& nSrc,char& nDes);
	bool ToValue(const unsigned long& nSrc,	char& nDes);
	bool ToValue(const unsigned int& nSrc,	char& nDes);
	bool ToValue(const float& nSrc,			char& nDes);
	bool ToValue(const double& nSrc,		char& nDes);

	bool ToValue(const bool& nSrc,			short& nDes);
	bool ToValue(const char& nSrc,			short& nDes);
	bool ToValue(const signed char& nSrc,	short& nDes);
	bool ToValue(const signed short& nSrc,	short& nDes);
	bool ToValue(const signed long& nSrc,	short& nDes);
	bool ToValue(const signed int& nSrc,	short& nDes);
	bool ToValue(const unsigned char& nSrc,	short& nDes);
	bool ToValue(const unsigned short& nSrc,short& nDes);
	bool ToValue(const unsigned long& nSrc,	short& nDes);
	bool ToValue(const unsigned int& nSrc,	short& nDes);
	bool ToValue(const float& nSrc,			short& nDes);
	bool ToValue(const double& nSrc,		short& nDes);

	bool ToValue(const bool& nSrc,			long& nDes);
	bool ToValue(const char& nSrc,			long& nDes);
	bool ToValue(const signed char& nSrc,	long& nDes);
	bool ToValue(const signed short& nSrc,	long& nDes);
	bool ToValue(const signed long& nSrc,	long& nDes);
	bool ToValue(const signed int& nSrc,	long& nDes);
	bool ToValue(const unsigned char& nSrc,	long& nDes);
	bool ToValue(const unsigned short& nSrc,long& nDes);
	bool ToValue(const unsigned long& nSrc,	long& nDes);
	bool ToValue(const unsigned int& nSrc,	long& nDes);
	bool ToValue(const float& nSrc,			long& nDes);
	bool ToValue(const double& nSrc,		long& nDes);

	bool ToValue(const bool& nSrc,			int& nDes);
	bool ToValue(const char& nSrc,			int& nDes);
	bool ToValue(const signed char& nSrc,	int& nDes);
	bool ToValue(const signed short& nSrc,	int& nDes);
	bool ToValue(const signed long& nSrc,	int& nDes);
	bool ToValue(const signed int& nSrc,	int& nDes);
	bool ToValue(const unsigned char& nSrc,	int& nDes);
	bool ToValue(const unsigned short& nSrc,int& nDes);
	bool ToValue(const unsigned long& nSrc,	int& nDes);
	bool ToValue(const unsigned int& nSrc,	int& nDes);
	bool ToValue(const float& nSrc,			int& nDes);
	bool ToValue(const double& nSrc,		int& nDes);

	bool ToValue(const bool& nSrc,			unsigned char& nDes);
	bool ToValue(const char& nSrc,			unsigned char& nDes);
	bool ToValue(const signed char& nSrc,	unsigned char& nDes);
	bool ToValue(const signed short& nSrc,	unsigned char& nDes);
	bool ToValue(const signed long& nSrc,	unsigned char& nDes);
	bool ToValue(const signed int& nSrc,	unsigned char& nDes);
	bool ToValue(const unsigned char& nSrc,	unsigned char& nDes);
	bool ToValue(const unsigned short& nSrc,unsigned char& nDes);
	bool ToValue(const unsigned long& nSrc,	unsigned char& nDes);
	bool ToValue(const unsigned int& nSrc,	unsigned char& nDes);
	bool ToValue(const float& nSrc,			unsigned char& nDes);
	bool ToValue(const double& nSrc,		unsigned char& nDes);

	bool ToValue(const bool& nSrc,			unsigned short& nDes);
	bool ToValue(const char& nSrc,			unsigned short& nDes);
	bool ToValue(const signed char& nSrc,	unsigned short& nDes);
	bool ToValue(const signed short& nSrc,	unsigned short& nDes);
	bool ToValue(const signed long& nSrc,	unsigned short& nDes);
	bool ToValue(const signed int& nSrc,	unsigned short& nDes);
	bool ToValue(const unsigned char& nSrc,	unsigned short& nDes);
	bool ToValue(const unsigned short& nSrc,unsigned short& nDes);
	bool ToValue(const unsigned long& nSrc,	unsigned short& nDes);
	bool ToValue(const unsigned int& nSrc,	unsigned short& nDes);
	bool ToValue(const float& nSrc,			unsigned short& nDes);
	bool ToValue(const double& nSrc,		unsigned short& nDes);

	bool ToValue(const bool& nSrc,			unsigned long& nDes);
	bool ToValue(const char& nSrc,			unsigned long& nDes);
	bool ToValue(const signed char& nSrc,	unsigned long& nDes);
	bool ToValue(const signed short& nSrc,	unsigned long& nDes);
	bool ToValue(const signed long& nSrc,	unsigned long& nDes);
	bool ToValue(const signed int& nSrc,	unsigned long& nDes);
	bool ToValue(const unsigned char& nSrc,	unsigned long& nDes);
	bool ToValue(const unsigned short& nSrc,unsigned long& nDes);
	bool ToValue(const unsigned long& nSrc,	unsigned long& nDes);
	bool ToValue(const unsigned int& nSrc,	unsigned long& nDes);
	bool ToValue(const float& nSrc,			unsigned long& nDes);
	bool ToValue(const double& nSrc,		unsigned long& nDes);

	bool ToValue(const bool& nSrc,			unsigned int& nDes);
	bool ToValue(const char& nSrc,			unsigned int& nDes);
	bool ToValue(const signed char& nSrc,	unsigned int& nDes);
	bool ToValue(const signed short& nSrc,	unsigned int& nDes);
	bool ToValue(const signed long& nSrc,	unsigned int& nDes);
	bool ToValue(const signed int& nSrc,	unsigned int& nDes);
	bool ToValue(const unsigned char& nSrc,	unsigned int& nDes);
	bool ToValue(const unsigned short& nSrc,unsigned int& nDes);
	bool ToValue(const unsigned long& nSrc,	unsigned int& nDes);
	bool ToValue(const unsigned int& nSrc,	unsigned int& nDes);
	bool ToValue(const float& nSrc,			unsigned int& nDes);
	bool ToValue(const double& nSrc,		unsigned int& nDes);

	bool ToValue(const std::string& sSrc,	char* tDes);
	bool ToValue(const std::string& sSrc,	char* szDes,UINT uLength);
	bool ToValue(const char* szSrc,			char* szDes,UINT uLength);

	//ת�� - String to Value (֧��2����,8����,10����,16���Ƹ�ʽ,С��)
	bool ToValue(const std::string& sSrc,	bool& tDes);
	bool ToValue(const std::string& sSrc,	float& tDes);
	bool ToValue(const std::string& sSrc,	double& tDes);
	bool ToValue(const std::string& sSrc,	char& tDes);
	template<typename T>
	bool ToValue(const std::string& sSrc,	T& nValue);
	template <typename T>
	bool ToValue(const std::string* sSrc,	T& tDes);//��Ӷ��ַ���ָ��֧��
	template<typename T>
	bool ToValue(const char* szSrc,			T& nValue);

	//ת�� - Value to String
	bool ToValue(const std::string& sSrc,	std::string& sDes);
	bool ToValue(const char* szSrc,			std::string& sDes);
	bool ToValue(const std::string* sSrc,	std::string& sDes);


	//ת�� - �ַ��� - ����֧��(����֤ A->B B->A ֮��A���ܹ�һ��,���뱣��һ��,������,ʹ�����л�˼·ȥ��)
	template<typename T>
	bool ToValue(const std::string& tSrc,std::vector<T>& tDes,const std::string& sSp=",");
	template<typename T>
	bool ToValue(const std::string& tSrc,std::set<T>& tDes,const std::string& sSp=",");
	template<typename T>
	bool ToValue(const std::vector<T>& vSrc,std::string& sDes,const std::string& sSp=",");
	template<typename T>
	bool ToValue(const std::list<T>& vSrc,std::string& sDes,const std::string& sSp=",");
	template<typename T>
	bool ToValue(const std::set<T>& vSrc,std::string& sDes,const std::string& sSp=",");
	template<typename T,typename K>
	bool ToValue(const std::string& tSrc,std::map<T,K>& tDes,const std::string& sSpLine=" ",const std::string& sSpKeyValue=":");
	template<typename T,typename K>
	bool ToValue(const std::map<T,K>& tSrc, std::string& tDes,const std::string& sSpLine=" ",const std::string& sSpKeyValue=":");

	//ת�� - ��������Ԫ֮��ת�� - ����֧��(��Ҫ����Ĭ�Ϲ��캯��,ʵ�ֿ������캯��)
	template <typename T,typename K>
	bool ToValue(const std::vector<T>& vSrc,std::vector<K>& vDes);
	template <typename T,typename K>
	bool ToValue(const std::vector<T>& vSrc,std::list<K>& vDes);
	template <typename T,typename K>
	bool ToValue(const std::vector<T>& vSrc,std::set<K>& vDes);

	template <typename T,typename K>
	bool ToValue(const std::list<T>& vSrc,std::vector<K>& vDes);
	template <typename T,typename K>
	bool ToValue(const std::list<T>& vSrc,std::list<K>& vDes);
	template <typename T,typename K>
	bool ToValue(const std::list<T>& vSrc,std::set<K>& vDes);

	template <typename T,typename K>
	bool ToValue(const std::set<T>& vSrc,	std::vector<K>& vDes);
	template <typename T,typename K>
	bool ToValue(const std::set<T>& vSrc,	std::list<K>& vDes);
	template <typename T,typename K>
	bool ToValue(const std::set<T>& vSrc,	std::set<K>& vDes);
	template <typename TSrcKey,typename TSrcValue,typename TDesKey,typename TDesValue>
	bool ToValue(const std::map<TSrcKey,TSrcValue>& vSrc,std::map<TDesKey,TDesValue>& vDes);

	//ת�� - ���ַ���֮��ת��
	template<typename T>
	bool ToValue(const T& tSrc,std::string& sDes,int nWidth = 0,char cFill = ' ');
	template<typename T>
	bool ToValue(const T& tSrc,std::string* sDes,int nWidth = 0,char cFill = ' ');

	//ת�� - 2����ת������
	template<typename T>
	bool ToValueBin(const std::string& sSrc,T& tValue);

	//ת�� - ת����������(��ֵ��Χ)
	template<typename T>
	bool ToValueRange(const double& tSrc,T& tDes,double fMin,double fMax);

	//ת�� - ����
	int ToInteger(float fValue);
	int ToInteger(double fValue);

	//ת�� - (Value to String) ���� ToValue������д
	template <typename T>
	std::string			ToString(const T& tValue);

	const std::string&	ToString(const std::string& sValue);
	std::string			ToString(const char* szString);
	template <typename T>
	std::string			ToString(const T& tValue,const std::string& sSp/*=','*/);

	//�ж��Ƿ�ΪĿ��������
	template<typename T,typename TArg>
	bool IsTargetClass(TArg* pArg);

	//ת�� - ���� ת �ַ���
	template <typename T>
	std::string ArrayToString(T* tArray,int nLength);

	//ת�� - ��������Ԫ֮�侲̬ת��(ǿת)
	template <typename T>
	bool		StaticCast(T& tDes,const T& tSrc);
	template <typename T,typename K>
	bool		StaticCast(K& tDes,const T& tSrc);
	template <typename T>
	bool		StaticCast(bool& bDes,const T& tSrc);
	bool		StaticCast(bool& bDes,const bool& tSrc);

	template <typename T, typename K>
	T			StaticCast(const K& tSrc);

	//ת�� - ��������Ԫ֮�䶯̬ת��(����ת���ɸ���,��Ҫ��RTTI) 
	template <typename T,typename K>
	bool		DynamicCast(K& tDes,const T& tSrc);

	template <typename T, typename K>
	T			DynamicCast(const K& tSrc);

	//ת�� - ����/���� ��ת
	template<typename T>
	T&			ConstCast(const T& t);
	template<typename T>
	const T&	ConstCast(T& t);
	template<typename T>
	T*			ConstCast(const T* t);
	template<typename T>
	const T*	ConstCast(T* t);

	//�ַ�������
	template <typename T>
	void SafeStringCopy(const std::string& sSrc,T& szT);

	//�ڴ濽��
	template <typename T,typename K>
	void SafeCopy( T& tDes,const K& tSrc );

	//�жϺ���
	bool IsBool(const std::string& sSrc);
	bool IsFloat(const std::string& sSrc);
	bool IsIP( const std::string& sValue );
	bool IsInClosedInterval(const std::string& sSrc,int nBegin,int nEnd);

	//����
	template<typename T>
	T*	CreateByPtr(T*);

	//�ͷ� - delete
	template <typename T>
	void Delete(T*& pT,bool bGroup = false);

	//�ͷ� - drop(���ü�����һ)
	template <typename T>
	void SafeDrop(T* pT);
	template <typename Tkey,typename Tvalue>
	void SafeDrop(std::map<Tkey,Tvalue*>& vMap);

	//���� - ����
	template<typename T,typename K>
	bool Insert( std::set<T>& vSet,const K& tValue);
	template<typename T,typename K>
	bool Insert( std::multiset<T>& vSet,const K& tValue);
	template<typename T,typename K>
	bool Insert( std::vector<T>& vVct,const K& tValue);
	template<typename T,typename K>
	bool Insert( std::list<T>& vVct,const K& tValue );

	template<typename K>
	bool Insert( std::map<int,K>& vMap,int tKey,const K& kValue);
	template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
	bool Insert( std::map<TKey,TValue>& vMap,const TKeyInsert& tKey,const TValueInsert& kValue);
	template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
	bool Insert( std::multimap<TKey,TValue>& vMap,const TKeyInsert& tKey,const TValueInsert& kValue);

	bool Insert( VectorInt& vVct,int tValue );
	bool Insert( ListInt& vVct,int tValue );
	bool Insert( SetInt& vSet,int tValue);
	bool Insert( MultiSetInt& vSet,int tValue);
	bool Insert( MapIntInt& vMap,int nKey,int nValue);

	//���� - ����(��֤Ψһ��)
	template<typename T, typename K>
	bool InsertUnique(std::vector<T>& vVct, const K& tValue);
	template<typename T, typename K>
	bool InsertUnique(std::list<T>& vVct, const K& tValue);

	//���� - ���� - ���� ���������������������
	template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
	bool InsertVector( std::map<TKey,std::vector<TValue> >& vMap,const TKeyInsert& tKey,const TValueInsert& tValue);
	template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
	bool InsertVector( std::map<TKey,std::list<TValue> >& vMap,const TKeyInsert& tKey,const TValueInsert& tValue);
	
	//���� - ���� - �ַ���
	template<typename T>
	bool InsertString( VectorString& vString,const T& t);
	bool InsertString( MapIntString& vMap,int nKey,const std::string& sValue);
	template<typename T>
	bool InsertString( MapIntString& vMap,int nKey,const T& tValue);
	template<typename T,typename K>
	bool InsertString( MapIntString& vMap,const T& tKey,const K& tValue);
	
	bool InsertString( MapStringString& vMap,const std::string& sKey,int nValue,int nWidth=0,char chFill='0');
	template<typename T,typename K>
	bool InsertString( MapStringString& vMap,const T& tKey,const K& tValue);

	//���� - ���� - ������Ԫ��֮ǰ
	template<typename T,typename Arg>
	bool InsertByIndex( std::vector<T>& v,const Arg& tArg,int nIndex,bool bBack=false);

	//���� - ���� - ������ ���������ɵĽڵ�ĵ�����
	template<typename T>
	typename std::list<T>::iterator Insert(T& tValue, std::list<T>& vSrc, typename std::list<T>::iterator& itr, bool bFront = false);

	//���� - ���� - ָ��λ�ò��� ���� �²��� �ĵ�һ��Ԫ�صĵ�����
	template<typename T>
	typename std::vector<T>::iterator Insert(std::vector<T>& vSrc, typename std::vector<T>::iterator itr, const std::vector<T>& vVct);

	//���� - ���� - ָ��λ�ò��뷵�� �²��� �ĵ�һ��Ԫ�صĵ�����
	template<typename T>
	typename std::list<T>::iterator  Insert(std::list<T>& vSrc, typename std::list<T>::iterator itr, const std::list<T>& vVct);

	//���� - �滻
	template<typename T>
	typename std::vector<T>::iterator   Replace(std::vector<T>& vSrc, typename std::vector<T>::iterator itr, const T& t);

	//���� - �滻
	template<typename T>
	typename std::vector<T>::iterator   Replace(std::vector<T>& vSrc, typename std::vector<T>::iterator itr, const std::vector<T>& vVct);

	//���� - �滻
	template<typename T>
	typename std::list<T>::iterator   Replace(std::list<T>& vSrc, typename std::list<T>::iterator itr, const T& t);

	//���� - �滻
	template<typename T>
	typename std::list<T>::iterator   Replace(std::list<T>& vSrc, typename std::list<T>::iterator itr, const std::list<T>& vVct);

	//���� - ����
	template<typename T>
	bool EraseItr(std::list<T>& vSrc, typename std::list<T>::iterator itrBegin, typename std::list<T>::iterator itrEnd);

	//���� - ����������
	template<typename T>
	bool EraseCloseInterval(std::list<T>& vSrc, typename std::list<T>::iterator itrBegin, typename std::list<T>::iterator itrEnd);

	//���� - ����������
	template<typename T>
	bool EraseOpenInterval(std::list<T>& vSrc, typename std::list<T>::iterator itrBegin, typename std::list<T>::iterator itrEnd);

	//���� - ��ȫ����
	template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
	bool SafeInsert( std::map<TKey,TValue>& vMap,const TKeyInsert& tKey,const TValueInsert& kValue);

	//���� - ��ȡֵ(ָ����ֵ��һ�֡�Ҫʹ��ָ����ʹ�� typedef int* IntPtr��ʽ����ָ�����͡�)
	template<typename TKey,typename TValue,typename Arg>
	TValue&				GetValueByKey(const std::map<TKey,TValue>& vMap,const Arg& tKey );//���û���ҵ�,������

	template<typename TKey,typename TValue,typename Arg>
	const TValue&		GetValueByKey(const std::map<TKey,TValue>& vMap,const Arg& tKey,const TValue& tDefault );//���û�ҵ�����tDefault

	template<typename TKey,typename TValue,typename Arg>
	TValue&				GetValueByKey(const std::map<TKey,TValue>& vMap,const Arg& tKey,TValue& tDefault );//���û�ҵ�����tDefault
	
	template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
	TValue				GetValueByKey(const std::map<TKey,TValue>& vMap,const Arg& tKey,ArgDefault tDefault );//���û�ҵ�����tDefault

	template<typename TKey,typename Arg>
	const std::string&	GetValueByKey(const std::map<TKey,std::string>& vMap,const Arg& tKey,const std::string& tDefault );//���û�ҵ�����tDefault

	template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
	TValue*				GetValueByKey(const std::map<TKey,TValue*>& vMap,const Arg& tKey,ArgDefault tDefault );//���û�ҵ�����tDefault

	template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
	TValue&				GetValueByKey(std::multimap<TKey,TValue>& vSrc,const Arg& tKey,ArgDefault& tValue);
	template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
	const TValue&		GetValueByKey(const std::multimap<TKey,TValue>& vSrc,const Arg& tKey,const ArgDefault& tValue);

	template<typename TKey,typename TValue,typename Arg>
	TValue&				GetValueByKeyForce(std::map<TKey,TValue>& vMap,const Arg& tKey);//ǿ�ƻ�ȡֵ ���û�ҵ��ڲ�����TValue(),������������������

	//���� - ��ȡֵ��ָ��
	template<typename TKey>
	TKey*				GetValuePtrByKey(const std::set<TKey>& v,const TKey& tKey);

	template<typename TKey,typename TValue,typename Arg>
	TValue*				GetValuePtrByKey(const std::map<TKey,TValue>& vMap,const Arg& tKey);//���û�ҵ����ؿ�
	template<typename TKey,typename TValue,typename Arg>
	TValue*				GetValuePtrByKey(const std::multimap<TKey,TValue>& vSrc,const Arg& tKey );

	//���� - ��ȡָ��
	template <typename Tkey,typename ValuePtr,typename TkeyArg>
	ValuePtr GetPtrValueByKey(const std::map<Tkey,ValuePtr>& vMap,const TkeyArg& tKey);
	template <typename Tkey,typename ValuePtr,typename TKeyInsert>//�ṩ�˿չ��캯���Ĵ���
	ValuePtr GetPtrValueByKey(std::map<Tkey,ValuePtr>& vMap,TKeyInsert& tKey,bool bCreate);

	//���� - ��ȡָ��
	template <typename T>
	T		GetPtrValue(const std::vector<T>& vVct,typename std::vector<T>::iterator itr);
	template <typename T>
	T		GetPtrValue(const std::list<T>& vVct,typename std::list<T>::iterator itr);
	template <typename T>
	T		GetPtrValue(const std::set<T>& vVct,typename std::set<T>::iterator itr);
	template <typename Key,typename Value>
	Value	GetPtrValue(const std::map<Key,Value>& vVct,typename std::map<Key,Value>::iterator itr,bool bKey = false);

	//���� - ��ȡָ��-����
	template <typename T>
	const T		GetPtrValue(const std::vector<T>& vVct,typename std::vector<T>::const_iterator itr);
	template <typename T>
	const T		GetPtrValue(const std::list<T>& vVct,typename std::list<T>::const_iterator itr);
	template <typename T>
	const T		GetPtrValue(const std::set<T>& vVct,typename std::set<T>::const_iterator itr);
	template <typename Key,typename Value>
	const Value	GetPtrValue(const std::map<Key,Value>& vVct,typename std::map<Key,Value>::const_iterator itr,bool bKey = false);

	//���� - ��ȡֵ -��ȡָ��λ��Ԫ��ֵ
	template <typename Tvalue>
	Tvalue&	GetValueByIndex(const std::vector<Tvalue>& vSrc,	int nIndex);
	template <typename Tvalue>
	Tvalue&	GetValueByIndex(const std::list<Tvalue>& vSrc,		int nIndex);
	template <typename Tvalue>
	Tvalue&	GetValueByIndex(const std::set<Tvalue>& vSrc,		int nIndex);
	template <typename Tkey,typename Tvalue>
	Tvalue&	GetValueByIndex(const std::map<Tkey,Tvalue>& vSrc,	int nIndex);

	template <typename Tvalue>
	const Tvalue&	GetValueByIndex(const std::vector<Tvalue>& vSrc,	int nIndex,const Tvalue& tValue);
	template <typename Tvalue>
	const Tvalue&	GetValueByIndex(const std::list<Tvalue>& vSrc,		int nIndex,const Tvalue& tValue);
	template <typename Tvalue>
	const Tvalue&	GetValueByIndex(const std::set<Tvalue>& vSrc,		int nIndex,const Tvalue& tValue);
	template <typename Tkey,typename Tvalue>
	const Tvalue&	GetValueByIndex(const std::map<Tkey,Tvalue>& vSrc,	int nIndex,const Tvalue& tValue);

	//���� - ��ȡֵ��ָ��
	template <typename Tvalue>
	Tvalue*	GetValuePtrByIndex(const std::vector<Tvalue>& vSrc, int nIndex);

	//���� - ��ȡֵ ��ȡָ��λ��ָ��
	template <typename T>
	T	GetPtrValueByIndex(const std::vector<T>& vSrc, int nIndex);
	template <typename T>
	T	GetPtrValueByIndex(const std::list<T>& vSrc, int nIndex);
	template <typename T,typename Key>
	T	GetPtrValueByIndex(const std::map<Key,T>& vSrc, int nIndex);

	//���� - ��ȡ������
	template<typename value>
	typename std::set<value>::iterator		GetItrByValue(std::set<value>& vSrc,const value& tValue);
	template<typename value>
	typename std::vector<value>::iterator	GetItrByValue(std::vector<value>& vSrc,const value& tValue);
	template<typename value>
	typename std::list<value>::iterator		GetItrByValue(std::list<value>& vSrc,const value& tValue);
	template<typename key,typename value>
	typename std::map<key,value>::iterator	GetItrByValue(std::map<key,value>& vSrc,const value& tValue);

	//���� - ��ȡ������ - ����
	template<typename key,typename value>
	typename std::map<key,value>::const_iterator GetItrByValue(const std::map<key,value>& vSrc,const value& tValue);

	//���� - ��ȡֵ -��ȡ����N��Ԫ��(˳����Դ����һ��)
	template<typename T>
	int GetValueBySeq(std::vector<T>& vDes,const std::vector<T>& vSrc,int nNum,bool bFront = true);

	//���� - ��ȡֵ -��ȡ�������е�ֵ
	template<typename T>
	bool GetValuesByItr(std::list<T>& vDes,std::list<T>& vSrc,typename std::list<T>::iterator& itr);
	template<typename T>
	bool GetValuesByItr(std::list<T>& vDes,std::list<T>& vSrc,typename std::list<T>::iterator itrBegin,typename std::list<T>::iterator itrEnd,bool bKeepBegin=true,bool bKeepEnd=false);

	//���� - ����
	template<typename T>
	bool IsVaildIndex(const std::vector<T>& vSrc,int nIndex);
	template<typename T>
	bool IsVaildIndex(const std::list<T>& vSrc,int nIndex);
	template<typename TKey,typename TValue>
	bool IsVaildIndex(const std::map<TKey,TValue>& vSrc,int nIndex);

	//���� - ��ȡ - ���Ԫ������������λ�� (��Чֵ-1)
	template<typename T,typename TArg>
	int GetIndexByValue(const std::vector<T>& vDes,const TArg& tValue);

	//���� - ��ȡ - ���Ԫ�����ڵ�Key
	template<typename T,typename K,typename Value>
	const T& GetKeyByValue(const std::map<T,K>& vMap,const Value& tValue,const T& tDefault);

	//���� - ��ȡ - ��ȡ����Key
	template<typename T,typename K,typename Value>
	const T& GetKeyByKeyMax(const std::map<T,K>& vMap,const Value& tDefault);

	//���� - ����
	template<typename TFun, typename T>
	bool Filiter(std::vector<T>& vFilite, const std::vector<T>& vVector, TFun fnFiliter);
	template<typename TFun, typename T, typename TArg>
	bool Filiter(std::vector<T>& vFilite, const std::vector<T>& vVector, const TArg& tArg, TFun fnFiliter);

	//���� - ���
	template<typename T>
	bool Merge(std::vector<T>& vDes,const std::vector<T>& vSrc,int nNum = -1,bool bSrcBack = false,bool bDesBack = true);//��BACKָ�����������ǰ ���Ǻ�
	template<typename T>
	bool Merge(std::list<T>& vDes,const std::list<T>& vSrc,bool bBack = true);
	template<typename T,typename K>
	bool Merge(std::map<T,K>& vDes,const std::map<T,K>& vSrc);
	template<typename T>
	bool Merge(std::set<T>& vDes,const std::vector<T>& vSrc);
	template<typename T>
	bool Merge(std::vector<T>& vDes,const std::set<T>& vSrc);
	template<typename T>
	bool Merge(std::vector<T>& vDes, const T& tSrc,bool bBack = true);
	template<typename T>
	bool Merge(std::list<T>& vDes, const T& tSrc, bool bBack = true);
	template<typename T>
	bool Merge(std::set<T>& vDes, const T& tSrc);

	//���� - ��� - ����
	template<typename T>
	bool MergeExcept(std::vector<T>& vDes,const std::vector<T>& vSrc,const T& tVal);

	//���� - �ƶ�
	template<typename T>
	bool Move(std::list<T>& vDes,std::list<T>& vSrc);
	template<typename T>
	bool Move(std::list<T>& vSrc,std::list<T>& vDes,const std::list<T>& vSrcSub);
	template<typename T>
	bool Move(std::vector<T>& vSrc,std::vector<T>& vDes,int nNum = -1,bool bSrcBack = true,bool bDesBack = true);
	template<typename T>
	bool Move(std::vector<T>& vSrc,std::vector<T>& vDes,const std::vector<T>& vSrcSub,bool bSrcBack = true,bool bDesBack = true);
	template<typename T,typename K>
	bool Move(std::map<T,K>& vDes,std::map<T,K>& vSrc);

	//���� - ����
	template<typename T>
	uint Erase(std::set<T>& vVct,const T& tVal);
	template<typename T>
	uint Erase(std::vector<T>& vVct,const T& tVal);
	template<typename T>
	uint Erase(std::list<T>& vVct,const T& tVal);
	template<typename T>
	uint Erase(std::vector<T>& vDes,const std::vector<T>& vSrc);
	template<typename T>
	uint Erase(std::vector<T>& vDes,const std::set<T>& vSrc);
	template<typename T>
	uint Erase(std::list<T>& vVct,const std::list<T>& tVal);

	//���� - ����(������һ��������)
	template<typename T>
	typename std::set<T>::iterator		EraseByItr(std::set<T>& vSrc,typename std::set<T>::iterator& itr);
//  template<typename T>
//  typename std::vector<T>::iterator	EraseByItr(std::vector<T>& vSrc,typename std::vector<T>::const_iterator& itr);
	template<typename T>
	typename std::vector<T>::iterator	EraseByItr(std::vector<T>& vSrc,typename std::vector<T>::iterator& itr);//iosƽ̨���ܴӷ�const�Զ�ת����const_itr�����Ҫ����
	template<typename T>
	typename std::list<T>::iterator		EraseByItr(std::list<T>& vSrc,typename std::list<T>::iterator itr);
	//template<typename T>
	//typename std::list<T>::iterator	EraseByItr(std::list<T>& vSrc,typename std::list<T>::const_iterator itr);//ios��֧�ֲ���const������,Ҳ�޷�ת��
	template<typename T>
	typename std::list<T>::iterator		EraseByItr(std::list<T>& vSrc,typename std::list<T>::iterator itrBegin,typename std::list<T>::iterator itrEnd,bool bKeepBegin=false,bool bKeepEnd=true);
	template<typename T,typename K>
	typename std::map<T,K>::iterator	EraseByItr(std::map<T,K>& vSrc,typename std::map<T,K>::iterator itr);

	//���� - ���� - ����ָ������Ԫ�� (����1�������� �ɹ�����ʧ�� )
	template<typename T,typename Arg>
	bool EraseByValue(std::vector<T>& vVct,const Arg& tVal,bool bBack=true);//˳��
	template<typename T,typename Arg>
	bool EraseByValue(std::set<T>& vVct,const Arg& tVal);
	template<typename T,typename Arg>
	bool EraseByValue(std::list<T>& vVct,const Arg& tVal,bool bBack=true);
	template<typename Key,typename Value,typename Arg>
	bool EraseByValue(std::map<Key,Value>& vMap,const Arg& tValue);
	template<typename TKey,typename TValue,typename ArgKey,typename ArgValue>
	bool EraseByValue(std::multimap<TKey,TValue>& vDes,const ArgKey& tKey,const ArgValue& tValue);
	template<typename Key,typename Value,typename Arg>
	bool EraseByValue(std::map<Key,std::vector<Value> >& vMap,const Arg& tVal);//������һ��
	template<typename Key,typename Value,typename Arg>
	bool EraseByValue(std::map<Key,std::vector<Value> >& vMap,const Key& tKey,const Arg& tVal);//������һ��

	//������������ ���� ��������
	template<typename T,typename Arg>
	bool EraseByValue(std::list<T>& vVct,const std::list<Arg>& vSrc);
	template<typename T,typename Arg>
	bool EraseByValue(std::vector<T>& vDes,const std::vector<Arg>& vSrc);
	template<typename T,typename Arg>
	bool EraseByValue(std::vector<T>& vDes,const std::set<Arg>& vSrc);

	//���� - ���� - ����ָ������Ԫ�� (���� ���������ݵĸ���)
	template<typename T,typename Arg>
	uint EraseByValueAll(std::vector<T>& vVct,const Arg& tVal);
	template<typename T,typename Arg>
	uint EraseByValueAll(std::list<T>& vVct,const Arg& tVal);
	template<typename Key,typename Value,typename Arg>
	uint EraseByValueAll(std::map<Key,Value>& vMap,const Arg& tValue);
	template<typename Key,typename Value,typename Arg>
	uint EraseByValueAll(std::map<Key,std::vector<Value> >& vMap,const Arg& tVal);
	template<typename Key,typename Value,typename Arg>
	uint EraseByValueAll(std::map<Key,std::list<Value> >& vMap,const Arg& tVal);

	template<typename T, typename Arg>
	uint EraseByValueAll(std::list<T>& vVct, const std::list<Arg>& vSrc);
	template<typename T, typename Arg>
	uint EraseByValueAll(std::vector<T>& vDes, const std::vector<Arg>& vSrc);
	template<typename T, typename Arg>
	uint EraseByValueAll(std::vector<T>& vDes, const std::set<Arg>& vSrc);

	//���� - ���� - ��
	template<typename TKey,typename TValue,typename TArg>
	uint EraseByKey(std::map<TKey,TValue>& vDes,const TArg& tKey);
	template<typename TKey,typename TValue,typename TArg>
	uint EraseByKey(std::multimap<TKey,TValue>& vSrc,const TArg& tKey,bool bEraseAll = true);

	//���� - ���� - ָ��λ��
	template<typename T>
	bool EraseByIndex( std::vector<T>& vVct,int nIndex );

	//���� - ���� - ����ǰ(��)N��Ԫ��
	template<typename T>
	uint EraseBySeq(std::vector<T>& vVct,uint uNum,bool bFront = true);

	//���� - ���� - ����ָ������(��������trueΪ��Ҫɾ��)
	template<typename TFun, typename T>
	bool EraseByFn(std::vector<T>& vVector, TFun fn);
	template<typename TFun, typename T>
	uint EraseByFnAll(std::vector<T>& vVector, TFun fn);

	//���� - ���� - ����ָ������(��������falseΪ��Ҫɾ��)
	template<typename T, typename TFn>
	bool EraseByNotFn(std::vector<T>& vVector, TFn fn);
	template<typename T, typename TFn>
	uint EraseByNotFnAll(std::vector<T>& vVector, TFn fn);

	//���� - ���� - ����ͷ
	template<typename T>
	bool EraseFront(std::vector<T>& vSrc);
	template<typename T>
	bool EraseFront(std::set<T>& vSrc);
	template<typename T>
	bool EraseFront(std::list<T>& vSrc);
	template<typename T,typename TAlloc>
	bool EraseFront(std::set<T,TAlloc>& vSrc);

	template<typename T>
	bool EraseBack(std::vector<T>& vSrc);
	template<typename T>
	bool EraseBack(std::list<T>& vSrc);

	//���� - �޸� - �޸�ָ��λ������Ԫ��
	template<typename T,typename TArg>
	bool SetValueByIndex(std::vector<T>& v,int nIndex,const TArg& tArg);
	template<typename TKey,typename TValue>
	bool SetValueByIndex(std::map<TKey,TValue>& vMap,const TKey& tKey,const TValue& tValue,bool bCreate = false);

	//���� - �޸� - �滻ָ������Ԫ��(���ر��滻�����ݸ���)
	template<typename T>
	int ReplaceByValue(std::vector<T>& vVct,const T& tSrc,const T& tDes);

	//���� - ����
	template<typename T,typename K>
	bool Reverse(std::map<K,T>& vDes,const std::map<T,K>& vSrc);//Key,Value����
	template<typename T>
	bool Reverse(std::vector<T>& vDes,const std::vector<T>& vSrc);//˳��䷴
	template<typename T>
	bool Reverse(std::list<T>& vDes,const std::list<T>& vSrc);//˳��䷴

	//���� - ���N��һ����Ԫ��
	template<typename T,typename K>
	void PushSameValue(std::vector<T>& vDes,const K& kValue,int nCount);
	template<typename T>
	void PushSameValue(std::vector<T>& vDes,const std::vector<T>& vArg,int nCount);
	template<typename T,typename K>
	void PushSameValue(std::list<T>& vDes,const K& kValue,int nCount);

	//���� - �����ֵ������������
	template<typename T>
	T&	CreateValue(std::vector<T>& vVct);
	template<typename T>
	T&	CreateValue(std::list<T>& vVct);

	//���� - �ж� - �Ƿ������ڶ���ָ������Ԫ��
	template<typename T,typename Value>
	bool IsSameValue(const std::vector<T>& vVct,const Value& tVal);
	template<typename T,typename Value>
	bool IsSameValue(const std::list<T>& vVct,const Value& tVal);

	//���� - �ж� - �Ƿ������ڵ�Ԫ�ض��ǲ�һ����
	template<typename T>
	bool IsDifferentValue(const std::vector<T>& vVct);
	template<typename T>
	bool IsDifferentValue(const std::list<T>& vVct);
	template<typename T,typename K>
	bool IsDifferentValue(const std::map<T,K>& vVct);

	//���� - ��ȡǰ/��һ��������
	template<typename T>
	typename std::vector<T>::iterator				GetItrFront(typename std::vector<T>::iterator itr,std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::const_iterator			GetItrFront(typename std::vector<T>::const_iterator itr,const std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::reverse_iterator		GetItrFront(typename std::vector<T>::reverse_iterator itr,std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::const_reverse_iterator	GetItrFront(typename std::vector<T>::const_reverse_iterator itr,const std::vector<T>& vSrc);
	template<typename T>
	typename std::list<T>::iterator					GetItrFront(typename std::list<T>::iterator itr,std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::const_iterator			GetItrFront(typename std::list<T>::const_iterator itr,const std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::reverse_iterator			GetItrFront(typename std::list<T>::reverse_iterator itr,std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::const_reverse_iterator	GetItrFront(typename std::list<T>::const_reverse_iterator itr,const std::list<T>& vSrc);

	template<typename T>
	typename std::vector<T>::iterator				GetItrNext(typename std::vector<T>::iterator itr,std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::const_iterator			GetItrNext(typename std::vector<T>::const_iterator itr,const std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::reverse_iterator		GetItrNext(typename std::vector<T>::reverse_iterator itr,std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::const_reverse_iterator	GetItrNext(typename std::vector<T>::const_reverse_iterator itr,const std::vector<T>& vSrc);
	template<typename T>
	typename std::list<T>::iterator					GetItrNext(typename std::list<T>::iterator itr,std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::const_iterator			GetItrNext(typename std::list<T>::const_iterator itr,const std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::reverse_iterator			GetItrNext(typename std::list<T>::reverse_iterator itr,std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::const_reverse_iterator	GetItrNext(typename std::list<T>::const_reverse_iterator itr,const std::list<T>& vSrc);

	//����	- ��ȡ��һ��/���һ����Ч�ĵ�����
	template<typename T>
	typename std::vector<T>::iterator				GetItrBegin(std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::const_iterator			GetItrBegin(const std::vector<T>& vSrc);
	template<typename T>
	typename std::list<T>::iterator					GetItrBegin(std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::const_iterator			GetItrBegin(const std::list<T>& vSrc);

	template<typename T>
	typename std::vector<T>::iterator				GetItrLast(std::vector<T>& vSrc);
	template<typename T>
	typename std::vector<T>::const_iterator			GetItrLast(const std::vector<T>& vSrc);
	template<typename T>
	typename std::list<T>::iterator					GetItrLast(std::list<T>& vSrc);
	template<typename T>
	typename std::list<T>::const_iterator			GetItrLast(const std::list<T>& vSrc);

	//���� - ��ȡ���Ϲ���ĵ�����
	//���� - ��ȡ���Ϲ���ĵ����� - ���򲻴���
	template<typename T>
	typename std::list<T>::iterator					GetItrBegin(std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&));


	//���� - ��ȡ���Ϲ���ĵ����� - �����1��
	template<typename T,typename Arg>
	typename std::vector<T>::iterator				GetItrBegin(std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg);


	//���� - ��ȡ���Ϲ���ĵ����� - ����const���� - ���򲻴���
	template<typename T>
	typename std::list<T>::const_iterator			GetItrBegin(const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&));
	template<typename Key,typename Value>
	typename std::map<Key,Value>::const_iterator	GetItrBegin(const std::map<Key,Value>& vSrc,bool(*fn)(typename std::map<Key,Value>::const_iterator&));

	//���� - ��ȡ���Ϲ���ĵ����� - ����const���� - �����1��
	template<typename T,typename Arg>
	typename std::vector<T>::const_iterator			GetItrBegin(const std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg);
	template<typename T,typename Arg>
	typename std::list<T>::const_iterator			GetItrBegin(const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&,const Arg&),const Arg& tArg);

	template<typename T>
	typename std::list<T>::iterator					GetItrLast(std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&));

	template<typename T>
	typename std::list<T>::const_iterator			GetItrLast(const std::list<T>& vSrc,bool(*fn)( typename std::list<T>::const_iterator&));

	//���� - ��ȡ���Ϲ���ĵ�����
	//���� - ��ȡ���Ϲ���ĵ����� - ��������
	template<typename T>
	typename std::list<T>::iterator					GetItrNext(typename std::list<T>::iterator itr,std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&));

	//���� - ��ȡ���Ϲ���ĵ����� - �������� - ��������
	template<typename T>
	typename std::list<T>::const_iterator			GetItrNext(typename std::list<T>::const_iterator itr,const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&));

	//���� - ��ȡ���Ϲ���ĵ����� - ��1����
	template<typename T,typename Arg>
	typename std::vector<T>::iterator				GetItrNext(typename std::vector<T>::iterator itr,std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg);

	//���� - ��ȡ���Ϲ���ĵ����� - ��1���� - ��������
	template<typename T,typename Arg>
	typename std::vector<T>::const_iterator			GetItrNext(typename std::vector<T>::const_iterator itr,const std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg);
	template<typename T,typename Arg>
	typename std::list<T>::const_iterator			GetItrNext(typename std::list<T>::const_iterator itr,const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&,const Arg&),const Arg& tArg);

	template<typename T>
	typename std::list<T>::iterator					GetItrFront(typename std::list<T>::iterator itr,std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&));
	template<typename T>
	typename std::list<T>::const_iterator			GetItrFront(typename std::list<T>::const_iterator itr,const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&));

	//���� - pair
	template<typename TKey,typename TValue>
	std::pair<typename std::multimap<TKey,TValue>::iterator,typename std::multimap<TKey,TValue>::iterator >				EqualRange(std::multimap<TKey,TValue>& vSrc,const TKey& tKey);
	template<typename TKey,typename TValue>
	std::pair<typename std::multimap<TKey,TValue>::const_iterator,typename std::multimap<TKey,TValue>::const_iterator > EqualRange(const std::multimap<TKey,TValue>& vSrc,const TKey& tKey);

	template<typename T>
	bool	IsEnd(const std::pair<T,T>& itrPair);

	//���� ����
	template<typename T>
	bool	IsEndIndex(std::vector<T>& vVct,int nIndex);

	//���� ���� �� ��С�ĵ�����
	template<typename Key,typename Value>
	typename std::map<Key,Value>::iterator	FindItrMinKey(std::map<Key,Value>& vMap);

	//���� ���� ֵ ��С�ĵ�����
	template<typename Key,typename Value>
	typename std::map<Key,Value>::iterator	FindItrMinValue(std::map<Key,Value>& vMap);

	//���� ���� ���� ��������ֵ ����true ��Ϊ�ҵ�
	template<typename TFun, typename T>
	T  FindPtrByFn(const std::vector<T>& v, TFun fn);
	template<typename TFun, typename T, typename TArg>
	T  FindPtrByFn(const std::vector<T>& v,const TArg& tArg, TFun fn);
	template<typename TFun, typename T>
	T* FindByFn(const std::vector<T>& v, TFun fn);
	template<typename TFun, typename T, typename TArg>
	T* FindByFn(const std::vector<T>& v, const TArg& tArg, TFun fn);

	//���� ���� ���� �ȽϺ������� �����Ƚ� ����true Ϊ��Ҫ���Ǹ�
	template<typename TFun, typename T>
	T  FindPtrByCmpFn(const std::vector<T>& v, TFun fn);
	template<typename TFun, typename T>
	T* FindByCmpFn(const std::vector<T>& v, TFun fn);

	//���� ����
	template<typename T>
	bool Split(const std::vector<T>& vSrc,std::vector<T>& vDes1,std::vector<T>& vDes2,size_t uNum);

	//ɾ��(�ͷ�������ָ������)
	template <typename Tvalue>
	void Delete(std::list<Tvalue*>& vValues);
	template <typename Tvalue>
	void Delete(std::set<Tvalue*>& vValues);
	template<typename TValue,typename TCmp>
	void Delete(std::set<TValue,TCmp>& vSet);
	template <typename Tvalue>
	void Delete(std::vector<Tvalue*>& vValues);
	template <typename Tkey,typename Tvalue>
	void Delete(std::map<Tkey,Tvalue*>& vValues);
	template <typename Tkey,typename Tvalue>
	void Delete(std::map<Tkey,std::vector<Tvalue*> >& vValues);
	template <typename Tkey,typename Tvalue>
	void Delete(std::map<Tkey,std::list<Tvalue*> >& vValues);
	template <typename Tkey,typename Tvalue>
	void Delete(std::map<Tkey,std::set<Tvalue*>>& vValues);
	template <typename Tkey,typename Tvalue>
	void Delete(std::multimap<Tkey,Tvalue*>& vValues);

	//���� - ɾ�� - ɾ��ָ��������Ԫ��
	template <typename Tkey,typename Tvalue>
	bool DeleteByKey(std::map<Tkey,Tvalue*>& vMap,const Tkey& tKey);
	template <typename Tkey,typename Tvalue>
	bool DeleteByKey(std::multimap<Tkey,Tvalue*>& vMap,const Tkey& tKey);

	//���� - ɾ�� - ɾ����������(���� ��ɾ�����ݵĸ���)
	template<typename T>
	int DeleteByValue(std::set<T>& vVct,const T& tVal);

	//���� - ���
	template<typename T>
	bool Clear(std::list<T>& tVct);
	template<typename T>
	bool Clear(std::vector<T>& tVct);
	template<typename T>
	bool Clear(std::set<T>& tVct);
	template<typename T>
	bool Clear(std::multiset<T>& tVct);
	template<typename T,typename K>
	bool Clear(std::map<T,K>& tMap);
	template<typename T,typename K>
	bool Clear(std::multimap<T,K>& tMap);

	//��ѯ�Ƿ��м�
	template<typename TVct,typename TValue>
	bool IsHasKey(const std::set<TVct>& vSrc, const TValue& tValue);
	template<typename T,typename K,typename TArg>
	bool IsHasKey(const std::map<T,K>& vValues, const TArg& tKey);

	//��ѯ�Ƿ���ֵ
	template<typename T>
	bool IsHasValue(const std::vector<T>& vValues, const T& tValue);
	template<typename T>
	bool IsHasValue(const std::vector<T>& vValues, const std::vector<T>& tSub);//�Ƿ񶼴���

	template<typename T>
	bool IsHasValue(const std::list<T>& vValues, const T& tKey);
	template<typename T>
	bool IsHasValue(const std::list<T>& vValues, const std::list<T>& tSub);//�Ƿ񶼴���

	template<typename TVct,typename TValue>
	bool IsHasValue(const std::set<TVct>& vSrc, const TValue& tValue);
	template<typename T,typename K>
	bool IsHasValue(const std::vector<T>& vValues, const K& tKey);
	template<typename T,typename K,typename M>
	bool IsHasValue(const std::map<T,K>& vValues,const M& mValue);
	template<typename T>
	bool IsHasOne(const std::vector<T>& vValues, const std::vector<T>& tSub);//�Ƿ����ٴ���һ��

	//�ж����(��ȫ���,ֵ ˳��)
	bool IsEqual(const float t1,const double t2);
	bool IsEqual(const double t1,const float t2);
	bool IsEqual(const float t1,const float t2);
	bool IsEqual(const double t1,const double t2 ,const double relError = 0.00001f);//���
	bool IsEqual(const char ch1, const char ch2,bool bIgnoreCase = false);	//�Ƚ��ַ� �����Դ�Сд �����Ϊ��ĸ
	bool IsEqual(const char* pSrc,const char* pDes,bool bIgnoreCase=false);	//�Ƚ��ַ��� �����Դ�Сд �����Ϊ��ĸ
	template<typename T1,typename T2>
	bool IsEqual(const T1& t1,const T2& t2);
	template<typename T,typename TFunCompair>
	bool IsEqual(const std::vector<T>& vSrc, const std::vector<T>& vDes);
	template<typename T,typename TFunCompair>
	bool IsEqual(const std::vector<T>& vSrc, const std::vector<T>& vDes,TFunCompair fnCompair);
	template<typename T>
	bool IsEqual(const std::set<T>& vSrc, const std::set<T>& vDes);
	template<typename TKey,typename TValue>
	bool IsEqual( const std::map<TKey,TValue>& vSrc, const std::map<TKey,TValue>& vDes );
	bool IsEqual(const std::string& s1,const std::string& s2,bool bIgnoreCase=false);//�Ƚ��ַ��� �����Դ�Сд �����Ϊ��ĸ

	//�ж�ֵ�Ƿ����(�����Ƚ� ֵ)
	template<typename T>
	bool IsEqual(const std::vector<T>& vSrc, const std::set<T>& vDes);
	template<typename T>
	bool IsEqual(const std::set<T>& vSrc,const std::vector<T>& vDes );


	//Ĭ�ϱȽϷ�
	template<typename TValue1,typename TValue2>
	bool CompairLess(const TValue1 & tValue1,const TValue2 & tValue2);
	template<typename TValue1,typename TValue2>
	bool CompairEqual(const TValue1 & tValue1,const TValue2 & tValue2);

	//����
	template<typename T>
	bool Intersection(std::vector<T>& vDes,const std::vector<T>& vSrc1,const std::vector<T>& vSrc2);
	template<typename T>
	bool Intersection(std::set<T>& vDes,const std::set<T>& vSrc1,const std::set<T>& vSrc2);
	template<typename T>
	bool Intersection(std::vector<T>& vDes,const std::set<T>& vSrc1,const std::vector<T>& vSrc2);
	template<typename T>
	bool Intersection(std::vector<T>& vDes,const std::vector<T>& vSrc1,const std::set<T>& vSrc2);

	//����
	template<typename T>
	bool Union(std::vector<T>& vDes,const std::vector<T>& vSrc1,const std::vector<T>& vSrc2);
	template<typename T>
	bool Union(std::list<T>& vDes,const std::list<T>& vSrc1,const std::list<T>& vSrc2);
	template<typename T>
	bool Union(std::set<T>& vDes,const std::set<T>& vSrc1,const std::set<T>& vSrc2);
	
	//����
	template<typename T>
	bool Sort(std::vector<T>& vVct);
	template<typename T,typename TFn>
	bool Sort(std::vector<T>& vVct,TFn fnCompair);

	//����
	template<typename T>
	bool NextPermutaion(std::vector<T>& vVct);//��һ�����С����е����Ϊ������Sort���ֵ
	template<typename T>
	bool PrevPermutaion(std::vector<T>& vVct);//��һ�����С����е����Ϊ������Sort���ֵ

	//���� - ��
	template<typename T>
	bool IsEmpty(const std::vector<T>& vSrc);
	template<typename T> 
	bool IsEmpty(const std::list<T>& vSrc);
	template<typename T> 
	bool IsEmpty(const std::set<T>& vSrc);
	template<typename T,typename K> 
	bool IsEmpty(const std::map<T,K>& vSrc);
	template<typename T,typename K> 
	bool IsEmpty(const std::multimap<T,K>& vSrc);

	//���� - �����ͷ
	template<typename T, typename Value>
	bool PushFront(std::vector<T>& vVct, const Value& tValue);
	template<typename T, typename Value>
	bool PushFront(std::list<T>& vVct, const Value& tValue);

	//���� - �����β
	template<typename T,typename Value>
	bool PushBack(std::vector<T>& vVct,const Value& tValue);
	template<typename T,typename Value>
	bool PushBack(std::list<T>& vVct,const Value& tValue);

	//���� - ��ȡ��βԪ��(�����)
	template<typename T>
	const T& GetBack(const std::vector<T>& vSrc);
	template<typename T> 
	const T& GetBack(const std::list<T>& vSrc );

	//���� - ��ȡ��ͷԪ��(�����)
	template<typename T>
	T& GetFront(std::vector<T>& vSrc);
	template<typename T>
	T& GetFront(std::list<T>& vSrc);

	template<typename T>
	const T& GetFront(const std::vector<T>& vSrc);
	template<typename T>
	const T& GetFront(const std::list<T>& vSrc);

	template<typename T>
	T PopFront(std::vector<T>& vSrc);
	template<typename T>
	T PopFront(std::list<T>& vSrc);
	template<typename T,typename K>
	K PopFront(std::map<T,K>& vSrc);

	//��ջ
	template<typename T>
	T PopBack(std::vector<T>& vSrc);
	template<typename T>
	T PopBack(std::list<T>& vSrc);
	template<typename T,typename K>
	K PopBack(std::map<T,K>& vSrc);
	template<typename T>
	bool PopBack(std::vector<T>& vSrc,const T& t);//�����һ��Ϊ��ֵ�ſɵ����ɹ�

	//���� - ��ȡ��ͷָ��
	template<typename ValuePtr>
	ValuePtr GetFrontPtr(const std::vector<ValuePtr>& vSrc);
	template<typename ValuePtr>
	ValuePtr GetFrontPtr(const std::list<ValuePtr>& vSrc);

	//���� - ��ȡ��βָ��
	template<typename ValuePtr>
	ValuePtr GetBackPtr(const std::vector<ValuePtr>& vSrc);
	template<typename ValuePtr>
	ValuePtr GetBackPtr(const std::list<ValuePtr>& vSrc);

	template<typename ValuePtr>
	ValuePtr PopPtr(std::vector<ValuePtr>& vSrc);
	template<typename ValuePtr>
	ValuePtr PopPtr(std::list<ValuePtr>& vSrc);
	template<typename T,typename ValuePtr>
	ValuePtr PopPtr(std::map<T,ValuePtr>& vSrc);

	template<typename T>
	T PopFrontPtr(std::vector<T>& vSrc);
	template<typename T>
	T PopFrontPtr(std::list<T>& vSrc);
	template<typename T,typename K>
	K PopFrontPtr(std::map<T,K>& vSrc);

	//��ջ
	template<typename T>
	T PopBackPtr(std::vector<T>& vSrc);
	template<typename T>
	T PopBackPtr(std::list<T>& vSrc);
	template<typename T,typename K>
	K PopBackPtr(std::map<T,K>& vSrc);

	//ѭ������ -��ȡĳ�㸽������ֵ (�����)
	template<typename T>
	T& CircularPrev( std::vector<T>& vSrc,int nIndex);
	template<typename T>
	T& CircularNext( std::vector<T>& vSrc,int nIndex);
	template<typename T>
	const T& CircularPrev(const std::vector<T>& vSrc,int nIndex);
	template<typename T>
	const T& CircularNext(const std::vector<T>& vSrc,int nIndex);

	//�� - ������MakeHeap��ſ��Ե��������Ѳ�������
	template<typename T>
	void MakeHeap(std::vector<T>& vVct);	//�������γɶѽṹ(beginһ��������Ԫ��)
	template<typename T>
	void PopHeap(std::vector<T>& vVct);	//���ѵ����Ԫ������ĩβ,����������Ԫ���γ��¶�
	template<typename T>
	void PushHeap(std::vector<T>& vVct);	//��ĩβ��Ԫ�ز��뵽ǰ��Ķ���
	template<typename T>
	bool SortHeap(std::vector<T>& vVct);	//������(�����ڲ������Ƕѽṹ���Ǵ�С������������)
	template<typename T>
	bool SortHeapHead(std::vector<T>& vVct);	//����ǰ�Ѷ�Ԫ����������(�ԶѶ�Ԫ���޸Ĺ��� ���ô˺��� ����)

	template<typename T,typename TCmp>
	void MakeHeap(std::vector<T>& vVct,TCmp fnCmp);
	template<typename T,typename TCmp>
	void PopHeap(std::vector<T>& vVct,TCmp fnCmp);
	template<typename T,typename TCmp>
	void PushHeap(std::vector<T>& vVct,TCmp fnCmp);
	template<typename T,typename TCmp>
	bool SortHeap(std::vector<T>& vVct,TCmp fnCmp);
	template<typename T,typename TCmp>
	bool SortHeapHead(std::vector<T>& vVct,TCmp fnCmp);

	//�� - ָ��Ƚ�(��Ҫ���ڶ��� FUN_PTR_CMP)
	template<typename T>
	void PopHeapPtr(std::vector<T*>& vVct);
	template<typename T>
	void PushHeapPtr(std::vector<T*>& vVct);

	//ȡ��Сֵ
	template<typename TKey,typename ValuePtr>
	ValuePtr GetLowerMultMap(const std::multimap<TKey,ValuePtr>& vMap,const TKey& tKey);
	template<typename TKey,typename ValuePtr>
	ValuePtr GetLowerMap(const std::map<TKey,ValuePtr>& vMap,const TKey& tKey );

	//ȡ��Сֵ��ָ��
	template<typename TKey,typename Value>
	Value* GetLowerPtrMap(const std::map<TKey,Value>& vMap,const TKey& tKey );

	//ȡ�ϴ�ֵ
	template<typename TKey,typename ValuePtr>
	ValuePtr		GetValueUpperMap(const std::map<TKey,ValuePtr>& vMap,const TKey& tKey );
	template<typename TKey,typename TValue>
	TValue&			GetValueUpperMap(const std::map<TKey,TValue>& vMap,const TKey& tKey,TValue& tDefault );
	template<typename TKey,typename TValue>
	const TValue&	GetValueUpperMap(const std::map<TKey,TValue>& vMap,const TKey& tKey,const TValue& tDefault );

	template<typename TKey,typename TValue,typename TArg>
	TValue*			GetValuePtrUpperMap(const std::map<TKey,TValue>& vMap,const TArg& tKey );

	//ȡ���ֵ
	template<typename Tkey,typename TValue>
	bool GetMax(const std::multimap<Tkey,TValue>& vSrc,std::vector<TValue>& vDes);

	//ȡ��Сֵ
	template<typename Tkey,typename TValue>
	bool GetMin(const std::multimap<Tkey,TValue>& vSrc,std::vector<TValue>& vDes);

	//���Map��� ���Ҽ�
	template<typename T>
	std::vector<T> GetMapValue(const std::map<T,T>& vMap,bool bKey = true);

	template <typename TMapKey,typename TMapValue>
	void GetMapKey( const std::map<TMapKey,TMapValue>& vSrc,std::vector<TMapKey>& vDes);

	template <typename TMapKey,typename TMapValue>
	void GetMapValue( const std::map<TMapKey,TMapValue>& vSrc,std::vector<TMapKey>& vDes);

	//ָ�� - Ψһ��
	template<typename T1,typename T2>
	bool IsUnique(const T1& t1,const T2& t2);//�ж��Ƿ�����ֻ��1��ָ�벻Ϊ��
	template<typename T1,typename T2,typename T3>
	bool IsUnique(const T1& t1,const T2& t2,const T3& t3);//�ж��Ƿ�����ֻ��1��ָ�벻Ϊ��

	//ָ�� - ��ָ��
	template<typename T>
	T		GetNullPtr();

	//���Bit��
	int GetBits(const bool&);

	template<typename T>
	int GetBits(const T&);

	//λ����
	template <typename T,typename TCount>
	bool GetBool(T t,TCount tCount);
	template <typename T,typename TCount>
	void SetBool(T* tValue,TCount tCount,bool bBool = true);
	template <typename T,typename K>
	void InsertValue(T& tValue,K kSrc);

	//�Ƚ�
	template <typename T1>
	const T1&	Min(const T1& t1,const T1& t2 );
	template <typename T1,typename T2>
	T1			Min(const T1& t1,const T2& t2 );
	template <typename T,typename TCount>
	const T&	Min(const T* tArray,TCount tCountMax);

	template <typename T1>
	const T1&	Max(const T1& t1,const T1& t2 );
	template <typename T1,typename T2>
	const T1	Max(const T1& t1,const T2& t2 );
	template <typename T,typename TCount>
	const T&	Max(const T* tArray,TCount tCountMax);

	//�Ƚ� - ָ��
	template<typename T>
	const T* MinPtr(const T* pT1,const T* pT2);

	template<typename T>
	const T* MaxPtr(const T* pT1,const T* pT2);

	//���������ڴ����������ĵ�N����,�����������ǵڼ���
	int	CalIndexFromRight(int nIndexLeft,int nBegin,int nEnd);
	int	CalIndexFromLeft(int nIndexRight,int nBegin,int nEnd);

	unsigned int	CalIndexFromRight(unsigned int nIndexLeft,unsigned int nBegin,unsigned int nEnd);
	unsigned int	CalIndexFromLeft(unsigned int nIndexRight,unsigned int nBegin,unsigned int nEnd);

	//��ѧ
	float	Sqrt(float fValue);				//������
	float	Power(float fValue,int nPower);	//�η�
	double	Sin(double fAngel);				//Sin ����
	double	Cos(double fAngel);				//Cos ����
	double	ACos(double fValue);			//Arc Cos ������
	double	ATan(double fY,double fX);		//Arc Tan ������

	//���ȽǶȻ���
	double RadianToAngel(double fRadian);
	double AngelToRadian(double fAngel);

	//����ƫ�ƺ����ֵ
	bool Offset(size_t& uDes, size_t uSrc, int nOffset, size_t uLimitBegin, size_t uLimitEnd, bool bFix /*= true*/);

	//����ֵ
	template <typename T>
	T Abs(const T& t);
	
	//��ֵ
	template<typename T>
	int Difference(const T& a,const T& b);

	//���Բ�(������ֵ�Ĳ�ֵȡ����)
	template <typename T>
	T AbsDifference(const T& a,const T& b);

	//ȡ�ȽϽ���ֵ(ArgΪ�ο�ֵ)
	template <typename T>
	const T& GetNearValue(const T& tArg,const T& a,const T& b);

	//ȡ�Ƚ�Զ��ֵ(ArgΪ�ο�ֵ)
	template <typename T> 
	const T& GetFarValue( const T& tArg,const T& a,const T& b );

	//����
	template <typename T>
	void Swap(T& tSrc,T& tDes);

	//�ж��Ƿ����Լ�(ͬһ����������)
	template <typename T,typename K>
	bool IsSelf(const T& tVct1,const K& tVct2);

	//�����������(���򻮷�:1~nDivisorΪ��һ������,nDivisor+1 ~ 2*nDivisor Ϊ�ڶ�����)
	int GetIntervalNum(int nDividend,int nDivisor);

	//�ж��Ƿ��� ������(nBegin,nEnd)
	bool IsInOpenInterval(int nVal,int nBegin,int nEnd);
	template<typename T>
	bool IsInOpenInterval(const T& tVal,const T& tBegin,const T& tEnd);

	//�ж��Ƿ��� ������[nBegin,nEnd]
	bool IsInClosedInterval(int nVal,int nBegin,int nEnd);
	template<typename T>
	bool IsInClosedInterval(const T& tVal,const T& tBegin,const T& tEnd);

	//�ж��Ƿ�Ϊһ�¼���ֵ
	bool IsInValue(int nValue,int nArg1);
	bool IsInValue(int nValue,int nArg1,int nArg2);
	bool IsInValue(int nValue,int nArg1,int nArg2,int nArg3);
	bool IsInValue(int nValue,int nArg1,int nArg2,int nArg3,int nArg4);
	bool IsInValue(int nValue,int nArg1,int nArg2,int nArg3,int nArg4,int nArg5);

	//��ȡ �� ������(nBegin,nEnd)�� ��ӽ�Ŀ���ֵ
	int			GetValueInOpenInterval(int nVal,int nBegin,int nEnd);
	template<typename T>
	const T&	GetValueInOpenInterval(const T& tVal,const T& tBegin,const T& tEnd);

	//��ȡ �� ������(nBegin,nEnd)�� ��ӽ�Ŀ���ֵ
	int			GetValueInClosedInterval(int nVal,int nBegin,int nEnd);
	template<typename T>
	const T&	GetValueInClosedInterval(const T& tVal,const T& tBegin,const T& tEnd);

	//���鸳ֵ(��ά���� �ڴ������ʵҲ�����Ե�)
	template <typename T>
	void ArrayAssign(T* pDes,int nLength,T tValue);

	//��ά���鿽��
	template<typename T>
	void ArrayCopy( T pDes[],const T pSrc[],int nLength);

	//�������
	template <typename T>
	void ArrayCal(T* tArray,int nLength,const signed long& tValue);

	//�Ƿ��Ѿ�����ֵ
	template <typename T>
	bool IsHasValue(T* tArray,int nLength,T& tValue);

	//�������
	template<typename T,typename K>
	void ArrayToVct(std::vector<T>& vDes,K* kArray,int nCount);

	//����������
	template <typename TVct,typename KArray>
	bool VctToArray( const std::vector<TVct>& vSrc,KArray* tArray,int uLengthMax,int nLength = -1);

	//����ֵ
	template <typename T>
	bool  ModifyValue (T* tArray,int nLength,const T& tSrc,T& tDes);
	template <typename T>
	bool  ModifyValueCopy (T* tArray,int nLength,const T& tSrc,T tDes);

	//���Ԫ��ֵΪX�ĸ���
	template <typename T>
	int GetCountValueSame (T* tArray,int nLength,const T& tDes);

	//���Ԫ��ֵ��ΪX�ĸ���
	template <typename T>
	int GetCountValueDifferent (T* tArray,int nLength,const T& tDes);

	//ת��
	inline UCHAR ToHex(const UCHAR &x){ return x > 9 ? x + 55: x + 48; }
	inline UCHAR FromHex(const UCHAR &x){ return x > 64 ? x - 55 : x - 48; }

	//��ñ�ָ��ֵС�ĸ���
	int GetLessCount( const std::set<int>& vVct,int nNumber );

	//��ȡ�����ܱ������������ֺ�ÿ�ݵĸ���(nTotal>0,nPart>0,nIndex>0)
	int GetAvgCount(int nTotal,int nPart,int nIndex);

	//��ü���ֵ
	template<typename T>
	T				GetLimitMin(const T& );
	template<typename T>
	T				GetLimitMax(const T& );

	template<typename T>
	T				GetLimitMin();
	template<typename T>
	T				GetLimitMax();

	//�������Ҫ������ӽ���2�Ĵη���(����200������256,����300������512)
	size_t GetNearPowerOf2(size_t uNum);

	//�ڴ�
	size_t SmartMemoryLength(size_t uSize);			//���ܵ����ڴ���ʵĴ�С
	size_t SmartMemoryLengthNextLevel(size_t uSize);//���ܵ����ڴ���һ�״�С

	//ͳ��
	template<typename T,typename K>
	bool AddCount(std::map<T,uint>& vMap,const K& tK,uint nCount = 1);//����Key�ļ���

	template<typename T,typename K>
	bool ReduceCount(std::map<T,uint>& vMap,const K& tK,uint nCount = 1);//����Key�ļ���

	template<typename T,typename K>
	uint GetCount(const std::map<T,uint>& vMap,const K& tK);

	//���
	bool IsLetter(char ch);//�Ƿ�����ĸ
	bool IsNumber(const char cSrc,int nNumberSystem = NUMBER_SYSTEM_10);
	bool IsNumber(const std::string& sSrc,int nNumberSystem = NUMBER_SYSTEM_10);

	//�ַ�������
	template<typename TArg>
	bool SetValueByIndex(VectorString& v,int nIndex,const TArg& tArg);

	//������
	bool		ToValue(const MapStringString& vValues,std::string& sDes,const std::string& sSpKeyValue="=",const std::string& sSpLine=" ");
	bool		ToValue(const VectorString& vValues,std::string& sDes,const std::string& sSpLine=" ");
	bool		ToValue(const std::string& sSrc, MapStringString& vDes,const std::string& sSpKeyValue="=",const std::string& sSpLine=" ");
	bool		ToValue(const std::string& sSrc, VectorString& vDes,const std::string& sSpLine=" ");

	//�ַ��� - ����
	bool		IsLengthInOpenInterval(const std::string& sString,uint uBegin,uint uEnd);//�ж��ַ����Ƿ��� ������(nBegin,nEnd)
	bool		IsLengthInClosedInterval(const std::string& sString,uint uBegin,uint uEnd);//�ж��ַ����Ƿ��� ������[nBegin,nEnd]

	//�ַ��� - ��ȡֵ
	template<typename T>
	bool		GetValueByKeyString(const MapStringString& vValue,const std::string& sKey,T& tValue);

	//�ַ��� - ͳ���ַ����ֵĴ���
	int			CalStringCount(const std::string& sString,const std::string& sCount);

	//�ַ��� - ����
	VectorString	SplitString(const std::string& sSrc,const std::string& sSP,bool bHold = false,bool bFront = false);
	bool			SplitString(VectorString& vReturn,const std::string& sSrc,const std::string& sSP,bool bHold = false,bool bFront = false);
	
	//�ַ��� - ���� ������һ���ָ����ͷ���
	bool			SplitStringFirst(VectorString& vReturn,const std::string& sSrc,const std::string& sSP,bool bFront = true);

	//�ַ��� - �Ƴ��ַ���
	UINT			RemoveString(VectorString& vReturn,const std::string& sString = "");

	//�ַ��� - ��Сдת��
	char				ToLowerCase(char ch);
	const std::string&	ToLowerCase(std::string& sSrc);
	bool				ToLowerCase(VectorString& vSrc);
	char				ToUpperCase(char ch);
	const std::string&	ToUpperCase(std::string& sSrc);
	bool				ToUpperCase(VectorString& vSrc);

	//�ַ��� - �ж����ָ��� 
	int CalChineseCharacterNum(const std::string& sString);//�ж����ĵĸ���
	int CalEnglishCharacterNum(const std::string& sString);//�ж�Ӣ�ĵĸ���
	int CalCharacterNum(const std::string& sString);//�ж��ַ�����

	//�ַ��� - �Ӵ����ֵĴ���
	int GetSubNum(const std::string& sSrc,const std::string& sSub);

	//�ַ��� - ��ȡ����ָ���ַ��� ֮����ַ���(���������Ƿ�ģ������)
	std::string	GetMidString(const std::string& sSrc,const std::string& sBegin,const std::string& sEnd,bool bFuzzy = true );
	bool		GetMidString(std::string& sDes,const std::string& sSrc,const std::string& sBegin,const std::string& sEnd,bool bFuzzy = true );
	bool		GetMidString(VectorString& vDes,const std::string& sSrc,const std::string& sBegin,const std::string& sEnd,bool bFuzzy = true);

	//�ַ��� - ��ȡָ����ʽ֮����ַ���
	VectorString				GetValues(const std::string& sSrc,const VectorString& vFormat,const std::string& sValidFlag);
	std::vector<VectorString>	GetStringByFormat(const std::string& sSrc,const VectorString& vFormat );
	std::vector<VectorString>	GetStringByFormat(const std::string& sSrc,const VectorString& vFormat,const std::string& sValueFlag,const std::string& sValidFlag);
	std::vector<VectorString>	GetStringByFormat(const std::string& sSrc,const std::string& sTempalte,const std::string& sValueFlag,const std::string& sValidFlag);
	bool						GetStringByFormat(VectorString&vReturn, const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte);
	bool						GetStringByFormat(VectorString&vReturn, const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte1,const std::string& sTempalte2);
	bool						GetStringByFormat(VectorString&vReturn, const std::string& sSrc,const std::string& sValueFlag,const VectorString& vTempalte);
	
	//�ַ��� - ͨ��ָ����ʽ ��ȡֵ
	template<typename T>
	bool GetValueByString(const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T& t);
	template<typename T1,typename T2>
	bool GetValueByString(const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2);
	template<typename T1,typename T2,typename T3>
	bool GetValueByString(const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2,T3 & t3);
	template<typename T1,typename T2,typename T3,typename T4>
	bool GetValueByString(const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2,T3 & t3,T4 & t4);
	template<typename T1,typename T2,typename T3,typename T4,typename T5>
	bool GetValueByString(const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2,T3 & t3,T4 & t4,T5 & t5);

	//�ַ��� - ���� - �ϲ����ͬ���ַ�
	std::string StringCombine(const std::string& sSrc,const std::string& sValue =" ");

	//�ַ��� - ���� - �滻
	long		Replace(std::string& sString,const std::string& sSrc,const std::string& sDes);  
	long		Replace(VectorString& vStrings,const std::string& sSrc,const std::string& sDes); 
	long		Replace(std::string& sSrc,const MapStringString& vMap);//���ݸ�����ӳ����滻(��������Key������һ��������һ�����Ӽ�,��ô�滻�����Ȼ�����е�һ���������δ֪)

	//ȥ�����˵Ŀո���Ʊ��
	std::string TrimString(const std::string& sString);
	std::string TrimString(const std::string& sString,const char* const pCharSet);
	bool		TrimString(VectorString& vString);

	//ȥ���س���
	std::string RemoveReturn(const std::string& sSrc);

	//�ַ���
	bool		IsBeginWith(const std::string& sSrc,const std::string& sValue, SSIZE_TYPE uOffset = 0,bool bIgnoreCase=false);
	bool		IsBeginWith(const std::string& sSrc,const VectorString& vValue, SSIZE_TYPE uOffset = 0);
	bool		IsEndWith  (const std::string& sSrc,const std::string& sValue);
	bool		IsBeginEndWith(const std::string& sSrc,const std::string& sBegin,const std::string& sEnd);
	SSIZE_TYPE	FindFristNotOf(const std::string& sSrc,const char sz[], SSIZE_TYPE uOffset = 0);
	SSIZE_TYPE	SkipInvisibleChar(const std::string& sSrc, SSIZE_TYPE nOffset,bool bNot = false);//�������ɼ��ַ�
	bool		IsVisibleChar(char ch);//�Ƿ�ɼ��ַ�
	bool		IsVisibleString(const std::string& sSrc);//�Ƿ��ǿɼ��ַ�
	SSIZE_TYPE	SkipChar(const std::string& sSrc, SSIZE_TYPE nOffset,bool(*fn)(char),bool bNot = false);
	std::string PickChar(const std::string& sSrc, SSIZE_TYPE nOffset,bool(*fn)(char));
	SSIZE_TYPE	FindFrist(const std::string& sSrc,const std::string& sDes, SSIZE_TYPE nOffset = 0);
	SSIZE_TYPE	FindFrist(const std::string& sSrc,const VectorString& vDes, SSIZE_TYPE nOffset = 0);
	SSIZE_TYPE	FindFrist(std::string& sDes,const std::string& sSrc,const VectorString& vDes, SSIZE_TYPE nOffset = 0);
	SSIZE_TYPE	FindFrist(std::string* sDes,const std::string& sSrc,const VectorString& vDes, SSIZE_TYPE nOffset = 0);
	bool		IsBeforeCharactor(const std::string& sString,const std::string& sJudge, SSIZE_TYPE uOffSet );		//�ж�ǰһ���ַ��Ƿ���
	SSIZE_TYPE	IsVisibleCharBeginWith(const std::string& sSrc,const std::string& sCmp, SSIZE_TYPE nOffset = 0,bool bSkip = true);//��һ���ɼ��ַ����Ƿ���ָ���ַ���
	SSIZE_TYPE	PickVisibleString(std::string& sDes, const std::string& sSrc, SSIZE_TYPE nOffset);//������һ���ɼ��ַ���

	std::string RemoveBeginString(const std::string& sSrc,const std::string& sRemove);
	std::string RemoveEndString(const std::string& sSrc,const std::string& sRemove);

	//�Ƿ����Ŀ���ַ���
	bool IsHas(const std::string& sSrc,const std::string& sDes, bool bIgnoreCase=false);
	bool IsHas(const VectorString& vSrc, const std::string& sDes, bool bIgnoreCase = false);

	//Ǯ
	std::string	MoneyToString( uint32 uMoney );				//Ǯ���ַ��� ת��(��ȷ����)
	uint32		StringToMoney(const std::string& sMoney);	//�ַ�����Ǯ ת��
	bool		IsMoneyCharacter(char ch);					//�ж��Ƿ��ǽ�Ǯ���ַ�
	std::string TrimMoneyString(const std::string& sMoney);	//���� Ǯ�ַ���

	//�ڴ�
	template<typename T>
	T*			Construct(void* p);	//ִ�й��캯��(�����ѷ����ڴ�)
	template<typename T>
	void		Destruct(T* p);		//ִ����������

	//����
	std::string  MakeAddress(const std::string& sIP,const std::string&	sPort);
	std::string  MakeAddress(const std::string& sIP,const int&			nPort);
	std::string  MakeAddress(const std::string& sIP,const unsigned int&	uPort);
	bool		 ResolveAddress( std::string& sIP,std::string& sPort,const std::string& sAddress );
	VectorString SplitAddress(const std::string& sIP);		//������IP
	VectorString TrimAddress(const VectorString& vAddress);	//��������ַ

	//��ҳ - ���ı���
	std::string EncodeURL(const std::string& sSrc);
	std::string DecodeURL(const std::string& inTmp);
	//��ҳ - ��ȡ����ָ��HTML��ǩ֮����ַ�
	VectorString GetMidStringsHTML(const std::string& sSrc,const std::string& sBegin,const std::string& sEnd);

	//�ļ� - ·��
	//ע��:·��(Path) = �ļ���(Dir) + �ļ���(FileName)
	//Ϊ�˼��ݸ���ƽ̨һ��ʹ��'/'��Ϊ�ļ��еķָ���
	std::string	TrimPath( const std::string& sPath );
	std::string	TrimDir( const std::string& sDir );
	std::string GetFilePath(const std::string& sDir ,const std::string& sFileName);
	bool		IsSpecialDir(const std::string& sPath);
	std::string	PickDir(const std::string& sPath);					//��ȡĿ¼
	std::string	PickFileName(const std::string& sPath);				//��ȡ�ļ���(���� ��չ��)
	std::string	PickFileNameWithOutExt(const std::string& sPath);	//��ȡ�ļ���(������ ��չ��)
	std::string PickFileExt(const std::string& sPath);				//��ȡ�ļ�����չ��
	std::string	AbsPathToRelativePath( const std::string& sPath,const std::string& sCmpPath);//�������·��
	bool		AbsPathToRelativePath(VectorString& vDes,const VectorString& vAbsPath,const std::string& sCmpPath);

	//�ļ� - ��
	bool		OpenFile(std::fstream& fStream,	 const std::string& sFileName,const std::ios_base::openmode& nOpenMode = std::ios_base::in | std::ios_base::out);
	bool		OpenFile(std::ifstream& fStream, const std::string& sFileName,const std::ios_base::openmode& nOpenMode = std::ios_base::in);
	bool		OpenFile(std::ofstream& fStream, const std::string& sFileName,const std::ios_base::openmode& nOpenMode = std::ios_base::out);
	bool		CopyFile(std::ofstream& fDes,std::ifstream& fRes);
	bool		IsOpen(const std::fstream& fStream);
	bool		IsOpen(const std::ifstream& fStream);
	bool		IsOpen(const std::ofstream& fStream);
	UINT		GetFileLength(const std::ifstream& fStream);	//��ȡ�ļ��ܳ���
	UINT		GetFileLength(const std::fstream& fStream);	//��ȡ�ļ��ܳ���
	UINT		GetStreamLength(const std::ifstream& fStream);//��ȡ����δ��ȡ�ĳ���
	UINT		GetStreamLength(const std::fstream& fStream);	//��ȡ����δ��ȡ�ĳ���
	bool		IsFileGood(const std::fstream& fStream);//�Ƿ����
	bool		ResetFile(std::fstream& fStream);		//�����ļ���ָ��

	//�ļ� - �� - �ļ�Ԫ�� ��ȡ/д��(����ɶ�ʹ��)
	bool		FileElement(std::ifstream& fStream,VectorInt& vValue);
	bool		FileElement(std::ofstream& fStream,const VectorInt& vValue);

	bool		FileElement(std::ifstream& fStream,SetInt& vValue);
	bool		FileElement(std::ofstream& fStream,const SetInt& vValue);

	bool		FileElement(std::ifstream& fStream,std::string& sString);
	bool		FileElement(std::ofstream& fStream,const std::string& sString);

	template<typename TValue>
	bool		FileElement(std::ifstream& fStream,TValue& tValue);
	template<typename TValue>
	bool		FileElement(std::ofstream& fStream,const TValue& vValue);

	//XML
	std::string	EncodeXML(const std::string& sSrc);
	void		EncodeXML(VectorString& vValues);
	std::string	GetXMLString(const std::string& sLabel,const MapStringString* pvAttribute,const std::string sValue,int nLayer = 0);
	std::string	GetXMLString(const std::string& sLabel,const MapStringString* pvAttribute,const VectorString* pvValue,int nLayer = 0);

	//��ȡֵ
	template<typename T,typename TArg1>
	bool GetValue(const std::vector<T>& vSrc,TArg1& nArg1);
	template<typename T,typename TArg1,typename TArg2>
	bool GetValue(const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2);
	template<typename T,typename TArg1,typename TArg2,typename TArg3>
	bool GetValue(const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2,TArg3& nArg3);
	template<typename T,typename TArg1,typename TArg2,typename TArg3,typename TArg4>
	bool GetValue(const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2,TArg3& nArg3,TArg4& nArg4);
	template<typename T,typename TArg1,typename TArg2,typename TArg3,typename TArg4,typename TArg5>
	bool GetValue(const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2,TArg3& nArg3,TArg4& nArg4,TArg5& nArg5);

	template<typename T>
	bool GetValueArgs( const std::vector<T>& vSrc,int nArgs,... );//(�����ϸ����� nArgs <= ��������)

	//����ֵ
	template<typename T>
	bool SetValue(std::vector<T>& vSrc,int nArgs,...);//(�����ϸ����� nArgs <= ��������)
	template<typename T>
	bool SetValue(std::vector<T>& vSrc,int nArgs,T* tArray );

	//���
	void Srand();//��ʼ�����

	int	Rand(); //��� ���� RAND_MAX ���ñ�׼�� rand()
	int	Rand(int nBegin,int nEnd);

	uint16 Rand8();
	uint16 Rand16();
	uint32 Rand24();
	uint32 Rand32();
	uint64 Rand40();
	uint64 Rand48();
	uint64 Rand56();
	uint64 Rand64();

	template<typename T>
	int	RandIndex(const std::vector<T>& vSrc);
	template<typename T>
	int	RandIndex(const std::list<T>& vSrc);
	template<typename T>
	int	RandIndex(const std::set<T>& vSrc);
	template<typename T,typename K>
	int	RandIndex(const std::map<T,K>& vSrc);

	template<typename ValuePtr>
	ValuePtr RandPtr(const std::vector<ValuePtr>& vSrc);

	template<typename ValuePtr,typename TKey>
	ValuePtr RandPtr(const std::map<TKey,ValuePtr>& vSrc);

	template<typename T>
	T*		RandValuePtr(const std::vector<T>& vSrc);
	template<typename TKey, typename TValue>
	TValue* RandValuePtr(const std::map<TKey, TValue>& vSrc);

	template<typename T>
	T&		RandValue(const std::vector<T>& vSrc);
	template<typename T>
	T&		RandValue(const std::list<T>& vSrc);
	template<typename T>
	T&		RandValue(const std::set<T>& vSrc);
	template<typename TKey, typename TValue>
	TValue& RandValue(const std::map<TKey, TValue>& vSrc);

	template<typename T>
	const T&		RandValue(const std::vector<T>& vSrc,const T& tDefalut);
	template<typename T>
	const T&		RandValue(const std::set<T>& vSrc, const T& tDefalut);
	template<typename TKey, typename TValue>
	const TValue&	RandValue(const std::map<TKey, TValue>& vSrc, const TValue& tDefalut);

	template<typename T>
	T	RandValue(const std::vector<T>& vSrc,int tDefalut);
	template<typename T>
	T	RandValue(const std::set<T>& vSrc, int tDefalut);

	int	RandValue(const VectorInt& vSrc,int tDefalut);
	int RandValue(const SetInt& vSrc,int tDefalut);

	template<typename T>
	bool  RandValue(const std::vector<T>& vSrc,std::vector<T>& vDes,size_t uCount);
	template<typename T,typename K>
	bool  RandValue(const std::map<T,K>& vSrc,std::vector<K>& vDes,size_t uCount);

	//����Ƴ�
	template<typename T>
	bool RandErase(std::vector<T>& vSrc,size_t uRemoveCounter);//�Ƴ�����
	template<typename T>
	bool RandErase(std::list<T>& vSrc,size_t uRemoveCounter);//�Ƴ�����
	template<typename T>
	bool RandEraseRemain(std::vector<T>& vSrc,size_t uRemain);//ʣ�����
	template<typename T>
	bool RandEraseRemain(std::list<T>& vSrc,size_t uRemain);//ʣ�����

	//�������һ��������
	template<typename T>
	typename std::vector<T>::iterator RandItr(std::vector<T>& vSrc);
	template<typename T>
	typename std::list<T>::iterator RandItr(std::list<T>& vSrc);

	//�������ID
	std::string GenerateID(uint uCount = 40);	//�������ID(����λ��)

	//��� - ����
	template<typename T>
	void Shuffle(std::vector<T>& vValues);

	//��� - ����(���ʿ��Դ���1,uMax >= 1)
	uint RandProbability(uint uProbability,uint uMax=100);

	//��ϣ
	uint Hash(const std::string& sString,	uint nMax);
	uint Hash(uint uValue,					uint nMax);

#define MapEnumInsert(vct,eX) 	vct.insert(std::make_pair(eX,#eX));

	void EnumInsert(MapIntString& vct,int eEnum,const std::string& sValue);
	const std::string& EnumGetString(MapIntString& vct,int eFind,int eDefault);
	int EnumGetString(MapStringInt& vct,const std::string& sFind,int eDefault);

	//�жϲ�������
	inline int GetValueType(const bool&)			{return VALUE_TYPE_BOOL;}
	inline int GetValueType(const char&)			{return VALUE_TYPE_INT8;}
	inline int GetValueType(const unsigned char&)	{return VALUE_TYPE_UINT8;}
	inline int GetValueType(const signed short&)	{return VALUE_TYPE_INT16;}
	inline int GetValueType(const unsigned short&)	{return VALUE_TYPE_UINT16;}
	inline int GetValueType(const signed long&)		{return VALUE_TYPE_INT32;}
	inline int GetValueType(const unsigned long&)	{return VALUE_TYPE_UINT32;}
	inline int GetValueType(const int64&)			{return VALUE_TYPE_INT64;}
	inline int GetValueType(const uint64&)			{return VALUE_TYPE_UINT64;}
	template<typename TType>
	int GetValueType(const TType&)					{return VALUE_TYPE_USER_DEF;}

	//���Ի���
	void LocaleChinese();
	void LocaleC();
	void Locale();

	//ϵͳ
	void Exit();

	//���㵱��ʱ��
	time_t		CalLocalHour(int tTime,time_t tTimeNow );		//������������(ʱ���)
	time_t		CalLocalNextHour(int tTime,time_t tTimeNow);	//������һ������(ʱ���)
	time_t		CalLocalToNextHour(int tTime,time_t tTimeNow);	//���㵽��һ������� ʱ��

	int			GetLocalSec(time_t tTimeNow);		//��ȡ��ǰ��[0,59]
	int			GetLocalMin(time_t tTimeNow);		//��ȡ��ǰ����[0,59]
	int			GetLocalHour(time_t tTimeNow);		//��ȡ��ǰСʱ[0,23]
	int			GetLocalMonth(time_t tTimeNow);		//��ȡ��ǰ�·�[1,31]
	int			GetLocalYear(time_t tTimeNow);		//��ȡ��ǰ�·�
	int			GetLocalMonthDay(time_t tTimeNow);	//��ȡ��ǰ����
	int			GetLocalWeekDay(time_t tTimeNow);	//��ȡ��ǰ���ڼ�[0,6]
	int			GetLocalYearDay(time_t tTimeNow);	//��ȡ��ǰ���ڼ�[0,6]

	std::string PeriodToString(uint uPeriod);								//���� �� �ַ���ת��
	std::string PeriodToString(uint uPeriod,const std::string& sFormat);	//�ֱ��� YYYY-MM-DD:hh-mm-ss ����ʱ����(ע���Сд)
	time_t		StringToPeriod(const std::string& sPeriod );				//�ַ��� �� ���ڵ�ת��
	
	std::string TimeToString(time_t tTime);								//��ʽ %4d-%02d-%02d %02d:%02d:%02d
	std::string TimeToString(time_t tTime,const std::string& sFormat);	//�ֱ��� YYYY-MM-DD:hh-mm-ss ����ʱ����(ע���Сд)
	bool		StringToTime(const std::string& sSrc,time_t& tDes);		//ֻ�ܽ��� %4d-%02d-%02d %02d:%02d:%02d 
	std::string TimeToStringMill(uint64 tTime);								//��ʽ %4d-%02d-%02d %02d:%02d:%02d
	std::string TimeToStringMill(uint64 tTime, const std::string& sFormat);	//�ֱ��� YYYY-MM-DD:hh-mm-ss ����ʱ����(ע���Сд)


	std::string DateToString(time_t tTime);			//��ʽ YYYY-MM-DD
	std::string DateToStringNumber(time_t tTime);	//�������� 20151020������
	bool		StringToDate(time_t& tDes,const std::string& sSrc,const std::string& sFormat);
	bool		StringToDate(const std::string& sSrc,time_t& tDes);		//ֻ�ܽ��� YYYY-MM-DD �� YYYYMMDD ����
	time_t		ToTime( int nYear,int nMonth,int nDay,int nHour=0,int nMin=0,int nSec=0 );

	int			GetSecondsEveryMinute();				//ÿ��������
	int			GetSecondsEveryHour();					//ÿСʱ����
	int			GetSecondsEveryDay(int nHours = 24);	//ÿ������
	int			GetSecondsEveryWeek(int nDays = 7);		//ÿ������
	int			GetSecondsEveryMonth(int nDays = 30);	//ÿ������
	int			GetSecondsEveryYear(int nDays = 365);	//ÿ������

	//�����ֽ�������λ
	uint64		GetBytesEveryKB();						//ÿKB�ֽ���
	uint64		GetBytesEveryMB();						//ÿMB�ֽ���
	uint64		GetBytesEveryGB();						//ÿGB�ֽ���
	uint64		GetBytesEveryTB();						//ÿTB�ֽ���
	uint64		GetBytesEveryPB();						//ÿPB�ֽ���

	//���ֿɶ�
	std::string ValueToRead(uint64 uValue,uint uUint=3);			//ת���ַ���( 1024->1,024 6316541654->6,316,541,654)
	uint64		ReadToValue(const std::string& sRead,uint uUint=3);	//ת���ַ���( 1024->1,024 6316541654->6,316,541,654)

	//ʱ��ɶ�
	std::string TimeToRead(uint64 uValue);					//ת��ʱ��(3366->3:36:02)
	uint64		ReadToTime(const std::string& sRead);		

	//���ڴ浼��Ϊʮ�������ַ���
	std::string ConvertBuff(const char* szBuff,uint uLength);

	//��ʮ�������ַ�������Ϊ�ڴ� 
	bool ConvertValue(const std::string sSrc,char* sDes,size_t nDesLen);
	bool ConvertValue(const char* sSrc, size_t nSrcLen,char* sDes, size_t nDesLen);

	//����
	bool Clear(std::string& sString);
	bool Clear(std::stringstream& sStream);

	//�ڴ�����
	template<typename T>
	bool MemClear(T* pTStruct);
	template<typename T>
	bool MemClear(T& t);
	bool MemClear(void* p, size_t uLen);

	//�ڴ濽��
	template<typename T1,typename T2>
	bool MemCopy(T1& tDes,const T2& tSrc);
	template<typename T1,typename T2>
	bool MemCopy(std::vector<T1>& tDes,const std::vector<T2>& tSrc);
	template<typename T1,typename T2>
	bool MemCopy(std::set<T1>& tDes,const std::set<T2>& tSrc);
	template<typename TKey1,typename TValue1,typename TKey2,typename TValue2>
	bool MemCopy(std::map<TKey1,TValue1>& tDes,const std::map<TKey2,TValue2>& tSrc);

	bool MemCopyPtr(void* tDes,const void* tSrc, size_t nLen);

	//����ڴ�Խ�����(����new delete�ķ�ʽ��� ��Ҫ�����ڴ�����ʱ�ĵ�ַ�������µĵ�ַ)
	void* MemCheck(void* pSrc, size_t uMax);

	//�ڴ��Ƿ�һ��
	bool MemCmp(const void* p1, size_t uLen1, const void* p2, size_t uLen2);
	bool MemCmp(const void* p1, const void* p2, size_t uLen);

	//�ڴ��ӡ
	std::string MemString (const void* p, size_t uLen);
	bool		MemPrint  (const void* p, size_t uLen);

	//�ڴ�ռ��
	template<typename T>
	int SizeOf(T* pT);
	template<typename T>
	int SizeOf();

	//����ǩ�� - CodeSign
	const MapStringString&	GetVarCodeSignMap();
	const std::string		GetVarCodeSign(const std::string& sType);

	//�����������ǩ��
#define	DEFINE_VAR_CODE_SIGN(tType,tString)			inline const std::string	GetVarCodeSignByType(tType ){return GetVarCodeSign(tString);}
#define	DEFINE_VAR_CODE_SIGN_TYPE(tType)			DEFINE_VAR_CODE_SIGN(tType const &,#tType)
#define DEFINE_FUN_CODE_SIGN(tReturn,tArg1,tArg2)	inline const std::string&	MakeFunCodeSign(tReturn(*fnCodeSign)(tArg1,tArg2)){ static std::string sCodeSign;	if(sCodeSign.empty()){std::stringstream sStream;sStream<<GetVarCodeSign(#tReturn)<<GetVarCodeSign(#tArg1)<<GetVarCodeSign(#tArg2);sCodeSign = sStream.str();}  return sCodeSign;}

	//����������ͺ���ǩ��
	DEFINE_VAR_CODE_SIGN(void,"void");
	DEFINE_VAR_CODE_SIGN_TYPE(bool);
	DEFINE_VAR_CODE_SIGN_TYPE(char);
	DEFINE_VAR_CODE_SIGN_TYPE(unsigned char);
	DEFINE_VAR_CODE_SIGN_TYPE(short);
	DEFINE_VAR_CODE_SIGN_TYPE(unsigned short);
	DEFINE_VAR_CODE_SIGN_TYPE(int);
	DEFINE_VAR_CODE_SIGN_TYPE(unsigned int);
	DEFINE_VAR_CODE_SIGN_TYPE(long);
	DEFINE_VAR_CODE_SIGN_TYPE(unsigned long);
	DEFINE_VAR_CODE_SIGN_TYPE(float);
	DEFINE_VAR_CODE_SIGN_TYPE(double);

	//���庯������ǩ��
	DEFINE_FUN_CODE_SIGN(double,double,	double);
	DEFINE_FUN_CODE_SIGN(long,	long,	long);
	DEFINE_FUN_CODE_SIGN(void,	long,	long);

	template<typename TFun>
	std::string MakeCodeSign(const std::string& sFunName,TFun fnName);

	//����ǩ��
#define MAKE_CODE_SIGN(fnName) MakeCodeSign(#fnName,fnName)

	//����
	const VectorInt&	ZeroVectorInt();						//Zero
	const std::string&	EmptyString();							//EmptyString
	const VectorString&	EmptyVectorString();					//EmptyString
	const VectorInt&	EmptyVectorInt();
};

template<typename T>
T* ToolFrame::Construct( void* p )
{
	return new (p)T;
}

template<typename T>
void ToolFrame::Destruct( T* p )
{
	if (p)
		p->~T();
}

template<typename T>
const T* ToolFrame::MinPtr( const T* pT1,const T* pT2 )
{
	return (*pT1) < (*pT2) ? pT1:pT2;
}

template<typename T>
const T* ToolFrame::MaxPtr( const T* pT1,const T* pT2 )
{
	return (*pT1) > (*pT2) ? pT1:pT2;
}

template<typename TKey>
TKey* ToolFrame::GetValuePtrByKey( const std::set<TKey>& v,const TKey& tKey )
{
	typename std::set<TKey>::const_iterator itr = v.find(tKey);
	return itr == v.end() ? nullptr  : (TKey*)&(*itr);
}

template<typename T,typename Arg>
bool ToolFrame::InsertByIndex( std::vector<T>& v,const Arg& tArg,int nIndex,bool bBack/*=false*/ )
{
	//ʵ�ʵߵ�
	if (bBack)
		nIndex = (int)v.size() + 1 - nIndex;

	if (nIndex > (int)v.size() + 1 || nIndex < 0)			//������Ч�±�
		return false;

	if (nIndex > (int)v.size())
		v.push_back(tArg);
	else
		v.insert(v.begin() + nIndex,tArg);
	return true;
}

template<typename TKey,typename TValue>
bool ToolFrame::IsEqual( const std::map<TKey,TValue>& vSrc, const std::map<TKey,TValue>& vDes )
{
	if (IsSelf(vSrc,vDes))return true;
	if (vSrc.empty() == vDes.empty())return true;
	if (vSrc.size() != vDes.size())	return false;
	typename std::map<TKey,TValue>::const_iterator itrSrc = vSrc.begin(),itrDes = vDes.begin();
	for(;itrSrc != vSrc.end();++itrSrc,++itrDes)
		if (itrSrc->second != itrDes->second) return false;
	return true;
}

template<typename T,typename TArg>
bool ToolFrame::SetValueByIndex( std::vector<T>& v,int nIndex,const TArg& tArg )
{
	if (!ToolFrame::IsVaildIndex(v,nIndex))return false;
	v[nIndex] = tArg;
	return true;
}

template<typename TArg>
bool ToolFrame::SetValueByIndex( VectorString& v,int nIndex,const TArg& tArg )
{
	if (!ToolFrame::IsVaildIndex(v,nIndex))return false;
	v[nIndex] = ToString(tArg);
	return true;
}

template<typename T,typename TArg1,typename TArg2,typename TArg3,typename TArg4,typename TArg5>
bool ToolFrame::GetValue( const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2,TArg3& nArg3,TArg4& nArg4,TArg5& nArg5 )
{
	if(vSrc.size()<5)return false;
	if(!ToValue(vSrc[0],nArg1))return false;
	if(!ToValue(vSrc[1],nArg2))return false;
	if(!ToValue(vSrc[2],nArg3))return false;
	if(!ToValue(vSrc[3],nArg4))return false;
	if(!ToValue(vSrc[4],nArg5))return false;
	return true;
}

template<typename T,typename TArg1,typename TArg2,typename TArg3,typename TArg4>
bool ToolFrame::GetValue( const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2,TArg3& nArg3,TArg4& nArg4 )
{
	if(vSrc.size()<4)return false;
	if(!ToValue(vSrc[0],nArg1))return false;
	if(!ToValue(vSrc[1],nArg2))return false;
	if(!ToValue(vSrc[2],nArg3))return false;
	if(!ToValue(vSrc[3],nArg4))return false;
	return true;
}

template<typename T,typename TArg1,typename TArg2,typename TArg3>
bool ToolFrame::GetValue( const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2,TArg3& nArg3 )
{
	if(vSrc.size()<3)return false;
	if(!ToValue(vSrc[0],nArg1))return false;
	if(!ToValue(vSrc[1],nArg2))return false;
	if(!ToValue(vSrc[2],nArg3))return false;
	return true;
}

template<typename T,typename TArg1,typename TArg2>
bool ToolFrame::GetValue( const std::vector<T>& vSrc,TArg1& nArg1,TArg2& nArg2 )
{
	if(vSrc.size()<2)return false;
	if(!ToValue(vSrc[0],nArg1))return false;
	if(!ToValue(vSrc[1],nArg2))return false;
	return true;
}

template<typename T,typename TArg1>
bool ToolFrame::GetValue( const std::vector<T>& vSrc,TArg1& nArg1 )
{
	if(vSrc.size()<1)return false;
	if(!ToValue(vSrc[0],nArg1))return false;
	return true;
}

template<typename T,typename K>
K ToolFrame::PopBackPtr( std::map<T,K>& vSrc )
{
	if (vSrc.empty())return K();
	return PopBack(vSrc);
}

template<typename T>
T ToolFrame::PopBackPtr( std::list<T>& vSrc )
{
	if (vSrc.empty())return T();
	return PopBack(vSrc);
}

template<typename T>
T ToolFrame::PopBackPtr( std::vector<T>& vSrc )
{
	if (vSrc.empty())return T();
	return PopBack(vSrc);
}

template<typename T,typename K>
K ToolFrame::PopFrontPtr( std::map<T,K>& vSrc )
{
	if (vSrc.empty())return K();
	return PopFront(vSrc);
}

template<typename T>
T ToolFrame::PopFrontPtr( std::list<T>& vSrc )
{
	if (vSrc.empty())return T();
	return PopFront(vSrc);
}

template<typename T>
T ToolFrame::PopFrontPtr( std::vector<T>& vSrc )
{
	if (vSrc.empty())return T();
	return PopFront(vSrc);
}

template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
bool ToolFrame::SafeInsert( std::map<TKey,TValue>& vMap,const TKeyInsert& tKey,const TValueInsert& kValue )
{
	if (vMap.find(tKey) == vMap.end()){
		vMap.insert(std::make_pair(tKey,kValue));
		return true;
	}
	
	return false;
}

template<typename T>
bool ToolFrame::GetValueByString( const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T& t )
{
	VectorString vString;
	if (!ToolFrame::GetStringByFormat(vString,sSrc,sValueFlag,sTempalte))return false;
	if (vString.size()<1)return false;

	if (!ToolFrame::ToValue(vString[0],t))return false;
	return true;
}

template<typename T1,typename T2>
bool ToolFrame::GetValueByString( const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2 )
{
	VectorString vString;
	if (!ToolFrame::GetStringByFormat(vString,sSrc,sValueFlag,sTempalte))return false;
	if (vString.size()<2)return false;

	if (!ToolFrame::ToValue(vString[0],t1))return false;
	if (!ToolFrame::ToValue(vString[1],t2))return false;
	return true;
}

template<typename T1,typename T2,typename T3>
bool ToolFrame::GetValueByString( const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2,T3 & t3 )
{
	VectorString vString;
	if (!ToolFrame::GetStringByFormat(vString,sSrc,sValueFlag,sTempalte))return false;
	if (vString.size()<3)return false;

	if (!ToolFrame::ToValue(vString[0],t1))return false;
	if (!ToolFrame::ToValue(vString[1],t2))return false;
	if (!ToolFrame::ToValue(vString[2],t3))return false;
	return true;
}

template<typename T1,typename T2,typename T3,typename T4>
bool ToolFrame::GetValueByString( const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2,T3 & t3,T4 & t4 )
{
	VectorString vString;
	if (!ToolFrame::GetStringByFormat(vString,sSrc,sValueFlag,sTempalte))return false;
	if (vString.size()<4)return false;

	if (!ToolFrame::ToValue(vString[0],t1))return false;
	if (!ToolFrame::ToValue(vString[1],t2))return false;
	if (!ToolFrame::ToValue(vString[2],t3))return false;
	if (!ToolFrame::ToValue(vString[3],t4))return false;
	return true;
}

template<typename T1,typename T2,typename T3,typename T4,typename T5>
bool ToolFrame::GetValueByString( const std::string& sSrc,const std::string& sValueFlag,const std::string& sTempalte,T1& t1,T2 & t2,T3 & t3,T4 & t4,T5 & t5 )
{
	VectorString vString;
	if (!ToolFrame::GetStringByFormat(vString,sSrc,sValueFlag,sTempalte))return false;
	if (vString.size()<5)return false;

	if (!ToolFrame::ToValue(vString[0],t1))return false;
	if (!ToolFrame::ToValue(vString[1],t2))return false;
	if (!ToolFrame::ToValue(vString[2],t3))return false;
	if (!ToolFrame::ToValue(vString[3],t4))return false;
	if (!ToolFrame::ToValue(vString[4],t5))return false;
	return true;
}

template<typename Key,typename Value,typename Arg>
uint ToolFrame::EraseByValueAll( std::map<Key,std::list<Value> >& vMap,const Arg& tVal )
{
	if (vMap.empty())return 0;

	uint uCount = 0;
	typename std::map<Key,std::vector<Value> >::iterator itr;
	foreach(itr,vMap){
		uCount += EraseByValueAll(itr->second,tVal);
	}
	return uCount;
}

template<typename Key,typename Value,typename Arg>
uint ToolFrame::EraseByValueAll( std::map<Key,std::vector<Value> >& vMap,const Arg& tVal )
{
	if (vMap.empty())return 0;

	uint uCount = 0;
	typename std::map<Key,std::vector<Value> >::iterator itr;
	foreach(itr,vMap){
		uCount += EraseByValueAll(itr->second,tVal);
	}
	return uCount;
}

template<typename T>
void ToolFrame::PushSameValue( std::vector<T>& vDes,const std::vector<T>& vArg,int nCount )
{
	for (int nIndex = 0 ;nIndex<nCount;++nIndex)
		ToolFrame::Merge(vDes,vArg);
}

template<typename T,typename Arg>
uint ToolFrame::EraseByValueAll( std::list<T>& vVct,const Arg& tVal )
{
	if (vVct.empty())return 0;

	uint uCount = 0;
	typename std::list<T>::iterator itr = vVct.begin();
	while(itr != vVct.end()){
		if (tVal == *itr){
			itr = EraseByItr(vVct,itr);
			++uCount;
			continue;
		}
		++itr;
	}

	return uCount;
}

template<typename T,typename Arg>
uint ToolFrame::EraseByValueAll( std::vector<T>& vVct,const Arg& tVal )
{
	if (vVct.empty())return 0;

	uint uCount = 0;
	for (uint uSize = vVct.size();uSize != 0;--uSize)
	{
		uint uIndex = uSize - 1;
		if (tVal == vVct[uIndex])
		{
			vVct.erase(vVct.begin() + uIndex);
			++uCount;
		}
	}
	return uCount;
}

template<typename Key,typename Value,typename Arg>
bool ToolFrame::EraseByValue( std::map<Key,std::vector<Value> >& vMap,const Key& tKey,const Arg& tVal )
{
	if (vMap.empty())return false;

	typename std::vector<Value>* pvClientID = ToolFrame::GetValuePtrByKey(vMap,tKey);
	if (!pvClientID)return false;

	if (!ToolFrame::EraseByValue(*pvClientID,tVal))return false;

	if (pvClientID->empty())
		vMap.erase(tKey);

	return true;
}

template<typename Key,typename Value,typename Arg>
bool ToolFrame::EraseByValue( std::map<Key,std::vector<Value> >& vMap,const Arg& tVal )
{
	if (vMap.empty())return false;

	typename std::map<Key,std::vector<Value> >::iterator itr;
	foreach(itr,vMap){
		if (EraseByValue(itr->second,tVal))return true;
	}
	return false;
}

template<typename T,typename K>
bool ToolFrame::ToValue( const std::map<T,K>& tSrc, std::string& tDes,const std::string& sSpLine/*=" "*/,const std::string& sSpKeyValue/*=":"*/ )
{
	if (tSrc.empty())return true;

	std::stringstream sStream;

	bool bFirst = true;

	typename std::map<T,K>::const_iterator itr;
	foreach(itr,tSrc){
		if (!bFirst)
			sStream<<sSpLine;

		std::string sKey;std::string sValue;
		if (!ToValue(itr->first,sKey))return false;
		if (!ToValue(itr->second,sValue))return false;
		sStream <<sKey <<sSpKeyValue<<sValue;

		bFirst = false;
	}

	tDes = sStream.str();
	return true;
}

template<typename T,typename K>
bool ToolFrame::ToValue( const std::string& tSrc,std::map<T,K>& tDes,const std::string& sSpLine/*=" "*/,const std::string& sSpKeyValue/*=":"*/ )
{
	if (tSrc.empty())return true;

	VectorString vLine;
	if (!ToolFrame::SplitString(vLine,tSrc,sSpLine))return false;

	VectorString::const_iterator itr;
	foreach(itr,vLine){
		const std::string& sLine = *itr;

		uint uOffSet = sLine.find(sSpKeyValue);
		if (std::string::npos == uOffSet)return false;
		
		std::string s1 = sLine.substr(0,uOffSet);
		std::string s2 = sLine.substr(uOffSet+sSpKeyValue.length(),sLine.length() - uOffSet);

		T t;K k;
		if (!ToValue(s1,t))return false;
		if (!ToValue(s2,k))return false;
		if (!Insert(tDes,t,k))return false;
	}

	return true;
}

template <typename T>
std::string ToolFrame::ToString( const T& tValue,const std::string& sSp/*=','*/ )
{
	std::string sDes;
	if (!ToValue(tValue,sDes,sSp))return "";

	return sDes;
}

template<typename T>
bool ToolFrame::ToValue( const T& tSrc,std::string* sDes,int nWidth /*= 0*/,char cFill /*= ' '*/ )
{
	if (!sDes)return false;
	return ToValue(tSrc,*sDes);
}

template<typename T>
bool ToolFrame::ToValue( const T& tSrc,std::string& sDes,int nWidth /*= 0*/,char cFill /*= ' '*/ )
{
	std::stringstream ss;
	ss.fill(cFill);
	ss.width(nWidth);
	ss << std::fixed;
	ss << tSrc;

	sDes = ss.str();
	return true;
}

template <typename T,typename TCount>
const T& ToolFrame::Max( const T* tArray,TCount tCountMax )
{
	assert(tArray && tCountMax>0);

	TCount tIndexMax=0;
	for(TCount tCount=0;tCount<tCountMax;++tCount){
		if(tArray[tCount] > tArray[tIndexMax])
			tIndexMax = tCount;
	}
	return tArray[tIndexMax];
}

template <typename T1,typename T2>
const T1 ToolFrame::Max( const T1& t1,const T2& t2 )
{
	return t1 >= t2 ? t1 : t2;
}

template <typename T1>
const T1& ToolFrame::Max( const T1& t1,const T1& t2 )
{
	return t1 >= t2 ? t1 : t2;
}

template <typename T,typename TCount>
const T& ToolFrame::Min( const T* tArray,TCount tCountMax )
{
	assert(tArray && tCountMax>0);

	TCount tIndexMin=0;
	for(TCount tCount=0;tCount<tCountMax;++tCount){
		if(tArray[tCount] < tArray[tIndexMin])
			tIndexMin = tCount;
	}
	return tArray[tIndexMin];
}

template <typename T1,typename T2>
T1 ToolFrame::Min( const T1& t1,const T2& t2 )
{
	return t1 <= t2 ? t1 : t2;
}

template <typename T1>
const T1& ToolFrame::Min( const T1& t1,const T1& t2 )
{
	return t1 <= t2 ? t1 : t2;
}

template<typename T>
bool ToolFrame::Reverse( std::list<T>& vDes,const std::list<T>& vSrc )
{
	if (IsSelf(vSrc,vDes))
	{
		typename std::list<T> vTarget;
		if (!Reverse(vTarget,vSrc))return false;
		vDes = vTarget;
		return true;
	}

	typename std::list<T>::const_reverse_iterator itr;
	foreachR(itr,vSrc){
		vDes.push_back(*itr);
	}
	return true;
}

template<typename T>
bool ToolFrame::Reverse( std::vector<T>& vDes,const std::vector<T>& vSrc )
{
	if (IsSelf(vSrc,vDes))
	{
		typename std::vector<T> vTarget;
		if (!Reverse(vTarget,vSrc))return false;
		vDes = vTarget;
		return true;
	}

	typename std::vector<T>::const_reverse_iterator itr;
	foreachR(itr,vSrc){
		vDes.push_back(*itr);
	}
	return true;
}

template<typename T,typename TArg>
bool ToolFrame::IsTargetClass( TArg* pArg )
{
	return nullptr != dynamic_cast<T*>(pArg);
}

template<typename T,typename K>
bool ToolFrame::InsertString( MapIntString& vMap,const T& tKey,const K& tValue )
{
	int nKey = tKey;
	return Insert(vMap,nKey,ToString(tValue));
}

template<typename T>
bool ToolFrame::InsertString( MapIntString& vMap,int nKey,const T& tValue )
{
	return Insert(vMap,nKey,ToString(tValue));
}

template<typename T>
int ToolFrame::Difference( const T& a,const T& b )
{
	return a > b ? int(a - b) : - int(b-a);
}

template<typename T>
typename std::set<T>::iterator ToolFrame::EraseByItr( std::set<T>& vSrc,typename std::set<T>::iterator& itr )
{
	if(itr == vSrc.end())return vSrc.end();

	typename std::set<T>::iterator itrNext = itr;
	++itrNext;

	if (itrNext != vSrc.end())
	{
		const T& key = *itrNext;
		vSrc.erase(itr);
		return vSrc.find(key);
	}else{
		vSrc.erase(itr);
		return vSrc.end();
	}
	assert(false);
	return vSrc.end();
}

template<typename T>
bool ToolFrame::PopBack( std::vector<T>& vSrc,const T& t )
{
	if(vSrc.empty())return false;

	if (vSrc.back() != t)return false;

	return EraseBack(vSrc);
}

template<typename T>
bool ToolFrame::InsertString( VectorString& vString,const T& t )
{
	vString.push_back(ToString(t));
	return true;
}

template<typename TKey1,typename TValue1,typename TKey2,typename TValue2>
bool ToolFrame::MemCopy( std::map<TKey1,TValue1>& tDes,const std::map<TKey2,TValue2>& tSrc )
{
	tDes.clear();

	typename std::map<TKey2,TValue2>::const_iterator itr;
	foreach(itr,tSrc){
		TKey1 tKey;TValue1 tValue;
		if (!MemCopy(tKey,itr->first))return false;
		if (!MemCopy(tValue,itr->second))return false;

		tDes.insert(std::make_pair(tKey,tValue));
	}
	return true;
}

template<typename T,typename K,typename Value>
const T& ToolFrame::GetKeyByKeyMax( const std::map<T,K>& vMap,const Value& tDefault )
{
	if (vMap.empty())return tDefault;

	return (--vMap.end())->first;
}

template<typename T>
bool ToolFrame::Split( const std::vector<T>& vSrc,std::vector<T>& vDes1,std::vector<T>& vDes2,size_t uNum )
{
	if(vSrc.size() < uNum)return false;
	for (size_t uIndex =0;uIndex < vSrc.size();++uIndex)
	{
		if (uIndex < uNum)
		{
			vDes1.push_back(vSrc[uIndex]);
		}else{
			vDes2.push_back(vSrc[uIndex]);
		}
	}
	return true;
}

template<typename T>
bool ToolFrame::EraseByIndex( std::vector<T>& vVct,int nIndex )
{
	if (nIndex >= vVct.size() || nIndex < 0 )return false;

	vVct.erase(vVct.begin() + nIndex);

	return true;
}

template<typename T>
bool ToolFrame::RandEraseRemain( std::list<T>& vSrc,size_t uRemain )
{
	if (uRemain > vSrc.size())return false;
	return RandErase(vSrc,vSrc.size() - uRemain);
}

template<typename T>
bool ToolFrame::RandEraseRemain( std::vector<T>& vSrc,size_t uRemain )
{
	if (uRemain > vSrc.size())return false;
	return RandErase(vSrc,vSrc.size() - uRemain);
}

template<typename T>
T ToolFrame::GetNullPtr()
{
	return T();
}

template<typename T1,typename T2,typename T3>
bool ToolFrame::IsUnique( const T1& t1,const T2& t2,const T3& t3 )
{
	return (t1 && !t2 && !t3) || (!t1 && t2 && !t3) || (!t1 && !t2 && t3);
}

template<typename T1,typename T2>
bool ToolFrame::IsUnique( const T1& t1,const T2& t2 )
{
	return (t1 && !t2) || (!t1 && t2);
}

template<typename Key,typename Value>
typename std::map<Key,Value>::iterator ToolFrame::FindItrMinValue( std::map<Key,Value>& vMap )
{
	typename std::map<Key,Value>::iterator itrMin = vMap.end();

	typename std::map<Key,Value>::iterator itr;
	foreach(itr,vMap){
		if (itrMin == vMap.end() || itr->second < itrMin->second)
			itrMin = itr;
	}

	return itrMin;
}

template<typename Key,typename Value>
typename std::map<Key,Value>::iterator ToolFrame::FindItrMinKey( std::map<Key,Value>& vMap )
{
	return vMap.begin();
}

template<typename TKey,typename TValue,typename Arg>
TValue& ToolFrame::GetValueByKeyForce( std::map<TKey,TValue>& vMap,const Arg& tKey )
{
	typename std::map<TKey,TValue>::iterator itr = vMap.find(tKey);
	if (itr == vMap.end())
	{
		vMap[tKey]=TValue();
		return vMap[tKey];
	}
	return itr->second;
}

template <typename Tkey,typename Tvalue>
const Tvalue& ToolFrame::GetValueByIndex( const std::map<Tkey,Tvalue>& vSrc, int nIndex,const Tvalue& tValue )
{
	if (vSrc.empty())return tValue;
	if (!IsInClosedInterval<int>(nIndex,0,vSrc.size()-1))return tValue;

	return GetValueByIndex(vSrc,nIndex);
}

template <typename Tvalue>
const Tvalue& ToolFrame::GetValueByIndex( const std::set<Tvalue>& vSrc, int nIndex,const Tvalue& tValue )
{
	if (vSrc.empty())return tValue;
	if (!IsInClosedInterval<int>(nIndex,0,vSrc.size()-1))return tValue;

	return GetValueByIndex(vSrc,nIndex);
}

template <typename Tvalue>
const Tvalue& ToolFrame::GetValueByIndex( const std::list<Tvalue>& vSrc, int nIndex,const Tvalue& tValue )
{
	if (vSrc.empty())return tValue;
	if (!IsInClosedInterval<int>(nIndex,0,(int)vSrc.size()-1))return tValue;

	return GetValueByIndex(vSrc,nIndex);
}

template <typename Tvalue>
const Tvalue& ToolFrame::GetValueByIndex( const std::vector<Tvalue>& vSrc, int nIndex,const Tvalue& tValue )
{
	if (vSrc.empty())return tValue;
	if (!IsInClosedInterval<int>(nIndex,0,vSrc.size()-1))return tValue;

	return GetValueByIndex(vSrc,nIndex);
}

template <typename T, typename Key>
T ToolFrame::GetPtrValueByIndex(const std::map<Key, T>& vSrc, int nIndex)
{
	if (!IsVaildIndex(vSrc, nIndex))return T();
	return GetValueByIndex(vSrc, nIndex);
}

template <typename T>
T ToolFrame::GetPtrValueByIndex( const std::list<T>& vSrc, int nIndex )
{
	if(!IsVaildIndex(vSrc,nIndex))return T();
	return GetValueByIndex(vSrc,nIndex);
}

template <typename T>
T ToolFrame::GetPtrValueByIndex( const std::vector<T>& vSrc, int nIndex )
{
	if(!IsVaildIndex(vSrc,nIndex))return T();
	return GetValueByIndex(vSrc,nIndex);
}

template <typename Tkey,typename Tvalue>
Tvalue& ToolFrame::GetValueByIndex( const std::map<Tkey,Tvalue>& vSrc, int nIndex )
{
	assert(!vSrc.empty());
	assert(IsInClosedInterval<int>(nIndex,0,vSrc.size()-1));

	//����һ����Ӻ���ǰ
	if (nIndex > (int)vSrc.size() / 2)
	{
		typename std::map<Tkey,Tvalue>::const_iterator itr = vSrc.end();
		for (int nCount = (int)vSrc.size();nCount > nIndex;--nCount)
			--itr;

		return  (Tvalue&)itr->second;
	}else{
		typename std::map<Tkey,Tvalue>::const_iterator itr = vSrc.begin();
		for (int nCount = 0;nCount < nIndex; ++ nCount)
			++itr;

		return (Tvalue&)itr->second;
	}

	assert(false);
	return (Tvalue&)*vSrc.begin();
}

template <typename Tvalue>
Tvalue& ToolFrame::GetValueByIndex( const std::set<Tvalue>& vSrc, int nIndex )
{
	assert(!vSrc.empty());
	assert(IsInClosedInterval<int>(nIndex,0, (int)vSrc.size()-1));

	//����һ����Ӻ���ǰ
	if (nIndex > (int)vSrc.size() / 2)
	{
		typename std::set<Tvalue>::const_iterator itr = vSrc.end();
		for (int nCount = (int)vSrc.size();nCount > nIndex;--nCount)
			--itr;

		return  (Tvalue&)*itr;
	}else{
		typename std::set<Tvalue>::const_iterator itr = vSrc.begin();
		for (int nCount = 0;nCount < nIndex; ++ nCount)
			++itr;

		return  (Tvalue&)*itr;
	}

	assert(false);
	return (Tvalue&)*vSrc.begin();
}

template <typename Tvalue>
Tvalue& ToolFrame::GetValueByIndex( const std::list<Tvalue>& vSrc, int nIndex )
{
	assert(!vSrc.empty());
	assert(IsInClosedInterval<int>(nIndex,0,(int)vSrc.size()-1));

	//����һ����Ӻ���ǰ
	if (nIndex > (int)vSrc.size() / 2)
	{
		typename std::list<Tvalue>::const_iterator itr = vSrc.end();
		for (int nCount = (int)vSrc.size();nCount > nIndex;--nCount)
			--itr;

		return (Tvalue&)*itr;
	}else{
		typename std::list<Tvalue>::const_iterator itr = vSrc.begin();
		for (int nCount = 0;nCount < nIndex; ++ nCount)
			++itr;

		return  (Tvalue&)*itr;
	}

	assert(false);
	return (Tvalue&)*vSrc.begin();
}

template <typename Tvalue>
Tvalue& ToolFrame::GetValueByIndex( const std::vector<Tvalue>& vSrc, int nIndex )
{
	assert(!vSrc.empty());
	assert(IsInClosedInterval<int>(nIndex,0, (int)vSrc.size()-1));

	return (Tvalue&)vSrc[nIndex];//���ܻ����
}

template<typename T>
T& ToolFrame::RandValue( const std::set<T>& vSrc )
{
	assert(!vSrc.empty());

	return GetValueByIndex(vSrc,RandIndex(vSrc));
}

template<typename TKey, typename TValue>
TValue& ToolFrame::RandValue(const std::map<TKey, TValue>& vSrc)
{
	assert(!vSrc.empty());

	return GetValueByIndex(vSrc, RandIndex(vSrc));
}

template<typename T>
T& ToolFrame::RandValue( const std::list<T>& vSrc )
{
	assert(!vSrc.empty());
	return GetValueByIndex(vSrc,RandIndex(vSrc));
}

template<typename T>
T& ToolFrame::RandValue( const std::vector<T>& vSrc )
{
	assert(!vSrc.empty());

	return GetValueByIndex(vSrc,RandIndex(vSrc));
}

template<typename T>
T& ToolFrame::CreateValue( std::list<T>& vVct )
{
	vVct.push_back(T());
	return vVct.back();
}

template<typename T>
T& ToolFrame::CreateValue( std::vector<T>& vVct )
{
	vVct.push_back(T());
	return vVct.back();
}

template<typename T,typename K,typename Value>
const T& ToolFrame::GetKeyByValue( const std::map<T,K>& vMap,const Value& tValue,const T& tDefault )
{
	typename std::map<T,K>::const_iterator itr;
	foreach(itr,vMap){
		if (tValue == itr->second)
			return itr->first;
	}
	return tDefault;
}

template<typename T>
bool ToolFrame::IsInOpenInterval( const T& tVal,const T& tBegin,const T& tEnd )
{
	assert(tBegin < tEnd);
	return tVal>tBegin && tVal<tEnd;
}

template<typename T>
bool ToolFrame::IsInClosedInterval( const T& tVal,const T& tBegin,const T& tEnd )
{
	assert(tBegin <= tEnd);
	return tVal>=tBegin && tVal<=tEnd;
}

template<typename T>
const T& ToolFrame::GetValueInClosedInterval( const T& tVal,const T& tBegin,const T& tEnd )
{
	if (tVal <= tBegin)return tBegin;
	if (tVal >= tEnd)return tEnd;

	return tVal;
}

template<typename T>
const T& ToolFrame::GetValueInOpenInterval( const T& tVal,const T& tBegin,const T& tEnd )
{
	if (tVal < tBegin)return tBegin;
	if (tVal > tEnd)return tEnd;

	return tVal;
}

template<typename T>
bool ToolFrame::Merge( std::vector<T>& vDes, const T& tSrc ,bool bBack)
{
	if (bBack)
	{
		vDes.push_back(tSrc);
		return true;
	}
	
	vDes.insert(vDes.begin(), tSrc);
	return true;
}

template<typename T>
bool ToolFrame::Merge( std::set<T>& vDes,const T& tSrc )
{
	return Insert(vDes,tSrc);
}

template<typename T>
bool ToolFrame::Merge( std::list<T>& vDes,const T& tSrc, bool bBack)
{
	bBack ? vDes.push_back(tSrc): vDes.push_front(tSrc);
	return true;
}

template<typename T>
bool ToolFrame::ToValue(const std::vector<T>& vSrc,std::string& sDes,const std::string& sSp){
	if (vSrc.empty()){sDes = "";return true;}

	bool bFrist = true;

	std::string sTemp;

	std::stringstream sStream;
	typename std::vector<T>::const_iterator itr;
	foreach(itr,vSrc){
		if (!bFrist)
			sStream<<sSp;

		if (!ToValue(*itr,sTemp))
		{
			sDes = "";
			return false;
		}

		sStream<<sTemp;

		bFrist = false;
	}

	sDes = sStream.str();
	return true;
}

template<typename T>
bool ToolFrame::ToValue( const std::list<T>& vSrc,std::string& sDes,const std::string& sSp/*=","*/ ){
	if (vSrc.empty()){sDes = "";return true;}

	bool bFrist = true;

	std::string sTemp;

	std::stringstream sStream;
	typename std::list<T>::const_iterator itr;
	foreach(itr,vSrc){
		if (!bFrist)
			sStream<<sSp;

		if (!ToValue(*itr,sTemp))
		{
			sDes = "";
			return false;
		}

		sStream<<sTemp;

		bFrist = false;
	}

	sDes = sStream.str();
	return true;
}

template<typename T>
bool ToolFrame::ToValue(const std::set<T>& vSrc,std::string& sDes,const std::string& sSp){
	if (vSrc.empty()){sDes = "";return true;}

	bool bFrist = true;

	std::string sTemp;

	std::stringstream sStream;
	typename std::set<T>::const_iterator itr;
	foreach(itr,vSrc){
		if (!bFrist)
			sStream<<sSp;

		if (!ToValue(*itr,sTemp))
		{
			sDes = "";
			return false;
		}

		sStream<<sTemp;

		bFrist = false;
	}

	sDes = sStream.str();
	return true;
}

template<typename TKey,typename TValue,typename TArg>
TValue* ToolFrame::GetValuePtrUpperMap( const std::map<TKey,TValue>& vMap,const TArg& tKey )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.upper_bound(tKey);
	return  itr != vMap.end() ? (TValue*)&itr->second :nullptr;
}

template<typename TKey,typename TValue>
const TValue& ToolFrame::GetValueUpperMap( const std::map<TKey,TValue>& vMap,const TKey& tKey,const TValue& tDefault )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.upper_bound(tKey);
	return  itr != vMap.end() ? itr->second :tDefault;
}

template<typename key,typename value>
typename std::map<key,value>::const_iterator ToolFrame::GetItrByValue( const std::map<key,value>& vSrc,const value& tValue )
{
	return GetItrByValue((std::map<key,value>&)vSrc,tValue);
}

template<typename value>
typename std::list<value>::iterator ToolFrame::GetItrByValue( std::list<value>& vSrc,const value& tValue )
{
	typename std::list<value>::iterator itr;
	foreach(itr,vSrc){
		if (tValue == *itr)
			return itr;
	}

	return vSrc.end();
}

template<typename value>
typename std::set<value>::iterator ToolFrame::GetItrByValue( std::set<value>& vSrc,const value& tValue )
{
	typename std::set<value>::iterator itr;
	foreach(itr,vSrc){
		if (tValue == *itr)
			return itr;
	}

	return vSrc.end();
}

template<typename value>
typename std::vector<value>::iterator ToolFrame::GetItrByValue( std::vector<value>& vSrc,const value& tValue )
{
	typename std::vector<value>::iterator itr;
	foreach(itr,vSrc){
		if (tValue == *itr)
			return itr;
	}

	return vSrc.end();
}

template<typename key,typename value>
typename std::map<key,value>::iterator ToolFrame::GetItrByValue( std::map<key,value>& vSrc,const value& tValue )
{
	typename std::map<key,value>::iterator itr;
	foreach(itr,vSrc){
		if (tValue == itr->second)
			return itr;
	}

	return vSrc.end();
}

template<typename T>
T* ToolFrame::CreateByPtr( T* )
{
	return new T();
}

template<typename T>
typename std::list<T>::iterator ToolFrame::RandItr( std::list<T>& vSrc )
{
	if (vSrc.empty())return vSrc.end();

	int nCount = rand() % vSrc.size();

	typename std::list<T>::iterator itr = vSrc.begin();
	while(nCount--)
		++itr;

	return itr;
}

template<typename T>
typename std::vector<T>::iterator ToolFrame::RandItr( std::vector<T>& vSrc )
{
	if (vSrc.empty())return vSrc.end();

	int nCount = rand() % vSrc.size();

	typename std::vector<T>::iterator itr = vSrc.begin();
	while(nCount--)
		++itr;

	return itr;
}

template<typename T>
bool ToolFrame::RandErase( std::list<T>& vSrc,size_t uRemoveCounter )
{
	if(uRemoveCounter<=0)return true;
	if (vSrc.size()<uRemoveCounter)return false;
	if (vSrc.size() == uRemoveCounter)
	{
		vSrc.clear();
		return true;
	}

	size_t uLast = vSrc.size() - uRemoveCounter;
	while (vSrc.size() > uLast)
		vSrc.erase(RandItr(vSrc));

	return true;
}

template<typename T>
bool ToolFrame::RandErase( std::vector<T>& vSrc,size_t uRemoveCounter )
{
	if(uRemoveCounter<=0)return true;
	if (vSrc.size()<uRemoveCounter)return false;
	if (vSrc.size() == uRemoveCounter)
	{
		vSrc.clear();
		return true;
	}

	size_t uLast = vSrc.size() - uRemoveCounter;
	while (vSrc.size() > uLast)
		vSrc.erase(RandItr(vSrc));

	return true;
}

template <typename Key,typename Value>
const Value ToolFrame::GetPtrValue( const std::map<Key,Value>& vVct,typename std::map<Key,Value>::const_iterator itr,bool bKey /*= false*/ )
{
	if (itr == vVct.end())return Value();
	return bKey ? itr->first:itr->second;
}

template <typename T>
const T ToolFrame::GetPtrValue( const std::set<T>& vVct,typename std::set<T>::const_iterator itr )
{
	return itr == vVct.end() ? T() : *itr;
}

template <typename T>
const T ToolFrame::GetPtrValue( const std::list<T>& vVct,typename std::list<T>::const_iterator itr )
{
	return itr == vVct.end() ? T() : *itr;
}

template <typename T>
const T ToolFrame::GetPtrValue( const std::vector<T>& vVct,typename std::vector<T>::const_iterator itr )
{
	return itr == vVct.end() ? T() : *itr;
}

template <typename Key,typename Value>
Value ToolFrame::GetPtrValue( const std::map<Key,Value>& vVct,typename std::map<Key,Value>::iterator itr ,bool bKey )
{
	if (itr == vVct.end())return Value();
	return bKey ? itr->first:itr->second;
}

template <typename T>
T ToolFrame::GetPtrValue( const std::set<T>& vVct,typename std::set<T>::iterator itr )
{
	return itr == vVct.end() ? T() : *itr;
}

template <typename T>
T ToolFrame::GetPtrValue( const std::list<T>& vVct,typename std::list<T>::iterator itr )
{
	return itr == vVct.end() ? T() : *itr;
}

template <typename T>
T ToolFrame::GetPtrValue( const std::vector<T>& vVct,typename std::vector<T>::iterator itr )
{
	return itr == vVct.end() ? T() : *itr;
}

template<typename T>
bool ToolFrame::IsEndIndex( std::vector<T>& vVct,int nIndex )
{
	assert(nIndex > 0);
	return vVct.size() == nIndex;
}

template<typename T>
uint ToolFrame::Erase( std::vector<T>& vDes,const std::set<T>& vSrc )
{
	return EraseByValue(vDes,vSrc);
}

template<typename T>
uint ToolFrame::Erase( std::vector<T>& vDes,const std::vector<T>& vSrc )
{
	return EraseByValue(vDes,vSrc);
}

template<typename T>
uint ToolFrame::Erase( std::list<T>& vVct,const T& tVal )
{
	return EraseByValue(vVct,tVal);
}

template<typename T>
uint ToolFrame::Erase( std::set<T>& vVct,const T& tVal )
{
	return EraseByValue(vVct,tVal);
}

template<typename T>
uint ToolFrame::Erase( std::vector<T>& vVct,const T& tVal)
{
	return EraseByValue(vVct,tVal);
}

template<typename T>
uint ToolFrame::Erase( std::list<T>& vVct,const std::list<T>& vSrc )
{
	return EraseByValue(vVct,vSrc);
}

template<typename T,typename Arg>
bool ToolFrame::EraseByValue( std::list<T>& vVct,const std::list<Arg>& vSrc )
{
	if (vVct.empty())return false;

	typename std::list<T>::iterator itr;
	foreach(itr, vVct) {
		if (IsHasValue(vSrc, *itr))
		{
			vVct.erase(itr);
			return true;
		}
	}
	return false;
}

template<typename Key,typename Value,typename Arg>
bool ToolFrame::EraseByValue( std::map<Key,Value>& vMap,const Arg& tValue )
{
	if (vMap.empty())return false;

	typename std::map<Key,Value>::iterator itr = vMap.begin();
	while(itr != vMap.end()){
		if(itr->second == tValue){
			vMap.erase(itr);
			return true;
		}
	}

	return false;
}

template<typename T, typename Arg>
uint ToolFrame::EraseByValueAll(std::list<T>& vVct, const std::list<Arg>& vSrc)
{
	if (vVct.empty())return 0;

	uint nCount = 0;
	typename std::list<T>::iterator itr = vVct.begin();
	while (itr != vVct.end()) {
		if (IsHasValue(vSrc, *itr))
		{
			itr = EraseByItr(vVct, itr);
			++nCount;
		}
		else
		{
			++itr;
		}
	}

	return nCount;
}

template<typename T, typename Arg>
uint ToolFrame::EraseByValueAll(std::vector<T>& vDes, const std::vector<Arg>& vSrc)
{
	if (vDes.empty())return 0;

	uint nDeleted = 0;
	if (vSrc.empty())return nDeleted;
	for (int nIndex = (int)vDes.size() - 1; nIndex >= 0; --nIndex)
	{
		if (IsHasValue(vSrc, vDes[nIndex]))
		{
			vDes.erase(vDes.begin() + nIndex);
			++nDeleted;
		}
	}
	return nDeleted;
}

template<typename T, typename Arg>
uint ToolFrame::EraseByValueAll(std::vector<T>& vDes, const std::set<Arg>& vSrc)
{
	if (vDes.empty())return 0;

	uint nDeleted = 0;
	if (vSrc.empty())return nDeleted;
	for (int nIndex = (int)vDes.size() - 1; nIndex >= 0; --nIndex)
	{
		if (IsHasValue(vSrc, vDes[nIndex]))
		{
			vDes.erase(vDes.begin() + nIndex);
			++nDeleted;
		}
	}
	return nDeleted;
}

template<typename Key,typename Value,typename Arg>
UINT ToolFrame::EraseByValueAll( std::map<Key,Value>& vMap,const Arg& tValue )
{
	if (vMap.empty())return 0;

	UINT nCount = 0;
	typename std::map<Key,Value>::iterator itr = vMap.begin();
	while(itr != vMap.end()){
		if(itr->second == tValue){
			itr = EraseByItr(vMap,itr);
			++nCount;
		}else
		{
			++itr;
		}
	}

	return nCount;
}

template<typename T,typename Arg>
typename std::vector<T>::iterator ToolFrame::GetItrNext( typename std::vector<T>::iterator itr,std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg )
{
	while(itr != vSrc.end()){
		typename std::vector<T>::const_iterator itrConst = itr;
		if (fn(itrConst,tArg))
			return itr;

		itr = GetItrNext(itr,vSrc);
	}

	return itr;
}

template<typename T,typename Arg>
typename std::vector<T>::iterator ToolFrame::GetItrBegin( std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg )
{
	return GetItrNext(vSrc.begin(),vSrc,fn,tArg);
}

template<typename T,typename Arg>
typename std::vector<T>::const_iterator ToolFrame::GetItrNext( typename std::vector<T>::const_iterator itr,const std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg )
{
	return GetItrNext(itr,(std::vector<T>&) vSrc,fn,tArg);
}

template<typename T,typename Arg>
typename std::vector<T>::const_iterator ToolFrame::GetItrBegin( const std::vector<T>& vSrc,bool(*fn)(typename std::vector<T>::const_iterator&,const Arg&),const Arg& tArg )
{
	return GetItrNext(vSrc.begin(),vSrc,fn,tArg);
}

template<typename T,typename Arg>
typename std::list<T>::const_iterator ToolFrame::GetItrNext( typename std::list<T>::const_iterator itr,const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&,const Arg&),const Arg& tArg )
{
	while(itr != vSrc.end()){
		if (fn(itr,tArg))
			return itr;

		itr = GetItrNext(itr,vSrc);
	}

	return itr;
}

template<typename T,typename Arg>
typename std::list<T>::const_iterator ToolFrame::GetItrBegin( const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&,const Arg&),const Arg& tArg )
{
	return GetItrNext(vSrc.begin(),vSrc,fn,tArg);
}

template<typename Key,typename Value>
typename std::map<Key,Value>::const_iterator ToolFrame::GetItrBegin( const std::map<Key,Value>& vSrc,bool(*fn)(typename std::map<Key,Value>::const_iterator&) )
{
	typename std::map<Key,Value>::const_iterator itr;
	foreach(itr,vSrc){
		if (fn(itr))
			return itr;
	}
	return vSrc.end();
}

template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
const TValue& ToolFrame::GetValueByKey( const std::multimap<TKey,TValue>& vSrc,const Arg& tKey,const ArgDefault& tValue )
{
	typedef typename std::multimap<TKey,TValue>::const_iterator	ItrMap;
	typedef typename std::pair<ItrMap,ItrMap>					PairPairKeyValue;
	PairPairKeyValue pair = vSrc.equal_range(tKey);
	if (pair.first == pair.second)return (const TValue&)tValue;

	return pair.first->second;
}

template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
TValue& ToolFrame::GetValueByKey( std::multimap<TKey,TValue>& vSrc,const Arg& tKey,ArgDefault& tValue )
{
	typedef typename std::multimap<TKey,TValue>::iterator	ItrMap;
	typedef typename std::pair<ItrMap,ItrMap>				PairPairKeyValue;
	PairPairKeyValue pair = vSrc.equal_range(tKey);

	return pair.first == pair.second ? (TValue&)tValue : pair.first->second;
}

template<typename TKey,typename TValue,typename Arg>
TValue* ToolFrame::GetValuePtrByKey(const std::multimap<TKey,TValue>& vSrc,const Arg& tKey )
{
	typedef typename std::multimap<TKey,TValue>::iterator	ItrMap;
	typedef typename std::pair<ItrMap,ItrMap>				PairPairKeyValue;
	PairPairKeyValue pair = vSrc.equal_range(tKey);

	return pair.first == pair.second ? nullptr : &pair.first->second;
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrNext( typename std::list<T>::const_iterator itr,const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&) )
{
	while(itr != vSrc.end()){
		if (fn(itr))
			return itr;

		itr = GetItrNext(itr,vSrc);
	}

	return itr;
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrFront( typename std::list<T>::const_iterator itr,const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&) )
{
	while(itr != vSrc.end()){
		if (fn(itr))
			return itr;

		itr = GetItrFront(itr,vSrc);
	}

	return itr;
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrNext( typename std::list<T>::iterator itr,std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&) )
{
	while(itr != vSrc.end()){
		if (fn(itr))
			return itr;

		itr = GetItrNext(itr,vSrc);
	}

	return itr;
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrFront( typename std::list<T>::iterator itr,std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&) )
{
	while(itr != vSrc.end()){
		if (fn(itr))
			return itr;

		itr = GetItrFront(itr,vSrc);
	}

	return itr;
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrLast( const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator &) )
{
	if (vSrc.empty())return vSrc.end();
	return GetItrFront(--vSrc.end(),vSrc,fn);
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrBegin( const std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&) )
{
	return GetItrNext(vSrc.begin(),vSrc,fn);
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrLast( std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&) )
{
	if (vSrc.empty())return vSrc.end();
	return GetItrFront(--vSrc.end(),vSrc,fn);
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrBegin( std::list<T>& vSrc,bool(*fn)(typename std::list<T>::const_iterator&) )
{
	return GetItrNext(vSrc.begin(),vSrc,fn);
}

template<typename TKey,typename TValue,typename ArgKey,typename ArgValue>
bool ToolFrame::EraseByValue( std::multimap<TKey,TValue>& vDes,const ArgKey& tKey,const ArgValue& tValue )
{
	if (vDes.empty())return false;

	typedef typename std::multimap<TKey,TValue>::iterator	ItrMap;
	typedef typename std::pair<ItrMap,ItrMap>				PairMap;
	PairMap pair = vDes.equal_range(tKey);
	ItrMap itr;
	foreachPair(itr,pair){
		if (itr->second == tValue){
			vDes.erase(itr);
			return true;
		}
	}
	return false;
}

template<typename TKey,typename TValue,typename TArg>
uint ToolFrame::EraseByKey( std::map<TKey,TValue>& vDes,const TArg& tKey )
{
	size_t uSize = vDes.size();
	vDes.erase(tKey);
	return (uint)(uSize - vDes.size());
}

template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
bool ToolFrame::InsertVector( std::map<TKey,std::vector<TValue> >& vMap,const TKeyInsert& tKey,const TValueInsert& tValue )
{
	typename std::vector<TValue>& vValue = GetValueByKeyForce(vMap,tKey);
	return Insert(vValue,tValue);
}

template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
bool ToolFrame::InsertVector( std::map<TKey,std::list<TValue> >& vMap,const TKeyInsert& tKey,const TValueInsert& tValue )
{
	typename std::list<TValue>& vValue = GetValueByKeyForce(vMap,tKey);
	return Insert(vValue,tValue);
}

template<typename T,typename TFunCompair>
bool ToolFrame::IsEqual( const std::vector<T>& vSrc, const std::vector<T>& vDes )
{
	return IsEqual(vSrc,vDes,CompairEqual);
}

template<typename T, typename K>
bool ToolFrame::InsertUnique(std::vector<T>& vVct, const K& tValue)
{
	if (IsHasValue(vVct, tValue))return true;
	return Insert(vVct, tValue);
}

template<typename T, typename K>
bool ToolFrame::InsertUnique(std::list<T>& vVct, const K& tValue)
{
	if (IsHasValue(vVct, tValue))return true;
	return Insert(vVct, tValue);
}

template<typename T,typename K>
bool ToolFrame::Clear( std::multimap<T,K>& tMap )
{
	if (tMap.empty())
		return true;

	tMap.clear();
	return true;
}

template<typename T,typename K>
bool ToolFrame::Clear( std::map<T,K>& tMap )
{
	if (tMap.empty())
		return true;

	tMap.clear();
	return true;
}

template<typename T>
bool ToolFrame::Clear( std::multiset<T>& tVct )
{
	if (tVct.empty())
		return true;

	tVct.clear();
	return true;
}

template<typename T>
bool ToolFrame::Clear( std::set<T>& tVct )
{
	if (tVct.empty())
		return true;

	tVct.clear();
	return true;
}

template<typename T>
bool ToolFrame::Clear( std::vector<T>& tVct )
{
	if (tVct.empty())
		return true;

	tVct.clear();
	return true;
}

template<typename T>
bool ToolFrame::Clear( std::list<T>& tVct )
{
	if (tVct.empty())
		return true;

	tVct.clear();
	return true;
}

template<typename T>
bool ToolFrame::Move( std::list<T>& vDes,std::list<T>& vSrc )
{
	if (IsSelf(vDes,vSrc))return false;
	vDes.splice(vDes.end(),vSrc);
	return true;
}

template<typename T>
typename std::list<T>::iterator ToolFrame::Insert( T& tValue,std::list<T>& vSrc,typename std::list<T>::iterator& itr ,bool bFront)
{
	if (bFront)
	{
		typename std::list<T>::iterator itrFront = ToolFrame::GetItrFront(itr,vSrc);
		if (itrFront == vSrc.end()){
			vSrc.push_back(tValue);
			return vSrc.begin();
		}

		return vSrc.insert(itrFront,tValue);
	}

	return vSrc.insert(itr,tValue);
}

template<typename T,typename K>
typename std::map<T,K>::iterator ToolFrame::EraseByItr(std::map<T,K>& vSrc,typename std::map<T,K>::iterator itr)
{
	if(itr == vSrc.end())return vSrc.end();

	typename std::map<T,K>::iterator itrNext = itr;
	++itrNext;
	if (itrNext != vSrc.end())
	{
		const T& key = itrNext->first;
		vSrc.erase(itr);
		return vSrc.find(key);
	}else{
		vSrc.erase(itr);
		return vSrc.end();
	}
	assert(false);
	return vSrc.end();
}

template<typename T>
typename std::list<T>::iterator ToolFrame::EraseByItr( std::list<T>& vSrc,typename std::list<T>::iterator itrBegin,typename std::list<T>::iterator itrEnd,bool bKeepBegin/*=false*/,bool bKeepEnd/*=true*/ )
{
	//���� Ҫ ɾ���� �����յ�
	if (bKeepBegin)
		itrBegin = ToolFrame::GetItrNext(itrBegin,vSrc);

	if (!bKeepEnd)
		itrEnd = ToolFrame::GetItrNext(itrEnd,vSrc);

	return vSrc.erase(itrBegin,itrEnd);//�Ƴ���������Χ�ڵĽڵ�,��������ĩβ
}

template<typename T>
bool ToolFrame::GetValuesByItr( std::list<T>& vDes,std::list<T>& vSrc,typename std::list<T>::iterator& itr )
{
	if (itr == vSrc.end())return false;

	vDes.push_back(*itr);
	return true;
}

template<typename T>
bool ToolFrame::GetValuesByItr( std::list<T>& vDes,std::list<T>& vSrc,typename std::list<T>::iterator itrBegin,typename std::list<T>::iterator itrEnd,bool bKeepBegin/*=true*/,bool bKeepEnd/*=false*/ )
{
	if (itrBegin == itrEnd)return false;

	if (bKeepBegin && !GetValuesByItr(vDes,vSrc,itrBegin))return false;
	++itrBegin;
	for(;itrBegin != itrEnd;++itrBegin){
		if (!GetValuesByItr(vDes,vSrc,itrBegin))return false;
	}

	if (bKeepEnd && !GetValuesByItr(vDes,vSrc,itrBegin))return false;
	return true;
}

template<typename TKey,typename TValue>
std::pair<typename std::multimap<TKey,TValue>::const_iterator,typename std::multimap<TKey,TValue>::const_iterator >ToolFrame::EqualRange( const std::multimap<TKey,TValue>& vSrc,const TKey& tKey )
{
	return vSrc.equal_range(tKey);
}

template<typename TKey,typename TValue>
std::pair<typename std::multimap<TKey,TValue>::iterator,typename std::multimap<TKey,TValue>::iterator >ToolFrame::EqualRange( std::multimap<TKey,TValue>& vSrc,const TKey& tKey )
{
	return vSrc.equal_range(tKey);
}

template<typename TValue1,typename TValue2>
bool ToolFrame::CompairEqual( const TValue1 & tValue1,const TValue2 & tValue2 )
{
	return tValue1 == tValue2;
}

template<typename TValue1,typename TValue2>
bool ToolFrame::CompairLess( const TValue1 & tValue1,const TValue2 & tValue2 )
{
	return tValue1 < tValue2;
}

template<typename T>
bool ToolFrame::IsEnd( const std::pair<T,T>& itrPair )
{
	return itrPair.first == itrPair.second;
}

template<typename TFun>
std::string ToolFrame::MakeCodeSign(const std::string& sFunName,TFun fnName){
	std::string sFunCodeSign;

	std::stringstream sStream;
	sStream<<"?"<<sFunName<<"@@"<<MakeFunCodeSign(fnName)<<"@"<<"Z";
	return sStream.str();
}

template<typename T>
typename std::list<T>::const_reverse_iterator ToolFrame::GetItrNext( typename std::list<T>::const_reverse_iterator itr,const std::list<T>& vSrc )
{
	if (itr != vSrc.begin())
		--itr;

	return vSrc.end();
}

template<typename T>
typename std::list<T>::reverse_iterator ToolFrame::GetItrNext( typename std::list<T>::reverse_iterator itr,std::list<T>& vSrc )
{
	if (itr != vSrc.begin())
		--itr;

	return vSrc.end();
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrNext( typename std::list<T>::const_iterator itr,const std::list<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrNext( typename std::list<T>::iterator itr,std::list<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::list<T>::const_reverse_iterator ToolFrame::GetItrFront( typename std::list<T>::const_reverse_iterator itr,const std::list<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::list<T>::reverse_iterator ToolFrame::GetItrFront( typename std::list<T>::reverse_iterator itr,std::list<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrFront( typename std::list<T>::const_iterator itr,const std::list<T>& vSrc )
{
	if (itr != vSrc.begin())
		return --itr;

	return vSrc.end();
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrFront( typename std::list<T>::iterator itr,std::list<T>& vSrc )
{
	if (itr != vSrc.begin())
		return --itr;

	return vSrc.end();
}

template<typename T>
typename std::list<T>::iterator ToolFrame::EraseByItr( std::list<T>& vSrc,typename std::list<T>::iterator itr )
{
	return vSrc.erase(itr);
}

//IOS��֧�ֲ���CONST������,Ҳ�޷�ת��
// template<typename T>
// typename std::list<T>::iterator ToolFrame::EraseByItr( std::list<T>& vSrc,typename std::list<T>::const_iterator itr )
// {
// 	return vSrc.erase(itr);
// }

//android���벻ͨ��
// template<typename T>
// typename std::vector<T>::iterator ToolFrame::EraseByItr( std::vector<T>& vSrc,typename std::vector<T>::const_iterator& itr )
// {
// 	return vSrc.erase(itr);
// }

template<typename T>
typename std::vector<T>::iterator ToolFrame::EraseByItr( std::vector<T>& vSrc,typename std::vector<T>::iterator& itr )
{
	return vSrc.erase(itr);
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrLast( const std::list<T>& vSrc )
{
	if (vSrc.empty())return vSrc.end();

	return  --vSrc.end();
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrLast( std::list<T>& vSrc )
{
	if (vSrc.empty())return vSrc.end();

	return --vSrc.end();
}

template<typename T>
typename std::vector<T>::const_iterator ToolFrame::GetItrLast( const std::vector<T>& vSrc )
{
	if (vSrc.empty())return vSrc.end();

	return  --vSrc.end();
}

template<typename T>
typename std::vector<T>::iterator ToolFrame::GetItrLast( std::vector<T>& vSrc )
{
	if (vSrc.empty())return vSrc.end();

	return --vSrc.end();
}

template<typename T>
typename std::list<T>::const_iterator ToolFrame::GetItrBegin( const std::list<T>& vSrc )
{
	return vSrc.empty() ? vSrc.end() : vSrc.begin();
}

template<typename T>
typename std::list<T>::iterator ToolFrame::GetItrBegin( std::list<T>& vSrc )
{
	return vSrc.empty() ? vSrc.end() : vSrc.begin();
}

template<typename T>
typename std::vector<T>::const_iterator ToolFrame::GetItrBegin( const std::vector<T>& vSrc )
{
	return vSrc.empty() ? vSrc.end() : vSrc.begin();
}

template<typename T>
typename std::vector<T>::iterator ToolFrame::GetItrBegin( std::vector<T>& vSrc )
{
	return vSrc.empty() ? vSrc.end() : vSrc.begin();
}

template<typename T>
typename std::vector<T>::const_reverse_iterator ToolFrame::GetItrNext( typename std::vector<T>::const_reverse_iterator itr,const std::vector<T>& vSrc )
{
	if (itr != vSrc.begin())
		return --itr;

	return vSrc.end();
}

template<typename T>
typename std::vector<T>::reverse_iterator ToolFrame::GetItrNext( typename std::vector<T>::reverse_iterator itr,std::vector<T>& vSrc )
{
	if (itr != vSrc.begin())
		return --itr;

	return vSrc.end();
}

template<typename T>
typename std::vector<T>::const_iterator ToolFrame::GetItrNext( typename std::vector<T>::const_iterator itr,const std::vector<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::vector<T>::iterator ToolFrame::GetItrNext( typename std::vector<T>::iterator itr,std::vector<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::vector<T>::const_reverse_iterator ToolFrame::GetItrFront( typename std::vector<T>::const_reverse_iterator itr,const std::vector<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::vector<T>::reverse_iterator ToolFrame::GetItrFront( typename std::vector<T>::reverse_iterator itr,std::vector<T>& vSrc )
{
	return ++itr;
}

template<typename T>
typename std::vector<T>::const_iterator ToolFrame::GetItrFront( typename std::vector<T>::const_iterator itr,const std::vector<T>& vSrc )
{
	if (itr != vSrc.begin())
		return --itr;

	return vSrc.end();
}

template<typename T>
typename std::vector<T>::iterator ToolFrame::GetItrFront(typename std::vector<T>::iterator itr,std::vector<T>& vSrc )
{
	if (itr != vSrc.begin())
		return --itr;

	return vSrc.end();
}

template<typename T,typename K>
bool ToolFrame::Insert( std::list<T>& vVct,const K& tValue )
{
	size_t uSize = vVct.size();
	vVct.push_back(tValue);
	return uSize + 1 == vVct.size();
}

template<typename T,typename K>
bool ToolFrame::Insert( std::vector<T>& vVct,const K& tValue )
{
	size_t uSize = vVct.size();
	vVct.push_back(tValue);
	return uSize + 1 == vVct.size();
}

template<typename T,typename K>
bool ToolFrame::InsertString( MapStringString& vMap,const T& tKey,const K& tValue )
{
	size_t uSize = vMap.size();
	vMap[ToString(tKey)] = ToString(tValue);
	return vMap.size() == uSize + 1;
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::set<T>& vSrc, std::list<K>& vDes )
{
	if (vSrc.empty())return true;

	typename std::set<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tValue;
		if (!ToValue(*itr,tValue))return false;
		vDes.push_back(tValue);
	}
	return true;
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::list<T>& vSrc,std::set<K>& vDes )
{
	if (vSrc.empty())return true;

	typename std::list<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tValue;
		if (!ToValue(*itr,tValue))return false;
		vDes.insert(tValue);
	}
	return true;
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::list<T>& vSrc,std::list<K>& vDes )
{
	if (vSrc.empty())return true;

	typename std::list<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tValue;
		if (!ToValue(*itr,tValue))return false;
		vDes.push_back(tValue);
	}
	return true;
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::list<T>& vSrc,std::vector<K>& vDes )
{
	if (vSrc.empty())return true;

	typename std::list<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tValue;
		if (!ToValue(*itr,tValue))return false;
		vDes.push_back(tValue);
	}
	return true;
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::vector<T>& vSrc,std::list<K>& vDes )
{
	if (vSrc.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tValue;
		if (!ToValue(*itr,tValue))return false;
		vDes.push_back(tValue);
	}
	return true;
}

template<typename T>
bool ToolFrame::IsEqual( const std::set<T>& vSrc,const std::vector<T>& vDes )
{
	if (vSrc.empty() == vDes.empty())return true;
	if (vSrc.size() != vDes.size())return false;
	
	typename std::vector<T>::const_iterator itr;
	foreach(itr,vDes){
		if(!ToolFrame::IsHasValue(vSrc,*itr))return false;
	}
	return true;
}

template<typename T>
bool ToolFrame::IsEqual( const std::vector<T>& vSrc, const std::set<T>& vDes )
{
	if (vSrc.empty() == vDes.empty())return true;
	if (vSrc.size() != vDes.size())return false;
	if (vDes.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach(itr,vSrc){
		if(!ToolFrame::IsHasValue(vDes,*itr))return false;
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValueRange( const double& tSrc,T& tDes,double fMin,double fMax )
{
	if (tSrc > (GetLimitMax(TYPE_ARG(unsigned long long)) + 0.5f) || tSrc < (GetLimitMin(TYPE_ARG(long long)) - 0.5f))return false;

	return StaticCast(tDes,tSrc >=0 ? tSrc +0.5f : tSrc - 0.5f);
}

template<typename T>
T ToolFrame::GetLimitMax( const T& )
{
	return std::numeric_limits<T>::max();
}

template<typename T>
T ToolFrame::GetLimitMin( const T& )
{
	return std::numeric_limits<T>::min();
}

template<typename T>
T ToolFrame::GetLimitMin()
{
	return std::numeric_limits<T>::min();
}

template<typename T>
T ToolFrame::GetLimitMax()
{
	return std::numeric_limits<T>::max();
}

template<typename T,typename K>
bool ToolFrame::ToValue( const T& tSrc, K& tDes )
{
	if (IsSelf(tSrc,tDes))return true;
	
	return StaticCast(tDes,tSrc);
}

template <typename T>
bool ToolFrame::StaticCast(T& tDes,const T& tSrc )
{
	if (IsSelf(tSrc,tDes))return true;

	tDes = tSrc;
	return true;
}

template <typename T>
bool ToolFrame::StaticCast(bool& bDes,const  T& tSrc )
{
	bDes = 1 == tSrc;
	return true;
}

template<typename T>
bool ToolFrame::ToValue( const char* szSrc, T& nValue )
{
	if (!szSrc)return false;
	return ToValue(std::string(szSrc),nValue);
}

template<typename T>
bool ToolFrame::ToValue( const std::string& tSrc,std::set<T>& tDes,const std::string& sSp/*=','*/ )
{
	VectorString vString;
	ToolFrame::SplitString(vString,tSrc,sSp);
	VectorString::const_iterator itr;
	foreach(itr,vString){
		const std::string& sValue = *itr;
		T t;//û�г�ʼ��
		if (!ToValue(sValue,t))return false;
		if (!ToolFrame::Insert(tDes,t))return false;
	}
	return true;
}

template<typename T>
bool ToolFrame::ToValue( const std::string& tSrc,std::vector<T>& tDes,const std::string& sSp/*=','*/ )
{
	VectorString vString;
	ToolFrame::SplitString(vString,tSrc,sSp);
	VectorString::const_iterator itr;
	foreach(itr,vString){
		const std::string& sValue = *itr;
		T t;//û�г�ʼ��
		if (!ToValue(sValue,t))return false;
		if (!ToolFrame::Insert(tDes,t))return false;
	}
	return true;
}

template<typename T>
const T& ToolFrame::ConstCast( T& t )
{
	return t;
}

template<typename T>
T& ToolFrame::ConstCast( const T& t )
{
	return (T&)t;
}

template<typename T>
const T* ToolFrame::ConstCast( T* t )
{
	return t;
}

template<typename T>
T* ToolFrame::ConstCast( const T* t )
{
	return const_cast<T*>(t);
}

template <typename T, typename K>
T ToolFrame::DynamicCast(const K& tSrc)
{
	return dynamic_cast<T>(tSrc);
}

template <typename T,typename K>
bool ToolFrame::DynamicCast(K& tDes,const T& tSrc )
{
	tDes = dynamic_cast<K>(tSrc);
	return true;
}

template <typename T, typename K>
T StaticCast(const K& tSrc)
{
	return static_cast<T>(tSrc);
}

template <typename T,typename K>
bool ToolFrame::StaticCast(K& tDes,const T& tSrc )
{
	tDes = static_cast<K>(tSrc);
	return true;
}

template <typename TSrcKey,typename TSrcValue,typename TDesKey,typename TDesValue>
bool ToolFrame::ToValue( const std::map<TSrcKey,TSrcValue>& vSrc,std::map<TDesKey,TDesValue>& vDes )
{
	typename std::map<TSrcKey,TSrcValue>::const_iterator itr;
	foreach(itr,vSrc){
		TDesKey		tKeyDes;
		TDesValue	tValueDes;
		if (!ToValue(itr->first,	tKeyDes))return false;
		if (!ToValue(itr->second,	tValueDes))return false;

		if (!ToolFrame::Insert(vDes,tKeyDes,tValueDes))return false;
	}

	return true;
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::set<T>& vSrc,std::set<K>& vDes )
{
	typename std::set<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tK;						//����Ĭ�Ϲ���(������������δ��ʼ��)
		if (!ToValue(*itr,tK))return false;
		if (!ToolFrame::Insert(vDes,tK))return false;//���ÿ�������
	}
	return true;
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::set<T>& vSrc,std::vector<K>& vDes )
{
	typename std::set<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tK;						//����Ĭ�Ϲ���(������������δ��ʼ��)
		if (!ToValue(*itr,tK))return false;
		vDes.push_back(tK);			//���ÿ�������
	}
	return true;
}

template<typename T1,typename T2>
bool ToolFrame::IsEqual( const T1& t1,const T2& t2 )
{
	if (IsSelf(t1,t2))return true;
	return t1 == (const T1&)t2;
}

template<typename TKey,typename TValue,typename Arg>
TValue* ToolFrame::GetValuePtrByKey(const std::map<TKey,TValue>& vMap,const Arg& tKey )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.find(tKey);
	return itr == vMap.end() ? nullptr : (TValue*)&(itr->second);
}

template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
TValue* ToolFrame::GetValueByKey( const std::map<TKey,TValue*>& vMap,const Arg& tKey,ArgDefault tDefault )
{
	typename std::map<TKey,TValue*>::const_iterator itr = vMap.find(tKey);
	return itr == vMap.end() ?(TValue*) tDefault:itr->second;
}

template<typename TKey,typename Arg>
const std::string& ToolFrame::GetValueByKey( const std::map<TKey,std::string>& vMap,const Arg& tKey,const std::string& tDefault )
{
	typename std::map<TKey,std::string>::const_iterator itr = vMap.find(tKey);
	return itr == vMap.end() ? tDefault:itr->second;
}

template<typename TKey,typename TValue,typename Arg,typename ArgDefault>
TValue ToolFrame::GetValueByKey( const std::map<TKey,TValue>& vMap,const Arg& tKey,ArgDefault tDefault )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.find(tKey);
	return itr == vMap.end() ? tDefault:itr->second;
}

template<typename TKey,typename TValue,typename Arg>
TValue& ToolFrame::GetValueByKey( const std::map<TKey,TValue>& vMap,const Arg& tKey,TValue& tDefault )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.find(tKey);
	return itr == vMap.end() ? tDefault:(TValue&)itr->second;
}

template<typename TKey,typename TValue,typename Arg>
const TValue& ToolFrame::GetValueByKey( const std::map<TKey,TValue>& vMap,const Arg& tKey,const TValue& tDefault )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.find(tKey);
	return itr == vMap.end() ? tDefault:itr->second;
}

template<typename TKey,typename TValue,typename Arg>
TValue& ToolFrame::GetValueByKey(const std::map<TKey,TValue>& vMap,const Arg& tKey )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.find(tKey);
	assert(itr != vMap.end());
	return (TValue&)itr->second;
}

template<typename T>
const T& ToolFrame::CircularNext( const std::vector<T>& vSrc,int nIndex )
{
	return CircularNext((std::vector<T>&)vSrc,nIndex);
}

template<typename T>
const T& ToolFrame::CircularPrev( const std::vector<T>& vSrc,int nIndex )
{
	return CircularPrev((std::vector<T>&)vSrc,nIndex);
}

template<typename T>
T& ToolFrame::CircularNext( std::vector<T>& vSrc,int nIndex )
{
	assert(!vSrc.empty());
	++nIndex;
	if (nIndex >= (int)vSrc.size() )
		nIndex = 0;

	return vSrc[nIndex];
}

template<typename T>
T& ToolFrame::CircularPrev( std::vector<T>& vSrc,int nIndex )
{
	assert(!vSrc.empty());
	--nIndex;
	if (nIndex < 0)
		nIndex = (int)vSrc.size() - 1;

	return vSrc[nIndex];
}

template<typename T>
bool ToolFrame::PrevPermutaion( std::vector<T>& vVct )
{
	return std::prev_permutation(vVct.begin(),vVct.end());
}

template<typename T>
bool ToolFrame::NextPermutaion( std::vector<T>& vVct )
{
	return std::next_permutation(vVct.begin(),vVct.end());
}

template<typename T>
bool ToolFrame::IsVaildIndex( const std::vector<T>& vSrc,int nIndex )
{
	if (vSrc.empty())return false;

	return ToolFrame::IsInClosedInterval<int>(nIndex,0,(int)vSrc.size()-1);
}

template<typename T>
bool ToolFrame::IsVaildIndex( const std::list<T>& vSrc,int nIndex )
{
	if (vSrc.empty())return false;
	return ToolFrame::IsInClosedInterval<int>(nIndex,0, (int)vSrc.size()-1);
}

template<typename TKey,typename TValue>
bool ToolFrame::IsVaildIndex( const std::map<TKey,TValue>& vSrc,int nIndex )
{
	if (vSrc.empty())return false;

	return ToolFrame::IsInClosedInterval<int>(nIndex,0, (int)vSrc.size()-1);
}

template<typename T,typename K>
bool ToolFrame::IsEmpty( const std::multimap<T,K>& vSrc )
{
	return vSrc.empty();
}

template<typename T,typename K>
bool ToolFrame::IsEmpty( const std::map<T,K>& vSrc )
{
	return vSrc.empty();
}

template<typename T>
bool ToolFrame::IsEmpty( const std::set<T>& vSrc )
{
	return vSrc.empty();
}

template<typename T>
bool ToolFrame::IsEmpty( const std::list<T>& vSrc )
{
	return vSrc.empty();
}

template<typename T>
bool ToolFrame::IsEmpty( const std::vector<T>& vSrc )
{
	return vSrc.empty();
}

template<typename T>
bool ToolFrame::Intersection( std::vector<T>& vDes,const std::vector<T>& vSrc1,const std::set<T>& vSrc2 )
{
	if (vSrc1.empty() || vSrc2.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach (itr,vSrc1)
	{
		if(ToolFrame::IsHasValue(vSrc2,*itr)){
			vDes.push_back(*itr);
		}
	}
	return true;
}

template<typename T>
bool ToolFrame::Intersection( std::vector<T>& vDes,const std::set<T>& vSrc1,const std::vector<T>& vSrc2 )
{
	return Intersection(vDes,vSrc2,vSrc1);
}

template<typename T>
bool ToolFrame::Intersection( std::set<T>& vDes,const std::set<T>& vSrc1,const std::set<T>& vSrc2 )
{
	if (vSrc1.empty() || vSrc2.empty())return true;

	typename std::set<T>::const_iterator itr;
	foreach (itr,vSrc1)
	{
		if(ToolFrame::IsHasValue(vSrc2,*itr)){
			if (!ToolFrame::Insert(vDes,*itr))
				return false;
		}
	}
	return true;
}

template<typename T>
bool ToolFrame::Intersection( std::vector<T>& vDes,const std::vector<T>& vSrc1,const std::vector<T>& vSrc2 )
{
	if (vSrc1.empty() || vSrc2.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach (itr,vSrc1)
	{
		if(ToolFrame::IsHasValue(vSrc2,*itr)){
			vDes.push_back(*itr);
		}

	}
	return true;
}

template<typename T>
bool ToolFrame::Union( std::set<T>& vDes,const std::set<T>& vSrc1,const std::set<T>& vSrc2 )
{
	if (vSrc1.empty() || vSrc2.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach (itr,vSrc1)
	{
		if(!ToolFrame::IsHasValue(vDes,*itr)){
			vDes.push_back(*itr);
		}

	}
	foreach (itr,vSrc2)
	{
		if(!ToolFrame::IsHasValue(vDes,*itr)){
			vDes.push_back(*itr);
		}

	}

	return true;
}

template<typename T>
bool ToolFrame::Union( std::list<T>& vDes,const std::list<T>& vSrc1,const std::list<T>& vSrc2 )
{
	if (vSrc1.empty() || vSrc2.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach (itr,vSrc1)
	{
		if(!ToolFrame::IsHasValue(vDes,*itr)){
			vDes.push_back(*itr);
		}

	}
	foreach (itr,vSrc2)
	{
		if(!ToolFrame::IsHasValue(vDes,*itr)){
			vDes.push_back(*itr);
		}

	}

	return true;
}

template<typename T>
bool ToolFrame::Union( std::vector<T>& vDes,const std::vector<T>& vSrc1,const std::vector<T>& vSrc2 )
{
	if (vSrc1.empty() || vSrc2.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach (itr,vSrc1)
	{
		if(!ToolFrame::IsHasValue(vDes,*itr)){
			vDes.push_back(*itr);
		}

	}
	foreach (itr,vSrc2)
	{
		if(!ToolFrame::IsHasValue(vDes,*itr)){
			vDes.push_back(*itr);
		}

	}

	return true;
}

template <typename Tkey,typename Tvalue>
void ToolFrame::Delete( std::map<Tkey,std::set<Tvalue*> >& vValues )
{
	typename std::map<Tkey,std::set<Tvalue*> >::iterator itr;
	foreach(itr,vValues)
		ToolFrame::Delete(itr->second);
	
	vValues.clear();
}

template <typename Tkey,typename Tvalue>
void ToolFrame::Delete( std::map<Tkey,std::list<Tvalue*> >& vValues )
{
	typename std::map<Tkey,std::list<Tvalue*> >::iterator itr;
	foreach(itr,vValues)
		ToolFrame::Delete(itr->second);

	vValues.clear();
}

template <typename Tkey,typename Tvalue>
void ToolFrame::Delete( std::map<Tkey,std::vector<Tvalue*> >& vValues )
{
	typename std::map<Tkey,std::vector<Tvalue*> >::iterator itr;
	foreach(itr,vValues)
		ToolFrame::Delete(itr->second);

	vValues.clear();
}

template<typename TValue,typename TCmp>
void ToolFrame::Delete( std::set<TValue,TCmp>& vSet )
{
	typename std::set<TValue,TCmp>::iterator itr;
	foreach(itr,vSet){
		if(*itr){
			delete *itr;
		}
	}
	vSet.clear();
}

template <typename T>
const T& ToolFrame::GetNearValue( const T& tArg,const T& a,const T& b )
{
	return AbsDifference(tArg,a) > AbsDifference(tArg,b) ? b:a;
}

template <typename T>
const T& ToolFrame::GetFarValue( const T& tArg,const T& a,const T& b )
{
	return AbsDifference(tArg,a) > AbsDifference(tArg,b) ? a:b;
}

//���Բ�(������ֵ�Ĳ�ֵȡ����)
template <typename T>
T ToolFrame::AbsDifference(const T& a,const T& b){
	//������ȥС�� ��Ȼ �� ���� ����0 ����
	//�������Լ��� �з��ź��޷���
	return a > b ? a - b : b - a;
}

template <typename T>
T ToolFrame::Abs(const T& t )
{
	return abs(t);
}

template<typename T,typename K>
bool ToolFrame::Insert( std::multiset<T>& vSet,const K& tValue )
{
	size_t uSize = vSet.size();
	vSet.insert(tValue);

	return vSet.size() == uSize + 1;
}

template<typename ValuePtr>
ValuePtr ToolFrame::GetBackPtr( const std::vector<ValuePtr>& vSrc )
{
	if (vSrc.empty())return ValuePtr();

	return GetBack(vSrc);
}

template<typename ValuePtr>
ValuePtr ToolFrame::GetBackPtr( const std::list<ValuePtr>& vSrc )
{
	if (vSrc.empty())return ValuePtr();

	return GetBack(vSrc);
}

template<typename T,typename ValuePtr>
ValuePtr ToolFrame::PopPtr( std::map<T,ValuePtr>& vSrc )
{
	return PopFrontPtr(vSrc);
}

template<typename ValuePtr>
ValuePtr ToolFrame::PopPtr( std::list<ValuePtr>& vSrc )
{
	return PopFrontPtr(vSrc);
}

template<typename ValuePtr>
ValuePtr ToolFrame::PopPtr( std::vector<ValuePtr>& vSrc )
{
	return PopFrontPtr(vSrc);
}

template<typename T,typename K>
K ToolFrame::PopFront( std::map<T,K>& vSrc )
{
	assert(!vSrc.empty());
	typename std::map<T,K>::iterator itr = vSrc.begin();
	K t(itr->second);
	vSrc.erase(itr);
	return t;
}

template<typename T>
T ToolFrame::PopFront( std::list<T>& vSrc )
{
	assert(!vSrc.empty());
	T t = vSrc.front();
	vSrc.pop_front();
	return t;
}

template<typename T>
T ToolFrame::PopFront( std::vector<T>& vSrc )
{
	assert(!vSrc.empty());
	T t = *vSrc.begin();
	vSrc.erase(vSrc.begin());
	return t;
}

template<typename T,typename K>
K ToolFrame::PopBack( std::map<T,K>& vSrc )
{
	assert(!vSrc.empty());
	typename std::map<T,K>::iterator itr = vSrc.rbegin();
	K t(itr->second);
	vSrc.erase(itr);
	return t;
}

template<typename T>
T ToolFrame::PopBack( std::vector<T>& vSrc )
{
	assert(!vSrc.empty());
	typename std::vector<T>::iterator itr = --vSrc.end();
	T t = *itr;
	vSrc.erase(itr);
	return t;
}

template<typename T>
T ToolFrame::PopBack( std::list<T>& vSrc )
{
	assert(!vSrc.empty());
	typename std::list<T>::iterator itr = --vSrc.end();
	T t = *itr;
	vSrc.erase(itr);
	return t;
}

template <typename T,typename K>
bool ToolFrame::IsSelf(const T& tVct1,const K& tVct2){
	const void* p1 = &tVct1;
	const void* p2 = &tVct2;
	return p1 == p2;
}

template<typename Tkey,typename TValue>
bool ToolFrame::GetMin( const std::multimap<Tkey,TValue>& vSrc,std::vector<TValue>& vDes )
{
	if(vSrc.empty())return false;

	const Tkey& tKey = vSrc.begin()->first;
	typename std::multimap<Tkey,TValue>::const_iterator itr;
	foreach(itr,vSrc){
		if (tKey == itr->first)
		{
			vDes.push_back(itr->second);
			continue;
		}
		break;
	}

	return true;
}

template<typename Tkey,typename TValue>
bool ToolFrame::GetMax( const std::multimap<Tkey,TValue>& vSrc,std::vector<TValue>& vDes )
{
	if(vSrc.empty())return false;

	const Tkey& tKey = vSrc.rbegin()->first;
	typename std::multimap<Tkey,TValue>::const_reverse_iterator itr;
	foreachR(itr,vSrc){
		if (tKey == itr->first)
		{
			vDes.push_back(itr->second);
			continue;
		}
		break;
	}

	return true;
}

template<typename T,typename TFunCompair>
bool ToolFrame::IsEqual( const std::vector<T>& vSrc, const std::vector<T>& vDes,TFunCompair fnCompair )
{
	if (IsSelf(vSrc,vDes))return true;
	if (vSrc.empty() && vDes.empty())return true;//ĳЩ���size��empty�������ܶ�
	if (vSrc.size() != vDes.size())return false;

	if (!fnCompair) return false;

	for (size_t uIndex = 0;uIndex<vSrc.size();++uIndex)
	{
		if (!fnCompair(vSrc[uIndex],vDes[uIndex]))
			return false;
	}

	return true;
}

template<typename T>
bool ToolFrame::IsEqual( const std::set<T>& vSrc, const std::set<T>& vDes )
{
	if (IsSelf(vSrc,vDes))return true;
	if (vSrc.empty() && vDes.empty())return true;//ĳЩ���size��empty�������ܶ�
	if (vSrc.size() != vDes.size())return false;

	typename std::set<T>::const_iterator itrSrc,itrDes;
	for (itrSrc = vSrc.begin(),itrDes = vDes.begin();itrSrc != vSrc.end() && itrDes != vDes.end();++itrSrc,++itrDes)
	{
		if (*itrSrc != *itrDes)return false;
	}
	return true;
}

template<typename T>
bool ToolFrame::IsHasOne( const std::vector<T>& vValues, const std::vector<T>& tSub )
{
	if (vValues.empty() || tSub.empty())return false;

	typename std::vector<T>::const_iterator itr;
	foreach(itr,tSub){
		if (ToolFrame::IsHasValue(vValues,*itr))return true;
	}
	return false;
}

template<typename T>
bool ToolFrame::Merge( std::vector<T>& vDes,const std::set<T>& vSrc )
{
	if (vSrc.empty())return true;

	typename std::set<T>::const_iterator itr;
	foreach(itr,vSrc){
		vDes.push_back(*itr);
	}
	return true;
}

template<typename T>
bool ToolFrame::Merge( std::set<T>& vDes,const std::vector<T>& vSrc )
{
	if (vSrc.empty())return true;
	
	size_t uSize = vDes.size();
	typename std::vector<T>::const_iterator itr;
	foreach(itr,vSrc){
		vDes.insert(*itr);
	}
	return uSize + vSrc.size() == vDes.size();
}
template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
bool ToolFrame::Insert( std::multimap<TKey,TValue>& vMap,const TKeyInsert& tKey,const TValueInsert& kValue )
{
	size_t uSize = vMap.size();
	vMap.insert(std::make_pair((const TKey&)tKey,(const TValue&)kValue));
	return vMap.size() == uSize + 1;
}
template<typename TKey,typename TValue,typename TKeyInsert,typename TValueInsert>
bool ToolFrame::Insert( std::map<TKey,TValue>& vMap,const TKeyInsert& tKey,const TValueInsert& kValue )
{
	size_t uSize = vMap.size();
	vMap.insert(std::make_pair(tKey,kValue));//vMap[tKey]=kValue; ������д�������𡣴�д��������
	return vMap.size() == uSize + 1;
}

template<typename T,typename K>
bool ToolFrame::IsDifferentValue( const std::map<T,K>& vVct )
{
	if (vVct.empty())return true;

	//�洢ָ����ٿ���
	std::set<const K*> vTemp;

	typename std::map<T,K>::const_iterator itr;
	foreach(itr,vVct){
		const K* tK = &itr->second;
		typename std::set<const K*>::const_iterator itrTemp = vTemp.find(tK);
		if(itrTemp != vTemp.end()){
			return false;
		}

		vTemp.insert(tK);
	}

	return true;
}

template<typename T>
bool ToolFrame::IsDifferentValue( const std::vector<T>& vVct )
{
	//˼·:��ǰ���Ƚϵ�ֵ��֮���ÿһ��ֵ�Ƚϣ�����һ���ͷ���false

	if (vVct.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach(itr,vVct){
		const T& t1 = *itr;

		typename std::vector<T>::const_iterator itrNext=itr;
		++itrNext;
		foreachNext(itrNext,vVct){
			const T& t2 = *itrNext;
			if (t1 == t2)
				return false;
		}
	}

	return true;

	//if (vVct.empty())return true;

	//std::set<T> vTemp;

	//typename std::vector<T>::const_iterator itr;
	//foreach(itr,vVct){
	//	vTemp.insert(*itr);
	//}

	//return vTemp.size() == vVct.size();
}

template<typename T>
bool ToolFrame::IsDifferentValue( const std::list<T>& vVct )
{
	//˼·:��ǰ���Ƚϵ�ֵ��֮���ÿһ��ֵ�Ƚϣ�����һ���ͷ���false

	if (vVct.empty())return true;

	typename std::list<T>::const_iterator itr;
	foreach(itr,vVct){
		const T& t1 = *itr;

		typename std::list<T>::const_iterator itrNext=itr;
		++itrNext;
		foreachNext(itrNext,vVct){
			const T& t2 = *itrNext;
			if (t1 == t2)
				return false;
		}
	}

	return true;

	//if (vVct.empty())return true;

	//std::set<T> vTemp;

	//typename std::list<T>::const_iterator itr;
	//foreach(itr,vVct){
	//	vTemp.insert(*itr);
	//}

	//return vTemp.size() == vVct.size();
}

template<typename T>
void ToolFrame::PushHeapPtr( std::vector<T*>& vVct )
{
	std::push_heap(vVct.begin(),vVct.end(),T());
}

template<typename T>
void ToolFrame::PopHeapPtr( std::vector<T*>& vVct )
{
	std::pop_heap(vVct.begin(),vVct.end(),T());
}

template<typename T,typename TCmp>
bool ToolFrame::SortHeapHead( std::vector<T>& vVct,TCmp fnCmp )
{
	if (vVct.empty())return true;
	std::pop_heap(vVct.begin(),vVct.end(),fnCmp);
	std::push_heap(vVct.begin(),vVct.end(),fnCmp);
	return true;
}

template<typename T,typename TCmp>
bool ToolFrame::SortHeap( std::vector<T>& vVct,TCmp fnCmp )
{
	if (vVct.empty())return true;
	std::sort_heap(vVct.begin(),vVct.end(),fnCmp);
	return true;
}

template<typename T,typename TCmp>
void ToolFrame::PushHeap( std::vector<T>& vVct,TCmp fnCmp )
{
	std::push_heap(vVct.begin(),vVct.end(),fnCmp);
}

template<typename T,typename TCmp>
void ToolFrame::PopHeap( std::vector<T>& vVct,TCmp fnCmp )
{
	std::pop_heap(vVct.begin(),vVct.end(),fnCmp);
}

template<typename T,typename TCmp>
void ToolFrame::MakeHeap( std::vector<T>& vVct,TCmp fnCmp )
{
	std::make_heap(vVct.begin(),vVct.end(),fnCmp);
}

template<typename T>
bool ToolFrame::SortHeapHead( std::vector<T>& vVct )
{
	if (vVct.empty())return true;
	std::pop_heap(vVct.begin(),vVct.end());
	std::push_heap(vVct.begin(),vVct.end());
	return true;
}

template<typename T>
bool ToolFrame::SortHeap( std::vector<T>& vVct )
{
	if (vVct.empty())return true;
	std::sort_heap(vVct.begin(),vVct.end());
	return true;
}

template<typename T>
void ToolFrame::PushHeap( std::vector<T>& vVct )
{
	std::push_heap(vVct.begin(),vVct.end());
}

template<typename T>
void ToolFrame::PopHeap( std::vector<T>& vVct )
{
	std::pop_heap(vVct.begin(),vVct.end());
}

template<typename T>
void ToolFrame::MakeHeap( std::vector<T>& vVct )
{
	std::make_heap(vVct.begin(),vVct.end());
}

template<typename TValue>
bool ToolFrame::FileElement( std::ofstream& fStream,const TValue& tValue )
{
	fStream.write((const char*)&tValue,sizeof(tValue));

	return true;
}

template<typename TValue>
bool ToolFrame::FileElement( std::ifstream& fStream,TValue& tValue )
{
	fStream.read((char*)&tValue,sizeof(tValue));

	return true;
}

template<typename TKey,typename TValue,typename TArg>
uint ToolFrame::EraseByKey( std::multimap<TKey,TValue>& vSrc,const TArg& tKey,bool bEraseAll)
{
	if (bEraseAll)return vSrc.erase(tKey);

	typename std::multimap<TKey,TValue>::iterator itr = vSrc.find(tKey);
	if (itr != vSrc.end())
	{
		vSrc.erase(itr);
		return 1;
	}

	return 0;
}

template<typename TKey,typename Value>
Value* ToolFrame::GetLowerPtrMap( const std::map<TKey,Value>& vMap,const TKey& tKey )
{
	typename std::map<TKey,Value>::const_iterator itr = vMap.upper_bound(tKey);
	if (itr == vMap.begin())
		return nullptr;

	return  --itr != vMap.end() ? (Value*)&itr->second :nullptr;
}

template<typename TKey,typename ValuePtr>
ValuePtr ToolFrame::GetLowerMap(const std::map<TKey,ValuePtr>& vMap,const TKey& tKey )
{
	typename std::map<TKey,ValuePtr>::const_iterator itr = vMap.upper_bound(tKey);
	if (itr == vMap.begin())
		return ValuePtr();

	return  --itr != vMap.end() ? itr->second :ValuePtr();
}

template<typename T1,typename T2>
bool ToolFrame::MemCopy( T1& tDes,const T2& tSrc )
{
	::memcpy_s(&tDes,sizeof(T1),&tSrc,sizeof(T2));
	return true;
}

template<typename T1,typename T2>
bool ToolFrame::MemCopy( std::set<T1>& tDes,const std::set<T2>& tSrc )
{
	tDes.clear();

	typename std::set<T2>::const_iterator itr;
	foreach(itr,tSrc){
		T1 t;
		if (!MemCopy(t,*itr))return false;

		tDes.insert(t);
	}
	return true;
}

template<typename T1,typename T2>
bool ToolFrame::MemCopy( std::vector<T1>& tDes,const std::vector<T2>& tSrc )
{
	tDes.clear();

	typename std::vector<T2>::const_iterator itr;
	foreach(itr,tSrc){
		T1 t;
		if (!MemCopy(t,*itr))return false;

		tDes.push_back(t);
	}
	return true;
}

template<typename ValuePtr>
ValuePtr ToolFrame::GetFrontPtr(const std::vector<ValuePtr>& vSrc )
{
	if (vSrc.empty())return ValuePtr();
	return vSrc[0];
}

template<typename ValuePtr>
ValuePtr ToolFrame::GetFrontPtr(const std::list<ValuePtr>& vSrc )
{
	if (vSrc.empty())return ValuePtr();

	return vSrc.front();
}

template<typename T,typename TFn>
bool ToolFrame::Sort( std::vector<T>& vVct,TFn fnCompair )
{
	if (vVct.empty())return true;
	std::sort(vVct.begin(),vVct.end(),fnCompair);
	return true;
}

template<typename T>
bool ToolFrame::Sort( std::vector<T>& vVct)
{
	if (vVct.empty())return true;
	std::sort(vVct.begin(),vVct.end());
	return true;
}

template<typename T>
bool ToolFrame::EraseFront( std::list<T>& vSrc )
{
	if (vSrc.empty())return false;
	vSrc.erase(vSrc.begin());
	return true;
}

template<typename T,typename TAlloc>
bool ToolFrame::EraseFront( std::set<T,TAlloc>& vSrc )
{
	if (vSrc.empty())return false;
	vSrc.erase(vSrc.begin());
	return true;
}

template<typename T>
bool ToolFrame::EraseFront( std::set<T>& vSrc )
{
	if (vSrc.empty())return false;
	vSrc.erase(vSrc.begin());
	return true;
}

template<typename T>
int ToolFrame::SizeOf( T* pT )
{
	return sizeof(T);
}

template<typename T>
int ToolFrame::SizeOf()
{
	return sizeof(T);
}

template<typename T>
T ToolFrame::RandValue(const std::set<T>& vSrc,int tDefalut )
{
	if (vSrc.empty())return tDefalut;
	return RandValue(vSrc);
}

template<typename T, typename K>
int ToolFrame::RandIndex(const std::map<T, K>& vSrc)
{
	return vSrc.empty() ? -1 : Rand(0, (int)vSrc.size() - 1);
}

template<typename T>
int ToolFrame::RandIndex( const std::set<T>& vSrc )
{
	return vSrc.empty() ? -1:Rand(0, (int)vSrc.size()-1);
}

template<typename T>
int ToolFrame::RandIndex( const std::vector<T>& vSrc )
{
	return vSrc.empty() ? -1:Rand(0,(int)vSrc.size()-1);
}

template<typename T>
int ToolFrame::RandIndex( const std::list<T>& vSrc )
{
	return vSrc.empty() ? -1:Rand(0, (int)vSrc.size()-1);
}

template<typename T>
const T& ToolFrame::RandValue( const std::vector<T>& vSrc,const T& tDefalut )
{
	if (vSrc.empty())return tDefalut;

	return RandValue(vSrc);
}

template<typename TKey, typename TValue>
const TValue& ToolFrame::RandValue(const std::map<TKey, TValue>& vSrc, const TValue& tDefalut)
{
	if (vSrc.empty())return tDefalut;

	return RandValue(vSrc);
}

template<typename T>
const T& ToolFrame::RandValue(const std::set<T>& vSrc,const T& tDefalut )
{
	if (vSrc.empty())return tDefalut;
	return RandValue(vSrc);
}

template<typename T>
T ToolFrame::RandValue(const std::vector<T>& vSrc,int tDefalut )
{
	if (vSrc.empty())return tDefalut;
	return RandValue(vSrc);
}

template<typename T>
int ToolFrame::DeleteByValue( std::set<T>& vVct,const T& tVal )
{
	typename std::set<T>::iterator itr = vVct.find(tVal);
	if (itr != vVct.end())
	{
		Delete(*itr);
		vVct.erase(itr);
		return 1;
	}
	return 0;
}

template<typename T,typename K>
bool ToolFrame::Insert( std::set<T>& vSet,const K& tValue )
{
	size_t uSize = vSet.size();
	vSet.insert(tValue);
	return vSet.size() == uSize + 1;
}

template <typename TVct,typename KArray>
bool ToolFrame::VctToArray( const std::vector<TVct>& vSrc,KArray* tArray,int uLengthMax,int nLength)
{
	if ( -1 == nLength)nLength = vSrc.size();
	if (nLength > uLengthMax)return false;

	for ( int uIndex =0;uIndex<nLength;++uIndex)
	{
		tArray[uIndex] = (KArray)vSrc[uIndex];
	}

	return true;
}

template<typename T>
bool ToolFrame::IsHasValue( const std::list<T>& vValues, const std::list<T>& tSub )
{
	if (tSub.empty())return false;

	typename std::list<T>::const_iterator itr;
	foreach(itr,tSub){
		if (!IsHasValue(vValues,*itr))
			return false;
	}
	return true;
}

template<typename T>
bool ToolFrame::IsHasValue( const std::list<T>& vValues, const T& tValue )
{
	typename std::list<T>::const_iterator itr;
	foreach(itr,vValues){
		if(*itr == tValue){
			return true;
		}
	}
	return false;
}


template<typename T>
bool ToolFrame::IsHasValue( const std::vector<T>& vValues, const std::vector<T>& tSub )
{
	if (tSub.empty())return false;

	typename std::vector<T>::const_iterator itr;
	foreach(itr,tSub){
		if (!IsHasValue(vValues,*itr))
			return false;
	}
	return true;
}

template<typename T>
bool ToolFrame::EraseFront( std::vector<T>& vSrc )
{
	if (vSrc.empty())return false;

	vSrc.erase(vSrc.begin());
	return true;
}

template<typename T>
bool ToolFrame::EraseBack( std::list<T>& vSrc )
{
	if (vSrc.empty())return false;

	vSrc.pop_back();
	return true;
}

template<typename T>
bool ToolFrame::EraseBack( std::vector<T>& vSrc )
{
	if (vSrc.empty())return false;

	vSrc.erase(vSrc.begin() + vSrc.size() - 1 );
	return true;
}

template<typename T,typename TArg>
int ToolFrame::GetIndexByValue( const std::vector<T>& vDes,const TArg& kValue )
{
	for (size_t uIndex =0;uIndex<vDes.size();++uIndex)
	{
		if (ToolFrame::IsEqual(vDes[uIndex],kValue))
			return (int)uIndex;
	}
	return -1;
}

template<typename T>
bool ToolFrame::RandValue(const std::vector<T>& vSrc,std::vector<T>& vDes,size_t uCount )
{
	if (vSrc.size() == uCount)
		return ToolFrame::Merge(vDes,vSrc);

	//�����㹻�����ظ���Index
	if (vSrc.empty())return false;
	if (!IsInClosedInterval<int>(uCount,1,vSrc.size()))return false;

	SetInt vIndex;
	while(vIndex.size() < uCount){
		vIndex.insert(Rand(0,vSrc.size()-1));
	}

	typename SetInt::iterator itr;
	foreach(itr,vIndex)
	{
		const T& tValue = GetValueByIndex(vSrc,*itr);
		vDes.push_back(tValue);
	}
	return true;
}

template<typename T,typename K>
bool ToolFrame::RandValue(const std::map<T,K>& vSrc,std::vector<K>& vDes,size_t uCount )
{
	if (vSrc.size() == uCount)
		return ToolFrame::Merge(vDes,vSrc);

	//�����㹻�����ظ���Index
	if (vSrc.empty())return false;
	if (!IsInClosedInterval<int>(uCount,1,vSrc.size()))return false;

	SetInt vIndex;
	while(vIndex.size() < uCount){
		vIndex.insert(Rand(0,vSrc.size()-1));
	}

	typename SetInt::iterator itr;
	foreach(itr,vIndex)
	{
		const K& k = GetValueByIndex(vSrc,*itr);
		vDes.push_back(k);
	}
	return true;
}

template<typename K>
bool ToolFrame::Insert( std::map<int,K>& vMap,int tKey,const K& kValue )
{
	size_t uSize = vMap.size();
	vMap[tKey] = kValue;
	return vMap.size() == uSize + 1;
}
template <typename T>
int ToolFrame::GetCountValueDifferent( T* tArray,int nLength,const T& tDes )
{
	int nCount = 0;
	for (int nIndex =0;nIndex<nLength;++nIndex)
	{
		if (tArray[nIndex] != tDes)
			++nCount;
	}
	return nCount;
}

template <typename T>
int ToolFrame::GetCountValueSame( T* tArray,int nLength,const T& tDes )
{
	int nCount = 0;
	for (int nIndex =0;nIndex<nLength;++nIndex)
	{
		if (tArray[nIndex] == tDes)
			++nCount;
	}
	return nCount;
}

template<typename T>
int ToolFrame::GetValueBySeq( std::vector<T>& vDes,const std::vector<T>& vSrc,int nNum,bool bFront /*= true*/ )
{
	int nSize = (int)vSrc.size();
	if (nNum <= 0)return 0;
	if (nNum >= nSize)nNum = nSize;

	//Ҫ��֤ȡ�õ�ֵ��˳����Դһ��
	if (bFront)
	{
		for (int uIndex =0;uIndex<nNum;++uIndex)
		{
			vDes.push_back(vSrc[uIndex]);
		}
	}else{
		for (int uIndex =nSize - nNum;uIndex<nSize;++uIndex)
		{
			vDes.push_back(vSrc[uIndex]);
		}
	}

	return nNum;
}
template<typename T>
uint ToolFrame::EraseBySeq( std::vector<T>& vVct,uint uNum,bool bFront /*= true*/ )
{
	if (uNum <= 0)return 0;
	if (vVct.empty())return 0;
	uint uSize = vVct.size();
	if (uSize <= uNum)
	{
		vVct.clear();
		return uSize;
	}

	if (bFront)
	{
		for (uint nIndex =0;nIndex<uNum;++nIndex)
		{
			uint nIdx = (uNum-1)-nIndex;
			vVct.erase(vVct.begin() + nIdx);
		}
	}else{
		for (uint nIndex =0;nIndex<uNum;++nIndex)
		{
			uint nIdx = (uSize-1)-nIndex;
			vVct.erase(vVct.begin() + nIdx);
		}
	}

	return uNum;
}

template <typename T>
bool ToolFrame::ModifyValueCopy( T* tArray,int nLength,const T& tSrc,T tDes )
{
	for(int nIndex =0;nIndex<nLength;++nIndex){
		if (tArray[nIndex] == tSrc)
		{
			tArray[nIndex] = tDes;
			return true;
		}
	}
	return false;
}
template <typename T>
bool ToolFrame::ModifyValue( T* tArray,int nLength,const T& tSrc,T& tDes )
{
	for(int nIndex =0;nIndex<nLength;++nIndex){
		if (tArray[nIndex] == tSrc)
		{
			tArray[nIndex] = tDes;
			return true;
		}
	}
	return false;
}

template <typename T>
bool ToolFrame::IsHasValue( T* tArray,int nLength,T& tValue )
{
	for(int nIndex =0;nIndex<nLength;++nIndex){
		if (tArray[nIndex] == tValue)
			return true;
	}
	return false;
}

template<typename ValuePtr, typename TKey>
ValuePtr ToolFrame::RandPtr(const std::map<TKey, ValuePtr>& vSrc)
{
	if (vSrc.empty())return ValuePtr();

	return ToolFrame::GetPtrValueByIndex(vSrc,RandIndex(vSrc));
}

template<typename ValuePtr>
ValuePtr ToolFrame::RandPtr(const std::vector<ValuePtr>& vSrc )
{
	if (vSrc.empty())return ValuePtr();

	return vSrc[Rand(0,(int)vSrc.size()-1)];
}

template<typename T>
T* ToolFrame::RandValuePtr(const std::vector<T>& vSrc )
{
	if (vSrc.empty())return nullptr;

	return &RandValue(vSrc);
}

template<typename TKey, typename TValue>
TValue* ToolFrame::RandValuePtr(const std::map<TKey, TValue>& vSrc)
{
	if (vSrc.empty())return nullptr;

	return &RandValue(vSrc);
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::vector<T>& vSrc,std::set<K>& vDes )
{
	if (vSrc.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach(itr,vSrc){
		K tValue;
		if (!ToolFrame::ToValue(*itr,tValue))return false;
		vDes.insert(tValue);
	}

	return true;
}

template<typename T,typename Arg>
bool ToolFrame::EraseByValue( std::vector<T>& vDes,const std::set<Arg>& vSrc )
{
	if (vDes.empty())return false;

	typename std::vector<T>::iterator itr;
	foreach(itr, vDes) {
		if (IsHasValue(vSrc, *itr)) {
			vDes.erase(itr);
			return true;
		}
	}
	
	return false;
}

template<typename T,typename Arg>
bool ToolFrame::EraseByValue( std::vector<T>& vDes,const std::vector<Arg>& vSrc )
{
	if (vDes.empty())return false;

	typename std::vector<T>::iterator itr;
	foreach(itr, vDes) {
		if (IsHasValue(vSrc, *itr)) {
			vDes.erase(itr);
			return true;
		}
	}

	return false;
}

template<typename T,typename K>
void ToolFrame::ArrayToVct( std::vector<T>& vDes,K* kArray,int nCount )
{
	for (int nIndex =0;nIndex<nCount;++nIndex)
	{
		vDes.push_back(kArray[nIndex]);
	}
}

template<typename T,typename K>
void ToolFrame::PushSameValue(std::vector<T>& vDes,const K& kValue,int nCount)
{
	for (int nIndex = 0;nIndex <nCount;++nIndex)
		vDes.push_back(kValue);
}

template<typename T,typename K>
void ToolFrame::PushSameValue( std::list<T>& vDes,const K& kValue,int nCount )
{
	for (int nIndex = 0;nIndex <nCount;++nIndex)
		vDes.push_back(kValue);
}

template<typename T>
int ToolFrame::GetBits(const T&)
{
	return sizeof(T)*8;
}
template <typename T>
std::string ToolFrame::ArrayToString( T* tArray,int nLength)
{
	std::stringstream sStream;
	sStream<<tArray[0];
	for (int nIndex =1;nIndex<nLength;++nIndex)
	{
		sStream<<","<<tArray[nIndex];
	}

	return sStream.str();
}

template<typename T>
T& ToolFrame::GetFront( std::list<T>& vSrc )
{
	assert(!vSrc.empty());
	return vSrc.front();
}

template<typename T>
const T& ToolFrame::GetFront(const std::list<T>& vSrc )
{
	assert(!vSrc.empty());
	return vSrc.front();
}
template<typename T>
const T& ToolFrame::GetFront(const std::vector<T>& vSrc )
{
	assert(!vSrc.empty());
	return *vSrc.begin();
}
template<typename T>
const T& ToolFrame::GetBack(const std::vector<T>& vSrc )
{
	assert(!vSrc.empty());
	return *(--vSrc.end());
}

template<typename T>
T& ToolFrame::GetFront( std::vector<T>& vSrc )
{
	assert(!vSrc.empty());
	return *vSrc.begin();
}

template<typename T>
const T& ToolFrame::GetBack(const std::list<T>& vSrc )
{
	assert(!vSrc.empty());
	return vSrc.back();
}

template<typename T,typename K>
bool ToolFrame::Move( std::map<T,K>& vDes,std::map<T,K>& vSrc )
{
	if (IsSelf(vDes,vSrc))return false;

	if (!Merge(vDes,vSrc))return false;

	vSrc.clear();

	return true;
}

template<typename T>
bool ToolFrame::Move( std::list<T>& vSrc,std::list<T>& vDes,const std::list<T>& vSrcSub )
{
	if (IsSelf(vDes,vSrc))return false;
	//����:vSrcSubһ����vSrc���Ӽ�
	if (!Merge(vDes,vSrcSub))return false;
	return vSrcSub.size() == EraseByValueAll(vSrc,vSrcSub);
}

template<typename T>
bool ToolFrame::Move( std::vector<T>& vSrc,std::vector<T>& vDes,const std::vector<T>& vSrcSub,bool bSrcBack /*= true*/,bool bDesBack /*= true*/ )
{
	if (IsSelf(vDes,vSrc))return false;
	//����:vSrcSubһ����vSrc���Ӽ�
	if (!Merge(vDes,vSrcSub,vSrcSub.size(),bSrcBack,bDesBack))return false;
	return vSrcSub.size() == EraseByValueAll(vSrc,vSrcSub);
}

template<typename T>
bool ToolFrame::Move( std::vector<T>& vSrc,std::vector<T>& vDes,int nNum /*= -1*/,bool bSrcBack /*= true*/,bool bDesBack /*= true*/ )
{
	if (IsSelf(vDes,vSrc))return false;
	if (nNum < 0) nNum= (int)vSrc.size();
	if (nNum > (int)vSrc.size()) nNum = (int)vSrc.size();

	if (!Merge(vDes,vSrc,nNum,bSrcBack,bDesBack))return false;
	EraseBySeq(vSrc,nNum,!bSrcBack);

	return true;
}

template <typename T,typename K>
void ToolFrame::SafeCopy( T& tDes,const K& tSrc )
{
	int nMin = Min(sizeof(tDes),sizeof(tSrc));
	memcpy_s(&tDes,sizeof(tDes),&tSrc,nMin);
}
template <typename TMapKey,typename TMapValue>
void ToolFrame::GetMapValue( const std::map<TMapKey,TMapValue>& vSrc,std::vector<TMapKey>& vDes )
{
	typename std::map<TMapKey,TMapValue>::const_iterator itr;
	foreach(itr,vSrc){
		vDes.push_back(itr->second);
	}
}
template <typename TMapKey,typename TMapValue>
void ToolFrame::GetMapKey( const std::map<TMapKey,TMapValue>& vSrc,std::vector<TMapKey>& vDes )
{
	typename std::map<TMapKey,TMapValue>::const_iterator itr;
	foreach(itr,vSrc){
		vDes.push_back(itr->first);
	}
}

template <typename T,typename K>
bool ToolFrame::ToValue( const std::vector<T>& vSrc,std::vector<K>& vDes )
{
	if (vSrc.empty())return true;

	K tTemp;
	for (size_t uIndex = 0;uIndex<vSrc.size();++uIndex)
	{
		if (!ToolFrame::ToValue(vSrc[uIndex],tTemp))return false;
		vDes.push_back(tTemp);
	}
	return true;
}

template<typename T, typename Value>
bool ToolFrame::PushFront(std::vector<T>& vVct, const Value& tValue)
{
	vVct.insert(vVct.begin(),tValue);
	return true;
}

template<typename T, typename Value>
bool ToolFrame::PushFront(std::list<T>& vVct, const Value& tValue)
{
	vVct.push_front(tValue);
	return true;
}

template<typename T,typename Value>
bool ToolFrame::PushBack(std::vector<T>& vVct,const Value& tValue){
	vVct.push_back(tValue);
	return true;
}

template<typename T,typename Value>
bool ToolFrame::PushBack(std::list<T>& vVct,const Value& tValue){
	vVct.push_back(tValue);
	return true;
}

template<typename T>
bool ToolFrame::MemClear( T* pTStruct )
{
	if (!pTStruct)return false;

	memset(pTStruct,0,sizeof(T));
	return true;
}

template<typename T>
bool ToolFrame::MemClear( T& t )
{
	memset(&t,0,sizeof(t));
	return true;
}

template <typename T>
void ToolFrame::SafeStringCopy( const std::string& sSrc,T& szT )
{
	strcpy_s(szT,sizeof(szT),sSrc.c_str());
}

template<typename T>
void ToolFrame::ArrayCopy( T pDes[],const T pSrc[],int nLength )
{
	for (int nIndex = 0;nIndex<nLength;++nIndex)
	{
		pDes[nIndex] = pSrc[nIndex];
	}
}

template <typename T>
void ToolFrame::ArrayAssign( T* pDes,int nLength,T tValue )
{
	for (int nIndex = 0;nIndex<nLength;++nIndex)
	{
		pDes[nIndex] = tValue;
	}
}

template<typename T,typename Value>
bool ToolFrame::IsSameValue( const std::vector<T>& vVct,const Value& tVal )
{
	typename std::vector<T>::const_iterator itr;
	foreach(itr,vVct){
		if (*itr != tVal)
			return false;
	}

	return true;
}

template<typename T,typename Value>
bool ToolFrame::IsSameValue( const std::list<T>& vVct,const Value& tVal )
{
	typename std::list<T>::const_iterator itr;
	foreach(itr,vVct){
		if (*itr != tVal)
			return false;
	}

	return true;
}

template <typename T>
void ToolFrame::Swap( T& tSrc,T& tDes )
{
	T t = tSrc;
	tSrc = tDes;
	tDes = t;
}
template<typename T>
std::vector<T> ToolFrame::GetMapValue( const std::map<T,T>& vMap,bool bKey /*= true*/ )
{
	std::vector<T> vReturn;
	typename std::map<T,T>::const_iterator itr;
	foreach (itr,vMap)
	{
		vReturn.push_back( bKey ? itr->first:itr->second);
	}

	return vReturn;
}

template<typename T>
int ToolFrame::ReplaceByValue( std::vector<T>& vVct,const T& tSrc,const T& tDes )
{
	int nCount = 0;

	for (size_t uIndex =0;uIndex < vVct.size();++uIndex)
	{
		if (vVct[uIndex] == tSrc)
		{
			vVct[uIndex] = tDes;
			++nCount;
		}
	}

	return nCount;
}

template<typename T,typename Arg>
bool ToolFrame::EraseByValue( std::list<T>& vVct,const Arg& tVal,bool bBack)
{
	if (vVct.empty())return false;

	if(!bBack){
		typename std::list<T>::iterator itr;
		foreach(itr,vVct){
			if (tVal == *itr)
			{
				itr = vVct.erase(itr);
				return true;
			}
		}
	}else{
		typename std::list<T>::iterator itr;
		foreachReverse(itr,vVct){
			if (tVal == *itr)
			{
				itr = vVct.erase(itr);
				return true;
			}
		}
	}

	return false;
}

template<typename T,typename Arg>
bool ToolFrame::EraseByValue( std::set<T>& vVct,const Arg& tVal )
{
	if (vVct.empty())return false;

	size_t uSize = vVct.size();
	vVct.erase(tVal);

	return vVct.size() + 1 == uSize ? 1:0;
}

template<typename T,typename Arg>
bool ToolFrame::EraseByValue( std::vector<T>& vVct,const Arg& tVal,bool bBack)
{
	if (vVct.empty())return false;

	if (!bBack)
	{
		typename std::vector<T>::iterator itr;
		foreach(itr,vVct){
			if (tVal == *itr)
			{
				vVct.erase(itr);
				return true;
			}
		}
	}else{
		typename std::vector<T>::iterator itr;
		foreachReverse(itr,vVct){
			if (tVal == *itr)
			{
				itr = vVct.erase(itr);
				return true;
			}
		}
	}

	return false;
}

template <typename Tkey,typename Tvalue>
bool ToolFrame::DeleteByKey( std::map<Tkey,Tvalue*>& vMap,const Tkey& tKey )
{
	typename std::map<Tkey,Tvalue*>::iterator itr = vMap.find(tKey);
	if (itr == vMap.end())return false;

	Delete(itr->second);

	vMap.erase(itr);
	return true;
}

template <typename Tkey,typename Tvalue>
bool ToolFrame::DeleteByKey( std::multimap<Tkey,Tvalue*>& vMap,const Tkey& tKey )
{
	typedef typename std::multimap<Tkey,Tvalue*>::iterator	ItrMap;
	typedef typename std::pair<ItrMap,ItrMap>				PairItrMap;

	PairItrMap pair = vMap.equal_range(tKey);
	if (IsEnd(pair))return false;
	for (ItrMap itr = pair.first;itr != pair.second;++itr)
		Delete(itr->second);

	vMap.erase(tKey);
	return true;
}

template<typename TKey,typename TValue>
TValue& ToolFrame::GetValueUpperMap( const  std::map<TKey,TValue>& vMap,const TKey& tKey,TValue& tDefault )
{
	typename std::map<TKey,TValue>::const_iterator itr = vMap.upper_bound(tKey);
	return  itr != vMap.end() ? itr->second :tDefault;
}

template<typename TKey,typename ValuePtr>
ValuePtr ToolFrame::GetValueUpperMap(const std::map<TKey,ValuePtr>& vMap,const TKey& tKey )
{
	typename std::map<TKey,ValuePtr>::const_iterator itr = vMap.upper_bound(tKey);
	return  itr != vMap.end() ? itr->second :ValuePtr();

}
template<typename TKey,typename ValuePtr>
ValuePtr ToolFrame::GetLowerMultMap(const std::multimap<TKey,ValuePtr>& vMap,const TKey& tKey)
{
	typename std::multimap<TKey,ValuePtr>::const_iterator itr = vMap.upper_bound(tKey);
	if (itr == vMap.begin())
		return ValuePtr();

	return  --itr != vMap.end() ? itr->second :ValuePtr();
}

template<typename T>
void ToolFrame::Shuffle( std::vector<T>& vValues )
{
	if (vValues.empty())return;
	random_shuffle(vValues.begin(),vValues.end());
}

template <typename T,typename K>
void ToolFrame::InsertValue( T& tValue,K kSrc )
{
	tValue <<= GetBits(kSrc); 
	tValue |= kSrc;
}

template<typename T>
bool ToolFrame::SetValue( std::vector<T>& vSrc,int nArgs,T* tArray )
{
	for (int nIndex = 0;nIndex < nArgs;++nIndex)
		vSrc.push_back(tArray[nIndex]);

	return true;
}
template<typename T>
bool ToolFrame::SetValue( std::vector<T>& vSrc,int nArgs,... )
{
	va_list vaList;
	va_start(vaList, nArgs);

	for (int nIndex = 0;nIndex < nArgs;++nIndex)
		vSrc.push_back(*va_arg(vaList, T*));

	va_end(vaList);

	return true;
}

template<typename T>
bool ToolFrame::GetValueArgs( const std::vector<T>& vSrc,int nArgs,... )
{
	va_list vaList;
	va_start(vaList, nArgs);

	typename std::vector<T>::const_iterator itr;
	int nCount = 0;
	foreach(itr,vSrc){
		if (nCount >= nArgs)break;

		*va_arg(vaList, T*) = *itr;

		++nCount;
	}

	va_end(vaList);

	if (vSrc.size() < nArgs)return false;
	return true;
}

template <typename T>
void ToolFrame::ArrayCal(T* tArray,int nLength,const signed long& tValue){
	for(int tCount=0;tCount<nLength;++tCount)
		tArray[tCount] += tValue;
}

template <typename T,typename TCount>
void ToolFrame::SetBool( T* tValue,TCount tCount,bool bBool /*= true*/ )
{
	bBool? *tValue |= (1<<tCount) : *tValue &= ~(1<<tCount);
}
template <typename T,typename TCount>
bool ToolFrame::GetBool( T t,TCount tCount )
{
	return (t>>tCount) & 1;
}
template<typename T,typename K,typename TArg>
bool ToolFrame::IsHasKey( const std::map<T,K>& vValues, const TArg& tKey )
{
	return vValues.find(tKey) != vValues.end() ;
}

template<typename T,typename K,typename M>
bool ToolFrame::IsHasValue( const std::map<T,K>& vValues, const M& mValue )
{
	typename std::map<T,K>::const_iterator itr;
	foreach(itr,vValues){
		if(itr->second == mValue){
			return true;
		}
	}
	return false;
}

template<typename T,typename K>
bool ToolFrame::IsHasValue( const std::vector<T>& vValues, const K& tKey )
{
	typename std::vector<T>::const_iterator itr;
	foreach(itr,vValues){
		if (tKey == *itr)
			return true;
	}
	return false;
}

template<typename T>
bool ToolFrame::IsHasValue( const std::vector<T>& vValues, const T& tKey )
{
	typename std::vector<T>::const_iterator itr;
	foreach(itr,vValues){
		if(*itr == tKey)
			return true;
	}
	return false;
}

template<typename TVct,typename TValue>
bool ToolFrame::IsHasKey( const std::set<TVct>& vSrc, const TValue& tValue )
{
	return vSrc.find(tValue) != vSrc.end();
}

template<typename TVct,typename TValue>
bool ToolFrame::IsHasValue( const std::set<TVct>& vSrc, const TValue& tValue )
{
	return IsHasKey(vSrc,tValue);//��set������ֻ�м�
}

template <typename Tkey,typename Tvalue>
void ToolFrame::Delete( std::multimap<Tkey,Tvalue*>& vValues )
{
	typename std::multimap<Tkey,Tvalue*>::iterator itr;
	foreach(itr,vValues){
		Delete(itr->second);
	}
	vValues.clear();
}
template <typename Tkey,typename Tvalue>
void ToolFrame::Delete( std::map<Tkey,Tvalue*>& vValues )
{
	typename std::map<Tkey,Tvalue*>::iterator itr;
	foreach(itr,vValues){
		Delete(itr->second);
	}
	vValues.clear();
}
template <typename Tvalue>
void ToolFrame::Delete( std::vector<Tvalue*>& vValues )
{
	typename std::vector<Tvalue*>::iterator itr;
	foreach(itr,vValues){
		Delete(*itr);
	}
	vValues.clear();
}

template <typename Tvalue>
void ToolFrame::Delete( std::set<Tvalue*>& vValues )
{
	typename std::set<Tvalue*>::iterator itr;
	foreach(itr,vValues){
		Tvalue* pValue = *itr;
		Delete(pValue);
	}
	vValues.clear();
}

template <typename Tvalue>
void ToolFrame::Delete( std::list<Tvalue*>& vValues )
{
	typename std::list<Tvalue*>::iterator itr;
	foreach(itr,vValues){
		Delete(*itr);
	}
	vValues.clear();
}
template <typename TKey, typename TValue>
bool ToolFrame::SetValueByIndex(std::map<TKey,TValue>& vMap,const TKey& tKey,const TValue& tValue,bool bCreate){
	if(bCreate){
		vMap[tKey] = tValue;
		return true;
	}

	typename std::map<TKey,TValue>::iterator itr = vMap.find(tKey);
	if (itr == vMap.end()){
		return false;
	}

	itr->second = tValue;
	return true;
}

template<typename T,typename K>
bool ToolFrame::Reverse( std::map<K,T>& vDes,const std::map<T,K>& vSrc )
{
	vDes.clear();
	typename std::map<T,K>::const_iterator itr;
	foreach(itr,vSrc){
		vDes.insert(std::make_pair(itr->second,itr->first));
	}

	return true;
}
template<typename T,typename K>
bool ToolFrame::Merge( std::map<T,K>& vDes,const std::map<T,K>& vSrc )
{
	if (vSrc.empty())return true;

	size_t uSize = vDes.size();
	typename std::map<T,K>::const_iterator itr;
	foreach(itr,vSrc){
		vDes.insert(std::make_pair(itr->first,itr->second));
	}

	return uSize + vSrc.size() == vDes.size();
}
template<typename T>
bool ToolFrame::Merge( std::list<T>& vDes,const std::list<T>& vSrc,bool bBack)
{
	if (vSrc.empty())return true;

	if (bBack)
	{
		typename std::list<T>::const_iterator itr;
		foreach(itr, vSrc) {
			vDes.push_back(*itr);
		}
		return true;
	}

	typename std::list<T>::const_iterator itr;
	foreach(itr, vSrc) {
		vDes.push_front(*itr);
	}
	return true;
}

template<typename T>
bool ToolFrame::Merge( std::vector<T>& vDes,const std::vector<T>& vSrc,int nNum,bool bSrcBack /*= false*/,bool bDesBack /*= false*/ )
{
	if (vSrc.empty())return true;

	if (nNum < 0) nNum = (int)vSrc.size();
	if (nNum > (int)vSrc.size()) nNum = (int)vSrc.size();

	if (bDesBack && !bSrcBack)
	{
		for (int nIndex =0;nIndex<nNum;++nIndex)
		{
			vDes.push_back(vSrc[nIndex]);
		}

		return true;
	}
	if (bDesBack && bSrcBack)
	{
		for (int uIndex = (int)vSrc.size()-1;uIndex>(int)vSrc.size()-1 - nNum;--uIndex)
		{
			vDes.push_back(vSrc[uIndex]);
		}

		return true;
	}
	if (!bDesBack && !bSrcBack)
	{
		//˼·:���·�����ʵĿռ䣬Ȼ��Ŀ��������Ԫ�� �Ƶ���β�ͣ�Ȼ��������Ԫ�ط����·���Ŀռ�
		int nSizeDes = (int)vDes.size();
		int nSizeTotal = nSizeDes + nNum;
		vDes.resize(nSizeTotal);

		for (int nIndex =nSizeTotal-1;nIndex >=nNum ;--nIndex)
		{
			vDes[nIndex] = vDes[nIndex-nNum];
		}

		for (int nIndex =0;nIndex < nNum;++nIndex)
		{
			vDes[nIndex] = vSrc[nIndex];
		}

		return true;
	}

	if (!bDesBack && bSrcBack)
	{
		//˼·:���·�����ʵĿռ䣬Ȼ��Ŀ��������Ԫ�� �Ƶ���β�ͣ�Ȼ��������Ԫ�ط����·���Ŀռ�
		int nSizeDes = (int)vDes.size();
		int nSizeTotal = nSizeDes + nNum;
		vDes.resize(nSizeTotal);

		for (int nIndex =nSizeTotal-1;nIndex >=nNum ;--nIndex)
		{
			vDes[nIndex] = vDes[nIndex-nNum];
		}

		for (int nIndex =0;nIndex < nNum;++nIndex)
		{
			vDes[nIndex] = vSrc[vSrc.size()-1-nIndex];
		}

		return true;
	}

	return false;
}

template<typename T>
bool ToolFrame::MergeExcept( std::vector<T>& vDes,const std::vector<T>& vSrc,const T& tVal )
{
	if (vSrc.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach(itr,vSrc){
		if (tVal != *itr)
			vDes.push_back(*itr);
	}
	return true;
}

template <typename Tkey,typename ValuePtr,typename TKeyInsert>
ValuePtr ToolFrame::GetPtrValueByKey( std::map<Tkey,ValuePtr>& vMap,TKeyInsert& tKey,bool bCreate )
{
	ValuePtr pValue=GetPtrValueByKey(vMap,tKey);
	if (!pValue && bCreate )
	{
		pValue = CreateByPtr(pValue);
		vMap[tKey]=pValue;
	}

	return pValue;
}

template <typename Tkey,typename ValuePtr,typename TkeyArg>
ValuePtr ToolFrame::GetPtrValueByKey( const std::map<Tkey,ValuePtr>& vMap,const TkeyArg& tKey )
{
	typename std::map<Tkey,ValuePtr>::const_iterator itrMap = vMap.find(tKey);
	return itrMap!=vMap.end() ? itrMap->second : ValuePtr();
}

template <typename Tkey,typename Tvalue>
void ToolFrame::SafeDrop( std::map<Tkey,Tvalue*>& vMap )
{
	typename std::map<Tkey,Tvalue*>::iterator itr;
	foreach(itr,vMap){
		SafeDrop(itr->second);
	}
}
template <typename T>
void ToolFrame::SafeDrop( T* pT )
{
	if(pT) pT->Drop();
}

template <typename T>
void ToolFrame::Delete( T*& pT,bool bGroup /*= false*/ )
{
	if(pT){
		bGroup ? delete[] pT:delete pT;
		pT = nullptr;
	} 
}

template <typename T>
std::string ToolFrame::ToString(const T& tValue)
{
	std::string sValue;
	if (!ToValue(tValue,sValue))return "";
	return sValue;
}
template <typename T>
bool ToolFrame::ToValue( const std::string* sSrc,T& tDes )
{
	if (!sSrc)return false;
	return ToValue(*sSrc,tDes);
}

template<typename T>
bool ToolFrame::ToValue( const std::string& sSrc,T& nValue )
{
	if (sSrc.empty())return false;

	//����:һ�����ַ���������
	std::string sSrcUpper = sSrc;
	ToolFrame::ToUpperCase(sSrcUpper);

	//������ʽ
	//����˳������ ���ɵ���
	//16����
	if (ToolFrame::IsBeginWith(sSrcUpper,"-0X")){
		const std::string sValue = ToolFrame::GetMidString(sSrcUpper,"-0X","");
		if (sValue.empty())return false;

		long uTemp = 0;
		std::stringstream sStream;
		sStream <<"-"<< sValue;
		sStream >>std::hex>>uTemp;
		if (!sStream.eof())return false;
		return ToValue(uTemp,nValue);
	}
	if (ToolFrame::IsBeginWith(sSrcUpper,"0X")){
		const std::string sValue = ToolFrame::GetMidString(sSrcUpper,"0X","");
		if (sValue.empty())return false;

		unsigned long uTemp = 0;
		std::stringstream sStream;
		sStream << sValue;
		sStream >>std::hex>>uTemp;
		if (!sStream.eof())return false;
		return ToValue(uTemp,nValue);
	}

	//8����
	if (ToolFrame::IsEndWith(sSrcUpper,"O"))
	{
		const std::string sValue = ToolFrame::GetMidString(sSrcUpper,"","O");
		if (sValue.empty())return false;

		if (ToolFrame::IsBeginWith(sSrcUpper,"-"))
		{
			long uTemp = 0;
			std::stringstream sStream;
			sStream <<sValue;
			sStream >>std::oct>>uTemp;
			if (!sStream.eof())return false;
			return ToValue(uTemp,nValue);
		}else{
			unsigned long uTemp = 0;
			std::stringstream sStream;
			sStream <<sValue;
			sStream >>std::oct>>uTemp;
			if (!sStream.eof())return false;
			return ToValue(uTemp,nValue);
		}
	}

	//2����
	if (ToolFrame::IsEndWith(sSrcUpper,"B"))
	{
		if (ToolFrame::IsBeginWith(sSrcUpper,"-")){
			const std::string sValue = ToolFrame::GetMidString(sSrcUpper,"-","B");
			if (sValue.empty())return false;

			unsigned long uTemp = 0;
			if (!ToValueBin(sValue,uTemp))return false;

			long nTemp = 0;
			if (!ToValue(uTemp,nTemp))return false;
			return 	ToValue(-nTemp,nValue);
		}else{
			const std::string sValue = ToolFrame::GetMidString(sSrcUpper,"","B");
			if (sValue.empty())return false;

			unsigned long uTemp = 0;
			if (!ToValueBin(sValue,uTemp))return false;

			return ToValue(uTemp,nValue);
		}
	}

	//С��
	if (ToolFrame::IsHas(sSrcUpper,"."))
	{
		double f = 0.0;
		std::stringstream sStream;
		sStream << sSrcUpper;
		sStream >>std::dec>>f;
		if (!sStream.eof())return false;

		return ToValue(f,nValue);
	}

	//10����
	{
		if (ToolFrame::IsBeginWith(sSrcUpper,"-"))
		{
			long uTemp = 0;
			std::stringstream sStream;
			sStream << sSrc;
			sStream >> std::dec>> uTemp;
			if (!sStream.eof())return false;
			return ToValue(uTemp,nValue);
		}else
		{
			unsigned long uTemp = 0;
			std::stringstream sStream;
			sStream << sSrc;
			sStream >> std::dec>> uTemp;
			if (!sStream.eof())return false;
			return ToValue(uTemp,nValue);
		}
	}

	//�����û���Ϲ���� ��ô ����ʧ��(����������)
	return false;
}

template<typename T>
bool ToolFrame::ToValueBin( const std::string& sSrc,T& tValue )
{
	if (sSrc.empty())return false;

	size_t nBit = ToolFrame::GetBits(TYPE_ARG(T));
	if (sSrc.length() > nBit)return false;

	tValue = 0;
	size_t uLen = sSrc.length();
	for (size_t uIndex=0;uIndex<uLen;++uIndex)
	{
		tValue <<= 1;
		switch(sSrc.at(uIndex))
		{
		case '1':
			tValue |= 1;
			break;
		case '0':
			break;
		default:
			return false;
		}
	}
	return true;
}

template<typename T,typename K>
uint ToolFrame::GetCount( const std::map<T,uint>& vMap,const K& tK )
{
	typename std::map<T,uint>::const_iterator itr = vMap.find(tK);
	if (itr == vMap.end())return 0;
	return itr->second;
}

template<typename T,typename K>
bool ToolFrame::ReduceCount( std::map<T,uint>& vMap,const K& tK,uint nCount /*= 1*/ )
{
	typename std::map<T,uint>::iterator itr = vMap.find(tK);
	if (itr == vMap.end())return false;

	if (nCount > itr->second)
		return false;

	itr->second -= nCount;
	return true;
}

template<typename T,typename K>
bool ToolFrame::AddCount( std::map<T,uint>& vMap,const K& tK ,uint nCount)
{
	typename std::map<T,uint>::iterator itr = vMap.find(tK);
	if (itr == vMap.end())
	{
		vMap.insert(std::make_pair(tK,nCount));
		return true;
	}
	itr->second += nCount;
	return  true;
}

template <typename Tvalue>
Tvalue* ToolFrame::GetValuePtrByIndex( const std::vector<Tvalue>& vSrc, int nIndex )
{
	if (!IsVaildIndex(vSrc,nIndex))return nullptr;
	return (Tvalue*)&vSrc[nIndex];//���ܻ����
}

template<typename T>
bool ToolFrame::GetValueByKeyString( const MapStringString& vValue,const std::string& sKey,T& tValue )
{
	const std::string* pValue = ToolFrame::GetValuePtrByKey(vValue,sKey);
	if (!pValue)return false;

	return ToolFrame::ToValue(*pValue,tValue);
}

template<typename TFun, typename T>
T ToolFrame::FindPtrByFn(const std::vector<T>& v, TFun fn)
{
	if (v.empty())return T();
	
	typename std::vector<T>::const_iterator itr;
	foreach(itr,v) {
		T t = *itr;
		if (fn(t))
			return t;
	}
	return T();
}

template<typename TFun, typename T>
T* ToolFrame::FindByFn(const std::vector<T>& v, TFun fn)
{
	if (v.empty())return nullptr;

	typename std::vector<T>::const_iterator itr;
	foreach(itr, v) {
		const T* p = &*itr;
		if (fn(p))
			return (T*)p;
	}
	return nullptr;
}

template<typename TFun, typename T, typename TArg>
T ToolFrame::FindPtrByFn(const std::vector<T>& v, const TArg& tArg, TFun fn)
{
	if (v.empty())return T();

	typename std::vector<T>::const_iterator itr;
	foreach(itr, v) {
		T t = *itr;
		if (fn(t, tArg))
			return t;
	}
	return T();
}

template<typename TFun, typename T, typename TArg>
T* ToolFrame::FindByFn(const std::vector<T>& v, const TArg& tArg, TFun fn)
{
	if (v.empty())return nullptr;

	typename std::vector<T>::const_iterator itr;
	foreach(itr, v) {
		const T* p = &*itr;
		if (fn(p, tArg))
			return (T*)p;
	}
	return nullptr;
}

template<typename TFun, typename T>
T ToolFrame::FindPtrByCmpFn(const std::vector<T>& v, TFun fn)
{
	if (v.empty())return T();

	T pMax = *v.begin();
	typename std::vector<T*>::const_iterator itr;
	foreach(itr, v) {
		T pCur = *itr;
		if (fn(pCur, pMax))
			pMax = pCur;
	}

	return pMax;
}

template<typename TFun, typename T>
T* ToolFrame::FindByCmpFn(const std::vector<T>& v, TFun fn)
{
	if (v.empty())return nullptr;

	const T* pMax = &*v.begin();
	typename std::vector<T>::const_iterator itr;
	foreach(itr, v) {
		const T* pCur = &*itr;
		if (fn(pCur, pMax))
			pMax = pCur;
	}

	return (T*)pMax;
}

template<typename TFun, typename T, typename TArg>
bool ToolFrame::Filiter(std::vector<T>& vFilite, const std::vector<T>& vVector, const TArg& tArg, TFun fnFiliter)
{
	if (vVector.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach(itr, vVector) {
		const T& t = *itr;
		if (fnFiliter(t, tArg))
			vFilite.push_back(t);
	}

	return true;
}

template<typename TFun, typename T>
bool ToolFrame::Filiter(std::vector<T>& vFilite, const std::vector<T>& vVector, TFun fnFiliter)
{
	if (vVector.empty())return true;

	typename std::vector<T>::const_iterator itr;
	foreach(itr, vVector) {
		const T& t = *itr;
		if (fnFiliter(t))
			vFilite.push_back(t);
	}

	return true;
}

template<typename TFun, typename T>
bool ToolFrame::EraseByFn(std::vector<T>& vVector, TFun fn)
{
	if (vVector.empty())return false;

	typename std::vector<T>::iterator itr = vVector.begin();
	while (itr != vVector.end())
	{
		if (fn(*itr)) {
			vVector.erase(itr);
			return true;
		}
	}

	return false;
}

template<typename TFun, typename T>
uint ToolFrame::EraseByFnAll(std::vector<T>& vVector, TFun fn)
{
	if (vVector.empty())return 0;

	uint uCount = 0;
	for (size_t uIndex = vVector.size(); uIndex > 0; --uIndex)
	{
		size_t uRealIndex = uIndex - 1;
		if (fn(vVector[uRealIndex])) {
			vVector.erase(vVector.begin() + uRealIndex);
			++uCount;
		}
	}
	return uCount;
}

template<typename T, typename TFn>
bool ToolFrame::EraseByNotFn(std::vector<T>& vVector, TFn fn)
{
	if (vVector.empty())return false;

	typename std::vector<T>::iterator itr = vVector.begin();
	while (itr != vVector.end())
	{
		if (!fn(*itr)) {
			vVector.erase(itr);
			return true;
		}
	}

	return false;
}

template<typename T, typename TFn>
uint ToolFrame::EraseByNotFnAll(std::vector<T>& vVector, TFn fn)
{
	if (vVector.empty())return 0;

	uint uCount = 0;
	for (size_t uIndex = vVector.size(); uIndex > 0; --uIndex)
	{
		size_t uRealIndex = uIndex - 1;
		if (!fn(vVector[uRealIndex])) {
			vVector.erase(vVector.begin() + uRealIndex);
			++uCount;
		}
	}
	return uCount;
}

//���� - ���� - ָ��λ�ò��� ���� �²��� �ĵ�һ��Ԫ�صĵ�����
template<typename T>
typename std::vector<T>::iterator ToolFrame::Insert(std::vector<T>& vSrc, typename std::vector<T>::iterator itr, const std::vector<T>& vVct) {
	return vSrc.insert(itr, vVct.begin(), vVct.end());
}

//���� - ���� - ָ��λ�ò��뷵�� �²��� �ĵ�һ��Ԫ�صĵ�����
template<typename T>
typename std::list<T>::iterator  ToolFrame::Insert(std::list<T>& vSrc, typename std::list<T>::iterator itr, const std::list<T>& vVct) {
	return vSrc.insert(itr, vVct.begin(), vVct.end());
}

//���� - �滻
template<typename T>
typename std::vector<T>::iterator   ToolFrame::Replace(std::vector<T>& vSrc, typename std::vector<T>::iterator itr, const T& t) {
	itr = vSrc.erase(itr);
	return vSrc.insert(itr, t);
}

//���� - �滻
template<typename T>
typename std::vector<T>::iterator   ToolFrame::Replace(std::vector<T>& vSrc, typename std::vector<T>::iterator itr, const std::vector<T>& vVct) {
	itr = vSrc.erase(itr);
	return vSrc.insert(itr, vVct.begin(), vVct.end());
}

//���� - �滻
template<typename T>
typename std::list<T>::iterator   ToolFrame::Replace(std::list<T>& vSrc, typename std::list<T>::iterator itr, const T& t) {
	itr = vSrc.erase(itr);
	return vSrc.insert(itr, t);
}

//���� - �滻
template<typename T>
typename std::list<T>::iterator   ToolFrame::Replace(std::list<T>& vSrc, typename std::list<T>::iterator itr, const std::list<T>& vVct) {
	itr = vSrc.erase(itr);
	return vSrc.insert(itr, vVct.begin(), vVct.end());
}

//���� - ����
template<typename T>
bool ToolFrame::EraseItr(std::list<T>& vSrc, typename std::list<T>::iterator itrBegin, typename std::list<T>::iterator itrEnd) {
	vSrc.erase(itrBegin, itrEnd);
	return true;
}

//���� - ����������
template<typename T>
bool ToolFrame::EraseCloseInterval(std::list<T>& vSrc, typename std::list<T>::iterator itrBegin, typename std::list<T>::iterator itrEnd) {
	if (itrEnd != vSrc.end())
		++itrEnd;
	vSrc.erase(itrBegin, itrEnd);
	return true;
}

//���� - ����������
template<typename T>
bool ToolFrame::EraseOpenInterval(std::list<T>& vSrc, typename std::list<T>::iterator itrBegin, typename std::list<T>::iterator itrEnd) {
	if (itrBegin != itrEnd)
		++itrBegin;
	vSrc.erase(itrBegin, itrEnd);
	return true;
}