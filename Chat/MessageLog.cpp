#include "MessageLog.h"


void MessageLog::SetLogComponent(CRichEditUI* edtMsg)
{
	MessageLog::edtLog = edtMsg;
}

void MessageLog::AddLog(LPCTSTR str)
{
	wstring addStr = L"\n";
	wstring txt = str + addStr;
	MessageLog::edtLog->AppendText(txt.c_str());
}