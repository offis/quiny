// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_object.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    
    sc_object::
    sc_object()
    {
    }
    
    sc_object::
    sc_object(const char *name)
    : m_name(name)
    {
    }

    sc_object::
    ~sc_object()
    {
      /* TODO */
    }

    const char* 
    sc_object::
    basename() const
    {
      return m_name.c_str();
    }
  }


}

