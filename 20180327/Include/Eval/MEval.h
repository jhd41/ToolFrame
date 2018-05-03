#pragma once
#include "Macro.h"
#include "EvalNode.h"
#include "IEvalParser.h"
#include "EvalTypeInfo.h"

NS_TOOL_FRAME_BEGIN

class MEval
{
	ST_INTANCE(MEval);
public:
	const MapIntInt&				GetPriorityAssociativity()const;
	const MapEvalOperationConfig&	GetOperationConfig() const;
	
	bool							RegistPrecedenceAssociativity(int nPriority,EAssociativity eAssociativity);
	bool							RegistOperationConfig( EOperation eOperation,int nPrecedence,EAryOperation eAryOperation,const std::string& sDescription,const std::string& sExample,bool bOverLoading );

//	bool							CreateParser(CEval* pEval);
public:
	static  int						GetPrecedenceMin();
	static  int						GetPrecedenceMax();
public:
	static	double					Add_double	(double fSrc1,	double fSrc2);
	static	long					Add_long	(long nSrc1,	long nSrc2);
public:
	MEval(void);
	virtual ~MEval(void);
private:
	MapIntInt				_vPrecedenceAssociativity;		//优先级 结合方式
	MapEvalOperationConfig	_vOperationConfig;				//操作符配置
};

// 1: ?0: 构造器，?1 析构器
// 2:     @@QAE: public __thiscall
// @@AAE: private __thiscall
// @@QBE: public __thiscall const 
// 3: 返回值和参数类型
// B：const
// D：char
// E：unsigned char
// F：short
// G：unsigned short
// H：int
// I：unsigned int
// J：long
// K：unsigned long
// M：float
// N：double
// _N：bool
// PA：指针（*，后面的代号表明指针类型，如果相同类型的指针连续出现，以0代替，一个0代表一次重复）
// PB：const指针
// AA：引用（&）
// AB：const引用
// U：类或结构体
// V：Interface（接口）
// W4：enum
// X：void
// Z: 结尾标记
//    @： 空，无得意思，构造或析构使用,与?0, ?1配合

NS_TOOL_FRAME_END
