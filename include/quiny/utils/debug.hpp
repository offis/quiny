// 2006-03-22, Thorsten Schubert, OFFIS

#ifndef QUINY_UTILS_DEBUG_INCLUDED
#define QUINY_UTILS_DEBUG_INCLUDED

#include <iostream>
#include <cstdlib>


// =================================================================================================
// Printing error messages, emergency exit
// =================================================================================================

#define PRINT_ERROR(Msg) \
 {\
    std::cerr << "ERROR [" << __FILE__ << ':' << __LINE__ << "] " << Msg << std::endl; \
 }

#define PRINT_WARNING(Msg) \
 {\
    std::cerr << "WARNING [" << __FILE__ << ':' << __LINE__ << "] " << Msg << std::endl; \
 } 
 
#define EXIT_WITH_ERROR(Msg) { PRINT_ERROR(Msg); std::exit(1); }

#define NOT_YET_IMPLEMENTED PRINT_ERROR("Not yet implemented. Sorry.")

#define NOT_YET_FULLY_IMPLMENETED PRINT_WARNING("Not yet fully implemented. Sorry.")

#define THIS_IS_DEAD_CODE EXIT_WITH_ERROR("This should never be called")

// =================================================================================================
// Helpers for debugging with gdb
// =================================================================================================

#ifdef DEBUG

  // As gdb has problems with overloaded ctors, these macros construct helper
  // functions which can be used for setting break points

  #define DEFINE_GDB_CTOR_HELPER(className) \
    static void \
    gdb_##className(CL_CPP::className *that) \
    { \
      int dummy=0; \
    } 

  #define GDB_CTOR_CALL(className) gdb_##className(this);


  #define PRINT_DEBUG(Msg) \
   {\
      std::cerr << "DEBUG [" << __FILE__ << ':' << __LINE__ << "] " << Msg << std::endl; \
   } 

#else

  // No effect in non-debug mode
  
  #define PRINT_DEBUG(Msg)

  #define DEFINE_GDB_CTOR_HELPER(className) 
  #define GDB_CTOR_CALL(className) 

#endif


#endif
