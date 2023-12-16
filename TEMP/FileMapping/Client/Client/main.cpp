#include <iostream>
#include <Windows.h>

int main(void) {

	std::cout << "- CLIENT\n\n\n";

	HANDLE hFileMap;
	BOOL bResult;
	PCHAR lpBuffer = NULL;


	hFileMap = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,
		FALSE,
		L"fileMap2"
	);

	if(!hFileMap) {
		std::cout << "Error occured: " << GetLastError() << "\n";
		return 1;
	}
	std::cout << "- Success opening File Mapping!\n";

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
	std::cout << "- Success Map Viewing!\n";

	std::cout << "\n\n" << lpBuffer << "\n\n";

	char Buffer[1024] = "ya pominyav!!\n\n";
	size_t szBuffer = sizeof(Buffer);
	CopyMemory(lpBuffer, Buffer, szBuffer);

	std::cout << "\n\n" << lpBuffer << "\n\n";

	bResult = UnmapViewOfFile(lpBuffer);
	if (!bResult) {
		std::cout << "Error occured: " << GetLastError() << "\n";
		return 1;
	}
	std::cout << "- Success Unmapping View!\n";

	CloseHandle(hFileMap);

	return 0;
}