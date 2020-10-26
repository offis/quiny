// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_DT_SC_FIXED_INCLUDED
#define QUINY_SC_SC_DT_SC_FIXED_INCLUDED

#include "quiny_sc/sc_dt/sc_fix.hpp"

namespace quiny_sc
{

  namespace sc_dt
  {

    template<int WL, int IWL, 
             sc_q_mode = SC_DEFAULT_Q_MODE_,
             sc_o_mode = SC_DEFAULT_O_MODE_,
             int N = SC_DEFAULT_N_BITS_ >            
    class sc_fixed : public sc_fix
    {
      public:

    };

  }

}

#endif
