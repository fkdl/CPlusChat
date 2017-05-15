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

CHAR* EncodingTool::UnicodeToUTF8(const WCHAR* wideStr)
{
	char* utf8Str = NULL;
	int charLen = -1;
	charLen = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
	utf8Str = (char*)malloc(charLen);
	WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, utf8Str, charLen, NULL, NULL);
	return utf8Str;
}