/// @file NoopAtexit.cpp
/// @author Dennis Stumm
/// @date 2025
/// @version 1.0
/// @brief File to remove the standard exit functions from RAM, to save some memory.

// NOLINTBEGIN
// These two are defined by <cstdlib>.
extern "C" int __wrap_atexit(void (*)(void)) { return 0; }
extern "C" int __wrap_at_quick_exit(void (*)(void)) { return 0; }

// This function is part of the Itanium C++ ABI, there is no header which
// provides this.
extern "C" int __wrap___cxa_atexit(void (*)(void*), void*, void*) { return 0; }
// NOLINTEND
