#include "Utilities.h"

std::string ReplaceAll(std::string Subject, const std::string& Search, const std::string& Replace) {
	size_t Position = 0;
	while ((Position = Subject.find(Search, Position)) != std::string::npos) {
		Subject.replace(Position, Search.length(), Replace);
		Position += Replace.length();
	}
	return Subject;
}

inline std::string DownloadURL(const std::string& URL) {
	HINTERNET InternetWeb = InternetOpen("Mozilla/5.0", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
	std::string String;

	if (InternetWeb) {
		HINTERNET File = InternetOpenUrl(InternetWeb, URL.c_str(), NULL, NULL, NULL, NULL);

		if (File) {
			char Buffer[2000];
			DWORD BytesRead;

			do {
				InternetReadFile(File, Buffer, 2000, &BytesRead);
				String.append(Buffer, BytesRead);
				memset(Buffer, 0, 2000);
			} while (BytesRead);

			InternetCloseHandle(InternetWeb);
			InternetCloseHandle(File);
			std::string Contents = ReplaceAll(String, "|n", "\r\n");
			return Contents;
		}
	}

	InternetCloseHandle(InternetWeb);
	std::string Contents = ReplaceAll(String, "|n", "\r\n");
	return Contents;
}