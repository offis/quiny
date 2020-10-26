// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_port_base.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    sc_port_base::
    sc_port_base()
    {
    }
    
    sc_port_base::
    sc_port_base(const char *name)
    : sc_object(name)
    {
    }
    
    sc_port_base::
    ~sc_port_base()
    {
      /* TODO */
    }

  }


}

