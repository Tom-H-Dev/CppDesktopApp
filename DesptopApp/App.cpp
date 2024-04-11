#include <windows.h>

#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define CHANGE_TITLE 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);
void AddControls(HWND);

HMENU hMenu;

HWND hEdit;

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

    CreateWindowW(L"myWindowClass", L"My Application", WS_OVERLAPPEDWINDOW | WS_VISIBLE,100,100, 1200, 700, 
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
                case CHANGE_TITLE:
                    wchar_t text[100];
                    GetWindowTextW(hEdit, text, 100);
                    SetWindowTextW(hWnd, text);
                    return 0;
            }


            return 0;
        case WM_CREATE:
            AddMenus(hWnd);
            AddControls(hWnd);
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

    AppendMenu(hSubMenu, MF_STRING, CHANGE_TITLE, "Change Title");

    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_NEW, "New");
    AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)hSubMenu, "Open SubMenu");
    AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
    AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Quit");

    AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
    AppendMenu(hMenu, MF_STRING, NULL, "Help");

    SetMenu(hWnd, hMenu);
}

//Add items to the screen
void AddControls(HWND hWnd)
{
    CreateWindowW(L"static", L"Enter Text Here :", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 50,50, 100, 50, hWnd, NULL, NULL, NULL);
    hEdit = CreateWindowW(L"Edit", L"...", WS_VISIBLE | WS_CHILD | WS_BORDER| ES_MULTILINE | ES_AUTOVSCROLL, 50, 110, 100, 50, hWnd, NULL, NULL, NULL);
}