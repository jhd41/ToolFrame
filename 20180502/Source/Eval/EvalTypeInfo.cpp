#include "EvalTypeInfo.h"
#include "ToolFrame.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

//引用变量修饰
//////////////////////////////////////////////////////////////////////////
CRefTypeInfo::CRefTypeInfo()
{
	SetValueType(nullptr);

	SetConst(false);
	SetStatic(false);
	SetPtr(false);
	SetRef(false);
	SetResolve(false);

	SetValue(0);
}

CRefTypeInfo::CRefTypeInfo( const CRefTypeInfo& infoRef )
{
	ASSERT_LOG_ERROR(infoRef.GetValueType());

	COPY_CFIELD_REF(ValueType,infoRef);
	COPY_CFIELD_REF(Name,infoRef);

	COPY_CFIELD_BOOL(Const,infoRef);
	COPY_CFIELD_BOOL(Static,infoRef);
	COPY_CFIELD_BOOL(Ptr,infoRef);
	COPY_CFIELD_BOOL(Ref,infoRef); 

	COPY_CFIELD_BOOL(Resolve,infoRef); 

	COPY_CFIELD_REF(Value,infoRef);
}

CRefTypeInfo::CRefTypeInfo( const CVarTypeInfo* pValueType,const std::string& sName,bool bConst,bool bStatic,bool bPtr,bool bRef )
{
	ASSERT_LOG_ERROR(pValueType);

	SetValueType(pValueType);
	SetName(sName);

	SetConst(bConst);
	SetStatic(bStatic);
	SetPtr(bPtr);
	SetRef(bRef);
	SetResolve(false);

	SetValue(0);
}

CRefTypeInfo::CRefTypeInfo( const CVarTypeInfo* pValueType,const std::string& sName,double fValue )
{
	ASSERT_LOG_ERROR(pValueType);

	SetValueType(pValueType);
	SetName(sName);


	SetConst(false);
	SetStatic(false);
	SetPtr(false);
	SetRef(false);

	SetResolve(false);

	SetValue(fValue);
}

CRefTypeInfo::~CRefTypeInfo()
{

}

bool CRefTypeInfo::IsPassByValue()const
{
	return !IsRef() && !IsPtr();
}

bool CRefTypeInfo::IsTypeEqual( const CRefTypeInfo& infoRef ) const
{
	CMP_CFIELD_REF_RETURN_FALSE(ValueType,infoRef);

	CMP_CFIELD_BOOL_RETURN_FALSE(Const,infoRef);
	CMP_CFIELD_BOOL_RETURN_FALSE(Static,infoRef);
	CMP_CFIELD_BOOL_RETURN_FALSE(Ptr,infoRef);
	CMP_CFIELD_BOOL_RETURN_FALSE(Ref,infoRef);

	return true;
}

bool CRefTypeInfo::operator==( const CRefTypeInfo& infoRef ) const
{
	return IsTypeEqual(infoRef);
}

//作用域
//////////////////////////////////////////////////////////////////////////
CScopeInfo::CScopeInfo()
{
	SetParent(nullptr);

	static const CVarTypeInfo varType("double",sizeof(double),true);

	ASSERT_LOG_ERROR(DeclareType(varType));
}

CScopeInfo::CScopeInfo( const CScopeInfo& infoScope )
{
	COPY_CFIELD_REF(Name,infoScope);
	SetParent(infoScope.GetParent());
}

CScopeInfo::CScopeInfo( const std::string& sName,CScopeInfo* pParent )
{
	ASSERT_LOG_ERROR(pParent);

	SetName(sName);
	SetParent(pParent);

	static const CVarTypeInfo varType("double",sizeof(double),true);

	ASSERT_LOG_ERROR(DeclareType(varType));
}

CScopeInfo::~CScopeInfo()
{

}

bool CScopeInfo::DeclareType( const CVarTypeInfo& infoType )
{
	if (ToolFrame::IsHasKey(_vType,infoType.GetName()))
		return false;

	ASSERT_LOG_ERROR(ToolFrame::Insert(_vType,infoType.GetName(),infoType));
	return true;
}

bool CScopeInfo::DeclareVar( const CRefTypeInfo& infoRefType )
{
	if (IsExistVar(infoRefType.GetName()))return false;

	ASSERT_LOG_ERROR(ToolFrame::Insert(_vVar,infoRefType.GetName(),infoRefType));
	return true;
}

bool CScopeInfo::DeclareVar( const std::string& sTypeName,const std::string& sVarName,double fValue )
{
	const CVarTypeInfo*  pTypeInfo = GetType(sTypeName);
	if (!pTypeInfo)return false;

	return DeclareVar(CRefTypeInfo(pTypeInfo,sVarName,fValue));
}

const CVarTypeInfo* CScopeInfo::GetType( const std::string& sTypeName )const
{
	return ToolFrame::GetValuePtrByKey(_vType,sTypeName);
}

const CRefTypeInfo* CScopeInfo::GetVar( const std::string& sVarName )const 
{
	return ToolFrame::ConstCast(this)->GetVar(sVarName);
}

CRefTypeInfo* CScopeInfo::GetVar( const std::string& sVarName )
{
	return ToolFrame::GetValuePtrByKey(_vVar,sVarName);
}

const MapNameType& CScopeInfo::GetType() const
{
	return _vType;
}

const MapNameVar& CScopeInfo::GetVar() const
{
	return _vVar;
}

bool CScopeInfo::IsExistVar( const std::string& sVarName)const
{
	return ToolFrame::IsHasKey(_vVar,sVarName);
}

bool CScopeInfo::DeclareFun( const CFunTypeInfo& infoFunType )
{	
	//缺少是否有同名 同 类型 函数的判断。
	return ToolFrame::Insert(_vFun,infoFunType.GetName(),infoFunType);
}

bool CScopeInfo::DeclareFun( const std::string& sFunctionName,double(*fn)(double) )
{
	CFunTypeInfo info;
	info.SetName(sFunctionName);

	info.SetFunction1(boost::bind(fn,_1));

	return DeclareFun(info);
}

bool CScopeInfo::DeclareFun( const std::string& sFunctionName,double(*fn)() )
{
	CFunTypeInfo info;
	info.SetName(sFunctionName);

	info.SetFunction0(boost::bind(fn));

	return DeclareFun(info);
}

bool CScopeInfo::DeclareFun( const std::string& sFunctionName,double(*fn)(double,double) )
{
	CFunTypeInfo info;
	info.SetName(sFunctionName);

	info.SetFunction2(boost::bind(fn,_1,_2));

	return DeclareFun(info);
}

const MapNameFun& CScopeInfo::GetFun() const
{
	return _vFun;
}

PairItrMapNameFun CScopeInfo::GetFun( const std::string& sFunctionName )
{
	return _vFun.equal_range(sFunctionName);
}

PairConstItrMapNameFun CScopeInfo::GetFun( const std::string& sFunctionName ) const
{
	return _vFun.equal_range(sFunctionName);
}

bool CScopeInfo::UndeclareVar( const std::string& sVarName )
{
	return 1 == ToolFrame::EraseByKey(_vVar,sVarName);
}

CScopeInfo* CScopeInfo::GetScope( const std::string& sScopeName )
{
	ASSERT_LOG_ERROR(!sScopeName.empty());
	return ToolFrame::GetValuePtrByKey(_vScope,sScopeName);
}

bool CScopeInfo::DeclareScope( const std::string& sScopeName )
{
	ASSERT_LOG_ERROR(!sScopeName.empty());
	if (ToolFrame::IsHasKey(_vScope,sScopeName))return false;
	
	CScopeInfo& scope = ToolFrame::GetValueByKeyForce(_vScope,sScopeName);
	scope.SetName(sScopeName);
	scope.SetParent(this);
	return true;
}

bool CScopeInfo::UndeclareScope( const std::string& sScopeName )
{
	ASSERT_LOG_ERROR(!sScopeName.empty());

	return 1 == ToolFrame::EraseByKey(_vScope,sScopeName);
}

//变量类型描述
//////////////////////////////////////////////////////////////////////////
CVarTypeInfo::CVarTypeInfo()
{

}

CVarTypeInfo::CVarTypeInfo( const CVarTypeInfo& infoVar )
{
	COPY_CFIELD_REF(Name,infoVar);
	COPY_CFIELD_REF(Length,infoVar);
	COPY_CFIELD_BOOL(BaseType,infoVar);
}

CVarTypeInfo::CVarTypeInfo(const std::string& sName,int nLength,bool bBaseType /*= false*/ )
{
	SetName(sName);
	SetLength(nLength);
	SetBaseType(bBaseType);
}

CVarTypeInfo::~CVarTypeInfo()
{

}

// 函数类型信息
// ////////////////////////////////////////////////////////////////////////
CFunTypeInfo::CFunTypeInfo()
{
	SetFunction0(NULL);
	SetFunction1(NULL);
	SetFunction2(NULL);

	SetConst(false);
	SetStatic(false);
	SetVirtual(false);
	SetPureVirtual(false);
}

CFunTypeInfo::CFunTypeInfo( const CFunTypeInfo& infoFun )
{
	COPY_CFIELD_REF(Name,infoFun);

	COPY_CFIELD_REF(Function0,infoFun);
	COPY_CFIELD_REF(Function1,infoFun);
	COPY_CFIELD_REF(Function2,infoFun);

	COPY_CFIELD_BOOL(Const,infoFun);
	COPY_CFIELD_BOOL(Static,infoFun);
	COPY_CFIELD_BOOL(Virtual,infoFun);
	COPY_CFIELD_BOOL(PureVirtual,infoFun);
}

CFunTypeInfo::~CFunTypeInfo()
{

}

NS_TOOL_FRAME_END