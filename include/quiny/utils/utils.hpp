#ifndef CL_CPP_UTILS_INCLUDED
#define CL_CPP_UTILS_INCLUDED

#include <typeinfo>

#include "quiny/utils/debug.hpp"
#include "quiny/utils/owner_ptr.hpp"
#include "quiny/utils/observer_ptr.hpp"
#include "quiny/utils/owner_ptr_list.hpp"

#include "quiny/utils/visitor.hpp"

// =================================================================================================
// Cloning polymorphic objects
// =================================================================================================

// Define a "virtual copy constructor"
// This macro relies on className's copy ctor  
#define DEFINE_CLONE_METHOD(className) \
  virtual \
  className* \
  clone() const \
  { \
    if (typeid(this) != typeid(const className*)) \
    {\
      EXIT_WITH_ERROR("clone() method was not overridden for class: " #className)\
    }\
    return new className(*this); \
  }

// Returns a pointer to a cloned object or 0 if the given point (ptr) was 0
#define CLONE_OBJECT_P(ptr) ((ptr) == 0 ? 0 : (ptr)->clone())


#endif
