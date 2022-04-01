#include "memory.hpp"

#include <psapi.h>
#include <stdio.h>

#define INRANGE(x, a, b) (x >= a && x <= b)
#define getBits(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xA) : (INRANGE(x, '0', '9') ? x - '0' : 0))
#define getByte(x) (getBits(x[0]) << 4 | getBits(x[1]))

std::vector<Memory::ModuleInfo> Memory::moduleList;

bool Memory::TryGetModule(const char* moduleName, Memory::ModuleInfo* info) {
	if (Memory::moduleList.empty()) {
		HMODULE hMods[1024];
		HANDLE pHandle = GetCurrentProcess();
		DWORD cbNeeded;
		if(EnumProcessModules(pHandle, hMods, sizeof(hMods), &cbNeeded)) {
			for(unsigned i = 0; i < (cbNeeded / sizeof(HMODULE)); ++i) {
				char buffer[MAX_PATH];
				if(!GetModuleFileNameA(hMods[i], buffer, sizeof(buffer))) {
					continue;
				}
				
				auto modinfo = MODULEINFO();
				if(!GetModuleInformation(pHandle, hMods[i], &modinfo, sizeof(modinfo))) {
					continue;
				}

				auto module = ModuleInfo();

				std::string temp = std::string(buffer);
				auto index = temp.find_last_of("\\/");
				temp = temp.substr(index + 1, temp.length() - index);

				std::snprintf(module.name, sizeof(module.name), "%s", temp.c_str());
				module.base = (uintptr_t)modinfo.lpBaseOfDll;
				module.size = (uintptr_t)modinfo.SizeOfImage;
				std::snprintf(module.path, sizeof(module.path), "%s", buffer);

				Memory::moduleList.push_back(module);
			}
		}
	}

	for(Memory::ModuleInfo& item : Memory::moduleList) {
		if(!strcmp(item.name, moduleName)) {
			if(info) {
				*info = item;
			}
			return true;
		}
	}

	return false;
}

std::string Memory::GetModulePath(const char* moduleName) {
	auto info = Memory::ModuleInfo();
	return (Memory::TryGetModule(moduleName, &info)) ? std::string(info.path) : nullptr;
};

void* Memory::GetModuleHandleByName(const char* moduleName) {
	auto info = Memory::ModuleInfo();
	return (Memory::TryGetModule(moduleName, &info)) ? GetModuleHandleA(info.path) : nullptr;
}

void Memory::CloseModuleHandle(void* moduleHandle) {}

std::string Memory::GetProcessName() {
	char temp[MAX_PATH];
	GetModuleFileNameW(NULL, (LPWSTR)temp, sizeof(temp));

	auto proc = std::string(temp);
	auto index = proc.find_last_of("\\/");
	proc = proc.substr(index + 1, proc.length() - index);

	return proc;
}