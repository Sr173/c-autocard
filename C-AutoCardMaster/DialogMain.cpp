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

	//加载位图资源  
	HBITMAP hBmp = LoadBitmap(gHandleInstance, MAKEINTRESOURCE(IDB_BITMAP1));

	//获得位图的信息  
	BITMAP bmpInfo = { '\0' };
	GetObject(hBmp, sizeof(bmpInfo), &bmpInfo);

	//创建位图的DC.一个和指定的hDc相匹配的DC（DC中包含的信息一致）  
	HDC hBmpDC = CreateCompatibleDC(hDc);

	//将位图放入hBmpDc  
	HBITMAP hOldBmp = (HBITMAP)SelectObject(hBmpDC, hBmp);

	/*绘制位图
	* BOOL BitBlt(
	*   HDC hdcDest,//绘制的目的DC句柄
	　　 *   int nXDest,//绘制的目的左上x坐标
	   　　 *   int nYDest,//绘制的目的左上Y坐标
		  　　 *   int nWidth,//绘制的目的宽
			 　　 *   int nHeight,//绘制的目的高
				　　 *   HDC hdcSrc,//需要绘制的DC句柄
				   　　 *   int nXSrc,//需要绘制的原图的起始X坐标
					  　　 *   int nYSrc,//需要绘制的原图的起始Y坐标
						 　　 *   DWORD dwRop)；//绘图的方式
							*/
	BitBlt(hDc, 0, 0, 500, 500, hBmpDC, 0, 0, SRCCOPY);

	/*位图的拉伸函数
	*/
	//StretchBlt(hDc, 200, 200, 200, 200, hBmpDC, 0, 0, bmpInfo.bmWidth, bmpInfo.bmHeight, SRCCOPY);

	//取出位图  
	SelectObject(hBmpDC, hOldBmp);

	//刷出DC  
	DeleteDC(hBmpDC);

	//删除位图  
	DeleteObject(hBmp);

	EndPaint(hwnd, &ps);
}