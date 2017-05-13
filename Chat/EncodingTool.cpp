#include "EncodingTool.h"

CHAR* EncodingTool::WideCharToMultiChar(const WCHAR* str)
{
	int bufSize = WideCharToMultiByte(CP_ACP, NULL, str, -1, NULL, 0, NULL, FALSE);
	return new char[bufSize];
}