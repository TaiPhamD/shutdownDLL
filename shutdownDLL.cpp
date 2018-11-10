// shutdownDLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

extern "C" {
	__declspec(dllexport) bool MySystemShutdown() {
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;

		// Get a token for this process. 

		if (!OpenProcessToken(GetCurrentProcess(),
			TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
			return(FALSE);

		// Get the LUID for the shutdown privilege. 

		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,
			&tkp.Privileges[0].Luid);

		tkp.PrivilegeCount = 1;  // one privilege to set    
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		// Get the shutdown privilege for this process. 

		AdjustTokenPrivileges(hToken, FALSE, &tkp, 0,
			(PTOKEN_PRIVILEGES)NULL, 0);

		if (GetLastError() != ERROR_SUCCESS)
			return FALSE;

		// Shut down the system and force all applications to close. 

		if (!ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE,
			SHTDN_REASON_MAJOR_OPERATINGSYSTEM |
			SHTDN_REASON_MINOR_UPGRADE |
			SHTDN_REASON_FLAG_PLANNED))
			return FALSE;

		//shutdown was successful
		return TRUE;
	}
}