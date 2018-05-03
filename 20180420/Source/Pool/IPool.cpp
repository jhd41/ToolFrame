#include "IPool.h"
#include "MMemory.h"
#include "MLoger.h"

NS_TOOL_FRAME_BEGIN

 void* IPool::operator new(size_t uSize){
 	return Malloc(uSize,false,false,false);
 }
 void IPool::operator delete(void* pMem)
 {
 	Free(pMem,false);
 }
 
 void* IPool::operator new[](size_t uSize){
 	return Malloc(uSize,true,true,false);
 }
 void IPool::operator delete[](void* pMem)
 {
 	 Free(pMem,true);
 }

IPool::IPool()
 {
 }

 IPool::~IPool()
 {

 }

 void* IPoolZero::operator new(size_t uSize)
 {
 	return Malloc(uSize,false,false,true);
 }
 
 void IPoolZero::operator delete( void* pMem )
 {
 	Free(pMem,false);
 }
 
 void* IPoolZero::operator new[]( size_t uSize )
 {
 	return Malloc(uSize,true,true,true);
 }
 
 void IPoolZero::operator delete[]( void* pMem )
 {
 	Free(pMem,true);
 }

IPoolZero::IPoolZero()
 {
 }

IPoolZero::~IPoolZero()
 {

 }

 NS_TOOL_FRAME_END
