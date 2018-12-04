#pragma once
#include <Windows.h>
#include <string>
#include <WinInet.h>
#pragma comment(lib, "wininet.lib")

std::string ReplaceAll(std::string Subject, const std::string& Search, const std::string& Replace);
inline std::string DownloadURL(const std::string& URL);
