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
	MapIntInt				_vPrecedenceAssociativity;		//���ȼ� ��Ϸ�ʽ
	MapEvalOperationConfig	_vOperationConfig;				//����������
};

// 1: ?0: ��������?1 ������
// 2:     @@QAE: public __thiscall
// @@AAE: private __thiscall
// @@QBE: public __thiscall const 
// 3: ����ֵ�Ͳ�������
// B��const
// D��char
// E��unsigned char
// F��short
// G��unsigned short
// H��int
// I��unsigned int
// J��long
// K��unsigned long
// M��float
// N��double
// _N��bool
// PA��ָ�루*������Ĵ��ű���ָ�����ͣ������ͬ���͵�ָ���������֣���0���棬һ��0����һ���ظ���
// PB��constָ��
// AA�����ã�&��
// AB��const����
// U�����ṹ��
// V��Interface���ӿڣ�
// W4��enum
// X��void
// Z: ��β���
//    @�� �գ��޵���˼�����������ʹ��,��?0, ?1���

NS_TOOL_FRAME_END
