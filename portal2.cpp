#include <portal2.hpp>

#include <offsets.hpp>

// Portal2::Portal2() {}

Portal2::Portal2() {
	using namespace Offsets;

	// engine.dll
	Dtor = 9;
	InternalSetValue = 12;
	InternalSetFloatValue = 13;
	InternalSetIntValue = 14;
	Create = 27;
	AutoCompletionFunc = 66;

	// libvstdlib.dll
	RegisterConCommand = 9;
	UnregisterConCommand = 10;
	FindCommandBase = 13;
	InstallGlobalChangeCallback = 19;
	RemoveGlobalChangeCallback = 20;
	m_pConCommandList = 48;

	// server.dll
	Think = 31;
	UTIL_PlayerByIndex = 39; // from CServerGameDLL::Think
	m_szNetname = 3877;

	// vscript.dll
	CreateVM = 8;
	Run = 10; // IScriptVM

	// client.dll
	MsgFunc_SayText2 = 26;
	GetHud = 125;
	FindElement = 135;
	ChatPrintf = 22;
}

Portal2* portal2;
