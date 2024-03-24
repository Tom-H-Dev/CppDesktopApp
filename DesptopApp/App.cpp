#include <windows.h>

int WINAPI WinMin(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    MessageBox(NULL, "HELLO", "My first GUI", MB_OK);
    return 0;
}