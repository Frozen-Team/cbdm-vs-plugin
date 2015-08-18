#pragma once

#if defined(WIN32) || defined(_WIN32) 
#define PATH_SEP L"\\" 
#else
// For future use
#define PATH_SEP L"/" 
#endif 
