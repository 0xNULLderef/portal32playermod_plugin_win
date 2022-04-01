#ifndef UTILS_HPP
#define UTILS_HPP

#include "sdk.hpp"

#define MODULE(name) name MODULE_EXTENSION
#define MODULE_EXTENSION ".dll"

// Redeclare macro (not really redeclaring, just declaring something without the autism of actually doing so)
#define REDECL(name) decltype(name) name

// Detour stuff
#define DECL_DETOUR(name, ...) \
	using _##name = int(__thiscall*)(void* thisptr, ##__VA_ARGS__); \
	static _##name name; \
	static int __fastcall name##_Hook(void* thisptr, int edx, ##__VA_ARGS__)
#define DETOUR(name, ...) \
	int __fastcall name##_Hook(void* thisptr, int edx, ##__VA_ARGS__)

#define DECL_DETOUR_T(type, name, ...) \
	using _##name = type(__thiscall*)(void* thisptr, ##__VA_ARGS__); \
	static _##name name; \
	static type __fastcall name##_Hook(void* thisptr, int edx, ##__VA_ARGS__);
#define DETOUR_T(type, name, ...) \
	type __fastcall name##_Hook(void* thisptr, int edx, ##__VA_ARGS__)

// __stdcall detour for VScript
#define DECL_DETOUR_STD(type, name, ...) \
	using _##name = type(__stdcall*)(__VA_ARGS__); \
	static _##name name; \
	static type __stdcall name##_Hook(__VA_ARGS__);
#define DETOUR_STD(type, name, ...) \
    type __stdcall name##_Hook(__VA_ARGS__)

#define SAFE_DELETE(ptr) \
	if(ptr) { \
		delete ptr; \
		ptr = nullptr; \
	}

#endif // UTILS_HPP
