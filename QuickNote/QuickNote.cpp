// QuickNote.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QuickNote.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_QUICKNOTE, szWindowClass, MAX_LOADSTRING);

	// Main Window
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_QUICKNOTE));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_QUICKNOTE);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	if (!RegisterClassEx(&wcex))
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Register Class failed", L"Error", MB_ICONERROR);
	}

	// Create icon in notification area
	HICON hMainIcon;
	hInst = hInstance;

	hWnd_0 = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		300, 150, 600, 480, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd_0)
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Create main window error", L"Error", MB_ICONERROR);
	}
	ShowWindow(hWnd_0, SW_HIDE);
	UpdateWindow(hWnd_0);

	hMainIcon = LoadIcon(hInstance, (LPCTSTR)MAKEINTRESOURCE(IDI_QUICKNOTE));
	notifyIconData.cbSize = sizeof(NOTIFYICONDATA);
	notifyIconData.hWnd = (HWND)hWnd_0;              //handle of the window which will process this app. messages 
	notifyIconData.uID = IDI_QUICKNOTE;           //ID of the icon that willl appear in the system tray 
	notifyIconData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP; //ORing of all the flags 
	notifyIconData.hIcon = hMainIcon; // handle of the Icon to be displayed, obtained from LoadIcon 
	notifyIconData.uCallbackMessage = WM_SYSICON;
	LoadString(hInstance, IDS_APPTOOLTIP, notifyIconData.szTip, MAX_LOADSTRING);
	lstrcpyW(notifyIconData.szTip, L"Press Window+Z to create new note");
	Shell_NotifyIcon(NIM_ADD, &notifyIconData);
	
	
	//Create View Note window
	WNDCLASSEX wcex_1;
	ZeroMemory(&wcex_1, sizeof(WNDCLASSEX));
	wcex_1.cbClsExtra = NULL;
	wcex_1.cbSize = sizeof(WNDCLASSEX);
	wcex_1.cbWndExtra = NULL;
	wcex_1.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex_1.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex_1.hIcon = NULL;
	wcex_1.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_QUICKNOTE));
	wcex_1.hInstance = hInstance;
	wcex_1.lpfnWndProc = (WNDPROC)WndProc_1;
	wcex_1.lpszClassName = L"window_viewnotes";
	wcex_1.lpszMenuName = NULL;
	wcex_1.style = CS_HREDRAW | CS_VREDRAW;
	if (!RegisterClassEx(&wcex_1))
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Register Class failed", L"Error", MB_ICONERROR);
	}

	hWnd_1 = CreateWindow(wcex_1.lpszClassName, L"View Notes", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		50, 20, 1200, 650, NULL, NULL, hInstance, NULL);
	if (!hWnd_1)
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Create main window error", L"Error", MB_ICONERROR);
	}
	ShowWindow(hWnd_1, SW_HIDE);
	UpdateWindow(hWnd_1);

	//Create View Statistic window
	WNDCLASSEX wcex_2;
	ZeroMemory(&wcex_2, sizeof(WNDCLASSEX));
	wcex_2.cbClsExtra = NULL;
	wcex_2.cbSize = sizeof(WNDCLASSEX);
	wcex_2.cbWndExtra = NULL;
	wcex_2.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wcex_2.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex_2.hIcon = NULL;
	wcex_2.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_QUICKNOTE));
	wcex_2.hInstance = hInstance;
	wcex_2.lpfnWndProc = (WNDPROC)WndProc_2;
	wcex_2.lpszClassName = L"window_viewstatistic";
	wcex_2.lpszMenuName = NULL;
	wcex_2.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcex_2))
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Register Class failed", L"Error", MB_ICONERROR);
	}

	hWnd_2 = CreateWindow(wcex_2.lpszClassName, L"View Statistic", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		100, 50, 1000, 650, NULL, NULL, hInstance, NULL);
	if (!hWnd_2)
	{
		int nResult = GetLastError();
		MessageBox(NULL, L"Create main window error", L"Error", MB_ICONERROR);
	}
	ShowWindow(hWnd_2, SW_HIDE);
	UpdateWindow(hWnd_2);

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_QUICKNOTE));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}

void InitKeyHook(HWND hWnd)
{
	if (hHook != NULL)
		return;
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, NULL, 0);
}

void RemoveHook(HWND hWnd)
{
	if (hHook == NULL)
		return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	}

	if ((GetKeyState(VK_LWIN) & 0x8000) && (GetKeyState('Z') & 0x8000))
	{
		if (Hide_State == true) 
		{
			ShowWindow(hWnd_0, SW_SHOW);
			ShowWindow(hWnd_1, SW_HIDE);
			ShowWindow(hWnd_2, SW_HIDE);
			PostMessage(hWnd_0, WM_SYSCOMMAND, SC_RESTORE, 0);
			Hide_State = false;
		}
		else
		{
			ShowWindow(hWnd_0, SW_HIDE);
			Hide_State = true;
		}
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int Id, Event;
	POINT lpClickPoint;
	switch (message)
	{
	case WM_CREATE:
	{
		InitKeyHook(hWnd);
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&icc);

		HFONT hFont = CreateFont(-15, 0, 0, 0, FW_THIN, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT kFont = CreateFont(-15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT nFont = CreateFont(-25, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HWND hwnd = CreateWindowEx(0, L"STATIC", L"QUICK NOTE", WS_CHILD | WS_VISIBLE | SS_LEFT, 200, 0, 300, 100, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(nFont), TRUE);
		hwnd = CreateWindowEx(0, L"STATIC", L"Note:", WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 50, 100, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		hwnd = CreateWindowEx(0, L"STATIC", L"Tags:", WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 270, 100, 40, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		Note_Textbox = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL, 20, 80, 540, 150, hWnd, NULL, hInst, NULL);
		SendMessage(Note_Textbox, WM_SETFONT, WPARAM(kFont), TRUE);
		Tag_Textbox = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | WS_VSCROLL | WS_HSCROLL, 20, 300, 540, 50, hWnd, NULL, hInst, NULL);
		SendMessage(Tag_Textbox, WM_SETFONT, WPARAM(kFont), TRUE);

		hwnd = CreateWindowEx(0, L"BUTTON", L"Save", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 230, 350, 100, 40, hWnd, (HMENU)IDC_BUTTON1, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(kFont), TRUE);

		CreateDirectory(L"My Notes", NULL);
		CreateDirectory(L"My Tags", NULL);

	}
	case WM_COMMAND:
	{
		Id = LOWORD(wParam);
		Event = HIWORD(wParam);
		switch (Id)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		
		case ID_FILE_VIEWNOTES:
			ShowWindow(hWnd_0, SW_HIDE);
			Hide_State = true;
			ShowWindow(hWnd_1, SW_SHOW);
			PostMessage(hWnd_1, WM_SYSCOMMAND, SC_RESTORE, 0);
			ShowWindow(hWnd_2, SW_HIDE);
			break;
		case ID_FILE_VIEWSTATISTICS:
			ShowWindow(hWnd_0, SW_HIDE);
			Hide_State = true;
			ShowWindow(hWnd_1, SW_HIDE);
			ShowWindow(hWnd_2, SW_SHOW);
			PostMessage(hWnd_2, WM_SYSCOMMAND, SC_RESTORE, 0);
			break;
		case IDC_BUTTON1:
			TCHAR szName[MAX_PATH] = { 0 };
			TCHAR szTime[MAX_PATH] = { 0 };
			SYSTEMTIME st = { 0 };
			::GetLocalTime(&st);
			wsprintf(szName, _T("My Notes\\%d%d%d%d%d.txt"), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			wsprintf(szTime, _T("%d%d%d%d%d.txt"), st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
			if (GetWindowTextLength(Note_Textbox) == 0)
			{
				MessageBox(0, L"Please insert your note.", L"Error", MB_ICONERROR | MB_OK | MB_DEFBUTTON2);
				break;
			}
			else if (GetWindowTextLength(Tag_Textbox) == 0)
			{
				MessageBox(0, L"Please insert your tags", L"Error", MB_ICONERROR | MB_OK | MB_DEFBUTTON2);
				break;
			}

			wofstream f_note;
			WCHAR *bufferNote = new WCHAR[NOTESIZE];
			GetWindowText(Note_Textbox, bufferNote, NOTESIZE);
			const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
			f_note.open(szName, ios::out | ios::app);
			f_note.imbue(utf8_locale);
			f_note << bufferNote << endl;
			f_note.close();

			wofstream f_tag;
			WCHAR *bufferTag = new WCHAR[BUFFERSIZE];
			GetWindowText(Tag_Textbox, bufferTag, BUFFERSIZE);
			f_tag.open(L"My Tags\\Tags.txt", ios::out | ios::app);
			f_tag.imbue(utf8_locale);
			WCHAR* token;
			token = wcstok(bufferTag, L",");
			while (token != NULL)
			{
				f_tag << token << endl << szTime << endl;
				token = wcstok(NULL, L",");
			}
			SetWindowText(Note_Textbox, L"");
			SetWindowText(Tag_Textbox, L"");
			MessageBox(0, L"Saved!", L"Success", MB_ICONINFORMATION | MB_OK | MB_DEFBUTTON2);
			my_tags.my_list.clear();
			LoadListView(Tags_ListView);
			//LoadListView(Tags_ListView);
			//Percent_Chart();
			//Length_Chart();
			break;
		}
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	case WM_SYSICON:
		switch (LOWORD(lParam))
		{
		case WM_RBUTTONDOWN:
			UINT uFlag = MF_BYPOSITION | MF_STRING;
			GetCursorPos(&lpClickPoint);
			hMenu = CreatePopupMenu();
			InsertMenu(hMenu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, IDM_ABOUT, _T("About"));
			InsertMenu(hMenu, 0xFFFFFFFF, MF_SEPARATOR, NULL, NULL);
			InsertMenu(hMenu, 0xFFFFFFFF, uFlag, ID_FILE_VIEWNOTES, _T("View notes")); 
			InsertMenu(hMenu, 0xFFFFFFFF, uFlag, ID_FILE_VIEWSTATISTICS, _T("View statistics")); 
			InsertMenu(hMenu, 0xFFFFFFFF, MF_SEPARATOR, NULL, NULL);
			InsertMenu(hMenu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, IDM_EXIT, _T("Exit"));
			SetForegroundWindow(hWnd);
			TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, lpClickPoint.x, lpClickPoint.y, 0, hWnd, NULL);
			return TRUE;
		}
		break;
	case WM_DESTROY:
	{
		Shell_NotifyIcon(NIM_DELETE, &notifyIconData);
		RemoveHook(hWnd);
		PostQuitMessage(0);
	}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Window Procedure View Notes
LRESULT CALLBACK WndProc_1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CREATE:
	{
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&icc);

		HFONT hFont = CreateFont(-17, 0, 0, 0, FW_REGULAR, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT kFont = CreateFont(-15, 0, 0, 0, FW_REGULAR, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HWND hwnd = CreateWindowEx(0, L"STATIC", L"Tags:", WS_CHILD | WS_VISIBLE | SS_LEFT, 20, 20, 300, 30, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		hwnd = CreateWindowEx(0, L"STATIC", L"Preview:", WS_CHILD | WS_VISIBLE | SS_LEFT, 300, 20, 300, 30, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		hwnd = CreateWindowEx(0, L"STATIC", L"Content:", WS_CHILD | WS_VISIBLE | SS_LEFT, 300, 220, 300, 30, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);

		Tags_ListView = CreateWindowEx(0, WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_SHOWSELALWAYS | LVS_REPORT | ES_AUTOVSCROLL | WS_VSCROLL, 20, 60, 250, 510, hWnd, (HMENU)IDC_LISTVIEW1, hInst, NULL);
		SendMessage(Tags_ListView, WM_SETFONT, WPARAM(kFont), TRUE);
		Preview_ListView = CreateWindowEx(0, WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_SHOWSELALWAYS | LVS_REPORT, 300, 60, 850, 150, hWnd, (HMENU)IDC_LISTVIEW2, hInst, NULL);
		SendMessage(Preview_ListView, WM_SETFONT, WPARAM(kFont), TRUE);
		Content_Textbox = CreateWindowEx(0, L"EDIT", L"", WS_CHILD | WS_VISIBLE | ES_MULTILINE, 300, 250, 850, 320, hWnd, NULL, hInst, NULL);
		SendMessage(Content_Textbox, WM_SETFONT, WPARAM(kFont), TRUE);

		LVCOLUMN lvCol1;
		lvCol1.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol1.fmt = LVCFMT_LEFT;
		lvCol1.cx = 150;
		lvCol1.pszText = L"Tag";
		ListView_InsertColumn(Tags_ListView, 0, &lvCol1);

		LVCOLUMN lvCol2;
		lvCol2.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol2.fmt = LVCFMT_LEFT;
		lvCol2.cx = 100;
		lvCol2.pszText = L"Quantity";
		ListView_InsertColumn(Tags_ListView, 1, &lvCol2);

		LVCOLUMN lvCol3;
		lvCol3.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol3.fmt = LVCFMT_LEFT;
		lvCol3.cx = 200;
		lvCol3.pszText = L"File name";
		ListView_InsertColumn(Preview_ListView, 0, &lvCol3);

		LVCOLUMN lvCol4;
		lvCol4.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol4.fmt = LVCFMT_LEFT;
		lvCol4.cx = 600;
		lvCol4.pszText = L"Preview";
		ListView_InsertColumn(Preview_ListView, 1, &lvCol4);

		LoadListView(Tags_ListView);
	}

	case WM_NOTIFY:
	{
		WCHAR *namebuff = new WCHAR[BUFFERSIZE];
		WCHAR *filenamebuff = new WCHAR[BUFFERSIZE];
		WCHAR *contentbuff = new WCHAR[BUFFERSIZE];
		//Click chon tag o Tags_ListView
		NMHDR* nmhdr = (NMHDR*)lParam;
		if (nmhdr->idFrom == IDC_LISTVIEW1 && nmhdr->code == LVN_ITEMCHANGED)
		{
			LPNMLISTVIEW lpnm = (LPNMLISTVIEW)lParam;
			
			if ((lpnm->uNewState & LVIS_SELECTED) && (lpnm->uChanged & LVIF_STATE))
			{
				WCHAR *buffer = new WCHAR[NOTESIZE];
				WCHAR *tagbuff = new WCHAR[BUFFERSIZE];
				WCHAR *previewbuff = new WCHAR[BUFFERSIZE];
				SetWindowText(Content_Textbox, L"");
				ListView_DeleteAllItems(Preview_ListView);
				int i = ListView_GetNextItem(Tags_ListView, -1, LVNI_SELECTED);
				buffer = my_tags.my_list[i].tags;

				wifstream fi;
				const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
				fi.open(L"My Tags\\Tags.txt", ios::in | ios::app);
				fi.imbue(utf8_locale);
				while (!fi.eof())
				{
					fi.getline(tagbuff, BUFFERSIZE);
					fi.getline(namebuff, BUFFERSIZE);
					
					if (wcscmp(tagbuff, buffer) == 0)
					{
						wsprintf(filenamebuff, L"My Notes\\%s", namebuff);
						Load_Notes(filenamebuff, contentbuff);
						wcsncpy(previewbuff, contentbuff, 50);
						previewbuff[50] = '.';
						previewbuff[51] = '.';
						previewbuff[52] = '.';
						previewbuff[53] = NULL;

						LVITEM item;
						item.mask = LVIF_TEXT;
						item.cchTextMax = 6;
						item.iSubItem = 0;
						item.pszText = namebuff;
						item.iItem = 0;
						ListView_InsertItem(Preview_ListView, &item);
						ListView_SetItemText(Preview_ListView, 0, 1, previewbuff);
					}
				}
				fi.close();
				if (!buffer)
					delete[] buffer;
				if (!tagbuff)
					delete[] tagbuff;
				if (!previewbuff)
					delete[] previewbuff;
			}
		}
		if (nmhdr->idFrom == IDC_LISTVIEW2 && nmhdr->code == LVN_ITEMCHANGED)
		{
			LPNMLISTVIEW pnmv = (LPNMLISTVIEW)lParam;

			if ((pnmv->uChanged & LVIF_STATE) && (pnmv->uNewState & LVIS_SELECTED))
			{
				int i = ListView_GetNextItem(Preview_ListView, -1, LVNI_SELECTED);
				ListView_GetItemText(Preview_ListView, i, 0, namebuff, BUFFERSIZE);
				wsprintf(filenamebuff, L"My Notes\\%s", namebuff);

				Load_Notes(filenamebuff, contentbuff);

				SetWindowText(Content_Textbox, contentbuff);
			}
		}
		if (!namebuff)
			delete[] namebuff;
		if (!filenamebuff)
			delete[] filenamebuff;
		if (!contentbuff)
			delete[] contentbuff;
	}
	break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

//Window Procedure View Statistic 
LRESULT CALLBACK WndProc_2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_CTLCOLORSTATIC:
	{
		for (int i = 0; i < 5; i++)
		{
			tagspercent[i] = 0;
		}
		HDC hdcStatic = (HDC)wParam;
		DWORD CtrlID = GetDlgCtrlID((HWND)lParam);
		if (CtrlID == IDC_COMMENT1)
		{
			SetTextColor(hdcStatic, RGB(255, 0, 0));
		}
		else if (CtrlID == IDC_COMMENT2)
		{
			SetTextColor(hdcStatic, RGB(255, 201, 14));
		}
		else if (CtrlID == IDC_COMMENT3)
		{
			SetTextColor(hdcStatic, RGB(0, 255, 0));
		}
		else if (CtrlID == IDC_COMMENT4)
		{
			SetTextColor(hdcStatic, RGB(0, 0, 255));
		}
		else if (CtrlID == IDC_COMMENT5)
		{
			SetTextColor(hdcStatic, RGB(204, 0, 204));
		}
		SetBkColor(hdcStatic, RGB(240, 240, 240));
		return (INT_PTR)CreateSolidBrush(RGB(240, 240, 240));
	}
	case WM_CREATE:
	{
		INITCOMMONCONTROLSEX icc;
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_WIN95_CLASSES;
		InitCommonControlsEx(&icc);
		HFONT hFont = CreateFont(-17, 0, 0, 0, FW_REGULAR, TRUE, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT mFont = CreateFont(-22, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT kFont = CreateFont(-15, 0, 0, 0, FW_REGULAR, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HFONT nFont = CreateFont(-16, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Segoe UI");
		HWND hwnd = CreateWindowEx(0, L"STATIC", L"Tag list:", WS_CHILD | WS_VISIBLE | SS_LEFT, 600, 20, 300, 30, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(hFont), TRUE);
		
		hwnd = CreateWindowEx(0, L"STATIC", L"TOP 5 TAGS", WS_CHILD | WS_VISIBLE | SS_LEFT, 200, 20, 300, 30, hWnd, NULL, hInst, NULL);
		SendMessage(hwnd, WM_SETFONT, WPARAM(mFont), TRUE);
		Tags_ListView1 = CreateWindowEx(0, WC_LISTVIEW, L"", WS_VISIBLE | WS_CHILD | LVS_SHOWSELALWAYS | LVS_REPORT, 600, 50, 350, 530, hWnd, (HMENU)IDC_LISTVIEW3, hInst, NULL);
		SendMessage(Tags_ListView1, WM_SETFONT, WPARAM(kFont), TRUE);

		Comment1_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 260, 150, 20, hWnd, (HMENU)IDC_COMMENT1, hInst, NULL);
		SendMessage(Comment1_Static, WM_SETFONT, WPARAM(nFont), TRUE);
		Comment2_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 320, 150, 20, hWnd, (HMENU)IDC_COMMENT2, hInst, NULL);
		SendMessage(Comment2_Static, WM_SETFONT, WPARAM(nFont), TRUE);
		Comment3_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 380, 150, 20, hWnd, (HMENU)IDC_COMMENT3, hInst, NULL);
		SendMessage(Comment3_Static, WM_SETFONT, WPARAM(nFont), TRUE);
		Comment4_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 440, 150, 20, hWnd, (HMENU)IDC_COMMENT4, hInst, NULL);
		SendMessage(Comment4_Static, WM_SETFONT, WPARAM(nFont), TRUE);
		Comment5_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 500, 150, 20, hWnd, (HMENU)IDC_COMMENT5, hInst, NULL);
		SendMessage(Comment5_Static, WM_SETFONT, WPARAM(nFont), TRUE);

		Percent1_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 280, 150, 20, hWnd, (HMENU)IDC_PERCENT1, hInst, NULL);
		SendMessage(Percent1_Static, WM_SETFONT, WPARAM(nFont), TRUE);															 
		Percent2_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 340, 150, 20, hWnd, (HMENU)IDC_PERCENT2, hInst, NULL);
		SendMessage(Percent2_Static, WM_SETFONT, WPARAM(nFont), TRUE);															 
		Percent3_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 400, 150, 20, hWnd, (HMENU)IDC_PERCENT3, hInst, NULL);
		SendMessage(Percent3_Static, WM_SETFONT, WPARAM(nFont), TRUE);															
		Percent4_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 460, 150, 20, hWnd, (HMENU)IDC_PERCENT4, hInst, NULL);
		SendMessage(Percent4_Static, WM_SETFONT, WPARAM(nFont), TRUE);															 
		Percent5_Static = CreateWindowEx(0, L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_LEFT, 120, 520, 150, 20, hWnd, (HMENU)IDC_PERCENT5, hInst, NULL);
		SendMessage(Percent5_Static, WM_SETFONT, WPARAM(nFont), TRUE);

		LVCOLUMN lvCol1;
		lvCol1.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol1.fmt = LVCFMT_LEFT;
		lvCol1.cx = 230;
		lvCol1.pszText = L"Tag";
		ListView_InsertColumn(Tags_ListView1, 0, &lvCol1);

		LVCOLUMN lvCol2;
		lvCol2.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
		lvCol2.fmt = LVCFMT_LEFT;
		lvCol2.cx = 150;
		lvCol2.pszText = L"Quantity";
		ListView_InsertColumn(Tags_ListView1, 1, &lvCol2);

		Percent_Chart();
		Length_Chart();
		Create_Color();
		prototypes.push_back(new My_Rectangle);
		Draw_Comment(hWnd, 50, 260, 100, 280);
		Draw_Comment(hWnd, 50, 320, 100, 340);
		Draw_Comment(hWnd, 50, 380, 100, 400);
		Draw_Comment(hWnd, 50, 440, 100, 460);
		Draw_Comment(hWnd, 50, 500, 100, 520);
		
		int k = my_tags.my_list.size();
		if (k <= 5)
		{
			for (int i = 0; i < k; i++)
			{
				Draw_Chart(hWnd, tagslength_a[i], tagslength_b[i]);
			}
		}
		else
		{
			for (int i = 0; i < 5; i++)
			{
				Draw_Chart(hWnd, tagslength_a[i], tagslength_b[i]);
			}
		}
	}
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, CreatePen(PS_NULL, NULL, NULL));
		for (int i = 0; i < shapes.size(); i++)
		{
			int k = i - 5;
			if (i < 5)
			{
				SelectObject(hdc, hbrush[i]);
			}
			else SelectObject(hdc, hbrush[k]);
			shapes[i]->Draw(hdc);
		}
		shapes.clear();
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void Load_Notes(WCHAR *filenamebuff, WCHAR *contentbuff)
{
	wcscpy(contentbuff, L"");
	WCHAR *buffer = new WCHAR[NOTESIZE];
	wifstream fi;
	const locale utf8_locale = locale(locale(), new codecvt_utf8<wchar_t>());
	fi.open(filenamebuff, ios::in | ios::app);
	fi.imbue(utf8_locale);
	while (!fi.eof())
	{
		fi.getline(buffer, NOTESIZE);
		wcscat(contentbuff, buffer);
	}
	fi.close();
}

void LoadListView(HWND hwnd)
{
	ListView_DeleteAllItems(hwnd);
	my_tags.Read_File();
	WCHAR* countbuff = new WCHAR[BUFFERSIZE];
	for (int i = my_tags.my_list.size() - 1; i >= 0; i--)
	{
		swprintf(countbuff, L"%d", my_tags.my_list[i].tagnum);
		LVITEM item;
		item.mask = LVIF_TEXT;
		item.cchTextMax = 6;

		item.iSubItem = 0;
		item.pszText = my_tags.my_list[i].tags;
		item.iItem = 0;
		ListView_InsertItem(hwnd, &item);
		ListView_SetItemText(hwnd, 0, 1, countbuff);
	}
	if (!countbuff)
		delete[] countbuff;
}

void Create_Color()
{
	hbrush[0] = CreateSolidBrush(RGB(255, 0, 0));
	hbrush[1] = CreateSolidBrush(RGB(255, 201, 14));
	hbrush[2] = CreateSolidBrush(RGB(0, 255, 0));
	hbrush[3] = CreateSolidBrush(RGB(0, 0, 255));
	hbrush[4] = CreateSolidBrush(RGB(204, 0, 204));
}

void Draw_Chart(HWND hWnd, int a, int b)
{
	shape = prototypes[0]->Create();
	shape->Set_Data(a, 100, b, 135);
	shapes.push_back(shape);
	InvalidateRect(hWnd, NULL, TRUE);
}

void Draw_Comment(HWND hWnd, int a, int b, int c, int d)
{
	shape = prototypes[0]->Create();
	shape->Set_Data(a, b, c, d);
	shapes.push_back(shape);
	InvalidateRect(hWnd, NULL, TRUE);
}

void Percent_Chart()
{
	int totaltag = 0;
	int k = my_tags.my_list.size();
	if (k <= 5)
	{
		for (int i = 0; i < k; i++)
		{
			totaltag += my_tags.my_list[i].tagnum;
		}
		for (int i = 0; i < k; i++)
		{
			tagspercent[i] = double(my_tags.my_list[i].tagnum * 100) / double(totaltag);
		}
	}
	else
	{
		for (int i = 0; i < 5; i++)
		{
			totaltag += my_tags.my_list[i].tagnum;
		}
		for (int i = 0; i < 5; i++)
		{
			tagspercent[i] = double(my_tags.my_list[i].tagnum * 100) / double(totaltag);
		}
	}
	Set_Color_Text(Comment1_Static, Percent1_Static, 0);
	Set_Color_Text(Comment2_Static, Percent2_Static, 1);
	Set_Color_Text(Comment3_Static, Percent3_Static, 2);
	Set_Color_Text(Comment4_Static, Percent4_Static, 3);
	Set_Color_Text(Comment5_Static, Percent5_Static, 4);
}

void Length_Chart()
{
	tagslength_a[0] = 50;
	for (int i = 0; i < 5; i++)
	{
		tagslength_b[i - 1] = tagslength_a[i - 1] + 5 * tagspercent[i - 1];
		tagslength_a[i] = tagslength_b[i - 1];
	}
	tagslength_b[4] = tagslength_a[4] + 5 * tagspercent[4];
}

void Set_Color_Text(HWND hwnd1, HWND hwnd2, int i)
{
	WCHAR temp[20];
	if (tagspercent[i] != 0.0)
	{
		swprintf_s(temp, L"%f", tagspercent[i]);
		temp[5] = '%';
		temp[6] = NULL;
		SetWindowText(hwnd1, my_tags.my_list[i].tags);
		SetWindowText(hwnd2, temp);
	}
}
