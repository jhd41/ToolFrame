#pragma once
#include "Macro.h"

//数据:所有存储在流里的都是数据
//有效数据:从当前游标开始算起到结尾的数据称为有效数据
//内部操作 均根据游标位置进行操作
//游标有两种类型 读游标，和 写游标，用于设置 默认 读取 写入时候的位置
//流的大小概念
//有效大小 即 写游标 减去 读游标的 有效空间，默认的判断都是基于这种判断
//数据大小 和 读写游标没有关系，内部从起点0 到 终点 总共拥有的数据大小

NS_TOOL_FRAME_BEGIN
class IStreamBase
{
public:
	//定义流方向
	enum EStreamDirection
	{
		STREAM_INVAILD = INVALID_ID,
		STREAM_INPUT,
		STREAM_OUTPUT,
		STREAM_MAX,
	};
	//基本属性
public:
	virtual	bool	IsEmpty()const;								//是否为空(有效数据)
	virtual bool	IsFull()const;								//已满(有效数据)
	virtual size_t	GetLength()const;							//获取有效数据长度
	virtual bool	Skip(int nOffset);							//跳过指定数据(移动只读指针)
	virtual bool	IsReadable();								//是否可读
	virtual	bool	IsWriteable();								//是否可写
	virtual	bool	IsVaildCursor(size_t uCursor)const;			//是否是有效游标
	virtual bool	IsTrimed()const;							//是否规整(内部的数据全部未读取)

	virtual bool	IsDataEmpty()const;							//数据是否为空
	virtual bool	IsDataFull()const;							//数据是否已满
	virtual	size_t	GetSize()const;								//获取数据总长度
	virtual size_t	GetUnusedSize()const;						//计算还未使用的空间大小
	virtual bool	Drop(size_t uSize);							//丢弃末尾的指定大小数据
	//基本操作
public:
	virtual bool	Resize(size_t uSize);						//重新分配空间
	virtual bool	Clear();									//清空流
	virtual	bool	Read(void* pBuff, size_t uSize);			//读取 从游标处开始(加入权限控制)
	virtual	bool	Write(const void* pBuff, size_t uSize);		//存储 从游标处开始(加入权限控制 )
	virtual	bool	Write(IStreamBase& stream, size_t uSize);	//存储 从游标处开始(加入权限控制)
	virtual	bool	Write(IStreamBase& stream);
	virtual	size_t	WriteSome(const void* pBuff, size_t uSize);	//存储 从游标处开始(加入权限控制 )	返回写入了多少字节
	virtual	size_t	ReadSome(void* pBuff, size_t uSize);		//读取 从游标处开始(加入权限控制)	返回读取了多少字节
	virtual	bool	Insert(size_t uCursor,const void* pBuff, size_t uSize);//插入 从指定游标处开始(加入权限控制)
	virtual bool	Modify(size_t uCursor,const void* pBuff, size_t uSize);//修改 修改指定游标位置的数据(加入权限控制)

	//游标操作
public:
	virtual	bool	SkipReadCursor(int nOffset,bool bFix = true);	//设置读取游标跳跃指定单位(如果超过极限 则 自动修正)
	virtual	bool	SkipWriteCursor(int nOffset, bool bFix = true);	//设置写入游标跳跃指定单位
	virtual bool	SetReadCursorBegin();							//设置读取游标至数据开头
	virtual bool	SetWriteCursorEnd();							//设置写入游标至数据末尾
	virtual bool	IsReadCursorBegin()const;						//是否读取游标在数据开头
	virtual bool	IsWriteCursorEnd()const;						//是否写入游标在数据末尾
	virtual bool	ResetCursor();									//重置游标(读游标在看数据开头，写游标在数据结尾)

	//出错相关
public:
	virtual	void	SetError();									//设置出错
	virtual	bool	IsError()const;								//判断是否出错
	virtual	void	ClearError();								//清除错误

	virtual bool	Copy(const IStreamBase& stream);			//复制基本数据
	virtual bool	Reset();									//重置基本属性

	//外部不要使用
public:
	virtual bool	SetSize(size_t uSize);						//设置数据长度
protected:
	virtual bool	DebugCheck()const;							//数据检查(调试用)
protected:
	virtual bool	_Read(size_t uCursor, void* pBuff,size_t uSize)=0;				//读取
	virtual bool	_Write(size_t uCursor, const void* pBuff, size_t uSize) = 0;	//写入
	virtual bool	_Insert(size_t uCursor, const void* pBuff, size_t uSize) = 0;	//插入
	virtual bool	_Clear();														//清除
	virtual	bool	_Write(IStreamBase& stream, size_t uSize);						//存储 从游标处开始
public:
	virtual IStreamBase& operator =(const IStreamBase& iStream);
public:
	IStreamBase(void);
	virtual ~IStreamBase(void);
private:
	CFIELD_INT(Direction);
	CFIELD_BOOL(ReadOnly);		//只读
	CFIELD_BOOL(WriteOnly);		//只写
	CFIELD_SIZE(ReadCursor);	//读游标(默认0)
	CFIELD_SIZE(WriteCursor);	//写游标(默认0)
	CFIELD_INT(UserInt);		//用户自定义数据
	CFIELD_STRING(UserString);	//用户自定义数据
	CFIELD_SIZE(MaxSize);		//最大尺寸
protected:
	bool		_bError;	//出错标记
	size_t		_uSize;		//数据长度
};
NS_TOOL_FRAME_END
