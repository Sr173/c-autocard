#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
#include <windows.h>


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <tchar.h>
#include <Commctrl.h>
#include <windowsx.h>
#include <stdlib.h>
#include <Shellapi.h>
#include "vector"


//#include <vector>
#include <stdio.h>

#include "resource.h"
#include "BaseAddr.h"
#include "GlobalData.h"

//#include "QQMusicResource.h"
//#include "RemoteMem.h"
#include "Shlwapi.h"

//#define VM_START
//#define VM_END
#include "C:\Themida\ThemidaSDK\Include\C\ThemidaSDK.h"

#include <Uxtheme.h>
#pragma comment(lib,"UxTheme.lib")

#pragma comment(lib,"Comctl32.lib")

#pragma comment(lib,"Shell32.lib")

#pragma comment(lib,"Shlwapi.lib")



#include "C:\�������ļ�\AES.h"
#ifdef _WIN64
#include "F:\StreamControl\StreamControl\StreamReader.h"
#include "F:\StreamControl\StreamControl\StreamWriter.h"
#pragma comment(lib,"F:\\StreamControl\\x64\\Release\\StreamControl.lib")
#pragma comment(lib,"F:\\��׼AES\\x64\\Release\\StdAes.lib")

#else

#include "C:\�������ļ�\StreamRWer.h"
#pragma comment(lib,"C:\\�������ļ�\\StreamControl.lib")


#pragma comment(lib,"C:\\�������ļ�\\StdAes.lib")
#endif



#define PSAPI_VERSION 1
#include <Psapi.h>
#pragma comment(lib, "Psapi.lib")

// һ�������, windowsx.h���HANDLE_MSG�겻�����ڶԻ���. 
// ��ΪDlgProc����BOOL, ������WndProcs��������LRESULT.
// HANDLE_DLGMSG��������������
#define HANDLE_DLGMSG(hWnd, message, fn)                 \
   case (message): return (SetDlgMsgResult(hWnd, uMsg,     \
   HANDLE_##message((hWnd), (wParam), (lParam), (fn))))



#if defined _M_IX86
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker, "/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif