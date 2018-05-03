#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

class CSqlEncryptLib
{
public:
	//–≠“Èº”√‹
	static bool OnEncrypt(uint32 uSecretKey, char* pBuffer,uint uLength );
	static bool OnDecrypt(uint32 uSecretKey, char* pBuffer,uint uLength );
public:
	CSqlEncryptLib(void);
	virtual ~CSqlEncryptLib(void);
};

#endif
