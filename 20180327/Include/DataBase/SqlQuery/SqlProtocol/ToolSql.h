#pragma once
#include "Macro.h"

#ifdef MACRO_LIB_MY_SQL

#include "SqlResults.h"

namespace ToolFrame
{
	template<typename Arg1>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1);
	template<typename Arg1, typename Arg2>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2);
	template<typename Arg1, typename Arg2, typename Arg3>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
	bool GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9, Arg10& tArg10);

	template<typename Arg1>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1);
	template<typename Arg1, typename Arg2>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2);
	template<typename Arg1, typename Arg2, typename Arg3>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9);
	template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
	bool GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9, Arg10& tArg10);
};

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9, Arg10& tArg10)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6, tArg7, tArg8, tArg9, tArg10);
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6, tArg7, tArg8, tArg9);
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6, tArg7, tArg8);
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6, tArg7);
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3, tArg4, tArg5, tArg6);
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3, tArg4, tArg5);
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3, tArg4);
}

template<typename Arg1, typename Arg2, typename Arg3>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2, tArg3);
}

template<typename Arg1, typename Arg2>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1, Arg2& tArg2)
{
	return GetRecordIndex(xRecord, 0, tArg1, tArg2);
}

template<typename Arg1>
bool ToolFrame::GetRecord(const CSqlResults& xRecord, Arg1& tArg1)
{
	return GetRecordIndex(xRecord, 0, tArg1);
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9, Arg10& tArg10)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg4))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg5))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg6))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg7))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg8))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg9))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg10))return false;
	return true;
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8, Arg9& tArg9)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg4))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg5))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg6))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg7))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg8))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg9))return false;
	return true;
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7, Arg8& tArg8)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg4))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg5))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg6))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg7))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg8))return false;
	return true;
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6, Arg7& tArg7)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg4))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg5))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg6))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg7))return false;
	return true;
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5, Arg6& tArg6)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg4))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg5))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg6))return false;
	return true;
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4, typename Arg5>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4, Arg5& tArg5)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg4))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg5))return false;
	return true;
}

template<typename Arg1, typename Arg2, typename Arg3, typename Arg4>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3, Arg4& tArg4)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg4))return false;
	return true;
}

template<typename Arg1, typename Arg2, typename Arg3>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2, Arg3& tArg3)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg3))return false;
	return true;
}

template<typename Arg1, typename Arg2>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1, Arg2& tArg2)
{
	if (xRecord.IsError())return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg1))return false;
	if (!ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart++), tArg2))return false;
	return true;
}

template<typename Arg1>
bool ToolFrame::GetRecordIndex(const CSqlResults& xRecord, int nIndexStart, Arg1& tArg1)
{
	if (xRecord.IsError())return false;
	return ToolFrame::ToValue(xRecord.GetFieldValue(nIndexStart), tArg1);
}

#endif//MACRO_LIB_MY_SQL
