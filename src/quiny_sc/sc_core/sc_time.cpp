// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_core/sc_time.hpp"
#include "quiny/collector/collector.hpp"
#include "quiny/ir/TimeLiteral.hpp"
#include "quiny/utils/utils.hpp"

namespace quiny_sc
{
  namespace
  {
     quiny::ir::TimeLiteral::TimeUnit
     convertUnit(sc_core::sc_time_unit unit)
     {
        return static_cast<quiny::ir::TimeLiteral::TimeUnit>(unit);
     }
  }

  namespace sc_core
  {
    sc_time::
    sc_time()
    {
      NOT_YET_IMPLEMENTED  
    }        
    
    sc_time::
    sc_time(double value, sc_time_unit unit)
    {
      ::quiny::collector::isTimeLiteral(this->id(), value, convertUnit(unit));
    }
    
    sc_time::
    sc_time(const sc_time &)
    {
      NOT_YET_IMPLEMENTED  
    }

  }


}

