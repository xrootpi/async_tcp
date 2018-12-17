#pragma once
#include <iostream>

#ifdef _DEBUG
#define DEBUG_CONSOLE(message) do { std::cout << message << std::endl; } while( false )
#else
#define DEBUG_CONSOLE(message) do { } while ( false )
#endif
