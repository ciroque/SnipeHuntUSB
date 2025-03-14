#pragma once

#ifdef SNIPEHUNTUSBCORE_EXPORTS
#define SNIPEHUNTUSBCORE_API __declspec(dllexport)
#else
#define SNIPEHUNTUSBCORE_API __declspec(dllimport)
#endif

extern "C" {
    SNIPEHUNTUSBCORE_API void SayHello();
}
    