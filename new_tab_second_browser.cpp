#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <shellapi.h>

void openNewTab()
{
    INPUT inputs[4] = {};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 'T';
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = 'T';
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].type = INPUT_KEYBOARD;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    SendInput(4, inputs, sizeof(INPUT));
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char windowTitle[256];
    GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
    if (strstr(windowTitle, "Brave"))
    {
        HWND *pBraveWindows = reinterpret_cast<HWND *>(lParam);
        if (pBraveWindows[0] == NULL)
        {
            pBraveWindows[0] = hwnd; // Store the first window handle
        }
        else if (pBraveWindows[1] == NULL)
        {
            pBraveWindows[1] = hwnd; // Store the second window handle and stop enumeration
            return FALSE;
        }
    }
    return TRUE; // Continue enumerating windows
}

void activateBraveBrowserWindow()
{
    HWND braveWindows[2] = {NULL, NULL};
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&braveWindows));

    if (braveWindows[1])
    {
        // If there are two windows, just activate the second one
        ShowWindow(braveWindows[1], SW_MAXIMIZE);
        SetForegroundWindow(braveWindows[1]);
        openNewTab(); // open a new tab in the second window
    }
    else if (braveWindows[0])
    {
        // If there's only one window, activate it and open a new tab
        ShowWindow(braveWindows[0], SW_MAXIMIZE);
        SetForegroundWindow(braveWindows[0]);
        openNewTab(); // open a new tab in the first window
    }
    else
    {
        // If there's no Brave window, just display a message
        std::cout << "Brave browser not found." << std::endl;
    }
}

int main()
{
    activateBraveBrowserWindow();
    return 0;
}
