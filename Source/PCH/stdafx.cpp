#include <stdafx.h>

void DebugLog(string str, const source_location& loc)
{
#ifdef _DEBUG
	cout << "[" << loc.function_name() << "] (" << loc.line() << ":" << loc.column() << ")" << str << "\n";
#endif
}