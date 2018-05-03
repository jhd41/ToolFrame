#pragma once

#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <set>
#include <map>

#include <time.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <time.h>

#include <stdarg.h>
#include <typeinfo>

//��������
typedef signed char         INT8,	*PINT8;
typedef signed short        INT16,	*PINT16;
typedef signed int          INT32,	*PINT32;
typedef signed long long    INT64,	*PINT64;
typedef unsigned char       UINT8,	*PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned long long  UINT64, *PUINT64;

typedef float			FLOAT32;
typedef double			FLOAT64;

typedef char			CHAR;
typedef short			SHORT;
typedef int				INT;
typedef unsigned char	UCHAR;
typedef unsigned short	USHORT;
typedef unsigned int	UINT,*PUINT;    

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;//typedef signed long			int32;
typedef signed long long	int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;//typedef unsigned long		uint32;
typedef unsigned long long	uint64;

typedef float				float32;
typedef double				float64;

typedef unsigned char		uchar;
typedef unsigned short		ushort;
typedef unsigned int		uint;
typedef unsigned long		ulong;
typedef unsigned long long	ulonglong;

// typedef int				BOOL; //�����Ͷ����ѱ����������ļ���
typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef unsigned long	DWORD;
typedef float			FLOAT,*PFLOAT;
typedef void			*PVOID;

//����Windows
typedef UINT_PTR        SOCKET;
#define INVALID_SOCKET  (SOCKET)(~0)
#define SOCKET_ERROR            (-1)

#define OUT
#define IN

#define CALLBACK    __stdcall
#define FN_CDECL	__cdecl

//��ȡ�� minwindef.h
#ifndef NO_STRICT
#ifndef STRICT
#define STRICT 1
#endif
#endif /* NO_STRICT */

//��ȡ�� winnt.h
#ifdef STRICT
typedef void *HANDLE;
#if 0 && (_MSC_VER > 1000)
#define DECLARE_HANDLE(name) struct name##__; typedef struct name##__ *name
#else
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#endif
#else
typedef PVOID HANDLE;
#define DECLARE_HANDLE(name) typedef HANDLE name
#endif
typedef HANDLE *PHANDLE;

#define MAX_PATH          260

typedef signed char         Int8,	*Int8Ptr;
typedef signed short        Int16,	*Int16Ptr;
typedef signed long         Int32,	*Int32Ptr,Int,*IntPtr;
typedef signed long long    Int64,	*Int64Ptr;
typedef unsigned char       Uint8,	*Uint8Ptr;
typedef unsigned short		Uint16,	*Uint16Ptr;
typedef unsigned long       Uint32,	*Uint32Ptr;
typedef unsigned long long  Uint64,	*Uint64Ptr;
typedef float				Float32,*Float32Ptr;
typedef double				Float64,*Float64Ptr;

typedef std::string::size_type				SSIZE_TYPE;

//����Unicode�ַ���
#if MACRO_TARGET_BIT == MACRO_BIT_32
typedef long			PtrAddress;
#elif  MACRO_TARGET_BIT == MACRO_BIT_64
typedef long long		PtrAddress;
#endif

//�淶:typedef ˳�� char,int,UINT,UINT32,string,vector,list,set,multiset,map,multimap
typedef std::pair<int,int>										PairIntInt;
typedef std::pair<std::string,int>								PairStringInt;

typedef std::vector<bool>										VectorBool;
typedef std::vector<char>										VectorChar;
typedef std::vector<INT>										VectorInt;
typedef std::vector<INT16>										VectorInt8;
typedef std::vector<INT16>										VectorInt16;
typedef std::vector<INT32>										VectorInt32;
typedef std::vector<INT64>										VectorInt64;
typedef std::vector<UINT>										VectorUint;
typedef std::vector<UINT16>										VectorUint8;
typedef std::vector<UINT16>										VectorUint16;
typedef std::vector<UINT32>										VectorUint32;
typedef std::vector<UINT64>										VectorUint64;
typedef std::vector<std::string>								VectorString;
typedef std::vector<time_t>										VectorTime;
typedef std::vector<void*>										VectorVoidPtr;
typedef std::vector<size_t>										VectorSize;
typedef std::vector<std::pair<std::string,int> >				VectorStringInt;
typedef std::stack<std::string>									StackString;
typedef std::list<char>											ListChar;
typedef std::list<int>											ListInt;
typedef std::list<uint>											ListUint;
typedef std::list<std::string>									ListString;
typedef std::list<void*>										ListVoidPtr;
typedef std::set<int>											SetInt;
typedef std::set<uint>											SetUint;
typedef std::set<std::string>									SetString;
typedef std::set<void*>											SetVoidPtr;
typedef std::multiset<int>										MultiSetInt;
typedef std::map<int,void*>										MapIntVoidPtr;
typedef std::map<int,bool>										MapIntBool;
typedef std::map<int,int>										MapIntInt;
typedef std::map<int,uint>										MapIntUint;
typedef std::map<int,std::string>								MapIntString;
typedef std::map<int,std::string*>								MapIntStringPtr;
typedef std::map<int,std::vector<int> >							MapIntVectorInt;
typedef std::map<uint,std::vector<uint> >						MapUintVectorUint;
typedef std::map<int,std::set<int> >							MapIntSetInt;
typedef	std::map<int,time_t>									MapIntTime;
typedef std::map<uint,int>										MapUintInt;
typedef std::map<uint,uint>										MapUintUint;
typedef std::map<uint,std::set<uint> >							MapUintSetUint;
typedef std::map<std::string,int >								MapStringInt;
typedef std::map<std::string,double >							MapStringDouble;
typedef std::map<std::string,std::string>						MapStringString;
typedef std::map<std::string,VectorInt >						MapStringVectorInt;
typedef std::map<std::string,VectorString >						MapStringVectorString;
typedef std::map<std::string,uint>								MapStringUint;
typedef std::map<std::string,size_t>							MapStringSize;
typedef std::map<std::string,PairStringInt >					MapStringPairStringInt;
typedef std::multimap<int,int>									MultimapIntInt;
typedef std::multimap<std::string,int>							MultimapStringInt;
typedef std::multimap<std::string,std::string>					MultimapStringString;
typedef std::multimap<std::string,std::vector<int> >			MultimapStringVectorInt;
typedef std::multimap<std::string,std::vector<std::string> >	MultimapStringVectorString;
typedef std::map<int8,int16>									MapInt8Int16;
typedef std::map<uint16,bool>									MapUint16Bool;
typedef std::map<uint8,uint16>									MapUint8Uint16;
typedef std::map<uint8,uint8>									MapUint8Uint8;
typedef std::map<uint16,uint8>									MapUint16Uint8;
typedef std::map<uint32,uint16>									MapUint32Uint16;

typedef std::queue<std::string>									QueueString;

typedef std::pair<std::string, uint8>							PairStringUint8;
typedef std::pair<std::string, uint16>							PairStringUint16;
typedef std::pair<std::string, uint32>							PairStringUint32;
typedef std::pair<std::string, uint64>							PairStringUint64;
typedef std::pair<std::string, int>								PairStringInt;
typedef std::pair<std::string, uint>							PairStringUint;
typedef std::pair<std::string, std::string>						PairStringString;
//����Unicode�ַ���
#if MACRO_TARGET_FONT == MACRO_FONT_ANSI
	typedef char			TCHAR;
	typedef char			char_t;
	namespace std {typedef std::string				string_t;}
	namespace std { typedef std::stringstream		stringstream_t; }
#elif  MACRO_TARGET_FONT == MACRO_FONT_UNICODE
	typedef wchar_t			TCHAR;
	typedef wchar_t			char_t;
	namespace std {typedef std::wstring				string_t;}
	namespace std { typedef std::wstringstream		stringstream_t; }
#endif

//�����������ö��ֵ
//��������
enum EValueType{
	VALUE_TYPE_INVAILD,

	VALUE_TYPE_BOOL,
	VALUE_TYPE_INT8,	VALUE_TYPE_UINT8,
	VALUE_TYPE_INT16,	VALUE_TYPE_UINT16,
	VALUE_TYPE_INT32,	VALUE_TYPE_UINT32,
	VALUE_TYPE_INT64,	VALUE_TYPE_UINT64,
	VALUE_TYPE_USER_DEF,

	VALUE_TYPE_MAX,
};

//C++Ȩ�޹ؼ��ֶ���
#define	PRIVATE		private
#define	PUBLIC		public
#define PROTECTED	protected
#define VIRTUAL		virtual
#define BLANK					//�հ� 

//���������ռ�
namespace ToolFrame{};
#define NS_TOOL_FRAME_BEGIN	namespace ToolFrame{
#define NS_TOOL_FRAME_END	};
#define USING_NS_TOOL_FRAME using namespace ToolFrame

//���û�������
NS_TOOL_FRAME_BEGIN

//����ָ��
template<typename T>
bool SetPtr(T*& pDes,T* pSrc){
	if (pDes == pSrc)return false;
	pDes = pSrc;
	return true;
}

//����ָ��Ϊ��
template<typename T>
bool SetPtrNull(T*& ptr){
	if (!ptr)return false;
	ptr = nullptr;
	return true;
}

//��ȡ��ǰ���������
template<typename T>
std::string GetTypeName(const T* p)
{
	if (!p)return "";

	const char* pName = typeid(*p).name();
	if (!pName)return "";
	return pName;
}

class CStringMaker
{
public:
	CStringMaker(){_stream<<std::string("")<<std::fixed;}
	virtual ~CStringMaker(){}
private:
	std::stringstream _stream;
public:
	template<typename T>
	inline CStringMaker& operator<<(const T& t){_stream<<t;return *this;}
	inline std::stringstream& GetStream(){return _stream;}
	inline std::string str()const{ return _stream.str();}
};

NS_TOOL_FRAME_END

//�����ֶ�,���ȶ����ֶε���ȫ��ʽ,֮����ݲ�������õ����ֶζ���
//�ֶ�(��������,������,ǰ׺,����Ȩ��,��ȡȨ��,:ʹ�����÷�ʽ)
#define DEFINE_CFIELD_REF(tT,tName,prefix,tPrefixSet,tPrefixGet,tPrefixGetConst) \
								protected:tT  _##prefix##tName;\
								tPrefixSet		bool		Set##tName(const tT& prefix##tName){_##prefix##tName = prefix##tName;return true;}\
								tPrefixGet		tT&			Get##tName(){return _##prefix##tName;}\
								tPrefixGetConst const tT&	Get##tName()const {return _##prefix##tName;}

//�ֶ�(��������,������,ǰ׺:ʹ�ÿ�����ʽ)
#define DEFINE_CFIELD_COPY(tT,tName,prefix,tPrefixSet,tPrefixGet,tPrefixGetConst) \
								protected:tT  _##prefix##tName;\
								tPrefixSet		bool		Set##tName(tT prefix##tName){_##prefix##tName = prefix##tName;return true;}\
								tPrefixGet		tT&			Get##tName(){return _##prefix##tName;}\
								tPrefixGetConst const tT&	Get##tName()const {return _##prefix##tName;}

//�ֶ�(��������,������,ǰ׺:ʹ�����÷�ʽ ��Ҫ֧�� == �Ƚ�)
#define DEFINE_CFIELD_CMP(tT,tName,prefix,tPrefixSet,tPrefixGet,tPrefixGetConst) \
								protected:tT  _##prefix##tName;\
								tPrefixSet		bool		Set##tName(const tT& prefix##tName){if (_##prefix##tName == prefix##tName)return false; _##prefix##tName = prefix##tName;return true;}\
								tPrefixGet		tT&			Get##tName(){return _##prefix##tName;}\
								tPrefixGetConst const tT&	Get##tName()const {return _##prefix##tName;}

//�ֶ�(��������,������,ǰ׺:ʹ�ÿ�����ʽ  ��Ҫ֧�� == �Ƚ�)
#define DEFINE_CFIELD_COPY_CMP(tT,tName,prefix,tPrefixSet,tPrefixGet,tPrefixGetConst) \
								protected:tT  _##prefix##tName;\
								tPrefixSet		bool		Set##tName(tT prefix##tName){if (_##prefix##tName == prefix##tName)return false; _##prefix##tName = prefix##tName;return true;}\
								tPrefixGet		tT&			Get##tName(){return _##prefix##tName;}\
								tPrefixGetConst const tT&	Get##tName()const {return _##prefix##tName;}

//�ֶ�(��������,������,ǰ׺:ָ������)
#define DEFINE_CFIELD_PTR(tT,tName,prefix,tPrefixSet,tPrefixGet,tPrefixGetConst) \
								protected : tT  _##prefix##tName;\
								tPrefixSet		bool		Set##tName(tT prefix##tName){return ToolFrame::SetPtr(_##prefix##tName,prefix##tName);}\
								tPrefixGet		tT&			Get##tName(){return _##prefix##tName;}\
								tPrefixGetConst tT   		Get##tName()const {return _##prefix##tName;}\
								tPrefixSet		bool		Set##tName##Null(){	return ToolFrame::SetPtrNull(_##prefix##tName);}

//�ֶ�(��������,������,ǰ׺:Bool����)
#define DEFINE_CFIELD_BOOL(tName,tPrefixSet,tPrefixGet,tPrefixGetConst) \
								protected:bool  _b##tName;\
								tPrefixSet		bool		Set##tName(bool b##tName){if (_b##tName == b##tName)return false; _b##tName = b##tName;return true;}\
								tPrefixGet		bool&		Is##tName(){return _b##tName;}\
								tPrefixGetConst	const bool&	Is##tName()const{return _b##tName;}
//ö��					
#define DEFINE_CFIELD_ENUM(tT,tName,prefix,tPrefixSet,tPrefixGet,tPrefixGetConst) \
								protected:tT  _##prefix##tName;\
								tPrefixSet		bool		Set##tName(const int& prefix##tName){if (_##prefix##tName == prefix##tName)return false; _##prefix##tName = (const tT&)prefix##tName;return true;}\
								tPrefixSet		bool		Set##tName(tT prefix##tName){if (_##prefix##tName == prefix##tName)return false; _##prefix##tName = prefix##tName;return true;}\
								tPrefixGet		tT&			Get##tName(){return _##prefix##tName;}\
								tPrefixGetConst const tT&	Get##tName()const {return _##prefix##tName;}


//ͨ���ֶ�(Ĭ��:public virtual)
#define CFIELD_REF(tType,tName,prefix)		DEFINE_CFIELD_REF		(tType,tName,prefix,	public: virtual ,public: virtual ,public: virtual )
#define CFIELD_COPY(tType,tName,prefix)		DEFINE_CFIELD_COPY		(tType,tName,prefix,	public: virtual ,public: virtual ,public: virtual ) 
#define CFIELD_CMP(tType,tName,prefix)		DEFINE_CFIELD_CMP		(tType,tName,prefix,	public: virtual ,public: virtual ,public: virtual ) 
#define CFIELD_COPY_CMP(tType,tName,prefix)	DEFINE_CFIELD_COPY_CMP	(tType,tName,prefix,	public: virtual ,public: virtual ,public: virtual ) 
#define CFIELD_PTR(tType,tName,prefix)		DEFINE_CFIELD_PTR		(tType,tName,prefix,	public: virtual ,public: virtual ,public: virtual )
#define CFIELD_BOOL(tName)					DEFINE_CFIELD_BOOL		(tName,					public: virtual ,public: virtual ,public: virtual ) 
#define CFIELD_ENUM(tType,tName)			DEFINE_CFIELD_ENUM		(tType,tName,e,			public: virtual ,public: virtual ,public: virtual )
#define CFIELD_FUNCTION(tType,tName)		DEFINE_CFIELD_PTR		(tType,tName,fn,		public: virtual ,public: virtual ,public: virtual )				

//ͨ��д��
//��CFIELD_REF��������ΪCFIELD ������д
#define CFIELD(tType,tName,tPrefix)					CFIELD_REF(tType,tName,tPrefix);
#define CFIELD_VECTOR(tName,tType)					CFIELD_REF(std::vector<tType>,	tName,v);
#define CFIELD_LIST(tName,tType)					CFIELD_REF(std::list<tType>,	tName,v);
#define CFIELD_SET(tName,tType)						CFIELD_REF(std::set<tType>,		tName,v);
#define CFIELD_MAP(tName,tKey,tValue,tMapName)		public:	typedef std::map<tKey,tValue>		tMapName;CFIELD_REF(tMapName,tName,v);
#define CFIELD_MULTIMAP(tName,tKey,tValue,tMapName)	public:	typedef std::multimap<tKey,tValue>	tMapName;CFIELD_REF(tMapName,tName,v);

//�Գ�������֧��
#define CFIELD_INT(tName)					CFIELD_COPY_CMP(int,tName,n);
#define CFIELD_UINT(tName)					CFIELD_COPY_CMP(uint,tName,u);

#define CFIELD_LONG(tName)					CFIELD_COPY_CMP(long,tName,n);
#define CFIELD_ULONG(tName)					CFIELD_COPY_CMP(ulong,tName,u);

#define CFIELD_FLOAT(tName)					CFIELD_COPY_CMP(float,tName,f);
#define CFIELD_DOUBLE(tName)				CFIELD_COPY_CMP(double,tName,f);

#define CFIELD_INT8(tName)					CFIELD_COPY_CMP(INT8,tName,n);
#define CFIELD_UINT8(tName)					CFIELD_COPY_CMP(UINT8,tName,u);

#define CFIELD_INT16(tName)					CFIELD_COPY_CMP(INT16,tName,n);
#define CFIELD_UINT16(tName)				CFIELD_COPY_CMP(UINT16,tName,u);

#define CFIELD_INT32(tName)					CFIELD_COPY_CMP(INT32,tName,n);
#define CFIELD_UINT32(tName)				CFIELD_COPY_CMP(UINT32,tName,u);

#define CFIELD_INT64(tName)					CFIELD_COPY_CMP(INT64,tName,n);
#define CFIELD_UINT64(tName)				CFIELD_COPY_CMP(UINT64,tName,u);

#define CFIELD_SIZE(tName)					CFIELD_COPY_CMP(size_t,tName,u);
#define CFIELD_STRING(tName)				CFIELD_CMP(std::string,tName,s);
#define CFIELD_TIME(tName)					CFIELD_COPY_CMP(time_t,tName,u);
#define CFIELD_FUNC(tName)					CFIELD_COPY_CMP(tName,tName,fn);

#define CFIELD_VECTOR_INT(tName)			CFIELD_REF(VectorInt,tName,v);
#define CFIELD_VECTOR_STRING(tName)			CFIELD_REF(VectorString,tName,v);
#define CFIELD_SET_INT(tName)				CFIELD_REF(SetInt,tName,v);
#define CFIELD_SET_STRING(tName)			CFIELD_REF(SetString,tName,v);

//�����ֶ�(���ڱ�д �������� ʱ��ʹ��)
#define COPY_CFIELD_BOOL(tName,tSrc)	Set##tName((tSrc).Is##tName())
#define COPY_CFIELD_REF(tName,tSrc)		Set##tName((tSrc).Get##tName())

//�Ƚ��ֶ�(���ڱ�д �ȽϺ��� ʱ��ʹ��)
#define CMP_CFIELD_BOOL(tName,tSrc)		Is##tName() == (tSrc).Is##tName()
#define CMP_CFIELD_REF(tName,tSrc)		Get##tName() == (tSrc).Get##tName()

//�Ƚ��ֶ�(���ڱ�д �ȽϺ��� ʱ��ʹ��)
#define CMP_CFIELD_BOOL_RETURN(tName,tSrc,tReturn)	if(!(CMP_CFIELD_BOOL(tName,tSrc)))	return tReturn;
#define CMP_CFIELD_REF_RETURN(tName,tSrc,tReturn)	if(!(CMP_CFIELD_REF(tName,tSrc)))	return tReturn;

//�Ƚ��ֶ�(���ڱ�д �ȽϺ��� ʱ��ʹ��)
#define CMP_CFIELD_BOOL_RETURN_FALSE(tName,tSrc)	CMP_CFIELD_BOOL_RETURN(tName,tSrc,false);
#define CMP_CFIELD_REF_RETURN_FALSE(tName,tSrc)		CMP_CFIELD_REF_RETURN(tName,tSrc,false);

//�Ƚ��ֶ�(���ڱ�д �ȽϺ��� ʱ��ʹ��)
#define CMP_CFIELD_BOOL_RETURN_TRUE(tName,tSrc)		CMP_CFIELD_BOOL_RETURN(tName,tSrc,true);
#define CMP_CFIELD_REF_RETURN_TRUE(tName,tSrc)		CMP_CFIELD_REF_RETURN(tName,tSrc,true);


//֧��ָ�����͵ıȽ�
#define FUN_PTR_CMP(className)  	bool operator() (const className* const  tSrc,const className* const tDes) const\
{  \
	return   *tSrc < *tDes;  \
}  

//����(����)	��ע:����Manager���Ѿ�����(�����ڴ�й¶,��д�鷳),ȫ�����ô˼�д������д���� ��ȫ�ɿ�,Ҳû�ڴ�й¶
#define ST_INTANCE(cName)			public:\
									static cName& Singleton(){static cName mgr; return mgr;};

#define IS_EQUAL(eExp1,eExp2)	if (eExp1 != eExp2) return false
#define UNIT_SIZE(tT,tName)		sizeof(tName) / sizeof(tT)

//ǿ������ת��������������
#define DECLARE_CAST(tT,tArgName,tArgSrc) tT tArgName = (tT)tArgSrc;

//��̬����ת��������������(��Ҫ��RTTI)
#define DECLARE_CAST_DYNAMIC_STD(tT,tArgName,tArgSrc) tT tArgName = dynamic_cast<tT>(tArgSrc);
//��̬����ת��������������
#define DECLARE_CAST_STATIC_STD(tT,tArgName,tArgSrc) tT tArgName = static_cast<tT>(tArgSrc);

//��ʼ�������(�������������벻�ܺ����麯��)
#define ZERO_CLASS(className) public: className(){memset(this,0,sizeof(className));}

//��������
#define CREATE_CLASS(className) public:static className* Create(){return new className();}

//���Ͳ���
#define TYPE_ARG(type) *(type*)nullptr

//���ɱ�����(��ͨ����)
#define NO_COPY(T)			private:\
										T&	operator =(const T& t){return *this;}\
										T(const T& t){}
//���ɱ�����(�麯��)
#define NO_COPY_VIRTUAL(T)	private:\
										virtual T&	operator =(const T& t){return *this;}\
										T(const T& t){}
//֧��Foreachѭ��
#define SUPPORT_FOREACH(VectorObj,vObj)							\
public:\
	typedef typename VectorObj::iterator		iterator;		\
	typedef typename VectorObj::const_iterator	const_iterator;	\
public:															\
	iterator begin(){return vObj.begin();}						\
	iterator end(){return vObj.end();}							\
	const_iterator begin()const{return vObj.begin();}			\
	const_iterator end()const{return vObj.end();}
	
//������ʹ�õ�(Ϊ����������)
#define USED_PARAM(T)		(void)T

//����ָ��ת������
#define DEFINE_TO_PTR_FUNC(fnName)			\
	template<typename T>				\
	T*			fnName() {				\
		return dynamic_cast<T*>(this);	\
	}									\
	template<typename T>				\
	const T*	fnName()const {			\
		return dynamic_cast<T*>(this);	\
	}

//����ָ��ת������
#define DEFINE_TO_PTR()	DEFINE_TO_PTR_FUNC(ToPtr)

//�����ܹؼ���
#define foreach(itr,vct)					for(itr=(vct).begin();itr != (vct).end(); ++itr)
#define foreachR(itr,vct)					for(itr=(vct).rbegin();itr != (vct).rend(); ++itr)
#define foreachDouble(itr1,vct1,itr2,vct2)	for(itr1=(vct1).begin(),itr2=(vct2).begin();itr1 != (vct1).end() && itr2 != (vct2).end(); ++itr1,++itr2)
#define foreachDoubleR(itr1,vct1,itr2,vct2)	for(itr1=(vct1).rbegin(),itr2=(vct2).rbegin();itr1 != (vct1).rend() && itr2 != (vct2).rend(); ++itr1,++itr2)
#define foreachPair(itr,pair)				for (itr = pair.first;itr != pair.second ;++itr)
#define foreachNext(itr,vct)				for(;itr != (vct).end(); ++itr)
#define foreachReverse(itr,vct)				for (itr = vct.end();itr != vct.begin() ? --itr,true:false;)

//���峣��
enum{
	MACRO_INT_MAX	= ~(1<<(sizeof(INT)*8-1)),
	MACRO_INT_MIN	= 1<<(sizeof(INT)*8-1),
	MACRO_UINT_MAX	= ~0,
	MACRO_UINT_MIN	= 0,
};

#define MACRO_BOOL_MAX	  1 
#define MACRO_BOOL_MIN	  0 

#define MACRO_INT8_MAX	  127 
#define MACRO_INT8_MIN	  -128 
#define MACRO_UINT8_MAX	  0xff 
#define MACRO_UINT8_MIN	  0 

#define MACRO_INT16_MAX	  32767 
#define MACRO_INT16_MIN	  -32768 
#define MACRO_UINT16_MAX  0xffff 
#define MACRO_UINT16_MIN  0 

#define MACRO_INT32_MAX	  2147483647 
#define MACRO_INT32_MIN	  1<<(sizeof(INT32)*8-1)
#define MACRO_UINT32_MAX  0xffffffff 
#define MACRO_UINT32_MIN  0 

// 	MACRO_INT64_MAX	= ~(1<<(sizeof(INT64)*8-1)),
// 	MACRO_INT64_MIN	= 1<<(sizeof(INT64)*8-1),
// 	MACRO_UINT64_MAX= 0xffffffffffffffff,
// 	MACRO_UINT64_MIN= 0,

//���� ����ID
enum{
	INVALID_ID		= 0,			//��Ч��ID
	ERR_CODE_SUCCEED= 1,			//�ɹ�
	MAX_LIMIT_ID= MACRO_UINT_MAX,	//ID���ֵ
};

//��������
enum{
	LANGUAGE_INVALID = 0,
	LANGUAGE_ENGLISH,		//Ӣ��
	LANGUAGE_CHINESE,		//����
	LANGUAGE_FRENCH,		//����
	LANGUAGE_ITALIAN,		//�������
	LANGUAGE_GERMAN,		//����
	LANGUAGE_SPANISH,		//��������
	LANGUAGE_RUSSIAN,		//����
	LANGUAGE_MAX
};

//����
enum ENumberSystem{
	NUMBER_SYSTEM_INVALID = 0,
	NUMBER_SYSTEM_2,	//������
	NUMBER_SYSTEM_8,	//�˽���
	NUMBER_SYSTEM_10,	//ʮ����
	NUMBER_SYSTEM_16,	//ʮ������

	NUMBER_SYSTEM_FLOAT,//С����
	NUMBER_SYSTEM_MAX,
};

//Ŀ¼����
enum EDirType{
	DIR_TYPE_INVALID,

	DIR_TYPE_WORKING,		//����Ŀ¼(��һ����д)ע:Ϊ��ͳһ����,��Ŀ¼����д
	DIR_TYPE_WRITEABLE,		//��дĿ¼(��һ���͹���Ŀ¼ΪͬĿ¼)
	DIR_TYPE_CACHE,			//����Ŀ¼
	DIR_TYPE_PATCH,			//����Ŀ¼
	DIR_TYPE_ARCHIVE,		//�浵Ŀ¼

	DIR_TYPE_EXT_WORKING,	//��չ����Ŀ¼(��һ����д)ע:Ϊ��ͳһ����,��Ŀ¼����д
	DIR_TYPE_EXT_WRITEABLE,	//��չ��дĿ¼(��һ���͹���Ŀ¼ΪͬĿ¼)
	DIR_TYPE_EXT_CACHE,		//��չ����Ŀ¼
	DIR_TYPE_EXT_PATCH,		//��չ����Ŀ¼
	DIR_TYPE_EXT_ARCHIVE,	//��չ�浵Ŀ¼

	DIR_TYPE_EXT_ROOT,		//��չ��Ŀ¼

	DIR_TYPE_USER_DEINFE,	//�û��Զ���Ŀ¼

	DIR_TYPE_MAX,
};

//Ԥ�����:
#define  MACRO_FILE __FILE__	//��Դ�����в��뵱ǰԴ�����к�
#define  MACRO_LINE __LINE__	//��Դ�����в��뵱ǰԴ�����ļ���
#define  MACRO_FUN	__FUNCTION__//��Դ�����в��뵱ǰԴ���뺯��
#define  MACRO_DATE	__DATE__	//��Դ�����в��뵱ǰ�������ڡ�ע��͵�ǰϵͳ������������
#define  MACRO_TIME	__TIME__	//��Դ�����в��뵱ǰ����ʱ�䡲ע��͵�ǰϵͳʱ����������
//__PRETTY_FUNCTION__

#define FUN_FILE_LINE		" ;FUN_FILE_LINE:"<<__FUNCTION__<<"(); File:"<<__FILE__<<" Line:"<<__LINE__
#define FUN_FILE_LINE_CLASS	FUN_FILE_LINE<< " Class:" << ToolFrame::GetTypeName(this) << " "

//StdPatch
inline std::stringstream& operator << (std::stringstream& sStream1,const std::stringstream& sStream2){
	sStream1<<sStream2.str();
	return sStream1;
}
inline std::stringstream& operator >> (const std::stringstream& sStream1,std::stringstream& sStream2){
	sStream2<<sStream1.str();
	return sStream2;
}

//�����������ΪC�淶 extern "C"{ //code }
#if MACRO_TARGET_CODE != MACRO_CODE_STD_C
#define MACRO_EXTERN_C_BEGIN	extern "C"{
#define MACRO_EXTERN_C_END		}
#else
#define MACRO_EXTERN_C_BEGIN	
#define MACRO_EXTERN_C_END		
#endif

//�ַ�����������
#define MAKE_STRING(msg)	(ToolFrame::CStringMaker()<<msg).GetStream().str()
