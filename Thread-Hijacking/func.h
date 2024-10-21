#pragma once
#include<windows.h>
#include<stdio.h>

BOOL ThreadHijack(IN HANDLE hThread, IN PBYTE pShell, IN SIZE_T sShellSize);
VOID Myfunc();
VOID Decrypt(IN PBYTE pShell);