#ifndef MESSAGELOG_H
#define MESSAGELOG_H


#include <iostream>
#include <string>
#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

class MessageLog
{
public:
	static void SetLogComponent(CRichEditUI*);
	static void AddLog(LPCTSTR str);

private:
	static CRichEditUI* edtLog;
};


#endif
