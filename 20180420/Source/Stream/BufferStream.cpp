#include "BufferStream.h"
#include "ToolFrame.h"

NS_TOOL_FRAME_BEGIN

CBufferStream::CBufferStream(void)
{
	_uSize = 0;
	_uSizeMax = 0;
}

CBufferStream::CBufferStream( const CBufferStream& xStream )
{
	*this = xStream;
}

CBufferStream::~CBufferStream(void)
{
}

 bool CBufferStream::SetSizeMax(size_t uSize )
 {
 	CLockWrite lock(_mutex);
 	_uSizeMax = uSize;
	return true;
 }
 
 bool CBufferStream::IsInfiniteSize() const
 {
 	CLockRead lock(_mutex);
 	return !_uSizeMax;
 }

 bool CBufferStream::PushFront(IStreamPtr ptr )
 {
	 if (!ptr)return false;

	 CLockWrite lock(_mutex);

	 if (_uSizeMax > 0 && ptr->GetLength() + _uSize > _uSizeMax)return false;
	 _vBuffer.push_front(ptr);
	 _uSize += ptr->GetLength();
	 return true;
 }

 bool CBufferStream::PushBack(IStreamPtr ptr )
 {
 	if (!ptr)return false;
 	
 	CLockWrite lock(_mutex);
 
 	if (_uSizeMax > 0 && ptr->GetLength() + _uSize > _uSizeMax)return false;
 	_vBuffer.push_back(ptr);
 	_uSize += ptr->GetLength();
 	return true;
 }

 IStreamPtr CBufferStream::PopFront()
 {
	 CLockWrite lock(_mutex);
	 IStreamPtr ptr = ToolFrame::PopFrontPtr(_vBuffer);
	 if (!ptr)return ptr;
	 _uSize -= ptr->GetLength();
	 return ptr;
 }

IStreamPtr CBufferStream::PopBack()
{
	CLockWrite lock(_mutex);
	IStreamPtr ptr = ToolFrame::PopBackPtr(_vBuffer);
	if (!ptr)return ptr;
	_uSize -= ptr->GetLength();
	return ptr;
}

size_t CBufferStream::GetSizeMax() const
 {
 	CLockRead lock(_mutex);
 	return _uSizeMax;
 }
 
size_t CBufferStream::GetSize() const
 {
 	CLockRead lock(_mutex);
 	return _uSize;
 }
 
 bool CBufferStream::Clear()
 {
 	CLockWrite lock(_mutex);
 	ToolFrame::Clear(_vBuffer);
 	_uSize = 0;
 	return true;
 }
 
 bool CBufferStream::Clear(ListStreamPtr& vBuffer )
 {
 	CLockWrite lock(_mutex);
 	ToolFrame::Merge(vBuffer,_vBuffer);
 	ToolFrame::Clear(_vBuffer);
 	_uSize = 0;
 	return true;
 }

 bool CBufferStream::IsEmpty() const
 {
	 CLockRead lock(_mutex);
	 return _vBuffer.empty();
 }

 size_t CBufferStream::GetCount() const
 {
	 CLockRead lock(_mutex);
	 return _vBuffer.size();
 }

 CBufferStream& CBufferStream::operator=( const CBufferStream& xStream )
 {
	 CLockWrite lockSelf(_mutex);
	 CLockWrite lockTarget(xStream._mutex);

	_vBuffer	= xStream._vBuffer;
	_uSize		= xStream._uSize;
	_uSizeMax	= xStream._uSizeMax;
	return *this;
 }

NS_TOOL_FRAME_END
