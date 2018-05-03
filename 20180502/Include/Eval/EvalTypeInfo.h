#pragma once
#include "Macro.h"

#include "MacroDefineBoost.h"

NS_TOOL_FRAME_BEGIN

typedef boost::function<double(void)>			EvalFunction0;
typedef boost::function<double(double)>			EvalFunction1;
typedef boost::function<double(double,double)>	EvalFunction2;

//ʵ��ռ���ڴ�ı�����������(����Ϊ������Ԫ,�κλ���������ʼ������,ֻ��Ĭ��ϵͳ�Ѿ�Ϊ�����߱�д��ɶ���)
class CVarTypeInfo{
public:
	CVarTypeInfo();
	CVarTypeInfo(const std::string& sName,int nLength,bool bBaseType = false);
	CVarTypeInfo(const CVarTypeInfo& infoVar);
	virtual ~CVarTypeInfo();
private:
	CFIELD_STRING(Name);					//��������
	CFIELD_INT(Length);						//����ռ�ÿռ�
	CFIELD_BOOL(BaseType);					//�Ƿ��ǻ�������
};

//���ñ�������
class CRefTypeInfo{
public:
	bool IsPassByValue()const;							//ֵ����
	bool IsTypeEqual(const CRefTypeInfo& infoRef)const;	//�Ƿ�����һ��

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
	CFIELD_PTR(const CVarTypeInfo* ,ValueType,p);	//��������
	
	CFIELD_STRING(Name);							//ʵ����������

	//���δ�
	CFIELD_BOOL(Const);								//����
	CFIELD_BOOL(Static);							//��̬����
	CFIELD_BOOL(Ptr);								//�Ƿ���ָ��
	CFIELD_BOOL(Ref);								//�Ƿ�������

	CFIELD_BOOL(Resolve);							//�Ƿ��Ǳ����� �����⹫����


	CFIELD_DOUBLE(Value);							//ֵ
};

typedef std::vector<CRefTypeInfo>											VectorRefTypeInfo;

//����������Ϣ
class CFunTypeInfo
{
public:
	CFunTypeInfo();
	CFunTypeInfo(const CFunTypeInfo& infoFun);
	virtual ~CFunTypeInfo();
private:
	CFIELD_STRING(Name);					//������

	CFIELD_REF(EvalFunction0,Function0,fn);
	CFIELD_REF(EvalFunction1,Function1,fn);
	CFIELD_REF(EvalFunction2,Function2,fn);

	//���δ�
	CFIELD_BOOL(Const);						//������
	CFIELD_BOOL(Static);					//��̬����
	CFIELD_BOOL(Virtual);					//�麯��
	CFIELD_BOOL(PureVirtual);				//���麯��
};

typedef std::map<std::string,CVarTypeInfo>		MapNameType;	//������,������������
typedef std::map<std::string,CRefTypeInfo>		MapNameVar;		//������,��������
typedef std::multimap<std::string,CFunTypeInfo>	MapNameFun;		//����

typedef std::pair<MapNameFun::iterator,         MapNameFun::iterator>		PairItrMapNameFun;
typedef std::pair<MapNameFun::const_iterator,	MapNameFun::const_iterator>	PairConstItrMapNameFun;

//������
class CScopeInfo{
	typedef	std::map<std::string,CScopeInfo>	MapNameScope;
public:
	//����
	bool						DeclareType(const CVarTypeInfo& infoType );	//������������
	bool						DeclareVar(const CRefTypeInfo& infoRefType);//��������
	bool						DeclareFun(const CFunTypeInfo& infoFunType);//��������

	//����
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

	//��ȡ
	const CVarTypeInfo*			GetType(const std::string& sTypeName)const;		//��ȡ����
	const CRefTypeInfo*			GetVar(const std::string& sVarName)const;		//��ȡ����
	CRefTypeInfo*				GetVar(const std::string& sVarName);			//��ȡ����
	PairItrMapNameFun			GetFun(const std::string& sFunctionName);		//��ȡ����
	PairConstItrMapNameFun		GetFun(const std::string& sFunctionName)const;	//��ȡ����
	CScopeInfo*					GetScope(const std::string& sScopeName);

	bool						IsExistVar(const std::string& sVarName)const;

	const MapNameType&			GetType()const;	//��������
	const MapNameVar&			GetVar()const;	//��������
	const MapNameFun&			GetFun()const;	//��������
public:
	CScopeInfo();
	CScopeInfo(const std::string& sName,CScopeInfo* pParent);
	CScopeInfo(const CScopeInfo& infoScope);
	virtual ~CScopeInfo();
private:
	CFIELD_STRING(Name);//����������
	CFIELD_PTR(CScopeInfo*,Parent,p);
private:
	MapNameType		_vType;	//����
	MapNameVar		_vVar;	//����
	MapNameFun		_vFun;	//����
	MapNameScope	_vScope;//������
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
