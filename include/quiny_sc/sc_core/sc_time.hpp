// 2006-03-27, Thorsten Schubert, OFFIS

#ifndef QUINY_SC_SC_CORE_SC_TIME_INCLUDED
#define QUINY_SC_SC_CORE_SC_TIME_INCLUDED

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_core
  {

    enum sc_time_unit 
    {
      SC_FS = 0, 
      SC_PS, 
      SC_NS, 
      SC_US, 
      SC_MS, 
      SC_SEC
    };
    
    class sc_time : public ::quiny::collector::HasId
    {
      public:
        sc_time();
        sc_time(double, sc_time_unit);
        sc_time(const sc_time &);
    };

  }

}

#endif
