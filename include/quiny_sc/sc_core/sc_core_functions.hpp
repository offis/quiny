// 2006-07-12, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_CORE_FUNCTIONS_INCLUDED
#define QUINY_SC_SC_CORE_SC_CORE_FUNCTIONS_INCLUDED

#include "quiny_sc/sc_core/sc_time.hpp"

namespace quiny_sc
{
  namespace sc_core
  {
    void sc_start();
    void sc_start(const sc_time &);
    void sc_start(double, sc_time_unit);
  }
}

#endif
