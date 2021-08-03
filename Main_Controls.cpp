#include <windows.h>
#include <windowsx.h>
#include <cwchar>
#include "resource.h"
#include "T_MainWin.h"
#include <strsafe.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndBtnProc(HWND, UINT, WPARAM, LPARAM);
void ErrorExit(LPTSTR lpszFunction);
LPCWSTR WindowName_Extra(LPCWSTR);

//wWinMain
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PWSTR lpCmdLine, int nCmdShow) {

    MSG  msg;
    WNDCLASSW wc = { 0 };
    wc.lpszClassName = L"Parent";
    wc.hInstance = hInstance;
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc = WndProc;
    wc.hCursor = LoadCursor(0, IDC_ARROW);


    RegisterClassW(&wc);
    CreateWindowW(wc.lpszClassName, L"Parent",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 800, 800, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

void ErrorExit(LPTSTR lpszFunction)
{
    LPVOID lpMsgBuffer;
    LPVOID lpDisplayBuffer;
    DWORD dw = GetLastError();

    FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM |
        FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL,
        dw,
        NULL,
        (LPTSTR)&lpMsgBuffer,
        0,
        NULL);

    lpDisplayBuffer = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuffer) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

    StringCchPrintf((LPTSTR)lpDisplayBuffer,
        LocalSize(lpDisplayBuffer) / sizeof(TCHAR),
        TEXT("%s Failed with error %d: %s"),
        lpszFunction, dw, lpMsgBuffer);

    MessageBoxW(0, (LPCTSTR)lpDisplayBuffer, L"Button Last Error?? Maybe it is maybe it isn't!", MB_OK | MB_ICONEXCLAMATION);

    LocalFree(lpMsgBuffer);
    LocalFree(lpDisplayBuffer);
    ExitProcess(dw);

}

LPCWSTR StaticName_Extra(LPCWSTR)
{
    /*I am unsure how to apply multiples of data from different datatypes: system information 
    seems to required very complex datatypes and type casting.*/

    const wchar_t* Anicdotes = L"Basically using this format\n\
    I can write anything i want as long as i want (?)\n\
    and just keep going\n\
    A New Line requires 2 new line marks... \n\
    While more is good \n\
    using the 'backslash n backslash' to end any line it is also very important to \n\
    make sure the code denotes this with a 'backslash n backslash' directly \n\
    after the last line of text via wchar_t* \n\
    white space is imperitive to take into account lol \n\
    So how do i add this as a wchar_t statement in this text format! well - \\n\\ \n\
    \r\
    \r\
    \\r\\ then there is carraige return done \n\
    \r\
    \r\
    \t\ \t\ \t\ \t\ \t\ \t\ \\t\\Tab marker! \n\
    \n\
     ";

    return (LPCWSTR)Anicdotes;
}



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg,
    WPARAM wParam, LPARAM lParam) {

    const wchar_t* update_check = {};
    const wchar_t* winName = (LPCWSTR)update_check;
    HWND hwnd_checkbox{}; // {} is how this variable is initialized
    
    switch (msg) 
    {

    case WM_CREATE:
    {
        CreateWindowW(L"Static", (LPCWSTR)winName,
            WS_CHILD | SS_NOTIFY | WS_VISIBLE | WS_BORDER | SS_LEFT,
            20, 20, 400, 130,
            hwnd, (HMENU)IDR_STATIC_INFO, NULL, NULL);

        /*hwnd_checkbox = */ CreateWindowW(
            L"BUTTON",
            L"OK",
            WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
            620,
            550,
            100,
            50,
            hwnd,
            (HMENU)IDR_CHECKBOX,
            (HINSTANCE)GetWindowLongPtr(0, GWLP_HINSTANCE),
            NULL);

        /*Message below not required, check box automatically sets and unsets the check status but great for changing the check status i.e.
        for user options that may cascade through an array of list entries */
        //SendMessage(hwnd_checkbox, BM_SETCHECK , BST_CHECKED, NULL); 

        break;
    }

    case WM_PAINT:
    {
       
    }

    case WM_LBUTTONDOWN:
    {
        break;
    }
    case WM_LBUTTONUP:
    {
        break;
    }

    case WM_COMMAND:
    {
        switch (LOWORD(wParam)) {
            case IDR_STATIC_INFO:
            {
                MessageBox(0, L"Test: Static Control numbered 'IDR_STATIC_INFO' command noticed!",
                    L"Testing (LOWORD)wParam", MB_OK | MB_ICONASTERISK);
                
                break;
            }
            case IDR_CHECKBOX:
            {
                if (IsDlgButtonChecked(hwnd, IDR_CHECKBOX))
                {
                    update_check = L"\n\ Checked! \n\ ";
                    const wchar_t* winName = (LPCWSTR)update_check;
                    InvalidateRect(hwnd, NULL, FALSE); //Still erases the painted font / window?
                   

                    
                   CreateWindowW(L"Static", (LPCWSTR)winName,
                        WS_CHILD | SS_NOTIFY | WS_VISIBLE | WS_BORDER | SS_LEFT,
                       20, 20, 400, 130,
                        hwnd, (HMENU)IDR_STATIC_INFO, NULL, NULL);

                    RedrawWindow(hwnd, 0, 0,
                        RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_FRAME | RDW_INVALIDATE | RDW_ERASE | RDW_INTERNALPAINT); // RDW_UPDATENOW 
                    UpdateWindow(hwnd);
                  
                }
                else
                {
                    update_check = L"UnChecked!\n\ ";
                    const wchar_t* winName = (LPCWSTR)update_check;
                    InvalidateRect(hwnd, NULL, FALSE); //Still erases the painted font / window?
                    UpdateWindow(hwnd);

                    CreateWindowW(L"Static", (LPCWSTR)winName,
                        WS_CHILD | SS_NOTIFY | WS_VISIBLE | WS_BORDER | SS_LEFT,
                        20, 20, 400, 130,
                        hwnd, (HMENU)IDR_STATIC_INFO, NULL, NULL);
                    
                    RedrawWindow(hwnd, 0, 0,
                        RDW_UPDATENOW | RDW_ALLCHILDREN | RDW_FRAME | RDW_INVALIDATE | RDW_ERASE || RDW_INTERNALPAINT); // RDW_UPDATENOW 

                }
               
                break;
            }
        }
        break;
    }

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}



