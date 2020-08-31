#include "mainwindow.h"
#include <QApplication>
#include <tchar.h>
#include <windows.h>
#include "mainwindow.h"
#include <QObject>
#include "QtDebug"


DWORD  lastTime;
BOOL lastIsRight = FALSE;
BOOL isHiden = FALSE; //定义为全局变量，每次点击保证重新载入值
LRESULT CALLBACK LowLevelMouseProc(
        int nCode,
        WPARAM wParam,
        LPARAM lParam
        )
{

    typedef void (WINAPI *PSWITCHTOTHISWINDOW) (HWND, BOOL);
    PSWITCHTOTHISWINDOW SwitchToThisWindow;
    HMODULE hUser32 = GetModuleHandle(_T("user32"));
    //载入窗口前置函数
    SwitchToThisWindow = (PSWITCHTOTHISWINDOW)GetProcAddress(hUser32, "SwitchToThisWindow");
    HWND hwnd = FindWindow(_T("Progman"), NULL);
    hwnd = FindWindowEx(hwnd, NULL, _T("SHELLDLL_DefView"), NULL);
    hwnd = FindWindowEx(hwnd, NULL, _T("SysListView32"), NULL);
    //桌面句柄查找
    if (hwnd != NULL) {


        if (nCode >= 0)
        {

            if (wParam == WM_RBUTTONUP)
            {

                if (!lastIsRight)
                {
                    lastTime = ::GetTickCount();
                    lastIsRight = TRUE;
                }
                else
                {
                    DWORD  nowTime = ::GetTickCount();
                    if (nowTime - lastTime < 350)//时间间隔为350ms
                    {
                        if (!isHiden) { ShowWindow(hwnd, SW_HIDE); isHiden = TRUE; }
                        else { ShowWindow(hwnd, SW_SHOW); isHiden = FALSE; }
                        lastIsRight = FALSE;
                    }
                    else
                        lastTime = nowTime;
                }

            }
        }
    }
    return CallNextHookEx(0, nCode, wParam, lParam);
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;

    w.gethook(LowLevelMouseProc);
    //    MSG msg;
    //    SetWindowsHookExW(WH_MOUSE_LL, LowLevelMouseProc, GetModuleHandleW(0), 0);
    //    while (GetMessageW(&msg, 0, 0, 0))DispatchMessageW(&msg);





    return a.exec();
}

