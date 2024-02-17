#include <iostream>
#include <windows.h>
#include <winuser.h>

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
    if (strstr(windowTitle, "Brave")) // Modify the condition as needed
    {
        *reinterpret_cast<HWND *>(lParam) = hwnd;
        return FALSE; // Stop enumerating windows
    }
    return TRUE; // Continue enumerating windows
}

void activateBraveBrowserWindow()
{
    HWND braveWindow = NULL;
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&braveWindow));

    if (braveWindow)
    {
        ShowWindow(braveWindow, SW_MAXIMIZE);
        SetForegroundWindow(braveWindow);
    }
    else
    {
        std::cout << "Brave browser not found" << std::endl;
    }
}

int main()
{
    activateBraveBrowserWindow();
    openNewTab();

    return 0;
}
