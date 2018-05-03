#pragma once
#include "Macro.h"
#include "EvalNode.h"
#include "IEvalParser.h"

/*
Eval C++�ű������� ��ֹ����˵��

���while(double nNum=0){}��䲻֧�֡��ڽ������ʽ�д����������⡣
Eval����Ҫ�������λ���ſ��ԱȽ�������֧���ִ���ʽ��BUG�����١�
1.�����Ծ�ȷƥ��˼·����������ͨ��������Ѱ��������ɼ��ַ����ж��Ƿ��ǵ�ǰ���������ܽ������ݡ�
2.�����������ҵ���һ������ƥ���Ȼ����ȡ�м���ַ������н�����
���ڻ����������󣬿��ұ������lua�ű����ڵ�����£���ֹEval�Ŀ�������ʱ����ǣ��պ�������á�
���ڿ�ʼ�о���luaΪ���� ���нű���װ������Ӧ����ѭһ��ԭ�����еĶ����Ͳ�Ҫ��д�������þͿ����ˡ�
C++�ű������� ��ȷ��һ�������˼·���������������ϵĸı䣬��һ���˵���������������Ӵ��ϵͳ����ʱû�б�Ҫ����ʱ���Կ��Ƿ��������ؾ��⣬luaΪ�����Ľű�֧�ֹ��߱ȽϺá�
*/

//�ܿ���ģ��
//��Ϊ���½׶�:
//���ͽ׶�:Ŀ��:��������ַ��������ɼ������ʶ��Ĳ���/�������С�����õ� "���� ���� ���� ���� ���� ���� ����"��������һ������.Ҫ��õ�����ֻ��һ�����С���������Ϊ���������塣
//���ӽ׶�:Ŀ��:�����ͽ׶����ɵ����н�������,�������������� �� �� ������ �� ���� ��Ӧ���������ղ������Ĺ��� ���� ���ȼ�����Ϸ�ʽ ���� �� ���ݽ�� ���� ������״�ṹ����ʵ���׶� �ڵ�һ���� ʱ���Ѿ�����,����Ϊ�� ��һ���׶ε�����Ŀ�� �����������塱���Ӻ�����ˣ��˽׶��ֿ��Ա���Ϊ�ǵ�һ�׶ε��ӽ׶Ρ�
//�Ż��׶�:Ŀ��:����Ч�Ĳ����ڵ�ȥ�����Դﵽ�Ż���Ŀ�ġ����� !! + + + +  - - ������������û������Ĳ�����
//ִ�н׶�:Ŀ��:ִ�����Ͻ׶����ɵ���,�õ������

NS_TOOL_FRAME_BEGIN

class CEval
{
public:
	//���ʽ
	bool							Expression(const std::string& sExp);
	double							GetReturnValue()const;
	
	//�ű�(C++�﷨)
	bool							Script(const std::string& sExp);
	bool							Execute()const;
public:
	void							Clear();
	const std::string&				GetExp()const;	
	CScopeInfo*						GetScopeByName(const VectorString& vScopeName);//��ȡ���ʽ
	bool							GetScopeName(VectorString& vScopeName,CScopeInfo* pScope )const;
	std::string						MakeNewScopeName();
public:
	static bool Clone( ListEvalNode& vNodeDes,const ListEvalNode& vNodeSrc );
	static bool Destory( ListEvalNode& vNodeDes );
	static bool Destory( IEvalNode* pNode );
public:
	virtual bool OnParseDone(IEvalNode* pNode,const size_t nSrc,IEvalParser* pCallBack);
public:
	CEval(void);
	virtual ~CEval(void);
private:
	CFIELD_BOOL(Error);
	CFIELD_BOOL(ParseDone);
	CFIELD_REF(CScopeInfo,DefaultScope,info);
private:
	std::string			_sExp;			//���ʽ
	CEvalParserCallBack	_parserCallBack;//�����ص�
	IEvalNode*			_pNode;			//������ɵĽ����
	UINT				_nRandID;		//�����������ʹ��
};

NS_TOOL_FRAME_END
