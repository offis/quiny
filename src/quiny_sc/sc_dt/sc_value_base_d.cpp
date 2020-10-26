// 2006-03-27, Thorsten Schubert, OFFIS

#include "quiny_sc/sc_dt/sc_value_base_d.hpp"

#include "quiny/collector/collector.hpp"

namespace quiny_sc
{

  namespace sc_dt
  {
    sc_value_base_d::
    sc_value_base_d() 
//    : m_id(quiny::collector::getNewId())
    {
    }

    sc_value_base_d::
    ~sc_value_base_d()
    {
//      quiny::collector::objectDeleted(m_id);
    }
    
//     bool
//     sc_value_base_d::
//     isSystemCType() const
//     {
//       return true;
//     }
// 
//     quiny::collector::IDType
//     sc_value_base_d::
//     id() const
//     {
//       return m_id;
//     }    
  }
}

