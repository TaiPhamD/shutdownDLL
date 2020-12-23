// shutdownDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

extern "C" {
	__declspec(dllexport) bool MySystemShutdown() {
        // Get the process token
        HANDLE hToken;
        OpenProcessToken(GetCurrentProcess(),
                            TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY,
                            &hToken);

        // Build a token privilege request object for shutdown
        TOKEN_PRIVILEGES tk;
        tk.PrivilegeCount = 1;
        tk.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        LookupPrivilegeValue(NULL, TEXT("SeShutdownPrivilege"),
                                &tk.Privileges[0].Luid);

        // Adjust privileges
        AdjustTokenPrivileges(hToken, FALSE, &tk, 0, NULL, 0);

        // Go ahead and shut down
        InitiateSystemShutdownEx(NULL, NULL, 0, FALSE, FALSE, 0);
		//shutdown was successful
		return TRUE;
	}
}