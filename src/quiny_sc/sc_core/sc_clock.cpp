// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_clock.hpp"

namespace quiny_sc
{

  namespace sc_core
  {
    sc_clock::
    sc_clock()
    {
    }
    
    sc_clock::    
    sc_clock(const char*name)
    : sc_signal<cpp_dt::Bool>(name)
    {
    }


  }


}

