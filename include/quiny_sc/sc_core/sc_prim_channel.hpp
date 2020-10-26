// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_PRIM_CHANNEL_INCLUDED
#define QUINY_SC_SC_CORE_SC_PRIM_CHANNEL_INCLUDED

#include "quiny_sc/sc_core/sc_object.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    class sc_prim_channel : public sc_object
    {
      public:

        sc_prim_channel(); 
        explicit sc_prim_channel( const char* ); 
          
        virtual
        ~sc_prim_channel();
    };

  }

}

#endif
