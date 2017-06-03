#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define MAX_LOADSTRING 100
#define BUFFERSIZE 260
#define NOTESIZE 4096
// Windows Header Files:
#include <windows.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#pragma comment(lib, "ComCtl32.lib")
#include <windowsx.h>
#include <shellapi.h>
#include <commctrl.h>
#include "time.h"
#include <string>
#include <objidl.h>
#include <gdiplus.h>
#include <codecvt>
#include <locale>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <iostream>
using namespace std;