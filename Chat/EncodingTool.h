#ifndef ENCODINGTOOL_H
#define ENCODINGTOOL_H

#include <windows.h>

class EncodingTool
{
public:
	// ���ֽڵ����ֽ�
	static CHAR* WideCharToMultiChar(const WCHAR* str);
	// UCS-2��UTF-8
	static CHAR* UnicodeToUTF8(const WCHAR* wideStr);
private:

};


#endif