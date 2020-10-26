// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_DT_SC_FXNUM_INCLUDED
#define QUINY_SC_SC_DT_SC_FXNUM_INCLUDED

namespace quiny_sc
{

  namespace sc_dt
  {
    enum sc_o_mode
    {
      SC_SAT,
      SC_SAT_ZERO,
      SC_SAT_SYM,
      SC_WRAP,
      SC_WRAP_SM
    };

    enum sc_q_mode
    {
      SC_RND,
      SC_RND_ZERO,
      SC_RND_MIN_INF,
      SC_RND_CONV,
      SC_TRN,
      SC_TRN_ZERO
    };

    #define SC_DEFAULT_O_MODE_ SC_WRAP
    #define SC_DEFAULT_Q_MODE_ SC_TRN
    #define SC_DEFAULT_N_BITS_ 0

    class sc_fxnum
    {
      public:

    };

  }

}

#endif
