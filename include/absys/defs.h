#ifndef ABSYSDEFS__H
#define ABSYSDEFS__H

// See https://gcc.gnu.org/wiki/Visibility

#if WINDOWS || defined(_WIN32) || defined(__CYGWIN__)
  #define ABSYS_HELPER_DLL_IMPORT __declspec(dllimport)
  #define ABSYS_HELPER_DLL_EXPORT __declspec(dllexport)
  #define ABSYS_HELPER_DLL_INTERNAL
#else
  #define ABSYS_HELPER_DLL_IMPORT __attribute__ ((visibility ("default")))
  #define ABSYS_HELPER_DLL_EXPORT __attribute__ ((visibility ("default")))
  #define ABSYS_HELPER_DLL_INTERNAL __attribute__ ((visibility ("hidden")))
#endif

#ifdef ABSYS_DLL
  #ifdef ABSYS_DLL_EXPORTS
    #define ABSYS_API ABSYS_HELPER_DLL_EXPORT
  #else
    #define ABSYS_API ABSYS_HELPER_DLL_IMPORT
  #endif
  #define ABSYS_INTERNAL ABSYS_HELPER_DLL_INTERNAL
#else
  #define ABSYS_API
  #define ABSYS_INTERNAL
#endif

#define absys_typecheck(type,x) \
({  type __dummy; \
    typeof(x) __dummy2; \
    (void)(&__dummy == &__dummy2); \
    1; \
})

#endif
