#pragma once

//��൥�δ�ȡ1�ֽ�
//֧�ָ����λ��ʶ
template<unsigned char _ctUnitSize, unsigned int _ctMax>
class TMultBitSet {
public:
	void Set(unsigned int uPos,unsigned char uValue);// ���� �ڼ��� Ϊ ʲôֵ
	void Clear();//�������λ
	void Clear(unsigned int uPos);//�������λ
	unsigned char Test(unsigned int uPos) const;// Are any of the specified bit(s) set?
private:
	static unsigned char MakeMask(unsigned char uSize);
public:
	TMultBitSet();
	~TMultBitSet();
private:
	unsigned char  _aBuffer[  _ctMax / (8 / _ctUnitSize) + 1 ];//����õ��ռ� ���� / (���ֽ��ܴ������) = ������С�ֽ���
};

template<unsigned char _ctUnitSize, unsigned int _ctMax>
void TMultBitSet<_ctUnitSize, _ctMax>::Set( unsigned int uPos,unsigned char uValue )
{
	//����1�ֽ����ܴ�����ٸ�Ŀ��ߴ��ֵ
	int  nUnitMax = 8 / _ctUnitSize;

	//�ҵ������ֽ�
	unsigned char& uValueBuffer = _aBuffer[ uPos / nUnitMax ];

	//�����ɰ�
	unsigned char uMask = MakeMask(_ctUnitSize);
	unsigned char uOffset = uPos % nUnitMax;
	uMask <<= uOffset;

	//������ֵ
	uValue <<= uOffset;
	uValue &= uMask;

	//��ֵ
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
	//����1�ֽ����ܴ�����ٸ�Ŀ��ߴ��ֵ
	int  nUnitMax = 8 / _ctUnitSize;

	//�ҵ������ֽ�
	unsigned char& uValueBuffer = _aBuffer[ uPos / nUnitMax ];

	//�����ɰ�
	unsigned char uMask = MakeMask(_ctUnitSize);
	unsigned char uOffset = uPos % nUnitMax;
	uMask <<= uOffset;

	//��ֵ
	uValueBuffer &= ~uMask;
}

template<unsigned char _ctUnitSize, unsigned int _ctMax>
unsigned char TMultBitSet<_ctUnitSize, _ctMax>::Test( unsigned int uPos ) const
{
	//����1�ֽ����ܴ�����ٸ�Ŀ��ߴ��ֵ
	int  nUnitMax = 8 / _ctUnitSize;

	//�ҵ������ֽ�
	unsigned char uValueBuffer = _aBuffer[ uPos / nUnitMax ];

	//�����ɰ�
	unsigned char uMask = MakeMask(_ctUnitSize);
	unsigned char uOffset = uPos % nUnitMax;
	uMask <<= uOffset;

	//ȡֵ
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
