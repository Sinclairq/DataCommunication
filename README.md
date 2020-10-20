# DataCommunication
A kernelmode driver swapping a .data pointer in the kernel to perform communication between the kernel and usermode.

# Information
DISCLAIMER! This will trigger PG (PatchGuard) on 2004 (untested on others.) If you try to use this raw project your system will crash after a while.

The driver will take care of the hook on the .data function residing in ntoskrnl.exe, so the driver must be loaded first.
Once the driver is loaded, run the program with the correct arguments to see if the communication has been setup correctly.

# Features
- Pattern Scanner
- Fast communication to perform r/w operations and else.
- Get the base of any process relative to it's process ID.
- etc...

# Usage

![Example](https://i.imgur.com/BPhGvSk.png)
This PoC has only been tested on 2004, but may work on 1909, and 1903.
