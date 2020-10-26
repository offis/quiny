// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_PORT_BASE_INCLUDED
#define QUINY_SC_SC_CORE_SC_PORT_BASE_INCLUDED

#include "quiny_sc/sc_core/sc_object.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    class sc_port_base : public sc_object
    {
      public:
      
        sc_port_base();
        explicit sc_port_base(const char *name);

        virtual
        ~sc_port_base();
    };

  }

}

#endif
