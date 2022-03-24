#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <windows.h>
#include <memoryapi.h>
#include <memory>
#include <string>
#include <vector>

namespace Memory {
	struct ModuleInfo {
		char name[MAX_PATH];
		uintptr_t base;
		uintptr_t size;
		char path[MAX_PATH];
	};

	extern std::vector<ModuleInfo> moduleList;

	bool TryGetModule(const char* moduleName, ModuleInfo* info);
	std::string GetModulePath(const char* moduleName);
	void* GetModuleHandleByName(const char* moduleName);
	void CloseModuleHandle(void* moduleHandle);
	std::string GetProcessName();

	template <typename T = uintptr_t> T Absolute(const char* moduleName, int relative) {
		auto info = Memory::ModuleInfo();
		return (Memory::TryGetModule(moduleName, &info)) ? (T)(info.base + relative) : (T)0;
	}

	template <typename T = void*> T GetSymbolAddress(void* moduleHandle, const char* symbolName) {
		return (T)GetProcAddress((HMODULE)moduleHandle, symbolName);
	}

	template <typename T = void*> inline T VMT(void* ptr, int index) {
		return reinterpret_cast<T>((*((void***)ptr))[index]);
	}

	template <typename T = uintptr_t> inline T Read(uintptr_t source) {
		auto rel = *reinterpret_cast<int*>(source);
		return (T)(source + rel + sizeof(rel));
	}

	template <typename T = uintptr_t> void Read(uintptr_t source, T* destination) {
		auto rel = *reinterpret_cast<int*>(source);
		*destination = (T)(source + rel + sizeof(rel));
	}

	template <typename T = void*> inline T Deref(uintptr_t source) {
		return *reinterpret_cast<T*>(source);
	}

	template <typename T = void*> void Deref(uintptr_t source, T* destination) {
		*destination = *reinterpret_cast<T*>(source);
	}

	template <typename T = void*> inline T DerefDeref(uintptr_t source) {
		return **reinterpret_cast<T**>(source);
	}

	template <typename T = void*> void DerefDeref(uintptr_t source, T* destination) {
		*destination = **reinterpret_cast<T**>(source);
	}

	inline void UnProtect(void* addr, size_t len) {
		uintptr_t startPage = (uintptr_t)addr & 0xFFFFF000;
		uintptr_t endPage = ((uintptr_t)addr + len) & 0xFFFFF000;
		uintptr_t pageLen = endPage - startPage + 0x1000;
		DWORD placeholder;
		VirtualProtect((void*)startPage, pageLen, PAGE_EXECUTE_READWRITE, &placeholder);
	}
};

#endif // MEMORY_HPP
