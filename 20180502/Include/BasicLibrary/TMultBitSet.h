#pragma once

//最多单次存取1字节
//支持更多的位标识
template<unsigned char _ctUnitSize, unsigned int _ctMax>
class TMultBitSet {
public:
	void Set(unsigned int uPos,unsigned char uValue);// 设置 第几个 为 什么值
	void Clear();//清除所有位
	void Clear(unsigned int uPos);//清除特殊位
	unsigned char Test(unsigned int uPos) const;// Are any of the specified bit(s) set?
private:
	static unsigned char MakeMask(unsigned char uSize);
public:
	TMultBitSet();
	~TMultBitSet();
private:
	unsigned char  _aBuffer[  _ctMax / (8 / _ctUnitSize) + 1 ];//计算得到空间 总量 / (单字节能储存的量) = 所需最小字节数
};

template<unsigned char _ctUnitSize, unsigned int _ctMax>
void TMultBitSet<_ctUnitSize, _ctMax>::Set( unsigned int uPos,unsigned char uValue )
{
	//计算1字节内能储存多少个目标尺寸的值
	int  nUnitMax = 8 / _ctUnitSize;

	//找到所在字节
	unsigned char& uValueBuffer = _aBuffer[ uPos / nUnitMax ];

	//制作蒙板
	unsigned char uMask = MakeMask(_ctUnitSize);
	unsigned char uOffset = uPos % nUnitMax;
	uMask <<= uOffset;

	//处理传入值
	uValue <<= uOffset;
	uValue &= uMask;

	//赋值
	uValueBuffer &= ~uMask;
	uValueBuffer |= uValue;
}

template<unsigned char _ctUnitSize, unsigned int _ctMax>
void TMultBitSet<_ctUnitSize, _ctMax>::Clear()
{
	memset(_aBuffer,0,sizeof(_aBuffer));
}

template<unsigned char _ctUnitSize, unsigned int _ctMax>
void TMultBitSet<_ctUnitSize, _ctMax>::Clear( unsigned int uPos )
{
	//计算1字节内能储存多少个目标尺寸的值
	int  nUnitMax = 8 / _ctUnitSize;

	//找到所在字节
	unsigned char& uValueBuffer = _aBuffer[ uPos / nUnitMax ];

	//制作蒙板
	unsigned char uMask = MakeMask(_ctUnitSize);
	unsigned char uOffset = uPos % nUnitMax;
	uMask <<= uOffset;

	//赋值
	uValueBuffer &= ~uMask;
}

template<unsigned char _ctUnitSize, unsigned int _ctMax>
unsigned char TMultBitSet<_ctUnitSize, _ctMax>::Test( unsigned int uPos ) const
{
	//计算1字节内能储存多少个目标尺寸的值
	int  nUnitMax = 8 / _ctUnitSize;

	//找到所在字节
	unsigned char uValueBuffer = _aBuffer[ uPos / nUnitMax ];

	//制作蒙板
	unsigned char uMask = MakeMask(_ctUnitSize);
	unsigned char uOffset = uPos % nUnitMax;
	uMask <<= uOffset;

	//取值
	uValueBuffer &= uMask;
	uValueBuffer >>= uOffset;

	return uValueBuffer;
}

template<unsigned char _ctUnitSize, unsigned int _ctMax>
unsigned char TMultBitSet<_ctUnitSize, _ctMax>::MakeMask( unsigned char uSize )
{
	if(uSize <= 0) return 0;

	unsigned char uMask = 1;
	for(unsigned char uIndex = 1; uIndex < uSize; ++uIndex) {
		uMask <<= 1;
		uMask |= 1;
	}

	return uMask;
}

template<unsigned char _ctUnitSize, unsigned int _ctMax>
TMultBitSet<_ctUnitSize, _ctMax>::TMultBitSet()
{
	Clear();
}

template<unsigned char _ctUnitSize, unsigned int _ctMax>
TMultBitSet<_ctUnitSize, _ctMax>::~TMultBitSet()
{

}
