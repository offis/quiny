// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_SIGNAL_IN_IF_INCLUDED
#define QUINY_SC_SC_CORE_SC_SIGNAL_IN_IF_INCLUDED

#include "quiny_sc/sc_core/sc_interface.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    template<typename T>
    class sc_signal_in_if : public virtual sc_interface
    {
      public:
      
        virtual
        const T&
        read() const = 0;

    };

    
    // ===============================================================================================
    // IMPLEMENTATION
    // ===============================================================================================     
        
  }

}

#endif
