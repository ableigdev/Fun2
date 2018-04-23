#pragma once

#include <iostream>

#ifdef UNICODE 
#define listStream std::wostream
#define listInStream std::wistream
#define out std::wcout
#else
#define listStream std::ostream
#define listInStream std::istream
#define out std::cout
#endif
