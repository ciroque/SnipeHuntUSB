#include <windows.h>
#include <shellapi.h>
#include "resource.h"

#define WM_TRAY (WM_APP + 1)

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_TRAY && lParam == WM_RBUTTONUP) {
        POINT pt;
        GetCursorPos(&pt);
        HMENU hMenu = LoadMenu(GetModuleHandle(NULL), MAKEINTRESOURCE(IDR_MENU));
        HMENU hPopup = GetSubMenu(hMenu, 0);
        SetForegroundWindow(hwnd);
        TrackPopupMenu(hPopup, TPM_RIGHTALIGN | TPM_BOTTOMALIGN, pt.x, pt.y, 0, hwnd, NULL);
        DestroyMenu(hMenu);
    }
    else if (msg == WM_COMMAND) {
        switch (LOWORD(wParam)) {
        case IDM_SHOW_DEVICES:
        case IDM_VIEW_LOGS:
        {
            wchar_t title[16], message[32];
            LoadStringW(GetModuleHandle(NULL), IDS_501, title, sizeof(title) / sizeof(wchar_t));
            LoadStringW(GetModuleHandle(NULL), IDS_NOT_IMPLEMENTED, message, sizeof(message) / sizeof(wchar_t));
            MessageBoxW(hwnd, message, title, MB_ICONWARNING);
        }
        break;
        case IDM_EXIT:
            PostQuitMessage(0);
            break;
        }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow) {
	LPCWSTR WINDOW_CLASS_NAME = L"SnipeHuntUSBTray";

    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = WINDOW_CLASS_NAME;
    RegisterClass(&wc);

    wchar_t title[32];
    LoadStringW(hInstance, IDS_WINDOW_TITLE, title, sizeof(title) / sizeof(wchar_t));
    HWND hwnd = CreateWindow(WINDOW_CLASS_NAME, title, WS_OVERLAPPEDWINDOW,
        0, 0, 0, 0, NULL, NULL, hInstance, NULL);

    NOTIFYICONDATA nid = { sizeof(NOTIFYICONDATA) };
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAY;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    LoadStringW(hInstance, IDS_TRAY_TOOLTIP, nid.szTip, sizeof(nid.szTip) / sizeof(wchar_t));
    Shell_NotifyIcon(NIM_ADD, &nid);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    Shell_NotifyIcon(NIM_DELETE, &nid);
    return 0;
}