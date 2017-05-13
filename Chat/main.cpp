// main.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ChatClient.h"

// ����ʵ������Ϣ��Ӧ����
class CFrameWindowWnd : public CWindowWnd, public INotifyUI
{
public:
	CFrameWindowWnd() { };
	LPCTSTR GetWindowClassName() const { return _T("UIMainFrame"); };
	UINT GetClassStyle() const { return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; };
	void OnFinalMessage(HWND /*hWnd*/) { delete this; };

	CPaintManagerUI m_pm;
	CRichEditUI* edtMsg;

	void Notify(TNotifyUI& msg)
	{
		if (msg.sType == _T("click")) {
			if (msg.pSender->GetName() == _T("btnConn")) {
				CRichEditUI* edtAddr = static_cast<CRichEditUI*>(m_pm.FindControl(_T("edtAddr")));
				CRichEditUI* edtPort = static_cast<CRichEditUI*>(m_pm.FindControl(_T("edtPort")));
				LPCTSTR addr = edtAddr->GetText();
				if (!this->IsIPv4Addr(addr))
				{
					MessageBox(NULL, _T("����IPv4��ַ"), _T("��ʾ"), MB_OK);
					return;
				}
				LPCTSTR portStr = edtPort->GetText();
				if (!this->IsDigitalStr(portStr)) {
					MessageBox(NULL, _T("�˿ڲ�������"), _T("��ʾ"), MB_OK);
					return;
				}
				int port = atoi(portStr);
				chatClient->Connect(addr, port);
			}
		}
	}



	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		if (uMsg == WM_CREATE) {
			m_pm.Init(m_hWnd);
			CDialogBuilder builder;
			CControlUI* pRoot = builder.Create(_T("skin/MainSkin.xml"), (UINT)0, NULL, &m_pm);
			ASSERT(pRoot && "Failed to parse XML");
			m_pm.AttachDialog(pRoot);
			m_pm.AddNotifier(this);
			return 0;
		}
		else if (uMsg == WM_DESTROY) {
			::PostQuitMessage(0);
		}
		LRESULT lRes = 0;
		if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}

private:
	// ��ȡ��ʾMessage��Edit�ؼ�
	CRichEditUI* GetEdtMsg() {
		if (edtMsg == NULL) {
			this->edtMsg = static_cast<CRichEditUI*>(m_pm.FindControl(_T("edtMsg")));
		}
		return this->edtMsg;
	};
	// �ж��Ƿ�Ϊ�����ַ���
	bool IsDigitalStr(LPCTSTR str) {
		return regex_match(str, regex("^[0-9]+$"));
	}
	// �ж��Ƿ�ΪIPv4��ַ
	bool IsIPv4Addr(LPCTSTR str)
	{
		return regex_match(str, regex("^([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.([1-9]?[0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$"));
	}
	ChatClient* chatClient = new ChatClient();

};


// ������ڼ�Duilib��ʼ������
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());

	CFrameWindowWnd* pFrame = new CFrameWindowWnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("����������ͻ���"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pFrame->ShowWindow(true);
	CPaintManagerUI::MessageLoop();

	return 0;
}
