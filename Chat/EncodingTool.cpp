#include "EncodingTool.h"

CHAR* EncodingTool::WideCharToMultiChar(const WCHAR* str)
{
	size_t len = wcslen(str) + 1;
	size_t converted = 0;
	CHAR* CStr;
	CStr = (char*)malloc(len * sizeof(char));
	wcstombs_s(&converted, CStr, len, str, _TRUNCATE);
	return CStr;
}