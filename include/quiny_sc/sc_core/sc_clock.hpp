// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_CLOCK_INCLUDED
#define QUINY_SC_SC_CORE_SC_CLOCK_INCLUDED

#include "quiny_sc/sc_core/sc_signal.hpp"

#include "quiny_sc/cpp_dt/Bool.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    class sc_clock : public sc_signal<cpp_dt::Bool>
    {
      public:
        sc_clock();
        explicit sc_clock(const char*name);

    };

  }

}

#endif
