#include "SqlResults.h"

#include "ToolFrame.h"


#ifdef MACRO_LIB_MY_SQL

NS_TOOL_FRAME_BEGIN

CSqlResults::CSqlResults()
{
	_pResults = nullptr;
	_nError = ERR_SQL_SUCCEED;

	_uResultIndex = 0;
	_uRecordIndex = 0;
}

CSqlResults::~CSqlResults()
{
}

bool CSqlResults::SetResults(const SqlResults* pResults)
{
	_pResults = pResults;
	return true;
}

bool CSqlResults::SetError(int nError)
{
	_nError = nError;
	return true;
}

bool CSqlResults::IsError() const
{
	return ERR_SQL_SUCCEED != _nError;
}

int CSqlResults::GetError() const
{
	return _nError;
}

const SqlResult* CSqlResults::FindResult(uint uResult) const
{
	if (!_pResults)return nullptr;
	return ToolFrame::GetValuePtrByIndex(*_pResults, uResult);
}

const SqlRecord* CSqlResults::FindRecord(uint uResult, uint uRecord) const
{
	if (!_pResults)return nullptr;

	SqlResult* pResult = ToolFrame::GetValuePtrByIndex(*_pResults, uResult);
	if (!pResult)return nullptr;

	return ToolFrame::GetValuePtrByIndex(*pResult, uRecord);
}

const SqlField* CSqlResults::FindField(uint uResult, uint uRecord, uint uField) const
{
	if (!_pResults)return nullptr;

	SqlResult* pResult = ToolFrame::GetValuePtrByIndex(*_pResults, uResult);
	if (!pResult)return nullptr;

	SqlRecord* pRecord = ToolFrame::GetValuePtrByIndex(*pResult, uRecord);
	if (!pRecord)return nullptr;

	return ToolFrame::GetValuePtrByIndex(*pRecord, uField);
}

size_t CSqlResults::GetFieldLength(uint uField) const
{
	const SqlField* pField = FindFieldCur(uField);
	if (!pField)return 0;
	
	return (*pField)->GetLength();
}

const char* CSqlResults::GetFieldValue(uint uField) const
{
	const SqlField* pField = FindFieldCur(uField);
	if (!pField)return 0;

	return (*pField)->GetBuffer();
}

const SqlResult* CSqlResults::FindResultCur() const
{
	return FindResult(_uResultIndex);
}

const SqlRecord* CSqlResults::FindRecordCur() const
{
	return FindRecord(_uResultIndex,_uRecordIndex);
}

const SqlField* CSqlResults::FindFieldCur(uint uField) const
{
	return FindField(_uResultIndex, _uRecordIndex, uField);
}

bool CSqlResults::ResetResults()
{
	_uResultIndex = 0;
	_uRecordIndex = 0;
	return true;
}

bool CSqlResults::FirstResult()
{
	_uResultIndex = 0;
	return !!FindResultCur();
}

size_t CSqlResults::GetFieldCount() const
{
	const SqlRecord* pRecord = FindRecordCur();
	if (!pRecord)return false;

	return pRecord->size();
}

size_t CSqlResults::GetRecordCount() const
{
	const SqlResult* pResult = FindResultCur();
	if (!pResult)return false;

	return pResult->size();
}

bool CSqlResults::IsRecordEmpty() const
{
	const SqlResult* pResult = FindResultCur();
	if (!pResult)return true;

	return pResult->empty();
}

bool CSqlResults::IsHasResult() const
{
	return !IsResultEmpty();
}

bool CSqlResults::IsResultEmpty() const
{
	if (!_pResults)return false;
	return _pResults->empty();
}

bool CSqlResults::IsHasRecord() const
{
	return !IsRecordEmpty();
}

size_t CSqlResults::GetResultCount() const
{
	if (!_pResults)return 0;
	return _pResults->size();
}

bool CSqlResults::NextResult()
{
	++_uResultIndex;
	_uRecordIndex = 0;

	return !!FindResultCur();
}

bool CSqlResults::FirstRecord()
{
	_uRecordIndex = 0;
	return !!FindRecordCur();
}

bool CSqlResults::NextRecord()
{
	++_uRecordIndex;
	
	return !!FindRecordCur();
}

NS_TOOL_FRAME_END

#endif
