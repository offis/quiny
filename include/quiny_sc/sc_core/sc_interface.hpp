// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_INTERFACE_INCLUDED
#define QUINY_SC_SC_CORE_SC_INTERFACE_INCLUDED

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    class sc_interface : public virtual ::quiny::collector::HasId
    {
      public:

        virtual
        ~sc_interface();
    };

  }

}

#endif
