#include <windows.h>
#include <iostream>

#include <vector>
#include <fstream>
#include <iterator>
#include <thread>
#include <mutex>

char* fileContent = new char[1024];
std::string content;
std::mutex contenetMtx;

void WatchDirectory(const std::wstring& directoryPath) {

	HANDLE hDir = CreateFile(
		directoryPath.c_str(),
		FILE_LIST_DIRECTORY,
		FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
		NULL,
		OPEN_EXISTING,
		FILE_FLAG_BACKUP_SEMANTICS,
		NULL
	);

	if (hDir == INVALID_HANDLE_VALUE) {
		std::cerr << "CreateFile failed: " << GetLastError() << std::endl;
		return;
	}

	const size_t bufSize = 1024*1024;
	char buffer[bufSize];
	DWORD bytesReturned;

	DWORD notifyFilter = FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_ATTRIBUTES;
	while (true) {
		if (!ReadDirectoryChangesW(
			hDir,
			buffer,
			bufSize,
			TRUE,
			notifyFilter,
			&bytesReturned,
			NULL,
			NULL
		)) {
			std::cerr << "ReadDirectoryChangesW failed: " << GetLastError() << std::endl;
			break;
		}
		std::cout << "Directory changed." << std::endl;
		std::unique_lock<std::mutex> lock(contenetMtx);
		std::ifstream file("1.txt");
		content = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		file.close();
	
	}
	CloseHandle(hDir);
}



int main() {
	std::ifstream file("1.txt");
	content = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	file.close();

	std::wstring directoryPath = L"1.txt";
	std::thread thWatch = std::thread(WatchDirectory, directoryPath);
	thWatch.detach();
	
	while (true) {
		
		std::this_thread::sleep_for(std::chrono::seconds(1));

		std::unique_lock<std::mutex> lock(contenetMtx);
		std::cout << content << "\n";
	}

	return 0;
}
