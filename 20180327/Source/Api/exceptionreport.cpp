#pragma warning(disable:4091)
#pragma warning(disable:4477)

#include "ExceptionReport.h"

NS_TOOL_FRAME_BEGIN
bool InitExceptionReport(){return true;}//�����ƹ���������ȫ���ӵ�ִ�д���
NS_TOOL_FRAME_END

#if MACRO_TARGET_OS == MACRO_OS_WINDOWS

#include "ApiWin.h"
#include "ToolFrame.h"
#include <xutility>

//==========================================
// Matt Pietrek
// MSDN Magazine, 2002
// FILE: ExceptionReport.CPP
//==========================================
#define WIN32_LEAN_AND_MEAN

#pragma comment(linker, "/defaultlib:dbghelp.lib")
#pragma warning(disable : 4311 4312)
#pragma warning( disable : 4996 )
#pragma warning( disable : 4267 )

NS_TOOL_FRAME_BEGIN

MExceptionReport& g_ExceptionReport = MExceptionReport::Singleton();

TCHAR m_szDumFileName[MAX_PATH]={0};

typedef bool (* MINIDUMPWRITEDUMP )(HANDLE hProcess,
									DWORD  ProcessId,
									HANDLE hFile,
									MINIDUMP_TYPE DumpType,
									PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam,
									PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam,
									PMINIDUMP_CALLBACK_INFORMATION CallbackParam);

LONG WINAPI TopLevelFilter(struct _EXCEPTION_POINTERS * pExceptionInfo)
{
	LONG ret = EXCEPTION_CONTINUE_SEARCH;
	HANDLE   hFile  =   CreateFile(m_szDumFileName,   GENERIC_WRITE,   FILE_SHARE_WRITE,   NULL,   CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,   NULL   );

	if   (hFile!=INVALID_HANDLE_VALUE)
	{
		MINIDUMP_EXCEPTION_INFORMATION   ExInfo;

		ExInfo.ThreadId  =   ::GetCurrentThreadId();
		ExInfo.ExceptionPointers  =   pExceptionInfo;
		ExInfo.ClientPointers  =   NULL;

		//   write   the   dump
		BOOL   bOK  =   MiniDumpWriteDump(GetCurrentProcess(),   GetCurrentProcessId(),   hFile,   MiniDumpNormal,  &ExInfo,   NULL,   NULL   );
		CloseHandle(hFile);
	}
	return ret;

// 	LONG ret = EXCEPTION_CONTINUE_SEARCH;
// 	HMODULE hDll = LoadLibrary(_T("DBGHelp.dll"));

// 	MINIDUMPWRITEDUMP pDump = (MINIDUMPWRITEDUMP)::GetProcAddress(hDll,"MiniDumpWriteDump");
// 	HANDLE hFile = CreateFile(m_szDumFileName,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
// 	if(hFile != INVALID_HANDLE_VALUE)
// 	{
// 		MINIDUMP_EXCEPTION_INFORMATION ExInfo;
// 		ExInfo.ThreadId = ::GetCurrentThreadId();
// 		ExInfo.ExceptionPointers = pExceptionInfo;
// 		ExInfo.ClientPointers = NULL;
// 
// 		pDump(GetCurrentProcess(),GetCurrentProcessId(),hFile,MiniDumpNormal,&ExInfo,NULL,NULL);
// 		CloseHandle(hFile);
// 	}
// 
// 	return ret;
}	 
//============================== Global Variables =============================

//
// Declare the static variables of the ExceptionReport class
//
TCHAR MExceptionReport::m_szLogFileName[MAX_PATH]={0};
LPTOP_LEVEL_EXCEPTION_FILTER MExceptionReport::m_previousFilter;
HANDLE MExceptionReport::m_hReportFile;
HANDLE MExceptionReport::m_hProcess;
LONG MExceptionReport::m_nException = EXCEPTION_EXECUTE_HANDLER;

// Declare global instance of class
//ExceptionReport g_ExceptionReport;

//============================== Class Methods =============================

MExceptionReport::MExceptionReport( )   // Constructor
{
	// Install the unhandled exception filter function
	m_previousFilter =
		SetUnhandledExceptionFilter(WheatyUnhandledExceptionFilter);

	m_hProcess = GetCurrentProcess();

	//����LOG�ļ���������DMP�ļ���
	std::string sPath		= ApiWin::GetExePath();
	std::string sDir		= ToolFrame::PickDir(sPath);
	std::string sFileName	= ToolFrame::PickFileNameWithOutExt(sPath);
	
	ApiWin::ApiStrCpy(MAKE_STRING(sDir<<sFileName<<ToolFrame::GetNowTimeString("YYYYMMDDhhmmss")<<".dmp"),m_szDumFileName,sizeof(m_szDumFileName));
	ApiWin::ApiStrCpy(MAKE_STRING(sDir<<sFileName<<ToolFrame::GetNowTimeString("YYYYMMDDhhmmss")<<".txt"),m_szLogFileName,sizeof(m_szLogFileName));

	m_nException = EXCEPTION_EXECUTE_HANDLER;
}

//============
// Destructor
//============
MExceptionReport::~MExceptionReport( )
{
	SetUnhandledExceptionFilter( m_previousFilter );
}

//==============================================================
// Lets user change the name of the report file to be generated
//==============================================================
void MExceptionReport::SetLogFileName( PTSTR pszLogFileName,PTSTR dumname )
{
	_tcscpy( m_szLogFileName, pszLogFileName );
	_tcscpy( m_szDumFileName, dumname );
	//strstr(m_szDumFileName,_T(".dmp"));
}

//===========================================================
// Entry point where control comes on an unhandled exception
//===========================================================
LONG WINAPI MExceptionReport::WheatyUnhandledExceptionFilter(
	PEXCEPTION_POINTERS pExceptionInfo )
{
	m_hReportFile = CreateFile( m_szLogFileName,
		GENERIC_WRITE,
		0,
		0,
		OPEN_ALWAYS,
		FILE_FLAG_WRITE_THROUGH,
		0 );

	if ( m_hReportFile )
	{
		SetFilePointer( m_hReportFile, 0, 0, FILE_BEGIN);

		GenerateExceptionReport( pExceptionInfo );

		CloseHandle( m_hReportFile );
		m_hReportFile = 0;
	}

	TopLevelFilter(pExceptionInfo);

	if ( m_previousFilter )
		return m_previousFilter( pExceptionInfo );
	else
		return m_nException;//EXCEPTION_EXECUTE_HANDLER;//EXCEPTION_CONTINUE_SEARCH SongJ

	//EXCEPTION_EXECUTE_HANDLER equ 1 ��ʾ���Ѿ��������쳣,�������ŵؽ�����  
	//EXCEPTION_CONTINUE_SEARCH equ 0 ��ʾ�Ҳ�����,����������,����windows����Ĭ�ϵĴ���������ʾһ�������,������  
	//EXCEPTION_CONTINUE_EXECUTION equ -1 ��ʾ�����Ѿ����޸�,����쳣����������ִ��  
}

//===========================================================================
// Open the report file, and write the desired information to it.  Called by
// WheatyUnhandledExceptionFilter
//===========================================================================
void MExceptionReport::GenerateExceptionReport(PEXCEPTION_POINTERS pExceptionInfo )
{
	// ���濪ͷ��¼��ҵ�
	while(ShowCursor(TRUE) < 0);

	// Start out with a banner
	_tprintf(_T("\r\n//=====================================================\r\n"));

	//Print Code Compile Time
	_tprintf(_T("Code Compile Time: %s %s \r\n"),MACRO_DATE,MACRO_TIME);

	PEXCEPTION_RECORD pExceptionRecord = pExceptionInfo->ExceptionRecord;

	// First print information about the type of fault
	_tprintf(   _T("Exception code: %08X %s\r\n"),
		pExceptionRecord->ExceptionCode,
		GetExceptionString(pExceptionRecord->ExceptionCode) );

	// Now print information about where the fault occured
	TCHAR szFaultingModule[MAX_PATH];
	DWORD section;
	LONGLONG offset;
	GetLogicalAddress(  pExceptionRecord->ExceptionAddress,
		szFaultingModule,
		sizeof( szFaultingModule ),
		section, offset );

	_tprintf( _T("Fault address:  %08X %02X:%08X %s\r\n"),
		pExceptionRecord->ExceptionAddress,
		section, offset, szFaultingModule );

	PCONTEXT pCtx = pExceptionInfo->ContextRecord;

	// Show the registers
#ifdef _M_IX86  // X86 Only!
	_tprintf( _T("\r\nRegisters:\r\n") );

	_tprintf(_T("EAX:%08X\r\nEBX:%08X\r\nECX:%08X\r\nEDX:%08X\r\nESI:%08X\r\nEDI:%08X\r\n")
		,pCtx->Eax, pCtx->Ebx, pCtx->Ecx, pCtx->Edx,
		pCtx->Esi, pCtx->Edi );

	_tprintf( _T("CS:EIP:%04X:%08X\r\n"), pCtx->SegCs, pCtx->Eip );
	_tprintf( _T("SS:ESP:%04X:%08X  EBP:%08X\r\n"),
		pCtx->SegSs, pCtx->Esp, pCtx->Ebp );
	_tprintf( _T("DS:%04X  ES:%04X  FS:%04X  GS:%04X\r\n"),
		pCtx->SegDs, pCtx->SegEs, pCtx->SegFs, pCtx->SegGs );
	_tprintf( _T("Flags:%08X\r\n"), pCtx->EFlags );

#endif

	SymSetOptions( SYMOPT_DEFERRED_LOADS );

	// Initialize DbgHelp
	if ( !SymInitialize( GetCurrentProcess(), 0, TRUE ) )
		return;

	CONTEXT trashableContext = *pCtx;

	WriteStackDetails( &trashableContext, false );

#ifdef _M_IX86  // X86 Only!

	_tprintf( _T("========================\r\n") );
	_tprintf( _T("Local Variables And Parameters\r\n") );

	trashableContext = *pCtx;
	WriteStackDetails( &trashableContext, true );

	_tprintf( _T("========================\r\n") );
	_tprintf( _T("Global Variables\r\n") );

	SymEnumSymbols( GetCurrentProcess(),
		(DWORD64)GetModuleHandle(szFaultingModule),
		0, EnumerateSymbolsCallback, 0 );

#endif      // X86 Only!

	SymCleanup( GetCurrentProcess() );

	_tprintf( _T("\r\n") );
}

//======================================================================
// Given an exception code, returns a pointer to a static string with a
// description of the exception
//======================================================================
LPTSTR MExceptionReport::GetExceptionString( DWORD dwCode )
{
#define EXCEPTION( x ) case EXCEPTION_##x: return _T(#x);

	switch ( dwCode )
	{
		EXCEPTION( ACCESS_VIOLATION )
			EXCEPTION( DATATYPE_MISALIGNMENT )
			EXCEPTION( BREAKPOINT )
			EXCEPTION( SINGLE_STEP )
			EXCEPTION( ARRAY_BOUNDS_EXCEEDED )
			EXCEPTION( FLT_DENORMAL_OPERAND )
			EXCEPTION( FLT_DIVIDE_BY_ZERO )
			EXCEPTION( FLT_INEXACT_RESULT )
			EXCEPTION( FLT_INVALID_OPERATION )
			EXCEPTION( FLT_OVERFLOW )
			EXCEPTION( FLT_STACK_CHECK )
			EXCEPTION( FLT_UNDERFLOW )
			EXCEPTION( INT_DIVIDE_BY_ZERO )
			EXCEPTION( INT_OVERFLOW )
			EXCEPTION( PRIV_INSTRUCTION )
			EXCEPTION( IN_PAGE_ERROR )
			EXCEPTION( ILLEGAL_INSTRUCTION )
			EXCEPTION( NONCONTINUABLE_EXCEPTION )
			EXCEPTION( STACK_OVERFLOW )
			EXCEPTION( INVALID_DISPOSITION )
			EXCEPTION( GUARD_PAGE )
			EXCEPTION( INVALID_HANDLE )
	}

	// If not one of the "known" exceptions, try to get the string
	// from NTDLL.DLL's message table.

	static TCHAR szBuffer[512] = { 0 };

	FormatMessage( FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_HMODULE,
		GetModuleHandle( _T("NTDLL.DLL") ),
		dwCode, 0, szBuffer, sizeof( szBuffer ), 0 );

	return szBuffer;
}

//=============================================================================
// Given a linear address, locates the module, section, and offset containing
// that address.
//
// Note: the szModule paramater buffer is an output buffer of length specified
// by the len parameter (in characters!)
//=============================================================================
BOOL MExceptionReport::GetLogicalAddress(
										PVOID addr, PTSTR szModule, DWORD len, DWORD& section, LONGLONG& offset )
{
	MEMORY_BASIC_INFORMATION mbi;

	if ( !VirtualQuery( addr, &mbi, sizeof(mbi) ) )
		return FALSE;

	LONGLONG hMod = (LONGLONG)mbi.AllocationBase;

	if ( !GetModuleFileName( (HMODULE)hMod, szModule, len ) )
		return FALSE;

	// Point to the DOS header in memory
	PIMAGE_DOS_HEADER pDosHdr = (PIMAGE_DOS_HEADER)hMod;

	// From the DOS header, find the NT (PE) header
	PIMAGE_NT_HEADERS pNtHdr = (PIMAGE_NT_HEADERS)(hMod + pDosHdr->e_lfanew);

	PIMAGE_SECTION_HEADER pSection = IMAGE_FIRST_SECTION( pNtHdr );

	LONGLONG rva = (LONGLONG)addr - hMod; // RVA is offset from module load address

	// Iterate through the section table, looking for the one that encompasses
	// the linear address.
	for (   unsigned i = 0;
		i < pNtHdr->FileHeader.NumberOfSections;
		i++, pSection++ )
	{
		DWORD sectionStart = pSection->VirtualAddress;
		DWORD sectionEnd = sectionStart
			+ max(pSection->SizeOfRawData, pSection->Misc.VirtualSize);

		// Is the address in this section???
		if ( (rva >= sectionStart) && (rva <= sectionEnd) )
		{
			// Yes, address is in the section.  Calculate section and offset,
			// and store in the "section" & "offset" params, which were
			// passed by reference.
			section = i+1;
			offset = rva - sectionStart;
			return TRUE;
		}
	}

	return FALSE;   // Should never get here!
}

//============================================================
// Walks the stack, and writes the results to the report file
//============================================================
void MExceptionReport::WriteStackDetails(
										PCONTEXT pContext,
										bool bWriteVariables )  // true if local/params should be output
{
	_tprintf( _T("\r\nCall stack:\r\n") );

	_tprintf( _T("Address   Frame     Function            SourceFile\r\n") );

	DWORD dwMachineType = 0;
	// Could use SymSetOptions here to add the SYMOPT_DEFERRED_LOADS flag

	STACKFRAME sf;
	memset( &sf, 0, sizeof(sf) );

#ifdef _M_IX86
	// Initialize the STACKFRAME structure for the first call.  This is only
	// necessary for Intel CPUs, and isn't mentioned in the documentation.
	sf.AddrPC.Offset       = pContext->Eip;
	sf.AddrPC.Mode         = AddrModeFlat;
	sf.AddrStack.Offset    = pContext->Esp;
	sf.AddrStack.Mode      = AddrModeFlat;
	sf.AddrFrame.Offset    = pContext->Ebp;
	sf.AddrFrame.Mode      = AddrModeFlat;

	dwMachineType = IMAGE_FILE_MACHINE_I386;
#endif

	while ( 1 )
	{
		// Get the next stack frame
		if ( ! StackWalk(  dwMachineType,
			m_hProcess,
			GetCurrentThread(),
			&sf,
			pContext,
			0,
			SymFunctionTableAccess,
			SymGetModuleBase,
			0 ) )
			break;

		if ( 0 == sf.AddrFrame.Offset ) // Basic sanity check to make sure
			break;                      // the frame is OK.  Bail if not.

		_tprintf( _T("%08X  %08X  "), sf.AddrPC.Offset, sf.AddrFrame.Offset );

		// Get the name of the function for this stack frame entry
		BYTE symbolBuffer[ sizeof(SYMBOL_INFO) + 1024 ];
		PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)symbolBuffer;
		pSymbol->SizeOfStruct = sizeof(symbolBuffer);
		pSymbol->MaxNameLen = 1024;

		DWORD64 symDisplacement = 0;    // Displacement of the input address,
		// relative to the start of the symbol

		if ( SymFromAddr(m_hProcess,sf.AddrPC.Offset,&symDisplacement,pSymbol))
		{
			_tprintf( _T("%hs+%I64X"), pSymbol->Name, symDisplacement );

		}
		else    // No symbol found.  Print out the logical address instead.
		{
			TCHAR szModule[MAX_PATH] = _T("");
			DWORD section = 0;
			LONGLONG offset = 0;

			GetLogicalAddress(  (PVOID)sf.AddrPC.Offset,
				szModule, sizeof(szModule), section, offset );

			_tprintf( _T("%04X:%08X %s"), section, offset, szModule );
		}

		// Get the source line for this stack frame entry
		IMAGEHLP_LINE lineInfo = { sizeof(IMAGEHLP_LINE) };
		DWORD dwLineDisplacement;
		if ( SymGetLineFromAddr( m_hProcess, sf.AddrPC.Offset,
			&dwLineDisplacement, &lineInfo ) )
		{
			_tprintf(_T("  %s line %u"),lineInfo.FileName,lineInfo.LineNumber);
		}

		_tprintf( _T("\r\n") );

		// Write out the variables, if desired
		if ( bWriteVariables )
		{
			// Use SymSetContext to get just the locals/params for this frame
			IMAGEHLP_STACK_FRAME imagehlpStackFrame;
			imagehlpStackFrame.InstructionOffset = sf.AddrPC.Offset;
			SymSetContext( m_hProcess, &imagehlpStackFrame, 0 );

			// Enumerate the locals/parameters
			SymEnumSymbols( m_hProcess, 0, 0, EnumerateSymbolsCallback, &sf );

			_tprintf( _T("\r\n") );
		}
	}

}

//////////////////////////////////////////////////////////////////////////////
// The function invoked by SymEnumSymbols
//////////////////////////////////////////////////////////////////////////////

BOOL CALLBACK
MExceptionReport::EnumerateSymbolsCallback(
	PSYMBOL_INFO  pSymInfo,
	ULONG         SymbolSize,
	PVOID         UserContext )
{

	char szBuffer[2048];

	__try
	{
		if ( FormatSymbolValue( pSymInfo, (STACKFRAME*)UserContext,
			szBuffer, sizeof(szBuffer) ) )
			_tprintf( _T("\t%s\r\n"), szBuffer );
	}
	__except( 1 )
	{
		_tprintf( _T("punting on symbol %s\r\n"), pSymInfo->Name );
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
// Given a SYMBOL_INFO representing a particular variable, displays its
// contents.  If it's a user defined type, display the members and their
// values.
//////////////////////////////////////////////////////////////////////////////
bool MExceptionReport::FormatSymbolValue(
										PSYMBOL_INFO pSym,
										STACKFRAME * sf,
										char * pszBuffer,
										unsigned cbBuffer )
{
	char * pszCurrBuffer = pszBuffer;

	// Indicate if the variable is a local or parameter
	if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_PARAMETER )
		pszCurrBuffer += sprintf( pszCurrBuffer, "Parameter " );
	else if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_LOCAL )
		pszCurrBuffer += sprintf( pszCurrBuffer, "Local " );

	// If it's a function, don't do anything.
	if ( pSym->Tag == 5 )   // SymTagFunction from CVCONST.H from the DIA SDK
		return false;

	// Emit the variable name
	pszCurrBuffer += sprintf( pszCurrBuffer, "\'%s\'", pSym->Name );

	DWORD_PTR pVariable = 0;    // Will point to the variable's data in memory

	if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGRELATIVE )
	{
		// if ( pSym->Register == 8 )   // EBP is the value 8 (in DBGHELP 5.1)
		{                               //  This may change!!!
			pVariable = sf->AddrFrame.Offset;
			pVariable += (DWORD_PTR)pSym->Address;
		}
		// else
		//  return false;
	}
	else if ( pSym->Flags & IMAGEHLP_SYMBOL_INFO_REGISTER )
	{
		return false;   // Don't try to report register variable
	}
	else
	{
		pVariable = (DWORD_PTR)pSym->Address;   // It must be a global variable
	}

	// Determine if the variable is a user defined type (UDT).  IF so, bHandled
	// will return true.
	bool bHandled;
	pszCurrBuffer = DumpTypeIndex(pszCurrBuffer,pSym->ModBase, pSym->TypeIndex,
		0, pVariable, bHandled );

	if ( !bHandled )
	{
		// The symbol wasn't a UDT, so do basic, stupid formatting of the
		// variable.  Based on the size, we're assuming it's a char, WORD, or
		// DWORD.
		BasicType basicType = GetBasicType( pSym->TypeIndex, pSym->ModBase );

		pszCurrBuffer = FormatOutputValue(pszCurrBuffer, basicType, pSym->Size,
			(PVOID)pVariable );
	}


	return true;
}

//////////////////////////////////////////////////////////////////////////////
// If it's a user defined type (UDT), recurse through its members until we're
// at fundamental types.  When he hit fundamental types, return
// bHandled = false, so that FormatSymbolValue() will format them.
//////////////////////////////////////////////////////////////////////////////
char * MExceptionReport::DumpTypeIndex(
									  char * pszCurrBuffer,
									  DWORD64 modBase,
									  DWORD dwTypeIndex,
									  unsigned nestingLevel,
									  DWORD_PTR offset,
									  bool & bHandled )
{
	bHandled = false;

	// Get the name of the symbol.  This will either be a Type name (if a UDT),
	// or the structure member name.
	WCHAR * pwszTypeName;
	if ( SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_SYMNAME,
		&pwszTypeName ) )
	{
		pszCurrBuffer += sprintf( pszCurrBuffer, " %ls", pwszTypeName );
		LocalFree( pwszTypeName );
	}

	// Determine how many children this type has.
	DWORD dwChildrenCount = 0;
	SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_GET_CHILDRENCOUNT,
		&dwChildrenCount );

	if ( !dwChildrenCount )     // If no children, we're done
		return pszCurrBuffer;

	// Prepare to get an array of "TypeIds", representing each of the children.
	// SymGetTypeInfo(TI_FINDCHILDREN) expects more memory than just a
	// TI_FINDCHILDREN_PARAMS struct has.  Use derivation to accomplish this.
	struct FINDCHILDREN : TI_FINDCHILDREN_PARAMS
	{
		ULONG   MoreChildIds[1024];
		FINDCHILDREN(){Count = sizeof(MoreChildIds) / sizeof(MoreChildIds[0]);}
	} children;

	children.Count = dwChildrenCount;
	children.Start= 0;

	// Get the array of TypeIds, one for each child type
	if ( !SymGetTypeInfo( m_hProcess, modBase, dwTypeIndex, TI_FINDCHILDREN,
		&children ) )
	{
		return pszCurrBuffer;
	}

	// Append a line feed
	pszCurrBuffer += sprintf( pszCurrBuffer, "\r\n" );

	// Iterate through each of the children
	for ( unsigned i = 0; i < dwChildrenCount; i++ )
	{
		// Add appropriate indentation level (since this routine is recursive)
		for ( unsigned j = 0; j <= nestingLevel+1; j++ )
			pszCurrBuffer += sprintf( pszCurrBuffer, "\t" );

		// Recurse for each of the child types
		bool bHandled2;
		pszCurrBuffer = DumpTypeIndex( pszCurrBuffer, modBase,
			children.ChildId[i], nestingLevel+1,
			offset, bHandled2 );

		// If the child wasn't a UDT, format it appropriately
		if ( !bHandled2 )
		{
			// Get the offset of the child member, relative to its parent
			DWORD dwMemberOffset;
			SymGetTypeInfo( m_hProcess, modBase, children.ChildId[i],
				TI_GET_OFFSET, &dwMemberOffset );

			// Get the real "TypeId" of the child.  We need this for the
			// SymGetTypeInfo( TI_GET_TYPEID ) call below.
			DWORD typeId;
			SymGetTypeInfo( m_hProcess, modBase, children.ChildId[i],
				TI_GET_TYPEID, &typeId );

			// Get the size of the child member
			ULONG64 length;
			SymGetTypeInfo(m_hProcess, modBase, typeId, TI_GET_LENGTH,&length);

			// Calculate the address of the member
			DWORD_PTR dwFinalOffset = offset + dwMemberOffset;

			BasicType basicType = GetBasicType(children.ChildId[i], modBase );

			pszCurrBuffer = FormatOutputValue( pszCurrBuffer, basicType,
				length, (PVOID)dwFinalOffset );

			pszCurrBuffer += sprintf( pszCurrBuffer, "\r\n" );
		}
	}

	bHandled = true;
	return pszCurrBuffer;
}

char * MExceptionReport::FormatOutputValue(   char * pszCurrBuffer,
										  BasicType basicType,
										  DWORD64 length,
										  PVOID pAddress )
{
	// Format appropriately (assuming it's a 1, 2, or 4 bytes (!!!)
	if ( length == 1 )
		pszCurrBuffer += sprintf( pszCurrBuffer, " = %X", *(PBYTE)pAddress );
	else if ( length == 2 )
		pszCurrBuffer += sprintf( pszCurrBuffer, " = %X", *(PWORD)pAddress );
	else if ( length == 4 )
	{
		if ( basicType == btFloat )
		{
			pszCurrBuffer += sprintf(pszCurrBuffer," = %f", *(PFLOAT)pAddress);
		}
		else if ( basicType == btChar )
		{
			std::string_t sAddress = ApiWin::ToStringT(*(PSTR*)pAddress);
			if ( !IsBadStringPtr(sAddress.c_str() , 32) )
			{
				pszCurrBuffer += sprintf( pszCurrBuffer, " = \"%.31s\"",
					(DWORD_PTR)pAddress ); //SongJ *(PDWORD)pAddress );
			}
			else
				pszCurrBuffer += sprintf( pszCurrBuffer, " = %X",
				*(PDWORD)pAddress );
		}
		else
			pszCurrBuffer += sprintf(pszCurrBuffer," = %X", *(PDWORD)pAddress);
	}
	else if ( length == 8 )
	{
		if ( basicType == btFloat )
		{
			pszCurrBuffer += sprintf( pszCurrBuffer, " = %lf",
				*(double *)pAddress );
		}
		else
			pszCurrBuffer += sprintf( pszCurrBuffer, " = %I64X",
			*(DWORD64*)pAddress );
	}

	return pszCurrBuffer;
}

BasicType
MExceptionReport::GetBasicType( DWORD typeIndex, DWORD64 modBase )
{
	BasicType basicType;
	if ( SymGetTypeInfo( m_hProcess, modBase, typeIndex,
		TI_GET_BASETYPE, &basicType ) )
	{
		return basicType;
	}

	// Get the real "TypeId" of the child.  We need this for the
	// SymGetTypeInfo( TI_GET_TYPEID ) call below.
	DWORD typeId;
	if (SymGetTypeInfo(m_hProcess,modBase, typeIndex, TI_GET_TYPEID, &typeId))
	{
		if ( SymGetTypeInfo( m_hProcess, modBase, typeId, TI_GET_BASETYPE,
			&basicType ) )
		{
			return basicType;
		}
	}

	return btNoType;
}

//============================================================================
// Helper function that writes to the report file, and allows the user to use
// printf style formating
//============================================================================
int __cdecl MExceptionReport::_tprintf(const TCHAR * format, ...)
{
	TCHAR szBuff[1024];
	int retValue;
	DWORD cbWritten;
	va_list argptr;

	va_start( argptr, format );

	std::string_t sFormat = format;

	//����Unicode�ַ���
#if MACRO_TARGET_FONT == MACRO_FONT_ANSI
	retValue = vsprintf( szBuff, sFormat.c_str(), argptr );
#elif  MACRO_TARGET_FONT == MACRO_FONT_UNICODE
	std::string sFormatMulti = ApiWin::ToMulti(sFormat);
	ToolFrame::Replace(sFormatMulti,"%s","%S");
	sFormat = ApiWin::ToWide(sFormatMulti);
	
	retValue = vswprintf( szBuff, sFormat.c_str(), argptr );
#endif
	
	va_end( argptr );

	
	WriteFile(m_hReportFile, szBuff, retValue * sizeof(TCHAR), &cbWritten, 0 );

	return retValue;
}

bool MExceptionReport::SetExceptionContinueSearch( bool bTrue )
{
	m_nException = bTrue ? EXCEPTION_CONTINUE_SEARCH : EXCEPTION_EXECUTE_HANDLER;
	return true;
}

NS_TOOL_FRAME_END
#endif