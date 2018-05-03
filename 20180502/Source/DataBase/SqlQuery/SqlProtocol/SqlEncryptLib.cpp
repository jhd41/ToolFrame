#include "SqlEncryptLib.h"

#ifdef MACRO_LIB_MY_SQL

CSqlEncryptLib::CSqlEncryptLib(void)
{
}

CSqlEncryptLib::~CSqlEncryptLib(void)
{
}

bool CSqlEncryptLib::OnEncrypt( uint32 uSecretKey, char* pBuffer,uint uLength )
{
	if (uLength<=0)return false;
	if (!pBuffer)return false;

	uint32 uSecretKey1 = uSecretKey;
	uint32 uSecretKey2 = uSecretKey1 + uSecretKey1+0xCBCEBCAA;
	uint32 uSecretKey3 = uSecretKey2 + uSecretKey1+0x19860202;

	uint uIndex =0;

	//能被4整除部分
	while(uIndex + sizeof(uSecretKey1) < uLength){
		uint32* pBufferUnit = (uint32*)&pBuffer[uIndex];
		*pBufferUnit ^= uSecretKey1;
		*pBufferUnit ^= uSecretKey2;
		*pBufferUnit ^= uSecretKey3;

		uIndex+= sizeof(uSecretKey1);
	}

	//不能被4整除部分
	while(uIndex<uLength){
		pBuffer[uIndex] ^= uSecretKey1;
		pBuffer[uIndex] ^= uSecretKey2;
		pBuffer[uIndex] ^= uSecretKey3;

		++uIndex;
	}
	return true;
}

bool CSqlEncryptLib::OnDecrypt( uint32 uSecretKey, char* pBuffer,uint uLength )
{
	if (uLength<=0)return false;
	if (!pBuffer)return false;

	uint32 uSecretKey1 = uSecretKey;
	uint32 uSecretKey2 = uSecretKey1 + uSecretKey1+0xCBCEBCAA;
	uint32 uSecretKey3 = uSecretKey2 + uSecretKey1+0x19860202;

	uint uIndex =0;

	//能被4整除部分
	while(uIndex + sizeof(uSecretKey1) < uLength){
		uint32* pBufferUnit = (uint32*)&pBuffer[uIndex];
		*pBufferUnit ^= uSecretKey3;
		*pBufferUnit ^= uSecretKey2;
		*pBufferUnit ^= uSecretKey1;

		uIndex+= sizeof(uSecretKey1);
	}

	//不能被4整除部分
	while(uIndex<uLength){
		pBuffer[uIndex] ^= uSecretKey3;
		pBuffer[uIndex] ^= uSecretKey2;
		pBuffer[uIndex] ^= uSecretKey1;

		++uIndex;
	}
	return true;
}

#endif
