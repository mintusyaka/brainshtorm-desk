#include <iostream>
#include <Windows.h>

int main(void) {

	std::cout << "- SERVER\n\n\n";

	HANDLE hFileMap;
	BOOL bResult;
	PCHAR lpBuffer = NULL;
	char Buffer[1024] = "some text!\n\n";
	size_t szBuffer = sizeof(Buffer);

	hFileMap = CreateFileMapping(
		INVALID_HANDLE_VALUE,
		NULL,
		PAGE_READWRITE,
		0,
		256,
		L"fileMap2"
	);

	if (!hFileMap) {
		std::cout << "Error occured: " << GetLastError() << "\n";
		return 1;
	}

	lpBuffer = (PCHAR)MapViewOfFile(
		hFileMap,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		256
	);

	if (!lpBuffer) {
		std::cout << "Error occured: " << GetLastError() << "\n";
		return 1;
	}

	CopyMemory(lpBuffer, Buffer, szBuffer);

	Sleep(5000);

	std::cout << lpBuffer << "\n";

	bResult = UnmapViewOfFile(lpBuffer);

	if(!bResult) {
		std::cout << "Error occured: " << GetLastError() << "\n";
		return 1;
	}

	return 0;
}