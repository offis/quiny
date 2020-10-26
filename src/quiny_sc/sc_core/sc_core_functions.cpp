// 2006-07-12, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_core_functions.hpp"
#include "quiny_sc/sc_core/sc_time.hpp"
#include "quiny/utils/utils.hpp"
#include "quiny/collector/collector.hpp"

namespace quiny_sc
{
  namespace sc_core
  {
    void 
    sc_start()
    {
      NOT_YET_IMPLEMENTED
    }
    
    void 
    sc_start(const sc_time &t)
    {
      ::quiny::collector::start(t.id());
    }
    
    void 
    sc_start(double value, sc_time_unit unit)
    {
      sc_time tmp(value, unit);
      sc_start(tmp);
    }
    
  }
}
