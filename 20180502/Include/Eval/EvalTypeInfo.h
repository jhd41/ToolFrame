#pragma once
#include "Macro.h"

#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

typedef boost::function<double(void)>			EvalFunction0;
typedef boost::function<double(double)>			EvalFunction1;
typedef boost::function<double(double,double)>	EvalFunction2;

//实际占用内存的变量类型描述(以类为基本单元,任何基本类型起始都是类,只是默认系统已经为开发者编写完成而已)
class CVarTypeInfo{
public:
	CVarTypeInfo();
	CVarTypeInfo(const std::string& sName,int nLength,bool bBaseType = false);
	CVarTypeInfo(const CVarTypeInfo& infoVar);
	virtual ~CVarTypeInfo();
private:
	CFIELD_STRING(Name);					//类型名称
	CFIELD_INT(Length);						//变量占用空间
	CFIELD_BOOL(BaseType);					//是否是基本类型
};

//引用变量修饰
class CRefTypeInfo{
public:
	bool IsPassByValue()const;							//值传递
	bool IsTypeEqual(const CRefTypeInfo& infoRef)const;	//是否类型一致

	bool GetValue(void* pData)const;
public:
	bool operator == (const CRefTypeInfo& infoRef)const;
public:
	CRefTypeInfo();
	CRefTypeInfo(const CVarTypeInfo* pValueType,const std::string& sName,bool bConst,bool bStatic,bool bPtr,bool bRef);
	CRefTypeInfo(const CVarTypeInfo* pValueType,const std::string& sName,double fValue);
	CRefTypeInfo(const CRefTypeInfo& infoRef);
	virtual ~CRefTypeInfo();
private:
	CFIELD_PTR(const CVarTypeInfo* ,ValueType,p);	//变量类型
	
	CFIELD_STRING(Name);							//实例化变量名

	//修饰词
	CFIELD_BOOL(Const);								//常量
	CFIELD_BOOL(Static);							//静态变量
	CFIELD_BOOL(Ptr);								//是否是指针
	CFIELD_BOOL(Ref);								//是否是引用

	CFIELD_BOOL(Resolve);							//是否是保留的 不对外公开的


	CFIELD_DOUBLE(Value);							//值
};

typedef std::vector<CRefTypeInfo>											VectorRefTypeInfo;

//函数类型信息
class CFunTypeInfo
{
public:
	CFunTypeInfo();
	CFunTypeInfo(const CFunTypeInfo& infoFun);
	virtual ~CFunTypeInfo();
private:
	CFIELD_STRING(Name);					//函数名

	CFIELD_REF(EvalFunction0,Function0,fn);
	CFIELD_REF(EvalFunction1,Function1,fn);
	CFIELD_REF(EvalFunction2,Function2,fn);

	//修饰词
	CFIELD_BOOL(Const);						//常函数
	CFIELD_BOOL(Static);					//静态函数
	CFIELD_BOOL(Virtual);					//虚函数
	CFIELD_BOOL(PureVirtual);				//纯虚函数
};

typedef std::map<std::string,CVarTypeInfo>		MapNameType;	//类型名,变量类型声明
typedef std::map<std::string,CRefTypeInfo>		MapNameVar;		//变量名,变量引用
typedef std::multimap<std::string,CFunTypeInfo>	MapNameFun;		//函数

typedef std::pair<MapNameFun::iterator,         MapNameFun::iterator>		PairItrMapNameFun;
typedef std::pair<MapNameFun::const_iterator,	MapNameFun::const_iterator>	PairConstItrMapNameFun;

//作用域
class CScopeInfo{
	typedef	std::map<std::string,CScopeInfo>	MapNameScope;
public:
	//声明
	bool						DeclareType(const CVarTypeInfo& infoType );	//声明变量类型
	bool						DeclareVar(const CRefTypeInfo& infoRefType);//声明变量
	bool						DeclareFun(const CFunTypeInfo& infoFunType);//声明函数

	//重载
	bool						DeclareVar(const std::string& sTypeName,const std::string& sVarName,double fValue);

	bool						DeclareFun(const std::string& sFunctionName,double(*fn)());
	template<typename T>
	bool						DeclareFun(const std::string& sFunctionName,double(T::*fn)(),T* p);
	
	bool						DeclareFun(const std::string& sFunctionName,double(*fn)(double));
	template<typename T>
	bool						DeclareFun(const std::string& sFunctionName,double(T::*fn)(double),T* p);

	bool						DeclareFun(const std::string& sFunctionName,double(*fn)(double,double));
	template<typename T>
	bool						DeclareFun(const std::string& sFunctionName,double(T::*fn)(double,double),T* p);
	bool						DeclareScope(const std::string& sScopeName);

	bool						UndeclareVar(const std::string& sVarName);
	bool						UndeclareScope(const std::string& sScopeName);

	//获取
	const CVarTypeInfo*			GetType(const std::string& sTypeName)const;		//获取类型
	const CRefTypeInfo*			GetVar(const std::string& sVarName)const;		//获取变量
	CRefTypeInfo*				GetVar(const std::string& sVarName);			//获取变量
	PairItrMapNameFun			GetFun(const std::string& sFunctionName);		//获取函数
	PairConstItrMapNameFun		GetFun(const std::string& sFunctionName)const;	//获取函数
	CScopeInfo*					GetScope(const std::string& sScopeName);

	bool						IsExistVar(const std::string& sVarName)const;

	const MapNameType&			GetType()const;	//类型名称
	const MapNameVar&			GetVar()const;	//变量名称
	const MapNameFun&			GetFun()const;	//函数名称
public:
	CScopeInfo();
	CScopeInfo(const std::string& sName,CScopeInfo* pParent);
	CScopeInfo(const CScopeInfo& infoScope);
	virtual ~CScopeInfo();
private:
	CFIELD_STRING(Name);//作用域名称
	CFIELD_PTR(CScopeInfo*,Parent,p);
private:
	MapNameType		_vType;	//类型
	MapNameVar		_vVar;	//变量
	MapNameFun		_vFun;	//函数
	MapNameScope	_vScope;//作用域
};

template<typename T>
bool CScopeInfo::DeclareFun( const std::string& sFunctionName,double(T::*fn)(double,double),T* p )
{
	CFunTypeInfo info;
	info.SetName(sFunctionName);

	info.SetFunction2(boost::bind(fn,p,_1,_2));

	return DeclareFun(info);
}

template<typename T>
bool CScopeInfo::DeclareFun( const std::string& sFunctionName,double(T::*fn)(),T* p )
{
	CFunTypeInfo info;
	info.SetName(sFunctionName);

	info.SetFunction0(boost::bind(fn,p));

	return DeclareFun(info);
}

template<typename T>
bool CScopeInfo::DeclareFun( const std::string& sFunctionName,double(T::*fn)(double),T* p )
{
	CFunTypeInfo info;
	info.SetName(sFunctionName);

	info.SetFunction1(boost::bind(fn,p,_1));

	return DeclareFun(info);
}

typedef std::vector<CScopeInfo>			VectorScopeInfo;

NS_TOOL_FRAME_END
