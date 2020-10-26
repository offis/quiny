// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_SIGNAL_INOUT_IF_INCLUDED
#define QUINY_SC_SC_CORE_SC_SIGNAL_INOUT_IF_INCLUDED

#include "quiny_sc/sc_core/sc_signal_in_if.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    #define sc_signal_out_if sc_signal_inout_if
    
    template<typename T>
    class sc_signal_inout_if : public sc_signal_in_if<T>
    {
      public:
        virtual
        void
        write (const T&) = 0;

    };

    
  }

}

#endif
