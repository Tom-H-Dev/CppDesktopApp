#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

HMENU hMenu;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    WNDCLASSW wc = {0};

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"My Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100, 600, 500, 
                  NULL, NULL, NULL, NULL);
    MSG msg = {0};

    while(GetMessage(&msg, NULL, NULL, NULL)  )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg)
    {   
        case WM_COMMAND:

            switch (wp)
            {
                case FILE_MENU_EXIT:
                    DestroyWindow(hWnd);
                    return 0;
                case FILE_MENU_NEW:
                    MessageBeep(MB_ICONINFORMATION);
                    return 0;
            }


            return 0;
        case WM_CREATE:
            AddMenus(hWnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcW(hWnd, msg, wp,lp);
    }
}

void AddMenus(HWND hWnd)
{
    hMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hSubMenu = CreateMenu();

    AppendMenu(hSubMenu, MF_STRING, NULL, "SubMenu Item");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");

    SetMenu(hWnd, hMenu);
}