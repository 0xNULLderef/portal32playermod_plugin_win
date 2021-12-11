#pragma once

#include <sdk.hpp>

// Platform specific - declare the __cdecl macro (different for windows) and the macro to complete the shared object names
#define __cdecl __attribute__((__cdecl__))

#define MODULE(name) name MODULE_EXTENSION
#define MODULE_EXTENSION ".dll"

// Redeclare macro (not really redeclaring, just declaring something without the autism of actually doing so)
#define REDECL(name) decltype(name) name

// Detour stuff
#define DECL_DETOUR(name, ...) \
	using _##name = int(__rescall*)(void* thisptr, ##__VA_ARGS__); \
	static _##name name; \
	static int __rescall name##_Hook(void* thisptr, ##__VA_ARGS__)
#define DECL_DETOUR_T(type, name, ...) \
	using _##name = type(__cdecl*)(void* thisptr, ##__VA_ARGS__); \
	static _##name name; \
	static type __cdecl name##_Hook(void* thisptr, ##__VA_ARGS__);

#define DETOUR(name, ...) \
	int __rescall name##_Hook(void* thisptr, ##__VA_ARGS__)
#define DETOUR_T(type, name, ...) \
	type __cdecl name##_Hook(void* thisptr, ##__VA_ARGS__)

// __stdcall detour for VScript
#define DECL_DETOUR_STD(type, name, ...) \
	using _##name = type(__stdcall*)(__VA_ARGS__); \
	static _##name name; \
	static type __stdcall name##_Hook(__VA_ARGS__);
#define DETOUR_STD(type, name, ...) \
    type __stdcall name##_Hook(__VA_ARGS__)

#define DECL_DETOUR_THIS(type, name, ...) \
	using _##name = type(__thiscall*)(void* thisptr, ##__VA_ARGS__); \
	static _##name name; \
	static type __thiscall name##_Hook(void* thisptr, ##__VA_ARGS__);
#define DETOUR_THIS(type, name, ...) \
	type __thiscall name##_Hook(void* thisptr, ##__VA_ARGS__)

#define SAFE_DELETE(ptr) \
	if(ptr) { \
		delete ptr; \
		ptr = nullptr; \
	}
