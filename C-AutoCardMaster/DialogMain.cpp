#include "stdafx.h"
#include "main.h"
#include "game.h"

BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
void Dlg_OnClose(HWND hwnd);
void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void Dlg_OnHotKey(HWND hwnd, int idHotKey, UINT fuModifiers, UINT vk);
void Dlg_OnNotify(HWND hwnd, int id, NMHDR* pnmhdr);
void Dlg_OnPaint(HWND hwnd/*, int id, HWND hwndCtl, UINT codeNotify*/);

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {
		HANDLE_DLGMSG(hwndDlg, WM_INITDIALOG, Dlg_OnInitDialog);
		HANDLE_DLGMSG(hwndDlg, WM_CLOSE, Dlg_OnClose);
		HANDLE_DLGMSG(hwndDlg, WM_COMMAND, Dlg_OnCommand);
		HANDLE_DLGMSG(hwndDlg, WM_HOTKEY, Dlg_OnHotKey);
		HANDLE_DLGMSG(hwndDlg, WM_PAINT, Dlg_OnPaint);

		////HANDLE_DLGMSG(hwndDlg, WM_MEASUREITEM, Dlg_OnMeasureItem);
		//HANDLE_DLGMSG(hwndDlg, WM_CTLCOLORSTATIC, Dlg_OnCtlColor);
	case WM_NOTIFY:
		HANDLE_WM_NOTIFY(hwndDlg, wParam, lParam, Dlg_OnNotify);
		return TRUE;
	}
	return FALSE;
}


BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT1);
	Edit_SetText(hEdit, L"E");
	hEdit = GetDlgItem(hwnd, IDC_EDIT2);
	Edit_SetText(hEdit, L"W");
	hEdit = GetDlgItem(hwnd, IDC_EDIT3);
	Edit_SetText(hEdit, L"A");


	gMainHwnd = hwnd;

	Button_SetCheck(GetDlgItem(gMainHwnd, IDC_CHECK2), true);
	Button_SetCheck(GetDlgItem(gMainHwnd, IDC_CHECK3), true);


	EnableThemeDialogTexture(hwnd, ETDT_USETABTEXTURE);
	SetTimer(gMainHwnd, 0x1000, 1000, mainTimer);
	srand(GetTickCount());
	return TRUE;
}

void Dlg_OnClose(HWND hwnd) {
	EndDialog(hwnd, 0);
	TerminateProcess((HANDLE)-1, 0);
}
void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {

}
void Dlg_OnHotKey(HWND hwnd, int idHotKey, UINT fuModifiers, UINT vk) {
	if (idHotKey == VK_PRIOR) {

	}
	else if (idHotKey == VK_NEXT) {
		float data = gMrw->readFloat(gMrw->readInt32(base_game, 1, 0xC) + 0x244);
		data += 100;
		gMrw->writeFloat(gMrw->readInt32(base_game, 1, 0xC) + 0x244, data);
	}

}
void Dlg_OnNotify(HWND hwnd, int id, NMHDR* pnmhdr) {

}

void Dlg_OnPaint(HWND hwnd/*hwnd, int id, HWND hwndCtl, UINT codeNotify*/) {
	PAINTSTRUCT ps = { '\0' };

	HDC hDc = BeginPaint(hwnd, &ps);

	//����λͼ��Դ  
	HBITMAP hBmp = LoadBitmap(gHandleInstance, MAKEINTRESOURCE(IDB_BITMAP1));

	//���λͼ����Ϣ  
	BITMAP bmpInfo = { '\0' };
	GetObject(hBmp, sizeof(bmpInfo), &bmpInfo);

	//����λͼ��DC.һ����ָ����hDc��ƥ���DC��DC�а�������Ϣһ�£�  
	HDC hBmpDC = CreateCompatibleDC(hDc);

	//��λͼ����hBmpDc  
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hBmpDC, hBmp);

	/*����λͼ
	* BOOL BitBlt(
	*   HDC hdcDest,//���Ƶ�Ŀ��DC���
	���� *   int nXDest,//���Ƶ�Ŀ������x����
	   ���� *   int nYDest,//���Ƶ�Ŀ������Y����
		  ���� *   int nWidth,//���Ƶ�Ŀ�Ŀ�
			 ���� *   int nHeight,//���Ƶ�Ŀ�ĸ�
				���� *   HDC hdcSrc,//��Ҫ���Ƶ�DC���
				   ���� *   int nXSrc,//��Ҫ���Ƶ�ԭͼ����ʼX����
					  ���� *   int nYSrc,//��Ҫ���Ƶ�ԭͼ����ʼY����
						 ���� *   DWORD dwRop)��//��ͼ�ķ�ʽ
							*/
	BitBlt(hDc, 0, 0, 500, 500, hBmpDC, 0, 0, SRCCOPY);

	/*λͼ�����캯��
	*/
	//StretchBlt(hDc, 200, 200, 200, 200, hBmpDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	//ȡ��λͼ  
	SelectObject(hBmpDC, hOldBmp);

	//ˢ��DC  
	DeleteDC(hBmpDC);

	//ɾ��λͼ  
	DeleteObject(hBmp);

	EndPaint(hwnd, &ps);
}