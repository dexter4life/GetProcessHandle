#include <Windows.h>
#include <tlhelp32.h>

HANDLE GetProcess(DWORD dwPID)
{
	PROCESSENTRY32 proc32;
	HANDLE hProcessSnap;

	// Take a snapshot of all modules in the specified process.
	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return(NULL);
	}
	proc32.dwSize = sizeof(PROCESSENTRY32);

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if (!Process32First(hProcessSnap, &proc32))
	{
		CloseHandle(hProcessSnap);           // clean the snapshot object
		return(FALSE);
	}

	// Now walk the module list of the process,
	// and display information about each module
	do
	{
		if (dwPID == proc32.th32ProcessID) {
			//return the process handle ( close immediately the job is done)
			return OpenProcess(PROCESS_ALL_ACCESS | PROCESS_SET_INFORMATION, TRUE, proc32.th32ProcessID);
		}
	} while (Process32Next(hProcessSnap, &proc32));

	CloseHandle(hProcessSnap);
}
