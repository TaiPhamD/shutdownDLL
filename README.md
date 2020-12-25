# shutdownDLL
A DLL library to provide C interface for shutting down and restarting a windows PC. The restart mode could also control the UEFI boot order ID although it's currently hard coded to switch between 0x0000 and 0x0080. This code should be updated to parametize the BootOrder ID in the future.
