#include <stdafx.h>

void DebugLog(string str, const source_location& loc)
{
#ifdef _DEBUG
	cout << "[" << loc.function_name() << "] (" << loc.line() << ":" << loc.column() << ")\n" << str << "\n";
#endif
}

void DebugLog(wstring wstr, const source_location& loc)
{
#ifdef _DEBUG
	wcout << "[" << loc.function_name() << "] (" << loc.line() << ":" << loc.column() << ")\n" << wstr << "\n";
#endif
}