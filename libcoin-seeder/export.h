#pragma once

#if defined(LIBCOIN_SEEDER_STATIC)         // Using static.
#  define LIBCOIN_SEEDER_SYMEXPORT
#elif defined(LIBCOIN_SEEDER_STATIC_BUILD) // Building static.
#  define LIBCOIN_SEEDER_SYMEXPORT
#elif defined(LIBCOIN_SEEDER_SHARED)       // Using shared.
#  ifdef _WIN32
#    define LIBCOIN_SEEDER_SYMEXPORT __declspec(dllimport)
#  else
#    define LIBCOIN_SEEDER_SYMEXPORT
#  endif
#elif defined(LIBCOIN_SEEDER_SHARED_BUILD) // Building shared.
#  ifdef _WIN32
#    define LIBCOIN_SEEDER_SYMEXPORT __declspec(dllexport)
#  else
#    define LIBCOIN_SEEDER_SYMEXPORT
#  endif
#else
// If none of the above macros are defined, then we assume we are being used
// by some third-party build system that cannot/doesn't signal the library
// type. Note that this fallback works for both static and shared but in case
// of shared will be sub-optimal compared to having dllimport.
//
#  define LIBCOIN_SEEDER_SYMEXPORT         // Using static or shared.
#endif
