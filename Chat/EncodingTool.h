#ifndef ENCODINGTOOL_H
#define ENCODINGTOOL_H

#include <windows.h>

class EncodingTool
{
public:
	// 宽字节到多字节
	static CHAR* WideCharToMultiChar(const WCHAR* str);
	// UCS-2到UTF-8
	static CHAR* UnicodeToUTF8(const WCHAR* wideStr);
private:

};


#endif