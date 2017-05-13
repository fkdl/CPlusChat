#ifndef MESSAGELOG_H
#define MESSAGELOG_H


#include <iostream>
#include <string>
#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

class MessageLog
{
public:
	MessageLog(CRichEditUI* edtMsg);
	void AddLog(LPCTSTR str);

private:
	CRichEditUI* edtMsg;
};

MessageLog::MessageLog(CRichEditUI* edtMsg)
{
	this->edtMsg = edtMsg;
}

void MessageLog::AddLog(LPCTSTR str)
{
	string txt = str + string("\n");
	this->edtMsg->AppendText(txt.c_str());
}


#endif
