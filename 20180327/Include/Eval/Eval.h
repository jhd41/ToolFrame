#pragma once
#include "Macro.h"
#include "EvalNode.h"
#include "IEvalParser.h"

/*
Eval C++脚本编译器 终止开发说明

语句while(double nNum=0){}语句不支持。在解析表达式中存在严重问题。
Eval还需要经历两次换髓才可以比较完美的支持现存表达式。BUG量较少。
1.不再以精确匹配思路进行制作，通过触发后寻找最近不可见字符来判断是否是当前解析器所能解析内容。
2.语句解析可以找到下一个括号匹配项，然后提取中间的字符串进行解析。
由于换髓任务量大，况且本身就有lua脚本存在的情况下，终止Eval的开发，暂时做标记，日后或许有用。
现在开始研究以lua为基础 进行脚本包装。我们应该遵循一个原则，现有的东西就不要重写了拿来用就可以了。
C++脚本编译器 的确是一个不错的思路，但仅仅是语言上的改变，靠一个人的力量来完善如此庞大的系统，暂时没有必要。暂时可以考虑服务器负载均衡，lua为基本的脚本支持工具比较好。
*/

//总控制模块
//分为以下阶段:
//解释阶段:目标:将输入的字符串解析成计算机可识别的操作/数据序列。例如得到 "数据 操作 数据 操作 操作 操作 数据"。这样的一个序列.要求得到有且只有一个序列。这样才认为不存在歧义。
//连接阶段:目标:将解释阶段生成的序列进行链接,此连接做的事情 是 将 操作符 和 数据 对应起来。按照操作符的规则 进行 优先级、结合方式 进行 和 数据结合 调整 生成树状结构。其实本阶段 在第一步骤 时就已经做了,就是为了 第一个阶段的任务目标 “不存在歧义”更加合理。因此，此阶段又可以被认为是第一阶段的子阶段。
//优化阶段:目标:将无效的操作节点去除。以达到优化的目的。比如 !! + + + +  - - 这种连续出现没有意义的操作。
//执行阶段:目标:执行以上阶段生成的树,得到结果。

NS_TOOL_FRAME_BEGIN

class CEval
{
public:
	//表达式
	bool							Expression(const std::string& sExp);
	double							GetReturnValue()const;
	
	//脚本(C++语法)
	bool							Script(const std::string& sExp);
	bool							Execute()const;
public:
	void							Clear();
	const std::string&				GetExp()const;	
	CScopeInfo*						GetScopeByName(const VectorString& vScopeName);//获取表达式
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
	std::string			_sExp;			//表达式
	CEvalParserCallBack	_parserCallBack;//解析回调
	IEvalNode*			_pNode;			//解析完成的结果树
	UINT				_nRandID;		//创建随机名称使用
};

NS_TOOL_FRAME_END
