#pragma once

#if defined(_MSC_VER)
    //  Microsoft
    #define EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
    //  GCC
    #define EXPORT __attribute__((visibility("default")))
#else
    #define EXPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif


//extern "C" {
    EXPORT double my_sqr_func(double val);
//}