// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_prim_channel.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    sc_prim_channel::
    sc_prim_channel()
    {
    }
    
    sc_prim_channel::
    sc_prim_channel( const char* name)
    : sc_object(name)
    {
    }
    
    sc_prim_channel::
    ~sc_prim_channel()
    {
      /* TODO */
    }

  }


}

