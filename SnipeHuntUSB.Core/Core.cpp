#include "Core.h"
#include <windows.h>

void SayHello() {
    MessageBox(NULL, L"Hello from SnipeHuntUSB.Core!", L"DLL Test", MB_OK);
}